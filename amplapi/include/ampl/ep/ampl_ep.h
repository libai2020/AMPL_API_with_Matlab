#ifndef AMPL_AMPL_EP_H
#define AMPL_AMPL_EP_H

#include "ampl/ep/declarations.h" // for AMPLAPI
#include "ampl/variant.h"
#include "ampl/output.h"
#include "ampl/errorhandler.h"
#include "ampl/runnable.h"

#include "ampl/ep/environment_ep.h"

namespace ampl {

namespace internal {
  class AMPL;
  class DataFrame;
  class EntityBase;
  template <class ENTITY> class EntityMap;
  class Variable;
  class Constraint;
  class Objective;
  class Parameter;
  class Set;
  class Table;
  struct ErrorInformation;
}
}
namespace ampl {
namespace internal {

  inline void defaultOutputHandlerFunction(output::Kind kind, const char* msg, void* oh) {
    static_cast<OutputHandler*>(oh)->output(kind, msg);
  }
  inline void defaultErrorHandlerFunction(bool isWarning, const char* filename, int row, int offset,
    const char* message, void* eh) {
    ampl::AMPLException e(filename, row, offset, message);
    if(isWarning)
      static_cast<ErrorHandler*>(eh)->warning(e);
    else
      static_cast<ErrorHandler*>(eh)->error(e);
  }

  inline void runCallback(void* cb) {
    static_cast<Runnable*>(cb)->run();
  }

