// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: application_struct.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "application_struct.pb.h"

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

namespace application {

namespace {

const ::google::protobuf::Descriptor* T_APP_FIRST_TEST_RSP_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  T_APP_FIRST_TEST_RSP_reflection_ = NULL;
const ::google::protobuf::Descriptor* T_APP_FIRST_TEST_REQ_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  T_APP_FIRST_TEST_REQ_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_application_5fstruct_2eproto() {
  protobuf_AddDesc_application_5fstruct_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "application_struct.proto");
  GOOGLE_CHECK(file != NULL);
  T_APP_FIRST_TEST_RSP_descriptor_ = file->message_type(0);
  static const int T_APP_FIRST_TEST_RSP_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(T_APP_FIRST_TEST_RSP, u32result_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(T_APP_FIRST_TEST_RSP, u32test_),
  };
  T_APP_FIRST_TEST_RSP_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      T_APP_FIRST_TEST_RSP_descriptor_,
      T_APP_FIRST_TEST_RSP::default_instance_,
      T_APP_FIRST_TEST_RSP_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(T_APP_FIRST_TEST_RSP, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(T_APP_FIRST_TEST_RSP, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(T_APP_FIRST_TEST_RSP));
  T_APP_FIRST_TEST_REQ_descriptor_ = file->message_type(1);
  static const int T_APP_FIRST_TEST_REQ_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(T_APP_FIRST_TEST_REQ, u32result_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(T_APP_FIRST_TEST_REQ, u32test_),
  };
  T_APP_FIRST_TEST_REQ_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      T_APP_FIRST_TEST_REQ_descriptor_,
      T_APP_FIRST_TEST_REQ::default_instance_,
      T_APP_FIRST_TEST_REQ_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(T_APP_FIRST_TEST_REQ, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(T_APP_FIRST_TEST_REQ, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(T_APP_FIRST_TEST_REQ));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_application_5fstruct_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    T_APP_FIRST_TEST_RSP_descriptor_, &T_APP_FIRST_TEST_RSP::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    T_APP_FIRST_TEST_REQ_descriptor_, &T_APP_FIRST_TEST_REQ::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_application_5fstruct_2eproto() {
  delete T_APP_FIRST_TEST_RSP::default_instance_;
  delete T_APP_FIRST_TEST_RSP_reflection_;
  delete T_APP_FIRST_TEST_REQ::default_instance_;
  delete T_APP_FIRST_TEST_REQ_reflection_;
}

void protobuf_AddDesc_application_5fstruct_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\030application_struct.proto\022\013application\""
    ":\n\024T_APP_FIRST_TEST_RSP\022\021\n\tu32Result\030\001 \002"
    "(\007\022\017\n\007u32Test\030\002 \002(\007\":\n\024T_APP_FIRST_TEST_"
    "REQ\022\021\n\tu32Result\030\001 \002(\007\022\017\n\007u32Test\030\002 \002(\007B"
    "\024B\022application_struct", 181);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "application_struct.proto", &protobuf_RegisterTypes);
  T_APP_FIRST_TEST_RSP::default_instance_ = new T_APP_FIRST_TEST_RSP();
  T_APP_FIRST_TEST_REQ::default_instance_ = new T_APP_FIRST_TEST_REQ();
  T_APP_FIRST_TEST_RSP::default_instance_->InitAsDefaultInstance();
  T_APP_FIRST_TEST_REQ::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_application_5fstruct_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_application_5fstruct_2eproto {
  StaticDescriptorInitializer_application_5fstruct_2eproto() {
    protobuf_AddDesc_application_5fstruct_2eproto();
  }
} static_descriptor_initializer_application_5fstruct_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int T_APP_FIRST_TEST_RSP::kU32ResultFieldNumber;
const int T_APP_FIRST_TEST_RSP::kU32TestFieldNumber;
#endif  // !_MSC_VER

T_APP_FIRST_TEST_RSP::T_APP_FIRST_TEST_RSP()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void T_APP_FIRST_TEST_RSP::InitAsDefaultInstance() {
}

T_APP_FIRST_TEST_RSP::T_APP_FIRST_TEST_RSP(const T_APP_FIRST_TEST_RSP& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void T_APP_FIRST_TEST_RSP::SharedCtor() {
  _cached_size_ = 0;
  u32result_ = 0u;
  u32test_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

T_APP_FIRST_TEST_RSP::~T_APP_FIRST_TEST_RSP() {
  SharedDtor();
}

void T_APP_FIRST_TEST_RSP::SharedDtor() {
  if (this != default_instance_) {
  }
}

void T_APP_FIRST_TEST_RSP::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* T_APP_FIRST_TEST_RSP::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return T_APP_FIRST_TEST_RSP_descriptor_;
}

const T_APP_FIRST_TEST_RSP& T_APP_FIRST_TEST_RSP::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_application_5fstruct_2eproto();
  return *default_instance_;
}

T_APP_FIRST_TEST_RSP* T_APP_FIRST_TEST_RSP::default_instance_ = NULL;

T_APP_FIRST_TEST_RSP* T_APP_FIRST_TEST_RSP::New() const {
  return new T_APP_FIRST_TEST_RSP;
}

void T_APP_FIRST_TEST_RSP::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    u32result_ = 0u;
    u32test_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool T_APP_FIRST_TEST_RSP::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required fixed32 u32Result = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_FIXED32>(
                 input, &u32result_)));
          set_has_u32result();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(21)) goto parse_u32Test;
        break;
      }

      // required fixed32 u32Test = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_u32Test:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_FIXED32>(
                 input, &u32test_)));
          set_has_u32test();
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

