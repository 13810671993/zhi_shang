import os

class commonTool(object):
	"""The common tool class."""
	def fileName(self, filename):
		"""Get the file name from the file path."""
		dirName, name = os.path.split(filename)
		name, ext = os.path.splitext(name)
		return name;
	def moduleName(self, filename):
		"""Get the module name from the file path."""
		return self.fileName(filename).split("_")[0]

class structParser(object):
	def __init__(self, filepath):
		self.filepath = filepath
		self.structs = {}

	def parse(self):
		lines = open(self.filepath).readlines()
		find_def = False
		structs = []
		struct = []
		for line in lines:
			if not line:
				break
			if "typedef struct" in line and not "//" in line and not find_def:
				find_def = True
				struct = []
			elif "}" in line and find_def:
				find_def = False
				line = self.trimmed(line)
				if len(line) != 0:
					struct.append(line)
				structs.append(struct)
			elif find_def:
				line = self.trimmed(line)
				if len(line) != 0:
					struct.append(line)
		print "parsing %s is done." % self.filepath
		return structs

	def trimmed(self, line):
		return line.split("//")[0].replace("\t", " ").strip()

	def convert(self):
		structs = self.parse()
		for struct in structs:
			lines = []
			for line in struct:
				if not line:
					break
				if "{" in line:
					continue
				elif "}" in line and ";" in line:
					name = self.name(line)
					self.structs[name] = lines
				else:
					lines.append(line)
		print "converting %s is done." % self.filepath
		return self.structs

	def name(self, line):
		start = line.find("}")
		end = line.find(";")
		structName = line[start + 1 : end]
		if "," in structName:
			structName = structName.split(",")[0].strip()
		return structName;

class protoWriter(object):
	def __init__(self, filepath, dependpath):
		self.filepath = filepath
		self.parser = structParser(filepath)
		self.dependpath = dependpath
		self.dependents = {}
		self.tool = commonTool()
	
	def dependent(self, dependpath):
		lines = open(dependpath).readlines()
		package = ""
		structs = []
		for line in lines:
			if not line:
				break
			if "package" in line:
				package = line.replace("package", "").replace(";", "").strip()
			elif "message" in line:
				structs.append(line.replace("message", "").strip())
			else:
				continue;
		if package != "":
			self.dependents[package] = structs
		print "package %s is completed." % package
	
	def allDependents(self):
		num = len(self.dependpath)
		if num == 0:
			print "%s depends nothing." % self.protoPath()
			return self.dependents
		for dependpath in self.dependpath:
			dependpath = dependpath.strip()
			if dependpath == "":
				continue
			self.dependent(dependpath)
		return self.dependents

	def protoPath(self):
		return self.filepath.replace(".h", ".proto")

	def write(self):
		self.allDependents()
		filepath = self.protoPath()
		protofile = open(filepath, "w")
		line = "package %s;\n\n" % self.tool.moduleName(self.filepath)
		protofile.write(line)
		line = "option java_outer_classname = \"%s\";\n\n" % self.tool.fileName(self.filepath)
		protofile.write(line)
		for dependpath in self.dependpath:
			if not dependpath:
				break
			dirName, protoName = os.path.split(dependpath)
			line = "import \"%s\";\n\n" % protoName
			protofile.write(line)
		structs = self.parser.convert()
		for struct, variable in structs.items():
			self.writeStruct(protofile, struct, variable)
		protofile.close()
		print "%s is done." % filepath

	def writeStruct(self, protofile, structName, structVar):
		line = "message %s\n{\n" % structName
		protofile.write(line)
		num = 1
		for variable in structVar:
			protofile.write(self.analyseVariable(variable, num))
			num += 1
		protofile.write("}\n")

	def splitVariable(self, variable):
		variable = variable.replace(";", "").strip()
		member = variable.split(" ")
		for line in member[::-1]:
			if line == "":
				member.remove(line)
		return member

	def analyseVariable(self, variable, num):
		member = self.splitVariable(variable)
		varType = member[0]
		varName = member[1]
		if ("UINT32" in varType or "u32" in varType or "UINT16" in varType or "u16" in varType or "DWORD" in varType or "WORD" in varType or "BOOL" in varType) and "T_" not in varType:
			if "[" in varName:
				return "\trepeated fixed32 %s = %d;\n" % (self.arrayName(varName), num)
			else:
				return "\trequired fixed32 %s = %d;\n" % (varName, num)
		elif "INT32" in varType:
			if "[" in varName:
				return "\trepeated int32 %s = %d;\n" % (self.arrayName(varName), num)
			else:
				return "\trequired int32 %s = %d;\n" % (varName, num)
		elif "UINT64" in varType or "u64" in varType or "HWND" in varType:
			if "[" in varName:
				return "\trepeated fixed64 %s = %d;\n" % (self.arrayName(varName), num)
			else:
				return "\trequired fixed64 %s = %d;\n" % (varName, num)
		elif "CHAR" in varType and "T_" not in varType:
			return "\trequired bytes %s = %d;\n" % (self.arrayName(varName), num)
		elif "BYTE" in varType or "UINT8" in varType or "u8" in varType:
			if "[" in varName:
				return "\trequired bytes %s = %d;\n" % (self.arrayName(varName), num)
			else:
				return "\trequired fixed32 %s = %d;\n" % (varName, num)
		elif "DOUBLE" in varType:
			if "[" in varName:
				return "\trepeated double %s = %d;\n" % (self.arrayName(varName), num)
			else:
				return "\trequired double %s = %d;\n" % (varName, num)
		elif "T_" in varType:
			protoName = self.dependProto(varType)
			if protoName == "":
				if "[" in varName:
					return "\trepeated %s %s = %d;\n" % (varType, self.arrayName(varName), num)
				else:
					return "\trequired %s %s = %d;\n" % (varType, varName, num)
			else:
				if "[" in varName:
					return "\trepeated %s.%s %s = %d;\n" % (protoName, varType, self.arrayName(varName), num)
				else:
					return "\trequired %s.%s %s = %d;\n" % (protoName, varType, varName, num)
		else:
			print "The variable type %s is invalid." % varType
			return "\n"

	def arrayName(self, array):
		index = array.find("[")
		return array[0:index]

	def dependProto(self, structName):
		for protoName, structNames in self.dependents.items():
			for name in structNames:
				if name == structName:
					return protoName
		return ""
		
