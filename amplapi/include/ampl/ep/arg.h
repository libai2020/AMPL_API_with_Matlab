#ifndef AMPL_ARG_H
#define AMPL_ARG_H

#include "ampl/variant.h"  // for Type

namespace ampl {
class Tuple;
namespace internal {
  struct AMPLArgs {
    union {
      const double *dbl_values;
      const char *const *str_values;
    };
    Type type;
  };

  /**
  Lightweight class used to pass references to arrays to and from the API
  */
  class Args {
  private:
    AMPLArgs data_;
    friend class ampl::Tuple;

  public:
    Args(AMPLArgs data) : data_(data) {}
    Args(const double *values) {
      data_.type = NUMERIC;
      data_.dbl_values = values;
    }
    Args(const char *const *values) {
      data_.type = STRING;
      data_.str_values = values;
    }
    AMPLArgs data() { return data_; }
    Type type() { return data_.type; }
  };
}  // namespace internal
}  // namespace ampl

#endif  // AMPL_ARG_H
