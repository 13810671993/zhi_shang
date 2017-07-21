// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: general_struct.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "general_struct.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace general {

namespace {

const ::google::protobuf::Descriptor* T_GNRL_ONLINE_USER_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  T_GNRL_ONLINE_USER_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_general_5fstruct_2eproto() {
  protobuf_AddDesc_general_5fstruct_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "general_struct.proto");
  GOOGLE_CHECK(file != NULL);
  T_GNRL_ONLINE_USER_descriptor_ = file->message_type(0);
  static const int T_GNRL_ONLINE_USER_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(T_GNRL_ONLINE_USER, acusername_),
  };
  T_GNRL_ONLINE_USER_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      T_GNRL_ONLINE_USER_descriptor_,
      T_GNRL_ONLINE_USER::default_instance_,
      T_GNRL_ONLINE_USER_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(T_GNRL_ONLINE_USER, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(T_GNRL_ONLINE_USER, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(T_GNRL_ONLINE_USER));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_general_5fstruct_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    T_GNRL_ONLINE_USER_descriptor_, &T_GNRL_ONLINE_USER::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_general_5fstruct_2eproto() {
  delete T_GNRL_ONLINE_USER::default_instance_;
  delete T_GNRL_ONLINE_USER_reflection_;
}

void protobuf_AddDesc_general_5fstruct_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024general_struct.proto\022\007general\"(\n\022T_GNR"
    "L_ONLINE_USER\022\022\n\nacUserName\030\001 \002(\014B\020B\016gen"
    "eral_struct", 91);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "general_struct.proto", &protobuf_RegisterTypes);
  T_GNRL_ONLINE_USER::default_instance_ = new T_GNRL_ONLINE_USER();
  T_GNRL_ONLINE_USER::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_general_5fstruct_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_general_5fstruct_2eproto {
  StaticDescriptorInitializer_general_5fstruct_2eproto() {
    protobuf_AddDesc_general_5fstruct_2eproto();
  }
} static_descriptor_initializer_general_5fstruct_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int T_GNRL_ONLINE_USER::kAcUserNameFieldNumber;
#endif  // !_MSC_VER

T_GNRL_ONLINE_USER::T_GNRL_ONLINE_USER()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void T_GNRL_ONLINE_USER::InitAsDefaultInstance() {
}

T_GNRL_ONLINE_USER::T_GNRL_ONLINE_USER(const T_GNRL_ONLINE_USER& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void T_GNRL_ONLINE_USER::SharedCtor() {
  _cached_size_ = 0;
  acusername_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

T_GNRL_ONLINE_USER::~T_GNRL_ONLINE_USER() {
  SharedDtor();
}

void T_GNRL_ONLINE_USER::SharedDtor() {
  if (acusername_ != &::google::protobuf::internal::kEmptyString) {
    delete acusername_;
  }
  if (this != default_instance_) {
  }
}

void T_GNRL_ONLINE_USER::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* T_GNRL_ONLINE_USER::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return T_GNRL_ONLINE_USER_descriptor_;
}

const T_GNRL_ONLINE_USER& T_GNRL_ONLINE_USER::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_general_5fstruct_2eproto();
  return *default_instance_;
}

T_GNRL_ONLINE_USER* T_GNRL_ONLINE_USER::default_instance_ = NULL;

T_GNRL_ONLINE_USER* T_GNRL_ONLINE_USER::New() const {
  return new T_GNRL_ONLINE_USER;
}

void T_GNRL_ONLINE_USER::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_acusername()) {
      if (acusername_ != &::google::protobuf::internal::kEmptyString) {
        acusername_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool T_GNRL_ONLINE_USER::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required bytes acUserName = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_acusername()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void T_GNRL_ONLINE_USER::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required bytes acUserName = 1;
  if (has_acusername()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      1, this->acusername(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* T_GNRL_ONLINE_USER::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required bytes acUserName = 1;
  if (has_acusername()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        1, this->acusername(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int T_GNRL_ONLINE_USER::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required bytes acUserName = 1;
    if (has_acusername()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->acusername());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void T_GNRL_ONLINE_USER::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const T_GNRL_ONLINE_USER* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const T_GNRL_ONLINE_USER*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void T_GNRL_ONLINE_USER::MergeFrom(const T_GNRL_ONLINE_USER& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_acusername()) {
      set_acusername(from.acusername());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void T_GNRL_ONLINE_USER::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void T_GNRL_ONLINE_USER::CopyFrom(const T_GNRL_ONLINE_USER& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool T_GNRL_ONLINE_USER::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void T_GNRL_ONLINE_USER::Swap(T_GNRL_ONLINE_USER* other) {
  if (other != this) {
    std::swap(acusername_, other->acusername_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata T_GNRL_ONLINE_USER::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = T_GNRL_ONLINE_USER_descriptor_;
  metadata.reflection = T_GNRL_ONLINE_USER_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace general

// @@protoc_insertion_point(global_scope)