class swapWriter(object):
	def __init__(self, filepath, headfiles):
		self.filepath = filepath
		self.headfiles = headfiles
		parser = structParser(filepath)
		self.structs = parser.convert()
		self.tool = commonTool()
	
	def hFilePath(self):
		moduleName = self.tool.moduleName(self.filepath)
		dirName, fileName = os.path.split(self.filepath)
		return self.filepath.replace(fileName, "%s_proto_swap.h" % moduleName)

	def cppFilePath(self):
		moduleName = self.tool.moduleName(self.filepath)
		dirName, fileName = os.path.split(self.filepath)
		return self.filepath.replace(fileName, "%s_proto_swap.cpp" % moduleName)

	def writeHFile(self):
		print "Write %s swap head file." % self.filepath	
		filePath = self.hFilePath()
		modulename = self.tool.moduleName(self.filepath)
		swapFile = open(filePath, "w")
		swapFile.write("#ifndef __%s_PROTO_SWAP_H__\n" % modulename.upper())
		swapFile.write("#define __%s_PROTO_SWAP_H__\n" % modulename.upper())
		for structName, structVar in self.structs.items():
			swapFile.write("UINT32 StructToProto(const %s& tStruct, %s::%s& proto);\n" % (structName, modulename, structName))
			swapFile.write("UINT32 ProtoToStruct(const %s::%s& proto, %s& tStruct);\n\n" % (modulename, structName, structName))
		swapFile.write("#endif")
		swapFile.close()
		print "%s is done." % filePath
	
	def writeCppFile(self):
		print "Write %s swap cpp file." % self.filepath
		filePath = self.cppFilePath()
		modulename = self.tool.moduleName(self.filepath)
		swapFile = open(filePath, "w")
		for headfile in self.headfiles:
			headfile = headfile.strip()
			if headfile == "":
				continue
			swapFile.write("#include \"%s\"\n" % headfile)
		swapFile.write("#include \"%s_proto_swap.h\"\n\n" % modulename) 
		for structName, structVar in self.structs.items():
			self.writeStructToProto(swapFile, modulename, structName, structVar)
			self.writeProtoToStruct(swapFile, modulename, structName, structVar)
		print "%s is done." % filePath

	def writeStructToProto(self, swapFile, modulename, structName, structVar):
		swapFile.write("UINT32 StructToProto(const %s& tStruct, %s::%s& proto)\n{\n" % (structName, modulename, structName))
		for variable in structVar:
			varType, varName, arrayNum = self.splitVariable(variable)
			if varType == "" or varName == "":
				print "The struct %s is incorrect with the variable %s." % (structName, variable)
			if "*" in varType:
				print "%s of %s is a pointer." % (varName, structName)
			elif ("UINT32" in varType or "u32" in varType or "DWORD" in varType or "UINT64" in varType \
							or "u64" in varType or "UINT16" in varType or "u16" in varType or "WORD" in varType \
							or "BOOL" in varType or "INT32" in varType) and "T_" not in varType:
				if arrayNum == "":
					swapFile.write("\tproto.set_%s(tStruct.%s);\n" % (varName.lower(), varName))
				else:
					swapFile.write("\tfor(INT32 i = 0; i < %s; ++i)\n\t{\n" % arrayNum)
					swapFile.write("\t\tproto.add_%s(tStruct.%s[i]);\n\t}\n" % (varName.lower(), varName))
			elif "CHAR" in varType and "T_" not in varType:
				if arrayNum == "":
					print "The type of %s isn't char array in struct %s." % (varName, structName)
				else:
					swapFile.write("\tproto.set_%s(tStruct.%s, %s);\n" % (varName.lower(), varName, arrayNum))
			elif "UINT8" in varType or "u8" in varType or "BYTE" in varType:
				if arrayNum == "":
					swapFile.write("\tproto.set_%s(tStruct.%s);\n" % (varName.lower(), varName))
				else:
					swapFile.write("\tproto.set_%s(tStruct.%s, %s);\n" % (varName.lower(), varName, arrayNum))
			elif "HWND" in varType:
				swapFile.write("\tproto.set_%s((UINT64)tStruct.%s);\n" % (varName.lower(), varName))
			elif "DOUBLE" in varType:
				if arrayNum == "":
					swapFile.write("\tproto.set_%s(tStruct.%s);\n" % (varName.lower(), varName))
				else:
					swapFile.write("\tfor(INT32 i = 0; i < %s; ++i)\n\t{\n" % arrayName)
					swapFile.write("\t\tproto.add_%s(tStruct.%s[i]);\n\t}\n" % (varName.lower(), varName))
			elif "T_" in varType:
				if arrayNum == "":
					swapFile.write("\tStructToProto(tStruct.%s, *(proto.mutable_%s()));\n" % (varName, varName.lower()))
				else:
					swapFile.write("\tfor(INT32 i = 0; i < %s; ++i)\n\t{\n" % arrayNum)
					swapFile.write("\t\tStructToProto(tStruct.%s[i], *(proto.add_%s()));\n\t}\n" % (varName, varName.lower()))
			else:
				print "%s is invalid type." % varType
		swapFile.write("\treturn TRUE;\n}\n\n")

	def writeProtoToStruct(self, swapFile, modulename, structName, structVar):
		swapFile.write("UINT32 ProtoToStruct(const %s::%s& proto, %s& tStruct)\n{\n" % (modulename, structName, structName))
		for variable in structVar:
			varType, varName, arrayNum = self.splitVariable(variable)
			if varType == "" or varName == "":
				print "The struct %s is incorrect with the variable %s." % (structName, variable)
				continue
			if "*" in varType:
				print "%s of %s is a pointer." % (varName, structName)
			elif ("UINT32" in varType or "u32" in varType or "DWORD" in varType or "BOOL" in varType or "UINT64" in varType or "u64" in varType or "INT32" in varType) and "T_" not in varType:
				if arrayNum == "":
					swapFile.write("\ttStruct.%s = proto.%s();\n" % (varName, varName.lower()))
				else:
					swapFile.write("\tfor(INT32 i = 0; i < proto.%s().size() && i < %s; ++i)\n\t{\n" % (varName.lower(), arrayNum))
					swapFile.write("\t\ttStruct.%s[i] = proto.%s(i);\n\t}\n" % (varName, varName.lower()))
			elif ("UINT16" in varType or "u16" in varType or "WORD" in varType) and "T_" not in varType:
				if arrayNum == "":
					swapFile.write("\ttStruct.%s = (UINT16)proto.%s();\n" % (varName, varName.lower()))
				else:
					swapFile.write("\tfor(INT32 i = 0; i < proto.%s().size() && i < %s; ++i)\n\t{\n" % (varName.lower(), arrayNum))
					swapFile.write("\t\ttStruct.%s[i] = (UINT16)proto.%s(i);\n\t}\n" % (varName, varName.lower()))
			elif "CHAR" in varType and "T_" not in varType:
				if arrayNum == "":
					print "The type of %s isn't char array in struct %s." % (varName, structName)
				else:
					swapFile.write("\tmemcpy(tStruct.%s, proto.%s().c_str(), %s);\n" % (varName, varName.lower(), arrayNum))
			elif "UINT8" in varType or "u8" in varType or "BYTE" in varType:
				if arrayNum == "":
					swapFile.write("\ttStruct.%s = (UINT8)proto.%s();\n" % (varName, varName.lower()))
				else:
					swapFile.write("\tmemcpy(tStruct.%s, proto.%s().c_str(), %s);\n" % (varName, varName.lower(), arrayNum))
			elif "HWND" in varType:
				swapFile.write("\ttStruct.%s = (HWND)proto.%s();\n" % (varName, varName.lower()))
			elif "DOUBLE" in varType:
				if arrayNum == "":
					swapFile.write("\ttStruct.%s = proto.%s();\n" % (varName, varName.lower()))
				else:
					swapFile.write("\tfor(INT32 i = 0; i < proto.%s().size() && i < %s; ++i\n\t{\n" % (varName.lower(), arrayNum))
					swapFile.write("\t\ttStruct.%s[i] = proto.%s(i);\n\t}\n" % (varName, varName.lower()))
			elif "T_" in varType:
				if arrayNum == "":
					swapFile.write("\tProtoToStruct(proto.%s(), tStruct.%s);\n" % (varName.lower(),varName))
				else:
					swapFile.write("\tfor(INT32 i = 0; i < proto.%s().size() && i < %s; ++i)\n\t{\n" % (varName.lower(), arrayNum))
					swapFile.write("\t\tProtoToStruct(proto.%s(i), tStruct.%s[i]);\n\t}\n" % (varName.lower(), varName))
			else:
				print "%s is invalid type." % varType
		swapFile.write("\treturn TRUE;\n}\n\n")

	def splitVariable(self, variable):
		member = variable.replace(";", "").strip().split(" ")
		space = member.count("")
		for i in range(0, space):
			member.remove("")
		varType = member[0]
		arrayNum = ""
		varName = ""
		if "[" not in member[1]:
			varName = member[1]
			return varType, varName, arrayNum
		else:
			start = member[1].find("[")
			end = member[1].find("]")
			varName = member[1][0 : start]
			arrayNum = member[1][start+1 : end]
			return varType, varName, arrayNum

