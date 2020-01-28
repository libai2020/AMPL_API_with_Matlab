#ifndef AMPL_VARIANT_EP_H
#define AMPL_VARIANT_EP_H

#include "ampl/ep/error_information.h"

namespace ampl {
namespace internal {
  struct Variant; // Forward dec
  extern "C" {
    AMPLAPI void AMPL_Variant_DeleteArray(const Variant* toDelete);
    AMPLAPI Variant* AMPL_Variant_CreateArray(std::size_t size, ErrorInformation* errorInfo);
  }

}  // namespace internal
}  // namespace ampl
#endif  // AMPL_VARIANT_EP_H
