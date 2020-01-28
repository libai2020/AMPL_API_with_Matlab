#ifndef AMPL_TUPLE_EP_H
#define AMPL_TUPLE_EP_H

#include "ampl/variant.h"
#include "ampl/ep/scopedarray.h" // for AMPL_CopyString

#include <assert.h>

namespace ampl {

namespace internal {
  /**
  POD structure representing a Tuple
  */
  struct Tuple {
    Variant* data;
    std::size_t size;
  };

  inline void deleteTuple(Tuple &t) {
    for (std::size_t i = 0; i < t.size; i++)
      if (t.data[i].type == STRING)
        AMPL_DeleteString(t.data[i].data.svalue.ptr);
    AMPL_Variant_DeleteArray(t.data);
  }

  class TupleBuilder {
    FMT_DISALLOW_COPY_AND_ASSIGN(TupleBuilder);

    Variant *data_;
    std::size_t size_;
    std::size_t current_;
  public:
    explicit TupleBuilder(std::size_t size) : current_(0) {
      data_ = AMPL_Variant_CreateArray(size, internal::ErrorInfo());
      size_ = size;
    }
    ~TupleBuilder() {
      for (std::size_t i = 0; i < current_; i++)
        internal::deleteVariant(data_[i]);
    }
    void add(VariantRef data) {
      assert(current_ < size_);
      data_[current_] = internal::copyVariant(data.impl());
      current_++;
    }

    internal::Tuple release() {
      internal::Tuple t = { data_, size_ };
      data_ = NULL;
      size_ = 0;
      current_ = 0;
      return t;
    }
  };

} // namespace internal
} // namespace ampl

#endif // AMPL_TUPLE_EP_H