void T_APP_FIRST_TEST_RSP::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required fixed32 u32Result = 1;
  if (has_u32result()) {
    ::google::protobuf::internal::WireFormatLite::WriteFixed32(1, this->u32result(), output);
  }

  // required fixed32 u32Test = 2;
  if (has_u32test()) {
    ::google::protobuf::internal::WireFormatLite::WriteFixed32(2, this->u32test(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* T_APP_FIRST_TEST_RSP::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required fixed32 u32Result = 1;
  if (has_u32result()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFixed32ToArray(1, this->u32result(), target);
  }

  // required fixed32 u32Test = 2;
  if (has_u32test()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFixed32ToArray(2, this->u32test(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int T_APP_FIRST_TEST_RSP::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required fixed32 u32Result = 1;
    if (has_u32result()) {
      total_size += 1 + 4;
    }

    // required fixed32 u32Test = 2;
    if (has_u32test()) {
      total_size += 1 + 4;
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

void T_APP_FIRST_TEST_RSP::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const T_APP_FIRST_TEST_RSP* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const T_APP_FIRST_TEST_RSP*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void T_APP_FIRST_TEST_RSP::MergeFrom(const T_APP_FIRST_TEST_RSP& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_u32result()) {
      set_u32result(from.u32result());
    }
    if (from.has_u32test()) {
      set_u32test(from.u32test());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void T_APP_FIRST_TEST_RSP::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void T_APP_FIRST_TEST_RSP::CopyFrom(const T_APP_FIRST_TEST_RSP& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool T_APP_FIRST_TEST_RSP::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void T_APP_FIRST_TEST_RSP::Swap(T_APP_FIRST_TEST_RSP* other) {
  if (other != this) {
    std::swap(u32result_, other->u32result_);
    std::swap(u32test_, other->u32test_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata T_APP_FIRST_TEST_RSP::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = T_APP_FIRST_TEST_RSP_descriptor_;
  metadata.reflection = T_APP_FIRST_TEST_RSP_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int T_APP_FIRST_TEST_REQ::kU32ResultFieldNumber;
const int T_APP_FIRST_TEST_REQ::kU32TestFieldNumber;
#endif  // !_MSC_VER

T_APP_FIRST_TEST_REQ::T_APP_FIRST_TEST_REQ()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void T_APP_FIRST_TEST_REQ::InitAsDefaultInstance() {
}

T_APP_FIRST_TEST_REQ::T_APP_FIRST_TEST_REQ(const T_APP_FIRST_TEST_REQ& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void T_APP_FIRST_TEST_REQ::SharedCtor() {
  _cached_size_ = 0;
  u32result_ = 0u;
  u32test_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

T_APP_FIRST_TEST_REQ::~T_APP_FIRST_TEST_REQ() {
  SharedDtor();
}

void T_APP_FIRST_TEST_REQ::SharedDtor() {
  if (this != default_instance_) {
  }
}

void T_APP_FIRST_TEST_REQ::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* T_APP_FIRST_TEST_REQ::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return T_APP_FIRST_TEST_REQ_descriptor_;
}

const T_APP_FIRST_TEST_REQ& T_APP_FIRST_TEST_REQ::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_application_5fstruct_2eproto();
  return *default_instance_;
}

T_APP_FIRST_TEST_REQ* T_APP_FIRST_TEST_REQ::default_instance_ = NULL;

T_APP_FIRST_TEST_REQ* T_APP_FIRST_TEST_REQ::New() const {
  return new T_APP_FIRST_TEST_REQ;
}

void T_APP_FIRST_TEST_REQ::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    u32result_ = 0u;
    u32test_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool T_APP_FIRST_TEST_REQ::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required fixed32 u32Result = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_FIXED32>(
                 input, &u32result_)));
          set_has_u32result();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(21)) goto parse_u32Test;
        break;
      }

      // required fixed32 u32Test = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_u32Test:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_FIXED32>(
                 input, &u32test_)));
          set_has_u32test();
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

void T_APP_FIRST_TEST_REQ::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required fixed32 u32Result = 1;
  if (has_u32result()) {
    ::google::protobuf::internal::WireFormatLite::WriteFixed32(1, this->u32result(), output);
  }

  // required fixed32 u32Test = 2;
  if (has_u32test()) {
    ::google::protobuf::internal::WireFormatLite::WriteFixed32(2, this->u32test(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* T_APP_FIRST_TEST_REQ::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required fixed32 u32Result = 1;
  if (has_u32result()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFixed32ToArray(1, this->u32result(), target);
  }

  // required fixed32 u32Test = 2;
  if (has_u32test()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFixed32ToArray(2, this->u32test(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int T_APP_FIRST_TEST_REQ::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required fixed32 u32Result = 1;
    if (has_u32result()) {
      total_size += 1 + 4;
    }

    // required fixed32 u32Test = 2;
    if (has_u32test()) {
      total_size += 1 + 4;
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

void T_APP_FIRST_TEST_REQ::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const T_APP_FIRST_TEST_REQ* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const T_APP_FIRST_TEST_REQ*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void T_APP_FIRST_TEST_REQ::MergeFrom(const T_APP_FIRST_TEST_REQ& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_u32result()) {
      set_u32result(from.u32result());
    }
    if (from.has_u32test()) {
      set_u32test(from.u32test());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void T_APP_FIRST_TEST_REQ::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void T_APP_FIRST_TEST_REQ::CopyFrom(const T_APP_FIRST_TEST_REQ& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool T_APP_FIRST_TEST_REQ::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void T_APP_FIRST_TEST_REQ::Swap(T_APP_FIRST_TEST_REQ* other) {
  if (other != this) {
    std::swap(u32result_, other->u32result_);
    std::swap(u32test_, other->u32test_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata T_APP_FIRST_TEST_REQ::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = T_APP_FIRST_TEST_REQ_descriptor_;
  metadata.reflection = T_APP_FIRST_TEST_REQ_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace application

// @@protoc_insertion_point(global_scope)