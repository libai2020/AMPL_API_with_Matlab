#ifndef AMPL_DATAFRAME_EP_H
#define AMPL_DATAFRAME_EP_H

#include "ampl/ep/declarations.h"
#include "ampl/ep/arg.h"
#include "ampl/variant.h"

namespace ampl {
namespace internal {
  class DataFrame;
  struct Tuple;
  struct ErrorInformation;
  class EntityBase;

  extern "C" {
    AMPLAPI int AMPL_DataFrame_Equals(DataFrame* df1,
      DataFrame* df2, ErrorInformation* errorInfo);
    AMPLAPI DataFrame* AMPL_DataFrame_Copy(DataFrame* dataframe,
      ErrorInformation* errorInfo);

    AMPLAPI DataFrame* AMPL_DataFrame_Create(std::size_t numberOfIndexColumns,
      std::size_t numberOfDataColumns,
      const char* const* headers,
      ErrorInformation* errorInfo);
    AMPLAPI DataFrame* AMPL_DataFrame_Create_2(std::size_t numberOfIndexColumns,
      ErrorInformation* errorInfo);
    AMPLAPI DataFrame* AMPL_DataFrame_Create_3(const EntityBase* const* entities,
      std::size_t nargs,
      ErrorInformation* errorInfo);

    AMPLAPI void AMPL_DataFrame_Destroy(DataFrame* dataframe);
    AMPLAPI char* AMPL_DataFrame_toString(DataFrame* dataframe,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_DataFrame_reserve(DataFrame* dataframe, std::size_t numRows,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_DataFrame_addRow(DataFrame* dataframe,
      Tuple value1,
      ErrorInformation* errorInfo);

    AMPLAPI void AMPL_DataFrame_setColumn_arg(DataFrame* dataframe,
      const char* header,
      AMPLArgs column, std::size_t n,
      ErrorInformation* errorInfo);

    AMPLAPI char const** AMPL_DataFrame_getHeaders(const DataFrame* dataframe,
      std::size_t* n,
      ErrorInformation* errorInfo);

    AMPLAPI void AMPL_DataFrame_addColumn(DataFrame* dataframe,
      const char* header, AMPLArgs values,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_DataFrame_addEmptyColumn(DataFrame* dataframe,
      const char* header,
      ErrorInformation* errorInfo);

    AMPLAPI void AMPL_DataFrame_setValue(DataFrame* dataframe,
      Tuple rowIndex, const char* header, Variant value,
      ErrorInformation* errorInfo);

    AMPLAPI void AMPL_DataFrame_setValueByIndex(DataFrame* dataframe,
      std::size_t rowNumber, std::size_t colNumber, Variant value,
      ErrorInformation* errorInfo);

    AMPLAPI std::size_t AMPL_DataFrame_getNumCols(const DataFrame* dataframe);
    AMPLAPI std::size_t AMPL_DataFrame_getNumRows(const DataFrame* dataframe);
    AMPLAPI std::size_t AMPL_DataFrame_getNumIndices(const DataFrame* dataframe);

    AMPLAPI void AMPL_DataFrame_setArray(DataFrame* dataframe, const double* values,
      std::size_t l0, AMPLArgs indices0,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_DataFrame_setArray_str(DataFrame* dataframe,
      const char* const* values,
      std::size_t l0, AMPLArgs indices0,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_DataFrame_setMatrix(DataFrame* dataframe,
      const double* values, std::size_t l0,
      AMPLArgs indices0, std::size_t l1,
      AMPLArgs indices1,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_DataFrame_setMatrix_str(DataFrame* dataframe,
      const char* const* values,
      std::size_t l0, AMPLArgs indices0,
      std::size_t l1, AMPLArgs indices1,
      ErrorInformation* errorInfo);

    AMPLAPI std::size_t AMPL_DataFrame_getColumnIndex(const DataFrame* dataframe,
      const char* name,
      ErrorInformation* errorInfo);
    AMPLAPI std::size_t AMPL_DataFrame_getRowIndex(const DataFrame* dataframe,
      Tuple index,
      ErrorInformation* errorInfo);
    AMPLAPI Variant AMPL_DataFrame_Element(DataFrame* dataframe,
      std::size_t rowindex,
      std::size_t colindex);
  }  // extern C
}  // namespace internal
}  // namespace ampl

#endif  // AMPL_DATAFRAME_EP_H
