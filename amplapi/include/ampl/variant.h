#ifndef AMPL_VARIANT_H
#define AMPL_VARIANT_H

#include "ampl/ep/variant_ep.h"
#include "ampl/ep/errorinfo_ep.h"
#include "ampl/ep/scopedarray.h" // for AMPL_CopyString
#include "ampl/format.h"
#include <string>
#include <cstring> // for strcmp

namespace ampl {
/**
Represents the type of a value in the %AMPL type system,
used in the Variant and VariantRef classes.
*/
enum Type {
  /**
  Empty variant, i.e. one that does not hold a value
  */
  EMPTY,
  /**
  Numeric (floating point) value
  */
  NUMERIC,
  /**
  String value
  */
  STRING
};

namespace internal {
/*
POD type representing any item in the %AMPL type system.
%AMPL has only two basic data types: string and numeric.
*/
struct Variant {
  /*
  Stores the type
  @see Type
  */
  Type type;

  /*
  Stores the reference as a discriminated union
  */
  union {
    double nvalue;

    struct StringValue {
      const char* ptr;
      std::size_t size;
    } svalue;
  } data;
};

/*
Function to copy Variant (memory is allocated inside the DLL boundary)
*/
inline Variant copyVariant(Variant source) {
  Variant copy = source;
  if (source.type == STRING)
    copy.data.svalue.ptr = AMPL_CopyString(source.data.svalue.ptr,
                                           source.data.svalue.size, internal::ErrorInfo());
  return copy;
}

/*
Delete Variant
*/
inline void deleteVariant(Variant v) {
  if (v.type == STRING)
    AMPL_DeleteString(v.data.svalue.ptr);
}
} // namespace internal

// forward declaration of a Variant class
template <bool OWNING>
class BasicVariant;

/**
* Public typedef of BasicVariant with ownership semantics.
*/
typedef BasicVariant<true> Variant;

/**
* Public typedef of BasicVariant without ownership semantics.
* It can be used both as a return type when the ownership semantics is not
* needed (e.g. returning a reference to a value stored in a container) and as an
* argument type to provide implicit conversions and reduce the number of
* required overloads.
*/
typedef BasicVariant<false> VariantRef;

// forward  declaration
namespace internal {
Variant release(ampl::BasicVariant<true>& v);
}

/** Template class which implements a variant object, with
* or without ownership semantics. The object can represent
* a string or a double number, and maps directly to the
* underlying %AMPL type system.
* It is not intended to be used directly, please use
* Variant (with ownership semantics, each object stores the
* values that it represents) or VariantRef
* (without ownership semantics, each object is only a reference
* to values stored elsewhere).
*/
template <bool OWNING>
class BasicVariant {
  friend internal::Variant internal::release(BasicVariant<true>& v);

private:
  internal::Variant impl_;

  void fromString(const char* value, std::size_t size) {
    impl_.type = STRING;
    if (OWNING) {
      impl_.data.svalue.ptr = internal::AMPL_CopyString(value, size,
                                                        internal::ErrorInfo());
      impl_.data.svalue.size = size;
    }
    else {
      impl_.data.svalue.ptr = value;
      impl_.data.svalue.size = size;
    }
  }

  void destroy() {
    if (OWNING)
      deleteVariant(impl_);
  }

  void assign(internal::Variant other) { impl_ = OWNING ? copyVariant(other) : other; }

  void assignAndFree(internal::Variant other) {
    if (OWNING && (impl_.type == STRING)) {
      const char* oldptr = impl_.data.svalue.ptr;
      assign(other);
      internal::AMPL_DeleteString(oldptr);
    }
    else
      assign(other); // no throw
  }

  static internal::Variant makeVariant(double value) {
    internal::Variant result = {NUMERIC, {value}};
    return result;
  }

public:
  /**
  Constructor from POD data type. If the BasicVariant has ownership
  semantics, it owns the POD data (deleting it when the BasicVariant
  is deleted and copying it when it is copied).
  */
  explicit BasicVariant(internal::Variant var) : impl_(var) {}

  /**
  Default constructor, creates an empty variant
  */
  BasicVariant() { impl_.type = EMPTY; }

  /**
  Creates a numeric variant with the specified value
  */
  BasicVariant(int value) : impl_(makeVariant(value)) {}
  /**
  Creates a numeric variant with the specified value
  */
  BasicVariant(unsigned value) : impl_(makeVariant(value)) {}
  /**
  Creates a numeric variant with the specified value
  */
  BasicVariant(long value) : impl_(makeVariant(value)) {}
  /**
  Creates a numeric variant with the specified value
  */
  BasicVariant(unsigned long value) : impl_(makeVariant(value)) {}
  /**
  Creates a numeric variant with the specified value
  */
  BasicVariant(double value) : impl_(makeVariant(value)) {}

