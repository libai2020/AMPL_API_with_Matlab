#ifndef AMPL_ENTITYMAP_H
#define AMPL_ENTITYMAP_H

#include <iterator>
#include "ampl/ep/entitymap_ep.h"

#include "ampl/entity.h"

namespace ampl {
/**
* Represents a synchronised list of %AMPL entities. It can be obtained using the functions AMPL::getVariables(),
* AMPL::getConstraints(), AMPL::getSets(), AMPL::getObjectives(), AMPL::getParameters().
* <p>
* The collection cannot be modified by the user (entities cannot be added nor deleted) and is linked to an AMPL object.
* When the corresponding %AMPL entities are modified (through AMPL::eval() or any other operation which influences the number of entities),
* the collection is automatically invalidated. It is updated lazily at the next access.
* <p>
* If the corresponding AMPL object is not running anymore, or it is null, an exception is thrown on all operations.
*/
template <class EntityClass> class EntityMap {
  friend class AMPL;
  typedef typename EntityClass::Inner EntityInner;

public:
  /**
  Iterator used to access the entities in the list
  \sa begin(), end() and find()
  */
  class iterator : public std::iterator<std::forward_iterator_tag, EntityClass> {

    // A proxy used for implementing operator->.
    class Proxy {
    private:
      EntityClass inner_;

    public:
      // Constructor
      explicit Proxy(EntityInner* e)
        : inner_(e) {}

      // Arrow operator
      const EntityClass* operator->() const { return &inner_; }
    };

  public:
    iterator() : data_(NULL) {}

    /**
    * Regular constructor
    */
    explicit iterator(internal::EntityMap_RefPointer<EntityInner>* it)
      : data_(it) {}

    /**
    * Copy constructor.
    */
    iterator(const iterator& other) {
      data_ = other.data_;
      data_->count_++;
    }

    /**
    Destructor
    */
    ~iterator() { destroy(); }

    /**
    * Equals comparison operator
    */
    bool operator==(const iterator& other) const { return internal::EntityFunctions<EntityClass>::equal(data_, other.data_); }

    /**
    * Not-equals comparison operator
    */
    bool operator!=(const iterator& other) const { return !(*this == other); }

    /**
    * Dereference operator
    * \return The entity this iterator is currently referring to
    */
    EntityClass operator*() const { return EntityClass(internal::EntityFunctions<EntityClass>::second(data_)); }

    /**
    Arrow operator
    */
    Proxy operator->() const { return Proxy(internal::EntityFunctions<EntityClass>::second(data_)); }

    /**
    Assignment operator
    */
    iterator& operator=(const iterator& other) {
      if (this != &other) {
        destroy();
        data_ = other.data_;
        data_->count_++;
      }
      return *this;
    }

    /**
    * Prefix increment operator (e.g., ++it)
    */
    iterator& operator++() {
      internal::EntityFunctions<EntityClass>::increment(data_);
      return *this;
    }

    /**
    * Postfix increment operator (e.g., it++)
    */
    iterator operator++(int) {
      // Use operator++()
      const iterator old(*this);
      ++(*this);
      return old;
    }

  private:
    internal::EntityMap_RefPointer<EntityInner>* data_;

    void destroy() {
      if (data_ != NULL) {
        data_->count_--;
        if (data_->count_ == 0)
          internal::EntityFunctions<EntityClass>::delete_iterator(data_);
      }
    }
  };

  /**
  Entity access
  Returns the entity identified by the specified name.
  \param name Name of the entity to be found
  \return The entity with the corresponding name
  \throws An std::out_of_range exception if the specified parameter does not exist
  */
  EntityClass operator[](fmt::CStringRef name) const {
    return EntityClass(
      internal::EntityFunctions<EntityClass>::getMap(impl_, name.c_str()));
  }

  /**
  * Get the number of items in the collection
  */
  std::size_t size() const { return internal::EntityFunctions<EntityClass>::size(impl_); }

  /**
  Return an iterator to the beginning of this collection. Use together
  with end() to iterate through the contents of this list.
  \rst
  An example, printing the names of all the variables defined in the AMPL object named ``ampl``::

    for (ampl::Variable v: ampl.getVariables())
      std::cout << v.name() << "\n";
  \endrst
  */
  iterator begin() const { return iterator(internal::EntityFunctions<EntityClass>::begin(impl_)); }

  /**
  Return iterator to the end of this collection
  */
  iterator end() const { return iterator(internal::EntityFunctions<EntityClass>::end(impl_)); }

  /**

  Searches the container for an entity with the specified
   name and returns an iterator to it if found, otherwise
    it returns an iterator to end().

  \rst

  An example which checks if the variable ``x`` is defined in the
  AMPL object called ``ampl``::

    ampl::EntityMap<Variable> vars = ampl.getVariables();
    ampl::EntityMap<Variable>::iterator it = vars.find("x");
    if(it == vars.end())
      std::cout << "Variable x does not exist\n");

  \endrst

  \param name The name of the entity to be found
  \return An iterator to the entity, if an Entity with specified key is
  found, or end() otherwise.

  */
  iterator find(fmt::CStringRef name) const { return iterator(internal::EntityFunctions<EntityClass>::find(impl_, name.c_str())); }

protected:
  internal::EntityMap<EntityInner>* impl_;

private:
  explicit EntityMap(internal::EntityMap<EntityInner>* impl) { impl_ = impl; }
};
}
#endif // AMPL_ENTITYMAP_H