from sys import argv
args = argv
args.pop(0)
arg_map = {}

proto_depend = "-proto_depend"
proto_path = "-proto_path"
proto_out = "-proto_out"

swap_header = "-swap_header"
h_file_out = "-h_file_out"
cpp_file_out = "-cpp_file_out"

struct_file = "-struct_file"

for arg in args:
	if proto_depend in arg or proto_path in arg or proto_out in arg or swap_header in arg or h_file_out in arg or cpp_file_out in arg or struct_file in arg:
		tmpArgs = arg.split("=")
		if len(tmpArgs) != 2:
			print "%s is invalid." % arg
			exit(0)
		arg_map[tmpArgs[0].strip()] = tmpArgs[1].strip()
	else:
		print "%s is unknown." % arg
		exit(0)

structFile = arg_map.get(struct_file, "")
if structFile == "" or not ".h" in structFile:
	print "The struct file is invalid."
	exit(0)
dirName, fileName = os.path.split(structFile)
os.system("copy %s %s" % (structFile, fileName))
arg_map[struct_file] = structFile = fileName

tmp = arg_map.get(proto_depend, "")
if tmp == "":
	arg_map[proto_depend] = []
else:
	dependents = tmp.split(",")
	arg_map[proto_depend] = dependents

arg_map[proto_path] = arg_map.get(proto_path, ".")
arg_map[proto_out] = arg_map.get(proto_out, ".")

