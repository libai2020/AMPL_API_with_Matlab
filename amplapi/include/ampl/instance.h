#ifndef AMPL_INSTANCE_H
#define AMPL_INSTANCE_H

#include <string>
#include <set>
#include "ampl/ep/instance_ep.h"
#include "ampl/ep/scopedarray.h"
#include "ampl/tuple.h"

#ifdef SWIGJAVA
#define INHERITANCE public
#else
#define INHERITANCE protected
#endif

namespace ampl {
class Entity;
template <class InnerInstance>
class BasicInstance;
template <class InstanceClass>
class BasicEntity;


/**
Base class for instances of modelling entities.
*/
class Instance {
  template <class InstanceClass>
  friend class BasicEntity;

public:
  /**
  Returns the entity that this instance is part of
  */
  Entity entity() const;

  /**
  Returns the key of this instance
  */
  Tuple key() const
  {
    return Tuple(internal::AMPL_Instance_key(impl_, internal::ErrorInfo()));
  }

  /**
  Returns the name of this instance
  */
  std::string name() const {
    return internal::getStringFromDLL(
      internal::AMPL_Instance_name(impl_, internal::ErrorInfo()));
  }

  /**
  Returns a string representation of this instance
  */
  std::string toString() const {
    return internal::getStringFromDLL(
      internal::AMPL_Instance_toString(impl_, internal::ErrorInfo()));
  }

  /**
  Constructor for base class conversions
  */
  template <class InnerInstance>
  Instance(BasicInstance<InnerInstance> instance);
  /**
  Operator for base class conversions
  */
  template <class InnerInstance>
  Instance& operator=(BasicInstance<InnerInstance> instance);


protected:
  internal::Instance* impl_;
  explicit Instance(internal::Instance* instance) { impl_ = instance; }

  /**
  Get a string suffix value
  */
  std::string strvalue(internal::suffix::StringSuffix kind) const {
    internal::PODStringRef returned = internal::AMPL_Instance_StringSuffix(
      impl_, kind, internal::ErrorInfo());
    return std::string(returned.ptr_, returned.size_);
  }

  /**
  Get a double suffix value
  */
  double dblvalue(internal::suffix::NumericSuffix kind) const {
    return internal::AMPL_Instance_getDoubleSuffix(impl_, kind,
                                                   internal::ErrorInfo());
  }

  /**
  Get an integer suffix value
  */
  int intvalue(internal::suffix::NumericSuffix kind) const {
    return internal::AMPL_Instance_getIntSuffix(impl_, kind,
                                                internal::ErrorInfo());
  }
};

/**
Templated class (infrastructure)
*/
template <class InnerInstance>
class BasicInstance : INHERITANCE Instance {
  friend class Instance;

protected:
  typedef InnerInstance Inner;
  InnerInstance* impl() const { return reinterpret_cast<InnerInstance *>(Instance::impl_); }
  using Instance::dblvalue;
  using Instance::strvalue;
  using Instance::intvalue;
  explicit BasicInstance(internal::Instance* i) : Instance(i) {}

public:
  using Instance::key;
  using Instance::toString;
  using Instance::entity;
  using Instance::name;
};

/**
* This class represent an instance of a constraint.
* <p>
* In general, all %AMPL suffixes for a constraint are available through methods
* with the same
* name in this class. See http://www.ampl.com/NEW/suffbuiltin.html
* for a list of the available suffixes.
* <p>
* Note that, since this class represents instances of both algebraic and logical
* constraints, some
* suffixes might not be available for every instance. If a wrong suffix for the
* specific class
* of constraint is accessed, an std::logic_error is thrown.
* <p>
* All the accessors in this class throw an std::runtime_error if the instance
* has been deleted
* in the underlying %AMPL interpreter.
*/
class ConstraintInstance : public BasicInstance<internal::ConstraintInstance> {
public:
  /**
   Drop this constraint instance, corresponding to the %AMPL code:
   `drop constraintname;`.
   */
  void drop() { internal::AMPL_ConstraintInstance_drop(impl(), internal::ErrorInfo()); }

  /**
   * Restore this constraint instance, corresponding to the
   * %AMPL code: `restore constraintname;`.
   */
  void restore() { internal::AMPL_ConstraintInstance_restore(impl(), internal::ErrorInfo()); }

  /**
  * Get the current value of the constraint's body
  */
  double body() const { return dblvalue(internal::suffix::body); }

