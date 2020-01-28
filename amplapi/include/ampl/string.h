#ifndef AMPL_STRING_H
#define AMPL_STRING_H

#include "ampl/format.h"
#include <assert.h>

#include "ampl/ep/scopedarray.h"
#include "ampl/ep/errorinfo_ep.h"


namespace ampl {

/**
Efficiently stores references to string literals.
If the size is <= 4, the pointers to the literals are stored
internally, otherwise they are external.
*/
class StringArgs {
  std::size_t size_;

  enum Type { INLINE, EXTERNAL };

  Type type_;

  union {
    const char* inline_[4]; // inline arguments
    const char** external_; // pointer to external arguments
  };

public:
  /**
  * Construct a StringArgs object referencing the given strings
  *
  * @param arg0 First string
  */
  StringArgs(const char* arg0) : size_(1), type_(INLINE) { inline_[0] = arg0; }

  /**
  * Construct a StringArgs object referencing the given strings
  *
  * @param arg0 First string
  */
  StringArgs(fmt::CStringRef arg0) : size_(1), type_(INLINE) { inline_[0] = arg0.c_str(); }

  /**
  * Construct a StringArgs object referencing the given strings
  *
  * @param arg0 First string
  * @param arg1 Second string
  */
  StringArgs(fmt::CStringRef arg0, fmt::CStringRef arg1)
    : size_(2), type_(INLINE) {
    inline_[0] = arg0.c_str();
    inline_[1] = arg1.c_str();
  }

  /**
  * Construct a StringArgs object referencing the given strings
  *
  * @param arg0 First string
  * @param arg1 Second string
  * @param arg2 Third string
  */
  StringArgs(fmt::CStringRef arg0, fmt::CStringRef arg1, fmt::CStringRef arg2)
    : size_(3), type_(INLINE) {
    inline_[0] = arg0.c_str();
    inline_[1] = arg1.c_str();
    inline_[2] = arg2.c_str();
  }

  /**
  * Construct a StringArgs object referencing the given strings
  *
  * @param arg0 First string
  * @param arg1 Second string
  * @param arg2 Third string
  * @param arg3 Fourth string
  */
  StringArgs(fmt::CStringRef arg0, fmt::CStringRef arg1, fmt::CStringRef arg2,
             fmt::CStringRef arg3)
    : size_(4), type_(INLINE) {
    inline_[0] = arg0.c_str();
    inline_[1] = arg1.c_str();
    inline_[2] = arg2.c_str();
    inline_[3] = arg3.c_str();
  }

  /**
  * Construct a StringArgs object referencing the given strings,
  * having the pointers stored externally
  *
  * @param args The array of strings to represent
  * @param num_args The number of string
  */
  StringArgs(const char* args[], std::size_t num_args)
    : size_(num_args), type_(EXTERNAL) { external_ = args; }

  /**
  * Get a pointer to the arguments
  */
  const char*const * args() const { return (type_ == INLINE) ? inline_ : external_; }

  /**
  Get the number of strings passed as arguments
  */
  std::size_t size() const { return size_; }
};

namespace internal {

/*
Internal class to safely build string arrays
*/
class StringArrayBuilder {
  FMT_DISALLOW_COPY_AND_ASSIGN(StringArrayBuilder);
  const char** data_;
  std::size_t capacity_;
  std::size_t size_;
public:
  explicit StringArrayBuilder(std::size_t capacity) : size_(0) {
    data_ = AMPL_CreateArrayStrings(capacity, ErrorInfo());
    capacity_ = capacity;
  }

  ~StringArrayBuilder() {
    for (std::size_t i = 0; i < size_; i++)
      AMPL_DeleteString(data_[i]);
    AMPL_DeleteArrayStrings(data_);
  }

  void add(fmt::StringRef data) {
    assert(size_ < capacity_);
    data_[size_] = AMPL_CopyString(data.data(), data.size(), ErrorInfo());
    size_++;
  }

