#ifndef AMPL_TUPLE_H
#define AMPL_TUPLE_H

#include "ampl/variant.h"
#include "ampl/ep/tuple_ep.h"

#include <vector>

namespace ampl {
namespace internal {
class TupleUtils;
}

/**
Generic tuple (with or without ownership)

Represents a tuple with the concept of ownership. It always has ownership of the
array of variant itself, but not the data they contain. This second is controlled by
the template argument.
*/
template <bool OWNING>
class BasicTuple {
  friend class internal::TupleBuilder;
  friend class Tuple;
  template <bool O>
  friend class BasicTuple; // For coercing
  friend class internal::TupleUtils;


  void destroy() {
    if (impl_.size > 0)
      deleteTuple(impl_);
  }

  void assign(internal::Tuple other) {
    std::size_t size = other.size;
    internal::Variant* data = other.data;
    if (!OWNING) {
      impl_.size = size;
      impl_.data = data;
      return;
    }
    internal::TupleBuilder tb(size);
    for (std::size_t i = 0; i < size; i++)
      tb.add(VariantRef(data[i]));
    impl_.size = 0;
    BasicTuple t;
    t.impl_ = tb.release();
    swap(*this, t);
  }

  friend void swap(BasicTuple& l, BasicTuple& r) {
    using std::swap;
    swap(l.impl_, r.impl_);
  }

protected:
  internal::Tuple impl_;

public:
  /**
  Get access to the inner immutable object (infrastructure).
  */
  internal::Tuple impl() const { return impl_; }

  /**
  Constructor from struct. If owning, copies all the data from it, otherwise
  it references it
  */
  explicit BasicTuple(internal::Tuple other) { assign(other); }

  /**
  Default constructor
  */
  BasicTuple() { impl_.size = 0; impl_.data = NULL; }

  /**
  Copy constructor
  */
  BasicTuple(BasicTuple const& other) { assign(other.impl_); }

  /**
  Coercing copy constructor
  */
  template <bool U>
  BasicTuple(BasicTuple<U> const& other) { assign(other.impl_); }

  /**
  Destructor
  */
  ~BasicTuple() {
    if (OWNING)
      destroy();
  }

  /**
  Coercing assignment operator
  */
  template <bool U>
  BasicTuple& operator=(BasicTuple<U> other) {
    using std::swap;
    swap(*this, other);
    if (OWNING && (!U))
      other.destroy();
    return *this;
  }

  /**
  Assignment operator
  */
  BasicTuple& operator=(BasicTuple other) {
    using std::swap;
    swap(*this, other);
    return *this;
  }

  /**
  Get the number of Elements in this tuple
  */
  std::size_t size() const { return impl_.size; }

  /**
  Return a string representation of this tuple. All elements are formatted
  as in BasicVariant::toString and comma separated.
  An empty tuple is returned as "()".
  */
  std::string toString() const {
    if (impl_.size == 0)
      return "()";
    fmt::MemoryWriter out;
    if (impl_.size == 1)
      return (*this)[0].toString();
    out << "(" << (*this)[0].toString();
    for (std::size_t i = 1; i < impl_.size; i++) { out << ", " << (*this)[i].toString(); }
    out << ")";
    return out.str();
  }

  /**
  Accessor for elements of the tuple
  */
  VariantRef operator[](std::size_t index) const {
    assert(index < impl_.size);
    return VariantRef(impl_.data[index]);
  }
};

/**
* Not owning Tuple.
*
* A public typedef of BasicTuple without ownership semantics.
* It can be used both as a return type when the ownership semantics is not
* needed (e.g. returning a reference to a tuple stored in a container) and as an
* argument type to provide implicit conversions and reduce the number of required
* overloads.
*/
typedef BasicTuple<false> TupleRef;

/**
Represents a tuple with ownership semantics (owns all the data it contains)
*/
class Tuple : public BasicTuple<true> {
public:

  /** @name Constructors
  * Constructors for Tuple objects.
  */
  //@{
  /**
  Construct an empty Tuple
  */
  Tuple() : BasicTuple<true>() {}

  /**
  Construct a n-Tuple from an array of variants
  */
  Tuple(Variant arguments[], std::size_t N) {
    internal::TupleBuilder tb(N);
    for (std::size_t i = 0; i < N; i++)
      tb.add(arguments[i]);
    impl_ = tb.release();
  }


  /**
  Construct a Tuple from a TupleRef
  */
  explicit Tuple(TupleRef t) : BasicTuple<true>(t.impl_) {}

