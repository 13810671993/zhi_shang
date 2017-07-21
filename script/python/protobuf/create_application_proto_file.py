import os
struct_file = "-struct_file=..\\..\\..\\code\\include\\application\\app_protocol\\application_struct.h"
proto_depend = "-proto_depend=..\\..\\..\\code\\include\\application\\app_protocol\\general_struct.proto"
proto_path = "-proto_path=..\\..\\..\\code\\include\\application\\app_protocol\\"
proto_out = "-proto_out=..\\..\\..\\code\\include\\application\\app_protocol\\"

swap_header = "-swap_header=common/data_type.h,common/common_define.h,application/app_protocol/general_struct.h,general_struct.pb.h,general_proto_swap.h,application/app_protocol/application_struct.h,application_struct.pb.h"
h_file_out = "-h_file_out=..\\..\\..\\code\\application\\app_protocol\\include"
cpp_file_out = "-cpp_file_out=..\\..\\..\\code\\application\\app_protocol\\source"

os.system("create_proto_file.py %s %s %s %s %s %s %s" % (struct_file, proto_depend, proto_path, proto_out, swap_header, h_file_out, cpp_file_out))
