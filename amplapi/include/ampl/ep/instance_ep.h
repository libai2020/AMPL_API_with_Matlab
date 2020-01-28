#ifndef AMPL_INSTANCE_EP_H
#define AMPL_INSTANCE_EP_H

#include "ampl/ep/scopedarray.h"   // for PODStringRef
#include "ampl/ep/declarations.h"  // for suffixes
#include "ampl/ep/arg.h"
#include "ampl/tuple.h"

namespace ampl {
namespace internal {
  class Instance;
  class VariableInstance;
  class ProblemInstance;
  class ConstraintInstance;
  class SetInstance;
  class EntityBase;
  class ObjectiveInstance;
  class TableInstance;
  struct ErrorInformation;
  class DataFrame;  // for SetInstance.getValues

  extern "C" {
    AMPLAPI char* AMPL_Instance_toString(Instance* impl,
      ErrorInformation* errorInfo);

    AMPLAPI const char* AMPL_Instance_name(Instance* impl,
      ErrorInformation* errorInfo);

    AMPLAPI EntityBase* AMPL_Instance_entity(Instance* impl);


    AMPLAPI const Tuple AMPL_Instance_key(Instance* impl,
      ErrorInformation* errorInfo);

    AMPLAPI double AMPL_Instance_getDoubleSuffix(Instance* impl,
      suffix::NumericSuffix suffix,
      ErrorInformation* errorInfo);
    AMPLAPI int AMPL_Instance_getIntSuffix(Instance* impl,
      suffix::NumericSuffix suffix,
      ErrorInformation* errorInfo);
    AMPLAPI PODStringRef AMPL_Instance_StringSuffix(Instance* impl,
      suffix::StringSuffix suffix,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_VariableInstance_fix(VariableInstance* impl,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_VariableInstance_fixToValue(VariableInstance* impl,
      double value,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_VariableInstance_unfix(VariableInstance* impl,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_VariableInstance_setValue(VariableInstance* impl,
      double value,
      ErrorInformation* errorInfo);

    AMPLAPI void AMPL_ConstraintInstance_setDual(ConstraintInstance* impl,
      double dual,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_ConstraintInstance_drop(ConstraintInstance* impl,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_ConstraintInstance_restore(ConstraintInstance* impl,
      ErrorInformation* errorInfo);

    AMPLAPI void AMPL_ObjectiveInstance_drop(ObjectiveInstance* impl,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_ObjectiveInstance_restore(ObjectiveInstance* impl,
      ErrorInformation* errorInfo);

    AMPLAPI std::size_t AMPL_SetInstance_size(SetInstance* impl);

    AMPLAPI const Tuple* AMPL_SetInstance_data(SetInstance* impl, std::size_t* size,
      ErrorInformation* errorInfo);
    AMPLAPI bool AMPL_SetInstance_contains(SetInstance* impl, Tuple t,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_SetInstance_setValues_Arg(SetInstance* impl,
      AMPLArgs objects, std::size_t n,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_SetInstance_setValues_Tuple(SetInstance* impl,
      Tuple objects[], std::size_t n,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_SetInstance_getValues(SetInstance* impl, DataFrame *output,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_SetInstance_setValues_Dataframe(SetInstance *impl, DataFrame* data,
      ErrorInformation *errorInfo);

    // ************* Table *************
    AMPLAPI void AMPL_TableInstance_read(TableInstance *impl,
      ErrorInformation *errorInfo);
    AMPLAPI void AMPL_TableInstance_write(TableInstance *impl,
      ErrorInformation *errorInfo);
  }  // extern C
}  // namespace internal
}  // namespace ampl
#endif  // AMPL_INSTANCE_EP_H
