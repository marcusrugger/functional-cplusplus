#pragma once


namespace mtr
{

template <typename T>
class forward_enumerator
{
private:

  const T _idx;
  const T _end;

public:

  forward_enumerator(void)
  : _idx(0), _end(-1)
  {}

  forward_enumerator(const T &start, const T &end)
  : _idx(start), _end(end)
  {}

  T operator ()(void) const
  { return _idx; }

  bool is_empty(void) const
  { return _idx > _end; }

  forward_enumerator next(void) const
  { return forward_enumerator(_idx+1, _end); }

  template <typename ACC>
  using _foreach_ = mtr::foreach<forward_enumerator,ACC,T>;

  template <typename ACC>
  _foreach_<ACC> foreach(const ACC &acc) const
  { return _foreach_<ACC>((*this), acc); }

};

}
