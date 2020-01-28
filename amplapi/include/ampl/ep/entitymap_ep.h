#ifndef AMPL_ENTITYMAP_EP_H
#define AMPL_ENTITYMAP_EP_H

#include "ampl/ep/declarations.h"
#include "ampl/ep/errorinfo_ep.h"
#include "ampl/ep/error_information.h"

#include <map>
#include <string>

namespace ampl {
class Variable;
class Constraint;
class Objective;
class Parameter;
class Set;
class Table;

namespace internal {

  template <class EntityClass> struct EntityMap_RefPointer {
    std::size_t count_;
    typename std::map<std::string, EntityClass *>::const_iterator it_;
  };

  template <class EntityClass> class EntityMap;
  class Variable;
  class Objective;
  class Parameter;
  class Set;
  class Constraint;
  class Table;
  

  typedef std::map<std::string, Variable *>::iterator VariableIterator;
  typedef std::map<std::string, Constraint *>::iterator ConstraintIterator;
  typedef std::map<std::string, Set *>::iterator SetIterator;
  typedef std::map<std::string, Objective *>::iterator ObjectiveIterator;
  typedef std::map<std::string, Parameter *>::iterator ParameterIterator;
  typedef std::map<std::string, Table *>::iterator TableIterator;

  extern "C" {
    AMPLAPI Variable *AMPL_EntityMap_Variable_get(EntityMap<Variable> *impl,
      const char *name);
    AMPLAPI std::size_t AMPL_EntityMap_Variable_size(EntityMap<Variable> *impl);
    AMPLAPI EntityMap_RefPointer<Variable> *
      AMPL_EntityMap_iterator_Variable_begin(EntityMap<Variable> *impl,
        ErrorInformation *errorInfo);
    AMPLAPI EntityMap_RefPointer<Variable> *
      AMPL_EntityMap_iterator_Variable_end(EntityMap<Variable> *impl,
        ErrorInformation *errorInfo);
    AMPLAPI EntityMap_RefPointer<Variable> *AMPL_EntityMap_iterator_Variable_find(
      EntityMap<Variable> *impl, const char *name, ErrorInformation *errorInfo);
    AMPLAPI bool
      AMPL_EntityMap_iterator_Variable_equal(EntityMap_RefPointer<Variable> *it1,
        EntityMap_RefPointer<Variable> *it2);
    AMPLAPI void
      AMPL_EntityMap_iterator_Variable_delete(EntityMap_RefPointer<Variable> *it);
    AMPLAPI void
      AMPL_EntityMap_iterator_Variable_increment(EntityMap_RefPointer<Variable> *it,
        ErrorInformation *errorInfo);
    AMPLAPI Variable*
      AMPL_EntityMap_iterator_Variable_second(EntityMap_RefPointer<Variable> *it,
        ErrorInformation *errorInfo);

    AMPLAPI Objective *AMPL_EntityMap_Objective_get(EntityMap<Objective> *impl,
      const char *name);
    AMPLAPI std::size_t AMPL_EntityMap_Objective_size(EntityMap<Objective> *impl);
    AMPLAPI EntityMap_RefPointer<Objective> *
      AMPL_EntityMap_iterator_Objective_begin(EntityMap<Objective> *impl,
        ErrorInformation *errorInfo);
    AMPLAPI EntityMap_RefPointer<Objective> *
      AMPL_EntityMap_iterator_Objective_end(EntityMap<Objective> *impl,
        ErrorInformation *errorInfo);
    AMPLAPI EntityMap_RefPointer<Objective> *
      AMPL_EntityMap_iterator_Objective_find(EntityMap<Objective> *impl,
        const char *name, ErrorInformation *errorInfo);
    AMPLAPI bool
      AMPL_EntityMap_iterator_Objective_equal(EntityMap_RefPointer<Objective> *it1,
        EntityMap_RefPointer<Objective> *it2);
    AMPLAPI void
      AMPL_EntityMap_iterator_Objective_delete(EntityMap_RefPointer<Objective> *it);
    AMPLAPI void
      AMPL_EntityMap_iterator_Objective_increment(EntityMap_RefPointer<Objective> *it,
        ErrorInformation *errorInfo);
    AMPLAPI Objective*
      AMPL_EntityMap_iterator_Objective_second(EntityMap_RefPointer<Objective> *it,
        ErrorInformation *errorInfo);

    AMPLAPI Set *AMPL_EntityMap_Set_get(EntityMap<Set> *impl, const char *name);
    AMPLAPI std::size_t AMPL_EntityMap_Set_size(EntityMap<Set> *impl);
    AMPLAPI EntityMap_RefPointer<Set> *
      AMPL_EntityMap_iterator_Set_begin(EntityMap<Set> *impl,
        ErrorInformation *errorInfo);
    AMPLAPI EntityMap_RefPointer<Set> *
      AMPL_EntityMap_iterator_Set_end(EntityMap<Set> *impl,
        ErrorInformation *errorInfo);
    AMPLAPI EntityMap_RefPointer<Set> *
      AMPL_EntityMap_iterator_Set_find(EntityMap<Set> *impl, const char *name,
        ErrorInformation *errorInfo);
    AMPLAPI bool AMPL_EntityMap_iterator_Set_equal(EntityMap_RefPointer<Set> *it1,
      EntityMap_RefPointer<Set> *it2);
    AMPLAPI void AMPL_EntityMap_iterator_Set_delete(EntityMap_RefPointer<Set> *it);
    AMPLAPI void
      AMPL_EntityMap_iterator_Set_increment(EntityMap_RefPointer<Set> *it,
        ErrorInformation *errorInfo);
    AMPLAPI Set*
      AMPL_EntityMap_iterator_Set_second(EntityMap_RefPointer<Set> *it,
        ErrorInformation *errorInfo);

    AMPLAPI Parameter *AMPL_EntityMap_Parameter_get(EntityMap<Parameter> *impl,
      const char *name);
    AMPLAPI std::size_t AMPL_EntityMap_Parameter_size(EntityMap<Parameter> *impl);
    AMPLAPI EntityMap_RefPointer<Parameter> *
      AMPL_EntityMap_iterator_Parameter_begin(EntityMap<Parameter> *impl,
        ErrorInformation *errorInfo);
    AMPLAPI EntityMap_RefPointer<Parameter> *
      AMPL_EntityMap_iterator_Parameter_end(EntityMap<Parameter> *impl,
        ErrorInformation *errorInfo);
    AMPLAPI EntityMap_RefPointer<Parameter> *
      AMPL_EntityMap_iterator_Parameter_find(EntityMap<Parameter> *impl,
        const char *name, ErrorInformation *errorInfo);
    AMPLAPI bool
      AMPL_EntityMap_iterator_Parameter_equal(EntityMap_RefPointer<Parameter> *it1,
        EntityMap_RefPointer<Parameter> *it2);
    AMPLAPI void
      AMPL_EntityMap_iterator_Parameter_delete(EntityMap_RefPointer<Parameter> *it);
    AMPLAPI void
      AMPL_EntityMap_iterator_Parameter_increment(EntityMap_RefPointer<Parameter> *it, ErrorInformation *errorInfo);
    AMPLAPI Parameter*
      AMPL_EntityMap_iterator_Parameter_second(EntityMap_RefPointer<Parameter> *it,
        ErrorInformation *errorInfo);

    AMPLAPI Table *AMPL_EntityMap_Table_get(EntityMap<Table> *impl,
      const char *name);
    AMPLAPI std::size_t AMPL_EntityMap_Table_size(EntityMap<Table> *impl);
    AMPLAPI EntityMap_RefPointer<Table> *
      AMPL_EntityMap_iterator_Table_begin(EntityMap<Table> *impl,
        ErrorInformation *errorInfo);
    AMPLAPI EntityMap_RefPointer<Table> *
      AMPL_EntityMap_iterator_Table_end(EntityMap<Table> *impl,
        ErrorInformation *errorInfo);
    AMPLAPI EntityMap_RefPointer<Table> *
      AMPL_EntityMap_iterator_Table_find(EntityMap<Table> *impl,
        const char *name, ErrorInformation *errorInfo);
    AMPLAPI bool
      AMPL_EntityMap_iterator_Table_equal(EntityMap_RefPointer<Table> *it1,
        EntityMap_RefPointer<Table> *it2);
    AMPLAPI void
      AMPL_EntityMap_iterator_Table_delete(EntityMap_RefPointer<Table> *it);
    AMPLAPI void
      AMPL_EntityMap_iterator_Table_increment(EntityMap_RefPointer<Table> *it,
        ErrorInformation *errorInfo);
    AMPLAPI Table*
      AMPL_EntityMap_iterator_Table_second(EntityMap_RefPointer<Table> *it,
        ErrorInformation *errorInfo);



    AMPLAPI Constraint *AMPL_EntityMap_Constraint_get(EntityMap<Constraint> *impl,
      const char *name);
    AMPLAPI std::size_t AMPL_EntityMap_Constraint_size(EntityMap<Constraint> *impl);
    AMPLAPI EntityMap_RefPointer<Constraint> *
      AMPL_EntityMap_iterator_Constraint_begin(EntityMap<Constraint> *impl,
        ErrorInformation *errorInfo);
    AMPLAPI EntityMap_RefPointer<Constraint> *
      AMPL_EntityMap_iterator_Constraint_end(EntityMap<Constraint> *impl,
        ErrorInformation *errorInfo);
    AMPLAPI EntityMap_RefPointer<Constraint> *
      AMPL_EntityMap_iterator_Constraint_find(EntityMap<Constraint> *impl,
        const char *name, ErrorInformation *errorInfo);
    AMPLAPI bool
      AMPL_EntityMap_iterator_Constraint_equal(EntityMap_RefPointer<Constraint> *it1,
        EntityMap_RefPointer<Constraint> *it2);
    AMPLAPI void
      AMPL_EntityMap_iterator_Constraint_delete(EntityMap_RefPointer<Constraint> *it);
    AMPLAPI void AMPL_EntityMap_iterator_Constraint_increment(
      EntityMap_RefPointer<Constraint> *it, ErrorInformation *errorInfo);
    AMPLAPI Constraint*
      AMPL_EntityMap_iterator_Constraint_second(EntityMap_RefPointer<Constraint> *it,
        ErrorInformation *errorInfo);
  } // C Linkage

