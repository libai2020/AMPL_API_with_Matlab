#ifndef AMPL_SLICE_H
#define AMPL_SLICE_H

#include "ampl/variant.h"
#include "ampl/ep/dataframe_ep.h"

#include <vector>

namespace ampl {
class DataFrame;
namespace internal {
  class DataFrame;

/**
* Represents a slice (row or column) of a DataFrame.
*/
  template <bool ROW>
  class Slice {
    friend class ampl::DataFrame;
    DataFrame *data_;
    std::size_t fixedIndex_;

    Slice(internal::DataFrame *data, std::size_t index)
      : data_(data), fixedIndex_(index) {}
    // A proxy used for implementing operator->.
    class Proxy {
    private:
      VariantRef inner_;

    public:
      // Constructor
      explicit Proxy(VariantRef e)
        : inner_(e) {}
      // Arrow operator
      const VariantRef *operator->() const { return &inner_; }
    };
  public:
    class iterator : public std::iterator<std::forward_iterator_tag, VariantRef> {
      friend class Slice;
      const Slice *parent_;
      std::size_t index_;
      iterator(const Slice *parent, std::size_t index)
        : parent_(parent), index_(index) {}
    public:
      value_type operator*() const {
        return (*parent_)[index_];
      }
      iterator &operator++() {
        ++index_;
        return *this;
      }
      iterator operator++(int) {
        iterator clone(*this);
        ++index_;
        return clone;
      }
      bool operator==(const iterator &other) const {
        return (parent_->data_ == other.parent_->data_) &&
          (parent_->fixedIndex_ == other.parent_->fixedIndex_) &&
          (index_ == other.index_);
      }
      bool operator!=(const iterator &other) const { return !(*this == other); }
      /*
      * Arrow operator
      */
      Proxy operator->() const {
        return Proxy((*parent_)[index_]);
      }
    };



    std::size_t size() const {
      if (ROW)
        return internal::AMPL_DataFrame_getNumCols(data_);
      else
        return internal::AMPL_DataFrame_getNumRows(data_);
    }

    iterator begin() const { return iterator(this, 0); }

    iterator end() const { return iterator(this, size()); }

    VariantRef operator[](std::size_t index) const {
      if (ROW)
        return VariantRef(
          internal::AMPL_DataFrame_Element(data_, fixedIndex_, index));
      else
        return VariantRef(
          internal::AMPL_DataFrame_Element(data_, index, fixedIndex_));
    }
  };
}  // namespace internal
}  // namespace ampl

#endif  // AMPL_SLICE_H
