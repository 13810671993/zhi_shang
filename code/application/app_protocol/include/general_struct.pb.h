// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: general_struct.proto

#ifndef PROTOBUF_general_5fstruct_2eproto__INCLUDED
#define PROTOBUF_general_5fstruct_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace general {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_general_5fstruct_2eproto();
void protobuf_AssignDesc_general_5fstruct_2eproto();
void protobuf_ShutdownFile_general_5fstruct_2eproto();

class T_GNRL_ONLINE_USER;

// ===================================================================

class T_GNRL_ONLINE_USER : public ::google::protobuf::Message {
 public:
  T_GNRL_ONLINE_USER();
  virtual ~T_GNRL_ONLINE_USER();

  T_GNRL_ONLINE_USER(const T_GNRL_ONLINE_USER& from);

  inline T_GNRL_ONLINE_USER& operator=(const T_GNRL_ONLINE_USER& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const T_GNRL_ONLINE_USER& default_instance();

  void Swap(T_GNRL_ONLINE_USER* other);

  // implements Message ----------------------------------------------

  T_GNRL_ONLINE_USER* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const T_GNRL_ONLINE_USER& from);
  void MergeFrom(const T_GNRL_ONLINE_USER& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required bytes acUserName = 1;
  inline bool has_acusername() const;
  inline void clear_acusername();
  static const int kAcUserNameFieldNumber = 1;
  inline const ::std::string& acusername() const;
  inline void set_acusername(const ::std::string& value);
  inline void set_acusername(const char* value);
  inline void set_acusername(const void* value, size_t size);
  inline ::std::string* mutable_acusername();
  inline ::std::string* release_acusername();
  inline void set_allocated_acusername(::std::string* acusername);

  // @@protoc_insertion_point(class_scope:general.T_GNRL_ONLINE_USER)
 private:
  inline void set_has_acusername();
  inline void clear_has_acusername();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* acusername_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_general_5fstruct_2eproto();
  friend void protobuf_AssignDesc_general_5fstruct_2eproto();
  friend void protobuf_ShutdownFile_general_5fstruct_2eproto();

  void InitAsDefaultInstance();
  static T_GNRL_ONLINE_USER* default_instance_;
};
// ===================================================================


// ===================================================================

// T_GNRL_ONLINE_USER

// required bytes acUserName = 1;
inline bool T_GNRL_ONLINE_USER::has_acusername() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void T_GNRL_ONLINE_USER::set_has_acusername() {
  _has_bits_[0] |= 0x00000001u;
}
inline void T_GNRL_ONLINE_USER::clear_has_acusername() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void T_GNRL_ONLINE_USER::clear_acusername() {
  if (acusername_ != &::google::protobuf::internal::kEmptyString) {
    acusername_->clear();
  }
  clear_has_acusername();
}
inline const ::std::string& T_GNRL_ONLINE_USER::acusername() const {
  return *acusername_;
}
inline void T_GNRL_ONLINE_USER::set_acusername(const ::std::string& value) {
  set_has_acusername();
  if (acusername_ == &::google::protobuf::internal::kEmptyString) {
    acusername_ = new ::std::string;
  }
  acusername_->assign(value);
}
inline void T_GNRL_ONLINE_USER::set_acusername(const char* value) {
  set_has_acusername();
  if (acusername_ == &::google::protobuf::internal::kEmptyString) {
    acusername_ = new ::std::string;
  }
  acusername_->assign(value);
}
inline void T_GNRL_ONLINE_USER::set_acusername(const void* value, size_t size) {
  set_has_acusername();
  if (acusername_ == &::google::protobuf::internal::kEmptyString) {
    acusername_ = new ::std::string;
  }
  acusername_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* T_GNRL_ONLINE_USER::mutable_acusername() {
  set_has_acusername();
  if (acusername_ == &::google::protobuf::internal::kEmptyString) {
    acusername_ = new ::std::string;
  }
  return acusername_;
}
inline ::std::string* T_GNRL_ONLINE_USER::release_acusername() {
  clear_has_acusername();
  if (acusername_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = acusername_;
    acusername_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void T_GNRL_ONLINE_USER::set_allocated_acusername(::std::string* acusername) {
  if (acusername_ != &::google::protobuf::internal::kEmptyString) {
    delete acusername_;
  }
  if (acusername) {
    set_has_acusername();
    acusername_ = acusername;
  } else {
    clear_has_acusername();
    acusername_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace general

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_general_5fstruct_2eproto__INCLUDED
