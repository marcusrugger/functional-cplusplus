#pragma once
#include "mtr.foreach.h"


namespace mtr
{

template <typename T>
class forward_enumerator
{
private:

  const T _idx;
  const T _end;
  const int _step;

public:

  forward_enumerator(void)
  : _idx(0), _end(-1), _step(1)
  {}

  forward_enumerator(const T &start, const T &end, const int step=1)
  : _idx(start), _end(end), _step(step)
  {}

  T operator ()(void) const
  { return _idx; }

  bool is_empty(void) const
  { return _idx > _end; }

  forward_enumerator next(void) const
  { return forward_enumerator(_idx+_step, _end, _step); }

  template <typename ACC>
  using _foreach_ = mtr::foreach<forward_enumerator,ACC,T>;

  template <typename ACC>
  _foreach_<ACC> foreach(const ACC &acc) const
  { return _foreach_<ACC>((*this), acc); }

};

template <typename T>
class backward_enumerator
{
private:

  const T _idx;
  const T _start;
  const int _step;

public:

  backward_enumerator(void)
  : _idx(-1), _start(0), _step(1)
  {}

  backward_enumerator(const T &start, const T &end, const int step=1)
  : _idx(end), _start(start), _step(step)
  {}

  T operator ()(void) const
  { return _idx; }

  bool is_empty(void) const
  { return _idx < _start; }

  backward_enumerator next(void) const
  { return backward_enumerator(_start, _idx-_step, _step); }

  template <typename ACC>
  using _foreach_ = mtr::foreach<backward_enumerator,ACC,T>;

  template <typename ACC>
  _foreach_<ACC> foreach(const ACC &acc) const
  { return _foreach_<ACC>((*this), acc); }

};

}