  /**
  * Get the current %AMPL status (dropped, presolved, or substituted out)
  */
  std::string astatus() const { return strvalue(internal::suffix::astatus); }

  /**
  * Get the index in `_var` of "defined variable" substituted out by
  * the constraint
  */
  int defvar() const { return intvalue(internal::suffix::defvar); }

  /**
  * Get the current initial guess for the constraint's dual variable
  */
  double dinit() const { return dblvalue(internal::suffix::dinit); }

  /**
  * Get the original initial guess for the constraint's dual variable
  */
  double dinit0() const { return dblvalue(internal::suffix::dinit0); }

  /**
  * Get the current value of the constraint's dual variable.
  * <p>
  * Note that dual values are often reset by the underlying %AMPL interpreter by
  * the presolve functionalities triggered by some methods.
  * A possible workaround is to set the option `presolve;` to `false`
  * (see setBoolOption).
  */
  double dual() const { return dblvalue(internal::suffix::dual); }

  /**
  * Get the current value of the constraint's lower bound
  */
  double lb() const { return dblvalue(internal::suffix::lb); }

  /**
  * Get the current value of the constraint's upper bound
  */
  double ub() const { return dblvalue(internal::suffix::ub); }

  /**
  * Get the constraint lower bound sent to the solver (reflecting adjustment
  * for fixed variables)
  */
  double lbs() const { return dblvalue(internal::suffix::lbs); }

  /**
  * Get the constraint upper bound sent to the solver (reflecting adjustment
  * for fixed variables)
  */
  double ubs() const { return dblvalue(internal::suffix::ubs); }

  /**
  * Get the current dual value associated with the lower bound
  */
  double ldual() const { return dblvalue(internal::suffix::ldual); }

  /**
  * Get the current dual value associated with the upper bounds
  */
  double udual() const { return dblvalue(internal::suffix::udual); }

  /**
  * Get the slack at lower bound `body - lb`
  */
  double lslack() const { return dblvalue(internal::suffix::lslack); }

  /**
  * Get the slack at upper bound `ub - body`
  */
  double uslack() const { return dblvalue(internal::suffix::uslack); }

  /**
  * Constraint slack (the lesser of lslack and uslack)
  */
  double slack() const { return dblvalue(internal::suffix::slack); }

  /**
  * Get the solver status (basis status of constraint's %slack or artificial
  * variable)
  */
  std::string sstatus() const { return strvalue(internal::suffix::sstatus); }

  /**
  * Get the %AMPL status if not `in`, otherwise solver status
  */
  std::string status() const { return strvalue(internal::suffix::status); }

  /**
  * Set the value of the dual variable associated to this constraint.
  * Equivalent to the %AMPL statement:
  *
  * `let c := dual;`
  *
  * Note that dual values are often reset by the underlying %AMPL interpreter by
  * the presolve functionalities triggered by some methods.
  * A possible workaround is to set the option `presolve` to `false`
  * (see setBoolOption).
  *
  * \param dual
  *            The value to be assigned to the dual variable
  */
  void setDual(double dual) {
    internal::AMPL_ConstraintInstance_setDual(impl(), dual,
                                              internal::ErrorInfo());
  }

  /**
  * Get the AMPL val suffix. Valid only for logical constraints.
  */
  double val() const { return dblvalue(internal::suffix::val); }

private:
  friend class BasicEntity<ConstraintInstance>;
  friend class internal::EntityWrapper<ConstraintInstance>;
  explicit ConstraintInstance(internal::Instance* ci) : BasicInstance<internal::ConstraintInstance>(ci) {}
};

/**
* Represents an objective instance.
* <p>
* All %AMPL suffixes for an objective are available through methods with the
* same name in this class. See http://www.ampl.com/NEW/suffbuiltin.html for a
* list of the available suffixes.
* <p>
* All the accessors in this class throw an std::runtime_error if the instance
* has been deleted in the underlying AMPL interpreter.
*/
class ObjectiveInstance : public BasicInstance<internal::ObjectiveInstance> {
public:
  /**
  * Get the value of the objective instance
  */
  double value() const { return dblvalue(internal::suffix::value); }

  /**
  * Return the %AMPL status
  */
  std::string astatus() const { return strvalue(internal::suffix::astatus); }

  /**
  * Return the solver status
  */
  std::string sstatus() const { return strvalue(internal::suffix::sstatus); }