  template <typename EntityPrivate> struct EntityFunctions;
  
  template <> struct EntityFunctions<ampl::Variable> {
    static Variable *getMap(EntityMap<Variable> *impl, const char *name) {
      return AMPL_EntityMap_Variable_get(impl, name);
    }

    static std::size_t size(EntityMap<Variable> *impl) {
      return AMPL_EntityMap_Variable_size(impl);
    }

    static internal::EntityMap_RefPointer<Variable> *
      begin(EntityMap<Variable> *impl) {
      return AMPL_EntityMap_iterator_Variable_begin(impl, ErrorInfo());
    }
    static internal::EntityMap_RefPointer<Variable> *
      end(EntityMap<Variable> *impl) {
      return AMPL_EntityMap_iterator_Variable_end(impl, ErrorInfo());
    }
    static internal::EntityMap_RefPointer<Variable> *
      find(EntityMap<Variable> *impl, const char *name) {
      return AMPL_EntityMap_iterator_Variable_find(impl, name, ErrorInfo());
    }
    static bool equal(internal::EntityMap_RefPointer<Variable> *it1,
      internal::EntityMap_RefPointer<Variable> *it2) {
      return AMPL_EntityMap_iterator_Variable_equal(it1, it2);
    }
    static void delete_iterator(internal::EntityMap_RefPointer<Variable> *it) {
      AMPL_EntityMap_iterator_Variable_delete(it);
    }
    static void increment(internal::EntityMap_RefPointer<Variable> *it) {
      AMPL_EntityMap_iterator_Variable_increment(it, ErrorInfo());
    }
    static Variable* second(internal::EntityMap_RefPointer<Variable> *it) {
      return AMPL_EntityMap_iterator_Variable_second(it, ErrorInfo());
    }
  };

