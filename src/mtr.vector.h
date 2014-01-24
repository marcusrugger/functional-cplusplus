#pragma once
#include <memory>
#include "mtr.iterators.h"

namespace mtr
{

template <typename T>
class template_vector
{
private:

  template <typename DT>
  struct array_deleter
  {
    const int count;
    array_deleter(const int cnt) : count(cnt) {}
    array_deleter(const array_deleter &other) : count(other.count) {}
    void operator ()( DT const * p)
    {
      if (count > 0) destruct_objects(p, count-1);
      std::free((void *) p);
    }
    void destruct_objects(const DT *p, const int i)
    {
      p[i].~DT();
      if (i > 0)
        destruct_objects(p, i-1);
      else
        return;
    }
  };

  const std::shared_ptr<const T> _vector;
  const size_t _vector_length;

  const T *copy_vector(const T *psrc, T *pdst, const size_t idx) const
  {
    new (&pdst[idx]) T(psrc[idx]);
    if (idx > 0)
      return copy_vector(psrc, pdst, idx-1);
    else
      return pdst;
  }

  const T *create_vector(const T *p, const size_t len) const
  {
    if (len > 0)
    {
      T *pdst = static_cast<T *> (::operator new (sizeof(T[len])));
      return copy_vector(p, pdst, len-1);
    }
    else
      return NULL;
  }

  template_vector(size_t len, const T *p)
  : _vector(p, array_deleter<T>(len)), _vector_length(len)
  {}

protected:

  using forward_iterator = index_forward_iterator<template_vector,T>;
  using backward_iterator = index_backward_iterator<template_vector,T>;

  friend forward_iterator;
  friend backward_iterator;

  template <typename ACC>
  using _foreach_ = mtr::foreach<forward_iterator,ACC,T>;

  using _fmap_ = mtr::fmap<template_vector,forward_iterator,T>;

  void validate_index(const index idx) const
  { if (idx < 0 || idx >= length()) throw std::runtime_error("index out of range in vector"); }

  const T &operator[](const index idx) const
  { validate_index(idx); return _vector.get()[idx]; }  

public:

  template_vector(void)
  : _vector(NULL, array_deleter<T>(0)), _vector_length(0)
  {}

  template_vector(const template_vector &other)
  : _vector(other._vector), _vector_length(other._vector_length)
  {}

  template_vector(const T *p, const size_t len)
  : _vector(create_vector(p, len), array_deleter<T>(len)), _vector_length(len)
  {}

  template_vector(const T &item)
  : _vector(create_vector(&item, 1), array_deleter<T>(1)), _vector_length(1)
  {}

  forward_iterator iterator(void) const
  { return forward_iterator((*this), 0, length()-1, 1); }

  backward_iterator back_iterator(void) const
  { return backward_iterator((*this), 0, length()-1, 1); }

  template <typename ACC>
  _foreach_<ACC> foreach(const ACC &acc) const
  { return iterator().foreach(acc); }

  _fmap_ fmap(void) const
  { return _fmap_(template_vector(), iterator()); }

  size_t length(void) const
  { return _vector_length; }

  template_vector append(const template_vector &other) const
  {
    size_t total_length = length() + other.length();
    T *p = static_cast<T *> (::operator new (sizeof(T[total_length])));
    if (length() > 0) copy_vector(_vector.get(), p, length()-1);
    if (other.length() > 0) copy_vector(other._vector.get(), p+length(), other.length()-1);
    return template_vector(total_length, p);
  }

  template_vector push_head(const T &c) const
  {
    size_t total_length = length() + 1;
    T *p = static_cast<T *> (::operator new (sizeof(T[total_length])));
    new (&p[0]) T(c);
    if (length() > 0) copy_vector(_vector.get(), p+1, length()-1);
    return template_vector(total_length, p);
  }

  template_vector push_tail(const T &c) const
  {
    size_t total_length = length() + 1;
    T *p = static_cast<T *> (::operator new (sizeof(T[total_length])));
    if (length() > 0) copy_vector(_vector.get(), p, length()-1);
    new (&p[length()]) T(c);
    return template_vector(total_length, p);
  }

  template_vector pop_tail(void) const
  {
    size_t total_length = length() - 1;
    T *p = static_cast<T *> (::operator new (sizeof(T[total_length])));
    if (length() > 0) copy_vector(_vector.get(), p, length()-2);
    return template_vector(total_length, p);
  }

  template_vector pop_head(void) const
  {
    size_t total_length = length() - 1;
    T *p = static_cast<T *> (::operator new (sizeof(T[total_length])));
    if (length() > 0) copy_vector(_vector.get()+1, p, length()-2);
    return template_vector(total_length, p);
  }

  template_vector put_tail(const T &c) const
  {
    size_t total_length = length();
    T *p = static_cast<T *> (::operator new (sizeof(T[total_length])));
    if (length() > 0) copy_vector(_vector.get(), p, length()-2);
    new (&p[length()-1]) T(c);
    return template_vector(total_length, p);
  }

  const T &head(void) const
  { return (*this)[0]; }

  const T &tail(void) const
  { return (*this)[length()-1]; }

};

template <typename T>
using vector = template_vector<T>;

}
