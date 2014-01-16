#pragma once
#include <memory>
#include "mtr.iterators.h"

namespace mtr
{

template <typename T>
class template_string
{
private:

  const std::shared_ptr<const T> _string;
  const size_t _string_length;

  index find_nil(const T *p, const int idx) const
  {
    if (p[idx] == '\0')
      return idx;
    else
      return find_nil(p, idx+1);
  }

  const T *copy_string(const T *psrc, T *pdst, const index idx) const
  {
    pdst[idx] = psrc[idx];
    if (psrc[idx] == '\0')
      return pdst;
    else
      return copy_string(psrc, pdst, idx+1);
  }

  const T *create_string(const T *p) const
  {
    const size_t s = find_nil(p, 0);
    T *pdst = new T[s];
    return copy_string(p, pdst, 0);
  }

protected:

  using forward_iterator = index_forward_iterator<template_string,T>;
  using backward_iterator = index_backward_iterator<template_string,T>;

  friend forward_iterator;
  friend backward_iterator;

  T operator[](const index idx) const
  { return _string.get()[idx]; }  

public:

  template_string(const template_string &other)
  : _string(other._string), _string_length(other._string_length)
  {}

  template_string(const T *p)
  : _string_length(find_nil(p, 0)), _string(create_string(p))
  {}

  forward_iterator iterator(void) const
  { return forward_iterator((*this), 0, _string_length-1, 1); }

  backward_iterator back_iterator(void) const
  { return backward_iterator((*this), 0, _string_length-1, 1); }

};

typedef template_string<char> string;
typedef template_string<wchar_t> wstring;

}