  template <> struct EntityFunctions<ampl::Constraint> {
    static Constraint *getMap(EntityMap<Constraint> *impl, const char *name) {
      return AMPL_EntityMap_Constraint_get(impl, name);
    }
    static std::size_t size(EntityMap<Constraint> *impl) {
      return AMPL_EntityMap_Constraint_size(impl);
    }
    static EntityMap_RefPointer<Constraint> *begin(EntityMap<Constraint> *impl) {
      return AMPL_EntityMap_iterator_Constraint_begin(impl, ErrorInfo());
    }
    static EntityMap_RefPointer<Constraint> *end(EntityMap<Constraint> *impl) {
      return AMPL_EntityMap_iterator_Constraint_end(impl, ErrorInfo());
    }
    static EntityMap_RefPointer<Constraint> *find(EntityMap<Constraint> *impl,
      const char *name) {
      return AMPL_EntityMap_iterator_Constraint_find(impl, name, ErrorInfo());
    }
    static bool equal(EntityMap_RefPointer<Constraint> *it1,
      EntityMap_RefPointer<Constraint> *it2) {
      return AMPL_EntityMap_iterator_Constraint_equal(it1, it2);
    }
    static void delete_iterator(EntityMap_RefPointer<Constraint> *it) {
      AMPL_EntityMap_iterator_Constraint_delete(it);
    }
    static void increment(EntityMap_RefPointer<Constraint> *it) {
      AMPL_EntityMap_iterator_Constraint_increment(it, ErrorInfo());
    }
    static Constraint* second(internal::EntityMap_RefPointer<Constraint> *it) {
      return AMPL_EntityMap_iterator_Constraint_second(it, ErrorInfo());
    }
  };

