#ifndef AMPL_SCOPEDARRAY_H
#define AMPL_SCOPEDARRAY_H

#include "ampl/ep/declarations.h"
#include "ampl/ep/error_information.h"

#include "ampl/format.h"

namespace ampl {
namespace internal {
  /**
  Represent a string literal with size
  */
  struct PODStringRef {
    const char* ptr_;
    std::size_t size_;
  };

  inline PODStringRef StringRefToPOD(fmt::StringRef ref) {
    PODStringRef r = { ref.data(), ref.size() };
    return r;
  }

  extern "C" {
    AMPLAPI void AMPL_DeleteArrayStrings(const char *const *ptr);
    AMPLAPI const char**  AMPL_CreateArrayStrings(std::size_t size,
      ErrorInformation* errorInfo);
    /*
    Get a copy of the source string, inside the library boundary.
    Note that a terminating \0 is added at position [size]
    of the copy.
    */
    AMPLAPI const char*
    AMPL_CopyString(const char* source, std::size_t size, ErrorInformation* errorInfo);
  AMPLAPI void AMPL_DeleteString(const char* s);

  }  // extern "C"

  template <typename TYPE>
  struct InDLL;
  template <>
  struct InDLL<char const *> {
    static void deletearray(const char *const *ptr) {
      AMPL_DeleteArrayStrings(ptr);
    }
  };
  template <>
  struct InDLL<const char> {
    static void deletearray(const char *ptr) {
		AMPL_DeleteString(ptr);
    }
  };



  template <typename T>
  class ScopedArray {
    template<typename Y>
    struct ScopedArray_ref {
      Y* yp;
      ScopedArray_ref(Y* rhs)
        : yp(rhs) {}
    };
    T *ptr_;
  public:
    /**
    Copy constructors invalidate the passed scoped pointer, transferring
    the ownership to the copy
    */
    ScopedArray(ScopedArray &other) : ptr_(other.release()) {}

    template<class Y>
    ScopedArray(ScopedArray<Y>& other)
      : ptr_(other.release()) {}
    /**
    Assignment (passes ownership to the assigned pointer)
    */
    ScopedArray &operator=(ScopedArray &other) {
      reset(other.release());
      return *this;
    }
    /**
    Assignment (passes ownership to the assigned pointer)
    */
    template<class Y>
    ScopedArray& operator= (ScopedArray<Y>& other) {
      reset(other.release());
      return *this;
    }

    explicit ScopedArray(T *ptr) : ptr_(ptr) {}

    ScopedArray() : ptr_(NULL) {}

    ~ScopedArray() { InDLL<T>::deletearray(ptr_); }

    T &operator[](std::size_t index) const { return ptr_[index]; }
    T *get() const { return ptr_; }

    T* release() {
      T* tmp(ptr_);
      ptr_ = 0;
      return tmp;
    }
    void reset(T* ptr) {
      if (ptr_ != ptr) {
        InDLL<T>::deletearray(ptr_);
        ptr_ = ptr;
      }
    }
    /* special conversions with auxiliary type to enable copies and assignments
    */
    ScopedArray(ScopedArray_ref<T> other)
      : ptr_(other.yp) {}
    ScopedArray& operator= (ScopedArray_ref<T> other) {
      reset(other.yp);
      return *this;
    }

    template<class Y>
    operator ScopedArray_ref<Y>() {
      return ScopedArray_ref<Y>(release());
    }
    template<class Y>
    operator ScopedArray<Y>() throw() {
      return ScopedArray<Y>(release());
    }
  };



  inline std::string getStringFromDLL(const char *internalArray) {
    if (internalArray == NULL) return "";
    return std::string(internal::ScopedArray<const char>(internalArray).get());
  }

}  // internal
}
#endif  // AMPL_SCOPEDARRAY_H