  extern "C" {
    AMPLAPI char* AMPL_Impl_exportModel(AMPL *ampl, ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_exportModelToFile(AMPL *ampl, const char *fileName,
      ErrorInformation *errorInfo);
    AMPLAPI char* AMPL_Impl_exportData(AMPL *ampl, int includeSets,
      ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_exportDataToFile(AMPL *ampl, const char *fileName,
      int includeSets, ErrorInformation *errorInfo);
    AMPLAPI AMPL *AMPL_Impl_Create(ErrorInformation *errorInfo);
    AMPLAPI AMPL *AMPL_Impl_Create_With_Env(Environment *env,
      ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_Destroy(AMPL *ampl);

    AMPLAPI EntityMap<Variable> *AMPL_Impl_getVariables(AMPL *ampl,
      ErrorInformation *info);
    AMPLAPI EntityMap<Constraint> *
      AMPL_Impl_getConstraints(AMPL *ampl, ErrorInformation *errorInfo);
    AMPLAPI EntityMap<Parameter> *
      AMPL_Impl_getParameters(AMPL *ampl, ErrorInformation *errorInfo);
    AMPLAPI EntityMap<Objective> *
      AMPL_Impl_getObjectives(AMPL *ampl, ErrorInformation *errorInfo);
    AMPLAPI EntityMap<Set> *AMPL_Impl_getSets(AMPL *ampl,
      ErrorInformation *errorInfo);
    AMPLAPI EntityMap<Table> *AMPL_Impl_getTables(AMPL *ampl,
      ErrorInformation *errorInfo);

    AMPLAPI EntityBase *AMPL_Impl_getEntity(AMPL *ampl, const char *name,
      ErrorInformation *errorInfo);
    AMPLAPI Variable *AMPL_Impl_getVariable(AMPL *ampl, const char *name,
      ErrorInformation *errorInfo);
    AMPLAPI Constraint *AMPL_Impl_getConstraint(AMPL *ampl, const char *name,
      ErrorInformation *errorInfo);
    AMPLAPI Objective *AMPL_Impl_getObjective(AMPL *ampl, const char *name,
      ErrorInformation *errorInfo);
    AMPLAPI Parameter *AMPL_Impl_getParameter(AMPL *ampl, const char *name,
      ErrorInformation *errorInfo);
    AMPLAPI Set *AMPL_Impl_getSet(AMPL *ampl, const char *name,
      ErrorInformation *errorInfo);
    AMPLAPI Table *AMPL_Impl_getTable(AMPL *ampl, const char *name,
      ErrorInformation *errorInfo);
    
    AMPLAPI void AMPL_Impl_eval(AMPL *ampl, const char *statement,
      ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_readAsync(AMPL *ampl, const char *filename,
      RunnablePtr function, void* cb, ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_readDataAsync(AMPL *ampl, const char *filename,
      RunnablePtr function, void* cb, ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_evalAsync(AMPL *ampl, const char *amplstatement,
      RunnablePtr function, void* cb, ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_solveAsync(AMPL *ampl, RunnablePtr function,
      void* cb, ErrorInformation *errorInfo);

    AMPLAPI void AMPL_Impl_reset(AMPL *ampl, ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_close(AMPL *ampl, ErrorInformation *errorInfo);
    AMPLAPI bool AMPL_Impl_isRunning(AMPL *ampl, ErrorInformation *errorInfo);
    AMPLAPI bool AMPL_Impl_isBusy(AMPL *ampl, ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_solve(AMPL *ampl, ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_interrupt(AMPL *ampl, ErrorInformation *errorInfo);
    AMPLAPI char *AMPL_Impl_cd(AMPL *ampl, ErrorInformation *errorInfo);
    AMPLAPI char *AMPL_Impl_cd2(AMPL *ampl, const char *path,
      ErrorInformation *errorInfo);

    AMPLAPI char *AMPL_Impl_getCurrentObjective(AMPL *ampl,
      ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_setOption(AMPL *ampl, const char *name,
      const char *value,
      ErrorInformation *errorInfo);
    AMPLAPI char *AMPL_Impl_getOption(AMPL *ampl, const char *name, bool *exists,
      ErrorInformation *errorInfo);
    AMPLAPI double AMPL_Impl_getDblOption(AMPL *ampl, const char *name,
      bool *exists,
      ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_setDblOption(AMPL *ampl, const char *name, double value,
      ErrorInformation *errorInfo);
    AMPLAPI int AMPL_Impl_getIntOption(AMPL *ampl, const char *name,
      bool *exists, ErrorInformation *errorInfo);

    AMPLAPI void AMPL_Impl_read(AMPL *ampl, const char *fileName,
      ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_readData(AMPL *ampl, const char *fileName,
      ErrorInformation *errorInfo);

    AMPLAPI void AMPL_Impl_getData(AMPL *ampl, const char *const *displayStatements,
      std::size_t N, DataFrame *output,
      ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_setDataAndSet(AMPL *ampl, DataFrame *df,
      const char *setName,
      ErrorInformation *errorInfo);
    AMPLAPI char *AMPL_Impl_toString(AMPL *ampl, ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_readTable(AMPL *ampl, const char *tableName,
      ErrorInformation *errorInfo);
    AMPLAPI void AMPL_Impl_writeTable(AMPL *ampl, const char *tableName,
      ErrorInformation *errorInfo);

    AMPLAPI void AMPL_Impl_callVisualisationCommandOnNames(
      AMPL *ampl, const char *command, const char *const *args, std::size_t nargs,
      ErrorInformation *errorInfo);

    AMPLAPI void AMPL_Impl_callVisualisationCommand(AMPL *ampl, const char *command,
      const EntityBase *const *args,
      std::size_t nargs,
      ErrorInformation *errorInfo);

    AMPLAPI Variant AMPL_Impl_getValue(AMPL *ampl, const char *scalarExpression,
      ErrorInformation *errorInfo);

    AMPLAPI char *AMPL_Impl_getOutput(AMPL *ampl, const char *amplstatement,
      ErrorInformation *errorInfo);

    AMPLAPI void AMPL_Impl_setOutputHandler(AMPL *ampl,
      void *outputhandler, OutputHandlerCbPtr callback);
    AMPLAPI void AMPL_Impl_setErrorHandler(AMPL *ampl, void *errorhandler,
      ErrorHandlerCbPtr callback);
    AMPLAPI void* AMPL_Impl_getOutputHandler(AMPL *ampl);
    AMPLAPI void *AMPL_Impl_getErrorHandler(AMPL *ampl);

  } // end C linkage
} // end namespace internal
} // end namespace ampl
#endif // AMPL_EP_H
