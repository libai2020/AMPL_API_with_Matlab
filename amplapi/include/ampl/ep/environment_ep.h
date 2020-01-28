#ifndef AMPL_ENVIRONMENT_EP_H
#define AMPL_ENVIRONMENT_EP_H

#include "ampl/ep/declarations.h"
#include "ampl/ep/errorinfo_ep.h"

#include <map>
#include <string>

namespace ampl {
namespace internal {

  class Environment;
  struct ErrorInformation;

  struct EnvironmentRefPointer {
    std::size_t count;
    std::map<std::string, std::string>::const_iterator it;
  };



  extern "C" {
    AMPLAPI Environment* AMPL_Environment_Create(ErrorInformation* errorInfo);
    AMPLAPI Environment* AMPL_Environment_Copy(const Environment* other,
      ErrorInformation* errorInfo);
    AMPLAPI Environment* AMPL_Environment_Create_WithBin(
      const char* binaryDirectory, ErrorInformation* errorInfo);
    AMPLAPI void AMPL_Environment_Destroy(Environment* env);
    AMPLAPI void AMPL_Environment_addEnvironmentVariable(
      Environment* env, const char* name, const char* value,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_Environment_setBinaryDirectory(Environment* env,
      const char* binaryDirectory,
      ErrorInformation* errorInfo);
    AMPLAPI const char* AMPL_Environment_getBinaryDirectory(
      Environment* env, ErrorInformation* errorInfo);
    AMPLAPI std::size_t AMPL_Environment_size(Environment* env, ErrorInformation* errorInfo);
    AMPLAPI const char* AMPL_Environment_toString(Environment* env,
      ErrorInformation* errorInfo);
    AMPLAPI EnvironmentRefPointer* AMPL_Environment_begin(
      Environment* impl, ErrorInformation* errorInfo);
    AMPLAPI EnvironmentRefPointer* AMPL_Environment_end(
      Environment*, ErrorInformation* errorInfo);
    AMPLAPI EnvironmentRefPointer* AMPL_Environment_find(
      Environment* impl, const char* name, ErrorInformation* errorInfo);
    AMPLAPI void AMPL_Environment_iterator_increment(EnvironmentRefPointer* it,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_Environment_iterator_delete(EnvironmentRefPointer* it);
    AMPLAPI bool AMPL_Environment_iterator_equal(EnvironmentRefPointer* it1,
      EnvironmentRefPointer* it2,
      ErrorInformation* errorInfo);
    AMPLAPI void AMPL_Environment_iterator_getPointer(EnvironmentRefPointer* it,
      const char** first,
      const char** second,
      ErrorInformation* errorInfo);
  }  // extern C

  class EnvironmentIterator {
  public:
    typedef  std::pair<const char*, const char*> ValueType;

    typedef const char* InstanceType;
    typedef const char* KeyType;

    typedef internal::EnvironmentRefPointer* ReferencePointer;

    static void dispose(ReferencePointer data) {
      internal::AMPL_Environment_iterator_delete(data);
    }

    static bool equal(ReferencePointer it1, ReferencePointer it2) {
      return AMPL_Environment_iterator_equal(it1, it2, internal::ErrorInfo());
    }
    static void increment(ReferencePointer it) {
      AMPL_Environment_iterator_increment(it, internal::ErrorInfo());
    }

    static ValueType getPointer(ReferencePointer it) {
      const char* first, *second;
      internal::AMPL_Environment_iterator_getPointer(it, &first, &second, internal::ErrorInfo());
      return ValueType(first, second);
    }

  };
}  // namespace internal
}  // namespace ampl
#endif  // AMPL_ENVIRONMENT_EP_H
