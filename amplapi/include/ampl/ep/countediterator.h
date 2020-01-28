#ifndef AMPL_COUNTEDITERATOR_H
#define AMPL_COUNTEDITERATOR_H

#include <iterator>
namespace ampl {
namespace internal {
  template <class FunctionClass>
  class CountedIterator
    : public std::iterator<std::forward_iterator_tag,
    typename FunctionClass::ValueType> {

    // A proxy used for implementing operator->.
    class Proxy {
    private:
      typename FunctionClass::ValueType inner_;

    public:
      explicit Proxy(const typename FunctionClass::ValueType &e)
        : inner_(e) {}

      const typename FunctionClass::ValueType *operator->() const { return &inner_; }
    };

  public:

    /**
    * Regular constructor
    */
    explicit CountedIterator(typename FunctionClass::ReferencePointer it) : data_(it) {}

    CountedIterator() : data_(NULL) {}
    /**
    * Copy constructor.
    */
    CountedIterator(const CountedIterator &other) {
      data_ = other.data_;
      data_->count++;
    }

    ~CountedIterator() { dispose(); }

    /**
    * Equals comparison operator
    */
    bool operator==(const CountedIterator &other) const {
      return FunctionClass::equal(data_, other.data_);
    }

    /**
    * Not-equals comparison operator
    */
    bool operator!=(const CountedIterator &other) const {
      return !(*this == other);
    }

    /**
    * Dereference operator
    * \return the value of the element this iterator is currently pointing at
    */
    typename FunctionClass::ValueType operator*() const {
      return FunctionClass::getPointer(data_);
    }

    /**
    * Arrow operator
    * \return the value of the element this iterator is currently pointing at
    */
    Proxy operator->() const {
      return Proxy(FunctionClass::getPointer(data_));
    }

    CountedIterator &operator=(const CountedIterator &other) {
      if (this != &other) {
        dispose();
        data_ = other.data_;
        data_->count++;
      }
      return *this;
    }
    /**
    * Prefix increment operator (e.g., ++it)
    */
    CountedIterator &operator++() {
      // Up to you to define: move iterator forwards
      FunctionClass::increment(data_);
      return *this;
    }

    /**
    * Postfix increment operator (e.g., it++)
    */
    CountedIterator operator++(int) {
      // Use operator++()
      const CountedIterator old(*this);
      ++(*this);
      return old;
    }

  private:
    void dispose() {
      if (data_ != NULL) {
        data_->count--;
        if (data_->count == 0)
          FunctionClass::dispose(data_);
      }
    }
    typename FunctionClass::ReferencePointer data_;


  };
}
}
#endif // AMPL_COUNTEDITERATOR_H