tmp = arg_map.get(swap_header, "")
if tmp == "":
	arg_map[swap_header] = []
else:
	arg_map[swap_header] = tmp.split(",")

arg_map[h_file_out] = arg_map.get(h_file_out, ".")
arg_map[cpp_file_out] = arg_map.get(cpp_file_out, ".")

proto = protoWriter(arg_map[struct_file], arg_map[proto_depend])
proto.write()
os.system("call protoc.exe -I=. --cpp_out=. --proto_path=%s %s" % (arg_map[proto_path], proto.protoPath()))

dirName, protoName = os.path.split(proto.protoPath())
protoTarget = os.path.join(arg_map[proto_out], protoName)
os.system("move %s %s" % (proto.protoPath(), protoTarget))

protoHFile = protoName.replace(".proto", ".pb.h")
protoHTarget = os.path.join(arg_map[h_file_out], protoHFile)
protoHFile = os.path.join(dirName, protoHFile)
os.system("move %s %s" % (protoHFile, protoHTarget))
protoCppFile = protoName.replace(".proto", ".pb.cc")
protoCppTarget = os.path.join(arg_map[cpp_file_out], protoCppFile)
protoCppFile = os.path.join(dirName, protoCppFile)
os.system("move %s %s" % (protoCppFile, protoCppTarget))

swap = swapWriter(arg_map[struct_file], arg_map[swap_header])
swap.writeHFile()
dirName, hFile = os.path.split(swap.hFilePath())
hFileTarget = os.path.join(arg_map[h_file_out], hFile)
os.system("move %s %s" % (swap.hFilePath(), hFileTarget))
swap.writeCppFile()
dirName, cppFile = os.path.split(swap.cppFilePath())
cppFileTarget = os.path.join(arg_map[cpp_file_out], cppFile)
os.system("move %s %s" % (swap.cppFilePath(), cppFileTarget))

os.system("erase %s" % structFile)