  /**
  * Exit code returned by solver after most recent solve with this objective
  */
  int exitcode() const { return intvalue(internal::suffix::exitcode); }

  /**
  * Result message returned by solver after most recent solve with this
  * objective
  */
  std::string message() const { return strvalue(internal::suffix::message); }

  /**
  * Result string returned by solver after most recent solve with this
  * objective
  */
  std::string result() const { return strvalue(internal::suffix::result); }

  /**
  * Drop this objective instance
  */
  void drop() { internal::AMPL_ObjectiveInstance_drop(impl(), internal::ErrorInfo()); }

  /**
  * Restore this objective instance (if it had been dropped, no effect
  * otherwise)
  */
  void restore() { internal::AMPL_ObjectiveInstance_restore(impl(), internal::ErrorInfo()); }

  /**
  * Get the sense of this objective
  * \return true if minimize, false if maximize
  */
  bool minimization() const {
    std::string sense = strvalue(internal::suffix::sense);
    return (sense.compare("minimize") == 0);
  }

private:
  friend class BasicEntity<ObjectiveInstance>;
  friend class internal::EntityWrapper<ObjectiveInstance>;
  explicit ObjectiveInstance(internal::Instance* ci) : BasicInstance<internal::ObjectiveInstance>(ci) {}
};


class DataFrame; // forward declaration for setValues below
/**
* A SetInstance object stores the information regarding a specific instance of
* a set. The instances can be accessed through the function ampl::Set.get
* of the parent entity.
* <p>
* The set contains a collection of ampl::Tuple
* <p>
* Data can be assigned using setValues or using
* AMPL::setData and a DataFrame object.
* <p>
* All the accessors in this class throw an std::runtime_error if
* the instance has been deleted in the underlying %AMPL interpreter.
*/
class SetInstance : public BasicInstance<internal::SetInstance> {
public:
  /**
  Get the number of tuples in this set instance
  */
  std::size_t size() const { return internal::AMPL_SetInstance_size(impl()); }

  /**
  Check wether this set instance contains the specified Tuple
  \param t Tuple to be found
  */
  bool contains(TupleRef t) const { return internal::AMPL_SetInstance_contains(impl(), t.impl(),
    internal::ErrorInfo()); }

  /**
  Class to access the members (tuples) in this set instance
  */
  class MemberRange {
  private:
    const internal::Tuple* members_;
    std::size_t size_;

  public:
    /**
    Constructor
    */
    explicit MemberRange(internal::SetInstance* impl_) : size_(0) {
      members_ =
        internal::AMPL_SetInstance_data(impl_, &size_, internal::ErrorInfo());
    }

    /**
    Iterator
    */
    class iterator : public std::iterator<std::forward_iterator_tag, TupleRef> {
      friend class SetInstance::MemberRange;
      const internal::Tuple* ptr_;
      explicit iterator(const internal::Tuple* ptr) : ptr_(ptr) {}

    public:
      /**
      Dereference operator. Gains access to the ampl::TupleRef which iterators points to.
      */
      TupleRef operator*() const { return TupleRef(*ptr_); }

      /**
      Postfix increment
      */
      iterator& operator++() {
        ptr_++;
        return *this;
      }

      /**
      Increment
      */
      iterator operator++(int) {
        iterator clone(*this);
        ptr_++;
        return clone;
      }

      /**
      Equality operator
      */
      bool operator==(const iterator& other) const { return (ptr_ == other.ptr_); }

      /**
      Inequality operator
      */
      bool operator!=(const iterator& other) const { return !(*this == other); }
    };

    /**
    Returns an iterator to the beginning of the members
    collection
    */
    iterator begin() const { return iterator(members_); }

    /**
    Returns an iterator to the first item after the end of
    the collection
    */
    iterator end() const { return iterator(members_ + size_); }
  };

  /**
  Get all members (tuples) in this set instance
  */
  MemberRange members() const { return MemberRange(impl()); }

  /**
  Set the tuples in this set instance using a flattened array.
  The size of the array must be a multiple of the arity of this
  set instance, and each `arity` elements in the array will be
  grouped into a Tuple.
  \param objects An array of doubles or strings to be grouped into tuples
  \param n The number of objects in the array
  */
  void setValues(internal::Args objects, std::size_t n) {
    internal::AMPL_SetInstance_setValues_Arg(impl(), objects.data(), n,
                                             internal::ErrorInfo());
  }

