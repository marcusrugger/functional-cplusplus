#pragma once
#include <ostream>
#include <memory>
#include <cstring>
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
    if (p[idx] == T())
      return idx;
    else
      return find_nil(p, idx+1);
  }

  const T *copy_string(const T *psrc, T *pdst, const index idx) const
  {
    pdst[idx] = psrc[idx];
    if (psrc[idx] == T())
      return pdst;
    else
      return copy_string(psrc, pdst, idx+1);
  }

  const T *create_string(const T *p) const
  {
    const size_t s = find_nil(p, 0);
    T *pdst = new T[s+1];
    return copy_string(p, pdst, 0);
  }

  int compare(const T *one, const T *two) const
  {
    const int c = (*one) - (*two);
    if (c != 0 || (*one) == '\0' || (*two) == '\0')
      return c;
    else
      return compare(one+1, two+1);
  }

  int find(const int idx, const T &c) const
  {
    if (idx >= length() || (*this)[idx] == c)
      return idx;
    else
      return find(idx+1, c);
  }

  template_string(const T *p, size_t len)
  : _string(p), _string_length(len)
  {}

protected:

  using forward_iterator = index_forward_iterator<template_string,T>;
  using backward_iterator = index_backward_iterator<template_string,T>;

  friend forward_iterator;
  friend backward_iterator;

  template <typename ACC>
  using _foreach_ = mtr::foreach<forward_iterator,ACC,T>;

  using _fmap_ = mtr::fmap<template_string,forward_iterator,T>;

  const T operator[](const index idx) const
  { return _string.get()[idx]; }  

public:

  template_string(void)
  : _string(NULL), _string_length(0)
  {}

  template_string(const template_string &other)
  : _string(other._string), _string_length(other._string_length)
  {}

  template_string(const T *p)
  : _string_length(find_nil(p, 0)), _string(create_string(p))
  {}

  forward_iterator iterator(void) const
  { return forward_iterator((*this), 0, length()-1, 1); }

  backward_iterator back_iterator(void) const
  { return backward_iterator((*this), 0, length()-1, 1); }

  template <typename ACC>
  _foreach_<ACC> foreach(const ACC &acc) const
  { return iterator().foreach(acc); }

  _fmap_ fmap(void) const
  { return _fmap_(template_string(), iterator()); }

  size_t length(void) const
  { return _string_length; }

  template_string append(const template_string &other) const
  {
    size_t total_length = length() + other.length();
    T *p = static_cast<T *> (::operator new (sizeof(T[total_length+1])));
    if (length() > 0) std::memcpy(p, _string.get(), length());
    if (other.length() > 0) std::memcpy(p+length(), other._string.get(), other.length());
    p[total_length] = '\0';
    return template_string(p, total_length);
  }

  template_string append(const T &c) const
  {
    size_t total_length = length() + 1;
    T *p = static_cast<T *> (::operator new (sizeof(T[total_length+1])));
    if (length() > 0) p+length(), memcpy(p, _string.get(), length());
    p[length()] = c;
    p[length()+1] = T();
    return template_string(p, total_length);
  }

  int compare(const template_string &other) const
  {
    return compare(_string.get(), other._string.get());
  }

  bool operator ==(const template_string &other) const
  {
    return compare(other) == 0;
  }

  bool is_included(const T &c) const
  { return find(0, c) < length(); }

  const T* c_str(void) const
  { return _string.get(); }

};

typedef template_string<char> string;
typedef template_string<wchar_t> wstring;

template<typename T>
std::ostream& operator << (std::ostream &os, const template_string<T> &str)
{
  os << str.c_str();
  return os;
}

}
