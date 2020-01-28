#ifndef AMPL_ERROR_INFORMATION_H_
#define AMPL_ERROR_INFORMATION_H_

#include <cstring>
#include "ampl/amplexception.h"
#include "ampl/ep/declarations.h"

namespace ampl {
namespace internal {
  /*
  C++ exception types
  */
  namespace error {
  enum Type {
    OK = 0,
    AMPLException,
    LicenseException,
    FileIOException,
    UnsupportedOperationException,
    InvalidSubscriptException,
    SyntaxErrorException,
    NoDataException,
    Logic_Error,
    Runtime_Error,
    Invalid_Argument,
    Out_Of_Range,
    Std_Exception


  };
  }

  struct ErrorInformation {
    error::Type errorType;
    char *message;
    int line;
    int offset;
    char *source;
  ErrorInformation(): errorType(error::OK), message(NULL), source(NULL) { }
  };
}
}

#endif // AMPL_ERROR_INFORMATION_H_
