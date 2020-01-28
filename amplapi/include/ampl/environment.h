#ifndef AMPL_ENVIRONMENT_H
#define AMPL_ENVIRONMENT_H

#include "ampl/ep/environment_ep.h"
#include "ampl/ep/errorinfo_ep.h"
#include "ampl/ep/scopedarray.h" // For getStringFromDLL
#include "ampl/ep/countediterator.h"
#include "ampl/format.h"


namespace ampl {
/**
* This class provides access to the environment variables and provides
* facilities to specify where to load the underlying %AMPL interpreter.
*/
class Environment {
  friend class AMPL;

private:
  internal::Environment* impl_;

public:
  /**
  \rst
  Default constructor
  \endrst
  */
  Environment() { impl_ = internal::AMPL_Environment_Create(internal::ErrorInfo()); }

  /**
  \rst
  Copy constructor
  \endrst
  */
  Environment(const Environment& other) { impl_ = internal::AMPL_Environment_Copy(other.impl_, internal::ErrorInfo()); }

  /**
  Assignment operator
  */
  Environment& operator=(const Environment& other) {
    internal::Environment* newimpl = internal::AMPL_Environment_Copy(other.impl_, internal::ErrorInfo());
    internal::AMPL_Environment_Destroy(impl_);
    impl_ = newimpl;
    return (*this);
  }

  /**
  \rst
  Constructor with ability to select the location of the AMPL binary.
  Note that if this constructor is used, the automatic lookup for an AMPL
  executable
  will not be executed.
  \endrst
  \param binaryDirectory The directory in which look for the %AMPL Binary
  */
  explicit Environment(fmt::CStringRef binaryDirectory) { impl_ = internal::AMPL_Environment_Create_WithBin(binaryDirectory.c_str(), internal::ErrorInfo()); }

  /**
   * Destructor
   */
  ~Environment() { internal::AMPL_Environment_Destroy(impl_); }

  /**
  * Add an environment variable to the environment, or change its value
  * if already defined
  * \param name name of the environment variable
  * \param value value to be assigned
  */
  void put(fmt::CStringRef name, fmt::CStringRef value) { internal::AMPL_Environment_addEnvironmentVariable(impl_, name.c_str(), value.c_str(), internal::ErrorInfo()); }

  /**
   * Set the location where %AMPLAPI will search for the %AMPL executable
   * \param binaryDirectory Directory
   */
  void setBinDir(fmt::CStringRef binaryDirectory) { internal::AMPL_Environment_setBinaryDirectory(impl_, binaryDirectory.c_str(), internal::ErrorInfo()); }

  /**
  * Get the location where AMPLAPI will search for the %AMPL executable
  */
  std::string getBinDir() const { return std::string(internal::AMPL_Environment_getBinaryDirectory(impl_, internal::ErrorInfo())); }

  /**
  \rst
  Print all variables in the map
  \endrst
  */
  std::string toString() const { return internal::getStringFromDLL(internal::AMPL_Environment_toString(impl_, internal::ErrorInfo())); }
  /**
  Iterator for the map
  */
  typedef internal::CountedIterator<internal::EnvironmentIterator> iterator;

  /**
  Returns an iterator pointing to the first environment variable in the map.
  */
  iterator begin() const { return iterator(internal::AMPL_Environment_begin(impl_, internal::ErrorInfo())); }

  /**
  Returns an iterator pointing to the past-the-end element in the map.
  */
  iterator end() const { return iterator(internal::AMPL_Environment_end(impl_, internal::ErrorInfo())); }

  /**
  Searches the current object for an environment variable called name and
  returns an iterator to it if found, otherwise it returns an iterator to Environment::end.
  */
  iterator find(fmt::CStringRef name) const { return iterator(internal::AMPL_Environment_find(impl_, name.c_str(), internal::ErrorInfo())); }

  /**
  Returns the size of the map.
  */
  std::size_t size() const {  return internal::AMPL_Environment_size(impl_, internal::ErrorInfo());
 }

};
}

#endif  // AMPL_ENVIRONMENT_H