  /**
  Set the tuples in this set instance

  \param objects An array of tuples
  \param n The number of tuples in the array
  */
  void setValues(const Tuple objects[], std::size_t n) {
    std::vector<internal::Tuple> toPass =
      internal::getInternalTupleArray(objects, n);
    internal::AMPL_SetInstance_setValues_Tuple(impl(), &toPass[0],
                                               n, internal::ErrorInfo());
  }

  /**
  \rst

  Set the values in this set instance to the indexing values of
  the passed DataFrame. The number of indexing columns of the
  parameter must be equal to the arity of this set instance.

  For example, considering the following AMPL entities and corresponding
  C++ objects::

  set A := 1..2;
  param p{i in A} := i+10;
  set AA;

  The following is valid::

  ampl::Set A = ampl.getSet("A"), AA = ampl.getSet("AA");
  AA.setValues(A.getValues()); // A has now the members {1, 2}

  \endrst
  */
  void setValues(DataFrame data);
  /**
  Get all the tuples in this set instance in a DataFrame
  */
  DataFrame getValues() const;

private:
  friend class BasicEntity<SetInstance>;
  friend class internal::EntityWrapper<SetInstance>;
  explicit SetInstance(internal::Instance* ci) : BasicInstance<internal::SetInstance>(ci) {}
};

/**
* A decision variable instance. Each member of this class belongs to a single
* Variable.
* Note that accessors available here are replicated at Variable level for ease
* of use
* when dealing with scalar variables.
* <p>
* All %AMPL suffixes for an algebraic variable are available through methods with
* the same
* name in this class. See http://www.ampl.com/NEW/suffbuiltin.html
* for a list of the available suffixes.
* <p>
* All the accessors in this class throw an std::runtime_error if the instance
* has been deleted
* in the underlying %AMPL interpreter.
*/
class VariableInstance : public BasicInstance<internal::VariableInstance> {
public:
  /**
  * Get the current value of this variable
  */
  double value() const { return dblvalue(internal::suffix::value); }

  /**
  * Fix all instances of this variable  to their current value
  */
  void fix() { internal::AMPL_VariableInstance_fix(impl(), internal::ErrorInfo()); }

  /**
  * Fix all instances of this variable to the specified value
  */
  void fix(double value) {
    internal::AMPL_VariableInstance_fixToValue(impl(), value,
                                               internal::ErrorInfo());
  }

  /**
  * Unfix this variable instances
  */
  void unfix() { internal::AMPL_VariableInstance_unfix(impl(), internal::ErrorInfo()); }

  // *************************************** SCALAR VARIABLES
  // *****************************************
  /**
  Set the current value of this variable (does not fix it),
  equivalent to the %AMPL command `let`
  \param value Value to be set
  */
  void setValue(double value) {
    internal::AMPL_VariableInstance_setValue(impl(), value,
                                             internal::ErrorInfo());
  }

  /**
  Get the %AMPL status (fixed, presolved, or substituted out)
  */
  std::string astatus() const { return strvalue(internal::suffix::astatus); }

  /**
  * Get the index in `_con` of "defining constraint" used to substitute variable
  * out
  */
  int defeqn() const { return intvalue(internal::suffix::defeqn); }

  /**
  * Get the dual value on defining constraint of variable substituted out
  */
  double dual() const { return dblvalue(internal::suffix::dual); }

  /**
  * Get the current initial guess
  */
  double init() const { return dblvalue(internal::suffix::init); }

  /**
  * Get the original initial guess (set by `:=` or`default` or by a data
  * statement)
  */
  double init0() const { return dblvalue(internal::suffix::init0); }

  /**
  * \rststar
  * Returns the current lower bound. See :ref:`secVariableSuffixesNotes`.
  * \endrststar
  */
  double lb() const { return dblvalue(internal::suffix::lb); }

  /**
  * \rststar
  * Returns the current upper bound. See :ref:`secVariableSuffixesNotes`.
  * \endrststar
  */
  double ub() const { return dblvalue(internal::suffix::ub); }

  /**
  * Returns the initial lower bounds, from the var declaration
  */
  double lb0() const { return dblvalue(internal::suffix::lb0); }

  /**
  * Returns the initial upper bound, from the var declaration
  */
  double ub0() const { return dblvalue(internal::suffix::ub0); }

  /**
  * Returns the weaker lower bound from %AMPL's presolve phase
  */
  double lb1() const { return dblvalue(internal::suffix::lb1); }