  template <> struct EntityFunctions<ampl::Parameter> {
    static Parameter *getMap(EntityMap<Parameter> *impl, const char *name) {
      return AMPL_EntityMap_Parameter_get(impl, name);
    }
    static std::size_t size(EntityMap<Parameter> *impl) {
      return AMPL_EntityMap_Parameter_size(impl);
    }
    static EntityMap_RefPointer<Parameter> *begin(EntityMap<Parameter> *impl) {
      return AMPL_EntityMap_iterator_Parameter_begin(impl, ErrorInfo());
    }
    static EntityMap_RefPointer<Parameter> *end(EntityMap<Parameter> *impl) {
      return AMPL_EntityMap_iterator_Parameter_end(impl, ErrorInfo());
    }
    static EntityMap_RefPointer<Parameter> *find(EntityMap<Parameter> *impl,
      const char *name) {
      return AMPL_EntityMap_iterator_Parameter_find(impl, name, ErrorInfo());
    }
    static bool equal(EntityMap_RefPointer<Parameter> *it1,
      EntityMap_RefPointer<Parameter> *it2) {
      return AMPL_EntityMap_iterator_Parameter_equal(it1, it2);
    }
    static void delete_iterator(EntityMap_RefPointer<Parameter> *it) {
      AMPL_EntityMap_iterator_Parameter_delete(it);
    }
    static void increment(EntityMap_RefPointer<Parameter> *it) {
      AMPL_EntityMap_iterator_Parameter_increment(it, ErrorInfo());
    }
    static Parameter* second(internal::EntityMap_RefPointer<Parameter> *it) {
      return AMPL_EntityMap_iterator_Parameter_second(it, ErrorInfo());
    }
  };