  /**
  Creates a string variant which references or owns a copy
  of the specified string
  */
  BasicVariant(const std::string& value) { fromString(value.c_str(), value.size()); }

  /**
  Creates a string variant which references or owns a copy
  of the specified string literal
  */
  BasicVariant(const char* value) { fromString(value, std::strlen(value)); }

  /**
  Copy constructor. If ``OWNING`` copy the resources
  */
  BasicVariant(const BasicVariant& other) { assign(other.impl_); }

  /**
  Coercing copy constructor
  */
  template <bool U>
  BasicVariant(BasicVariant<U> const& other) { assign(other.impl()); }

  /**
  Destructor. If ``OWNING`` frees the resources.
  */
  ~BasicVariant() { destroy(); }

  /**
  Coercing assignment operator
  */
  template <bool U>
  BasicVariant& operator=(const BasicVariant<U>& other) {
    assignAndFree(other.impl());
    return *this;
  }

  /**
  Assignment operator
  */
  BasicVariant& operator=(const BasicVariant& other) {
    assignAndFree(other.impl());
    return *this;
  }

  /**
  Returns the pointer to a C string.
  */
  const char* c_str() const {
    assert(impl_.type == STRING);
    return impl_.data.svalue.ptr;
  }

  /**
  Returns the numerical value
  */
  double dbl() const {
    assert(impl_.type == NUMERIC);
    return impl_.data.nvalue;
  }

  /**
  Converts an %AMPL variant element to an `std::string` object
  */
  std::string str() const {
    assert(impl_.type == STRING);
    return std::string(impl_.data.svalue.ptr, impl_.data.svalue.size);
  }

  /**
  Returns the type of this variant object
  */
  Type type() const { return impl_.type; }

  /**
  Get the inner POD struct
  */
  internal::Variant impl() const { return impl_; }

  /**
  Return an %AMPL like representation of this variant. String variants are
  single-quoted, numeric are not.
  */
  std::string toString() const {
    switch (impl_.type) {
    case NUMERIC:
      return fmt::format("{}", impl_.data.nvalue);
    case STRING:
      return fmt::format("'{}'", impl_.data.svalue.ptr);
    default:
      return "EMPTY";
    }
  }
}; // class BasicVariant


namespace internal {
/**
Comparison function. Returns 0 if lhs==rhs, a positive number if lhs>rhs and
a negative integer if lhs<rhs. Implements normal numeric comparison and lexicographic
string comparison (see std::strcmp). Numeric variant < string variant) is always true.
*/
inline int compare(VariantRef lhs, VariantRef rhs) {
  int result = lhs.type() - rhs.type();
  if (result != 0) return result;

  if (lhs.type() == NUMERIC) {
    if (lhs.dbl() == rhs.dbl())
      return 0;
    if ((lhs.dbl() - rhs.dbl()) > 0)
      return 1;
    else
      return -1;
  }
  if (lhs.type() == EMPTY)
	  return 0;
  return std::strcmp(lhs.c_str(), rhs.c_str());
}
} // internal

/**
Comparison operator.
Implements normal numeric comparison and normal string comparison,
(numeric variant < string variant) is always true.
*/
inline bool operator<(VariantRef t1, VariantRef t2) { return internal::compare(t1, t2) < 0; }

/**
Comparison operator.
Implements normal numeric comparison and normal string comparison,
(numeric variant <= string variant) is always true.
*/
inline bool operator<=(VariantRef t1, VariantRef t2) { return internal::compare(t1, t2) <= 0; }

/**
Equality operator
*/
inline bool operator==(VariantRef t1, VariantRef t2) { return internal::compare(t1, t2) == 0; }

/**
Inequality operator
*/
inline bool operator!=(VariantRef t1, VariantRef t2) { return internal::compare(t1, t2) != 0; }

/**
Comparison operator.
Implements normal numeric comparison and normal string comparison,
(string variant > numeric variant) is always true.
*/
inline bool operator>(VariantRef t1, VariantRef t2) { return internal::compare(t1, t2) > 0; }

/**
Comparison operator.
Implements normal numeric comparison and normal string comparison,
(string variant >= numeric variant) is always true.
*/
inline bool operator>=(VariantRef t1, VariantRef t2) { return internal::compare(t1, t2) >= 0; }
}

#endif // AMPL_VARIANT_H