  /** @name Constructors from variants
  * Constructors from ampl::Variant objects.
  */
  //@{
  explicit Tuple(VariantRef v1) {
    VariantRef args[1] = {v1};
    initialize(args, 1);
  }

  Tuple(VariantRef v1, VariantRef v2) {
    VariantRef args[2] = {v1, v2};
    initialize(args, 2);
  }

  Tuple(VariantRef v1, VariantRef v2, VariantRef v3) {
    VariantRef args[3] = {v1, v2, v3};
    initialize(args, 3);
  }

  /**
  * Construct tuples from variants
  *
  * \param v1 First element
  * \param v2 Second element
  * \param v3 Third element
  * \param v4 Fourth element
  */
  Tuple(VariantRef v1, VariantRef v2, VariantRef v3, VariantRef v4) {
    VariantRef args[4] = {v1, v2, v3, v4};
    initialize(args, 4);
  }

  /**@}*/ // end constructors from variants group
  /**@}*/ // end constructors group

  /**
  * Construct a tuple from an internal struct (infrastructure)
  */
  explicit Tuple(internal::Tuple other) : BasicTuple<true>(other) {}

  /**
  Join two tuples together and forms a new one copying all data
  */
  static Tuple join(TupleRef t1, TupleRef t2) {
    std::size_t size1 = t1.size();
    std::size_t size2 = t2.size();
    internal::TupleBuilder tb(size1 + size2);
    for (std::size_t i = 0; i < size1; i++)
      tb.add(VariantRef(t1.impl_.data[i]));
    for (std::size_t i = 0; i < size2; i++)
      tb.add(VariantRef(t2.impl_.data[i]));
    Tuple t;
    t.impl_ = tb.release();
    return t;
  }

private:
  void initialize(VariantRef args[], std::size_t n) {
    internal::TupleBuilder tb(n);
    for (std::size_t i = 0; i < n; i++)
      tb.add(args[i]);
    impl_ = tb.release();
  }
};

namespace internal {
inline std::vector<Tuple> getInternalTupleArray(
  const ampl::Tuple* array, std::size_t size) {
  std::vector<internal::Tuple> v;
  v.reserve(size);
  for (std::size_t i = 0; i < size; ++i)
    v.push_back(array[i].impl());
  return v;
}

inline int compare(TupleRef t1, TupleRef t2) {
  if (t1.size() == t2.size()) {
    for (std::size_t i = 0; i < t1.size(); i++) {
      int r = compare(t1[i], t2[i]);
      if (r != 0)
        return r;
    }
    return 0;
  }
  else
    return (t1.size() > t2.size()) ? 1 : -1;
}

template <std::size_t SIZE>
inline BasicTuple<false> MakeTempTuple(internal::Variant (&data)[SIZE]) {
  internal::Tuple tuple = {data, SIZE};
  return BasicTuple<false>(tuple);
}
}

/** @name Tuple comparison operators
*   Comparison operators for Tuple and TupleRef
*/
///@{

/**
Comparison operator.
Returns true if t1.size() < t2.size(). Otherwise
implements Variant comparison on all elements considering
element 0 as the most significative.
*/
inline bool operator<(TupleRef t1, TupleRef t2) { return internal::compare(t1, t2) < 0; }

/*Comparison operator.
Returns true if t1.size() <= t2.size(). Otherwise
implements Variant comparison on all elements considering
element 0 as the most significative.
*/
inline bool operator<=(TupleRef t1, TupleRef t2) { return internal::compare(t1, t2) <= 0; }

/**
Equality operator
*/
inline bool operator==(TupleRef t1, TupleRef t2) { return internal::compare(t1, t2) == 0; }

/**
Inequality operator
*/
inline bool operator!=(TupleRef t1, TupleRef t2) { return internal::compare(t1, t2) != 0; }

/**
Comparison operator.
Returns true if t1.size() > t2.size(). Otherwise
implements Variant comparison on all elements considering
element 0 as the most significative.
*/
inline bool operator>(TupleRef t1, TupleRef t2) { return internal::compare(t1, t2) > 0; }

/**
Comparison operator.
Returns true if t1.size() >= t2.size(). Otherwise
implements Variant comparison on all elements considering
element 0 as the most significative.
*/
inline bool operator>=(TupleRef t1, TupleRef t2) { return internal::compare(t1, t2) >= 0; }

///@}

} // namespace ampl

#endif  // AMPL_TUPLE_H