  template <> struct EntityFunctions<ampl::Set> {
    static Set *getMap(EntityMap<Set> *impl, const char *name) {
      return AMPL_EntityMap_Set_get(impl, name);
    }
    static std::size_t size(EntityMap<Set> *impl) {
      return AMPL_EntityMap_Set_size(impl);
    }
    static EntityMap_RefPointer<Set> *begin(EntityMap<Set> *impl) {
      return AMPL_EntityMap_iterator_Set_begin(impl, ErrorInfo());
    }
    static EntityMap_RefPointer<Set> *end(EntityMap<Set> *impl) {
      return AMPL_EntityMap_iterator_Set_end(impl, ErrorInfo());
    }
    static EntityMap_RefPointer<Set> *find(EntityMap<Set> *impl, const char *name) {
      return AMPL_EntityMap_iterator_Set_find(impl, name, ErrorInfo());
    }
    static bool equal(EntityMap_RefPointer<Set> *it1,
      EntityMap_RefPointer<Set> *it2) {
      return AMPL_EntityMap_iterator_Set_equal(it1, it2);
    }
    static void delete_iterator(EntityMap_RefPointer<Set> *it) {
      AMPL_EntityMap_iterator_Set_delete(it);
    }
    static void increment(EntityMap_RefPointer<Set> *it) {
      AMPL_EntityMap_iterator_Set_increment(it, ErrorInfo());
    }
    static Set* second(internal::EntityMap_RefPointer<Set> *it) {
      return AMPL_EntityMap_iterator_Set_second(it, ErrorInfo());
    }
  };

  template <> struct EntityFunctions<ampl::Objective> {
    static Objective *getMap(EntityMap<Objective> *impl, const char *name) {
      return AMPL_EntityMap_Objective_get(impl, name);
    }
    static std::size_t size(EntityMap<Objective> *impl) {
      return AMPL_EntityMap_Objective_size(impl);
    }
    static EntityMap_RefPointer<Objective> *begin(EntityMap<Objective> *impl) {
      return AMPL_EntityMap_iterator_Objective_begin(impl, ErrorInfo());
    }
    static EntityMap_RefPointer<Objective> *end(EntityMap<Objective> *impl) {
      return AMPL_EntityMap_iterator_Objective_end(impl, ErrorInfo());
    }
    static EntityMap_RefPointer<Objective> *find(EntityMap<Objective> *impl,
      const char *name) {
      return AMPL_EntityMap_iterator_Objective_find(impl, name, ErrorInfo());
    }
    static bool equal(EntityMap_RefPointer<Objective> *it1,
      EntityMap_RefPointer<Objective> *it2) {
      return AMPL_EntityMap_iterator_Objective_equal(it1, it2);
    }
    static void delete_iterator(EntityMap_RefPointer<Objective> *it) {
      AMPL_EntityMap_iterator_Objective_delete(it);
    }
    static void increment(EntityMap_RefPointer<Objective> *it) {
      AMPL_EntityMap_iterator_Objective_increment(it, ErrorInfo());
    }
    static Objective* second(internal::EntityMap_RefPointer<Objective> *it) {
      return AMPL_EntityMap_iterator_Objective_second(it, ErrorInfo());
    }
  };

  template <> struct EntityFunctions<ampl::Table> {
    static Table *getMap(EntityMap<Table> *impl, const char *name) {
      return AMPL_EntityMap_Table_get(impl, name);
    }
    static std::size_t size(EntityMap<Table> *impl) {
      return AMPL_EntityMap_Table_size(impl);
    }
    static EntityMap_RefPointer<Table> *begin(EntityMap<Table> *impl) {
      return AMPL_EntityMap_iterator_Table_begin(impl, ErrorInfo());
    }
    static EntityMap_RefPointer<Table> *end(EntityMap<Table> *impl) {
      return AMPL_EntityMap_iterator_Table_end(impl, ErrorInfo());
    }
    static EntityMap_RefPointer<Table> *find(EntityMap<Table> *impl,
      const char *name) {
      return AMPL_EntityMap_iterator_Table_find(impl, name, ErrorInfo());
    }
    static bool equal(EntityMap_RefPointer<Table> *it1,
      EntityMap_RefPointer<Table> *it2) {
      return AMPL_EntityMap_iterator_Table_equal(it1, it2);
    }
    static void delete_iterator(EntityMap_RefPointer<Table> *it) {
      AMPL_EntityMap_iterator_Table_delete(it);
    }
    static void increment(EntityMap_RefPointer<Table> *it) {
      AMPL_EntityMap_iterator_Table_increment(it, ErrorInfo());
    }
    static Table* second(internal::EntityMap_RefPointer<Table> *it) {
      return AMPL_EntityMap_iterator_Table_second(it, ErrorInfo());
    }
  };
}
}

#endif // AMPL_ENTITYMAP_EP_H