  void resize(std::size_t newCapacity)
  {
      const char** temp = data_;
      data_ = AMPL_CreateArrayStrings(newCapacity, ErrorInfo());
      capacity_ = newCapacity;
      for (std::size_t i = 0; (i < size_) && (i < newCapacity); i++)
        data_[i] = temp[i];
      if (newCapacity < size_)
      {
        for (std::size_t i = newCapacity; i < size_; i++)
          AMPL_DeleteString(data_[i]);
        size_ = newCapacity;
      }
      AMPL_DeleteArrayStrings(temp);
  }

  std::size_t size() const { return size_; }

  const char** release() {
    const char** strings = data_;
    data_ = NULL;
    capacity_ = 0;
    size_ = 0;
    return strings;
  }

};

// Forward decl
template <bool OWNING>
class BasicStringArray;
}

/**
* An array of references to strings (does not have ownership
* on the strings)
*/
typedef internal::BasicStringArray<false> StringRefArray;
/**
An array of strings (with ownership)
*/
typedef internal::BasicStringArray<true> StringArray;

namespace internal {
// Forward decl
StringArray move(const char** ptr, std::size_t size);

template <bool OWNING>
class BasicStringArray {
protected:
  ScopedArray<const char *> strings_;
  std::size_t size_;

  void deallocate() {
    if (OWNING) {
      for (std::size_t i = 0; i < size_; i++)
        AMPL_DeleteString(strings_[i]);
    }
    size_ = 0U;
  }

  void initialize(const char** arr, std::size_t size) {
    if (OWNING) {
      StringArrayBuilder sb(size);
      for (std::size_t i = 0U; i < size; i++)
        sb.add(arr[i]);
      strings_ = internal::ScopedArray<const char*>(sb.release());
    }
    else {
      internal::ScopedArray<const char *> newvalue(AMPL_CreateArrayStrings(size, internal::ErrorInfo()));
      for (std::size_t i = 0U; i < size; i++)
        newvalue[i] = arr[i];
      strings_ = newvalue;
    }
    size_ = size;
  }

public:
  /**
  Assignment operator, copies the array of pointers to the
  strings
  @param other Other StringRefArray
  */
  BasicStringArray& operator=(const BasicStringArray& other) {
    deallocate();
    initialize(other.strings_.get(), other.size());
    return *this;
  }

  /**
  Copy constructor, copies the array of pointers to the
  strings
  @param other Other StringRefArray
  */
  BasicStringArray(const BasicStringArray& other) : size_(0U) { initialize(other.strings_.get(), other.size()); }

  /**
  Constructor from an array of strings, it copies it.
  @param strings Array of strings
  @param size Number of strings
  */
  BasicStringArray(const char** strings, std::size_t size) { initialize(strings, size); }

  /**
  Destructor
  */
  ~BasicStringArray() { deallocate(); }

  /**
  Constructor of an empty array
  */
  BasicStringArray()
    : size_(0) {}

  /**
  Get the number of strings
  */
  std::size_t size() const { return size_; }
  /**
  An iterator to the contents
  */
  typedef const char** iterator;

  /**
  Accessor to the contents
  @param index The 0-based index of the content to get
  */
  const char* operator[](std::size_t index) const {
    assert(index < size_);
    return strings_[index];
  }

  /**
  Returns an iterator to the first element
  */
  iterator begin() const { return strings_.get(); }

  /**
  Returns an iterator to the element after the last
  */
  iterator end() const { return strings_.get() + size_; }

  /**
  Releases the ownership of the contained data
  */
  friend const char** release(BasicStringArray& array) {
    array.size_ = 0;
    return array.strings_.release();
  }

  /**
  Gains ownership of the passed data
  */
  friend StringArray internal::move(const char** ptr, std::size_t size);

};

const char** release(BasicStringArray<true>& array);
const char** release(BasicStringArray<false>& array);
} // namespace internal

/**
Get a new (owning) StringArray by transferring the ownership of the passed
strings (no copy).
*/
inline StringArray internal::move(const char** ptr, std::size_t size) {
  StringArray output;
  output.strings_.reset(ptr);
  output.size_ = size;
  return output;
}

}

#endif  // AMPL_STRINGARGS_H
