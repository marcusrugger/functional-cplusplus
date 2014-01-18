#pragma once
#include <memory>


namespace mtr
{


template <typename IT, typename ACC, typename T> class foreach;

template <typename ACC, typename T>
using foreach_callback = std::function<const ACC(const ACC&, const T&)>;


template <typename IT, typename ACC, typename T>
class executor
{
private:

  using callback = foreach_callback<ACC,T>;

  const callback _fn;

  const ACC loop(const ACC &acc, const IT &it) const
  {
    if (it.is_empty())
      return acc;
    else
      return loop(_fn(acc, it()), it.next());
  }

public:

  executor(const callback fn)
  : _fn(fn)
  {}

  const ACC operator()(const IT &it, const ACC &acc) const
  { return loop(acc, it); }

};


template <typename IT, typename ACC, typename T>
class foreach
{
private:

  const IT _it;
  const ACC _acc;

public:

  using executor = mtr::executor<IT,ACC,T>;
  using callback = foreach_callback<ACC,T>;

  foreach(const IT &it, const ACC &acc)
  : _it(it), _acc(acc)
  {}

  const ACC operator()(const callback fn) const
  {
    const executor f = executor(fn);
    return f(_it, _acc);
  }

};

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
