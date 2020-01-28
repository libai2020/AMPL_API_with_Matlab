#ifndef AMPL_ERRORINFO_H_
#define AMPL_ERRORINFO_H_

#include "ampl/ep/declarations.h"
#include "ampl/amplexception.h"
#include "ampl/ep/error_information.h"

#include <stdexcept>

namespace ampl {
namespace internal {
  extern "C" {
    AMPLAPI void AMPL_ErrorInformation_delete(ErrorInformation *info);
  } // extern C

#if FMT_USE_NOEXCEPT || FMT_HAS_FEATURE(cxx_noexcept) || \
    (FMT_GCC_VERSION >= 408 && FMT_HAS_GXX_CXX11) || (_MSC_VER >= 1900)
#define AMPL_THROWSEX noexcept(false)
#else
#define AMPL_THROWSEX
#endif



  inline void throwException(ErrorInformation *info) {
    /**
    Represents a generic system exception with message
    */
    class StdException : public std::exception {
      std::string message_;

    public:
      ~StdException() FMT_NOEXCEPT {}
      StdException(fmt::CStringRef cause) : message_(cause.c_str()) {}
      const char *what() const FMT_NOEXCEPT { return message_.c_str(); }
    };
    switch (info->errorType) {
    case error::LicenseException:
      throw LicenseException(info->message);
    case error::FileIOException:
      throw FileIOException(info->message);
    case error::UnsupportedOperationException:
      throw UnsupportedOperationException(info->message);
    case error::InvalidSubscriptException:
      throw InvalidSubscriptException(info->source, info->line, info->offset, info->message);
    case error::SyntaxErrorException:
      throw SyntaxErrorException(info->source, info->line, info->offset, info->message);
    case error::NoDataException:
      throw NoDataException(info->message);
    case error::AMPLException:
      throw AMPLException(info->source, info->line, info->offset, info->message);
    case error::Runtime_Error:
      throw std::runtime_error(info->message);
    case error::Logic_Error:
      throw std::logic_error(info->message);
    case error::Out_Of_Range:
      throw std::out_of_range(info->message);
    case error::Invalid_Argument:
      throw std::invalid_argument(info->message);
    case error::Std_Exception:
    {
      throw StdException(info->message);
    }
    case error::OK:
    {
    }
    }
  }

  class ErrorInfo {
  private:
    ErrorInformation result_;

  public:
    operator ErrorInformation *() { return &result_; }

    ~ErrorInfo() AMPL_THROWSEX {
      if (result_.errorType != error::OK) {
        try {
          throwException(&result_);
        }
        catch (...) {
          AMPL_ErrorInformation_delete(&result_);
          throw;
        }
      }
    }
  };
}
}
#endif // AMPL_ERRORINFO_H_