  /**
  * Returns the weaker upper bound from %AMPL's presolve phase
  */
  double ub1() const { return dblvalue(internal::suffix::ub1); }

  /**
  * Returns the stronger lower bound from %AMPL's presolve phase
  */
  double lb2() const { return dblvalue(internal::suffix::lb2); }

  /**
  * Returns the stronger upper bound from %AMPL's presolve phase
  */
  double ub2() const { return dblvalue(internal::suffix::ub2); }

  /**
  * Returns the reduced cost at lower bound
  */
  double lrc() const { return dblvalue(internal::suffix::lrc); }

  /**
  * Returns the reduced cost at upper bound
  */
  double urc() const { return dblvalue(internal::suffix::urc); }

  /**
  * \rststar
  * Return the slack at lower bound (``val - lb``). See :ref:`secVariableSuffixesNotes`.
  * \endrststar
  */
  double lslack() const { return dblvalue(internal::suffix::lslack); }

  /**
  * \rststar
  *  Return the slack at upper bound (``ub - val``). See :ref:`secVariableSuffixesNotes`.
  * \endrststar
  */
  double uslack() const { return dblvalue(internal::suffix::uslack); }

  /**
  * Get the reduced cost (at the nearer bound)
  */
  double rc() const { return dblvalue(internal::suffix::rc); }

  /**
  * \rststar
  * Returns the bound slack which is the lesser of lslack() and
  * uslack(). See :ref:`secVariableSuffixesNotes`.
  * \endrststar
  */
  double slack() const { return dblvalue(internal::suffix::slack); }

  /**
  * Solver status (basis status of variable)
  */
  std::string sstatus() const { return strvalue(internal::suffix::sstatus); }

  /**
  * %AMPL status if not `in`, otherwise solver status
  */
  std::string status() const { return strvalue(internal::suffix::status); }

  /**
   Returns a string representation of this VariableInstance object.
   The format is as follows:

   \rst
   ::

     'var' name attrs ';'
   \endrst

   where ``name`` is the string returned by the
   VariableInstance::name()  method and ``attrs``
   represent attributes similar to those used in variable declarations.
   <p>
   If the lower bound (``lb``) is equal to the upper bound (``ub``), the
   attributes contain ``= lb``.
   <p>
   If the lower bound is not equal to the upper bound and
  ``Double.NEGATIVE_INFINITY`` , the attributes contain ``>= lb``.
   <p>
   If the upper bound is not equal to the lower bound and
  ``Double.POSITIVE_INFINITY``, the attributes contain ``&lt;= ub``.

   <p>
   If the variable is integer, the attributes contain ``integer``.
   <p>
   If the variable is binary, the attributes contain ``binary``.
  */
  std::string toString() const { return BasicInstance<internal::VariableInstance>::toString(); }

private:
  friend class BasicEntity<VariableInstance>;
  friend class internal::EntityWrapper<VariableInstance>;
  explicit VariableInstance(internal::Instance* vi) : BasicInstance<internal::VariableInstance>(vi) {}
};

/**
* A table instance of an indexed table.
* Instances of the table can be read from or written to using TableInstance::read()
* and TableInstance::write().
* <p>
* All the accessors in this class throw an std::runtime_error if the instance
* has been deleted in the underlying %AMPL interpreter.
*/
class TableInstance : public BasicInstance<internal::TableInstance> {

private:
  friend class BasicEntity<TableInstance>;
  friend class internal::EntityWrapper<TableInstance>;
  explicit TableInstance(internal::Instance* ti) : BasicInstance<internal::TableInstance>(ti) {}

public:
  /**
  Read the current table instance, corresponding to the %AMPL code:
  `read table tablename[tableindex];`.
 */
  void read() { internal::AMPL_TableInstance_read(impl(), internal::ErrorInfo()); }

  /**
  Write the current table instance, corresponding to the %AMPL code:
  `write table tablename[tableindex];`.
 */
  void write() { internal::AMPL_TableInstance_write(impl(), internal::ErrorInfo()); }
};



template <class InnerInstance>
inline Instance::Instance(BasicInstance<InnerInstance> instance)
  : impl_(instance.impl_) {}

template <class InnerInstance>
inline Instance& Instance::operator=(BasicInstance<InnerInstance> instance) {
  impl_ = instance.impl_;
  return *this;
}
} // namespace ampl
#endif // AMPL_INSTANCE_H
