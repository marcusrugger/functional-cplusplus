#pragma once
#include <functional>
#include <memory>


namespace mtr
{


template <typename ACC, typename T>
using until_callback = std::function<const ACC(const ACC&, const T&)>;

template <typename ACC, typename T>
using until_condition = std::function<bool(const ACC&, const T&)>;


template <typename IT, typename ACC, typename T>
class until_executor
{
private:

  using callback = until_callback<ACC,T>;
  using condition = until_condition<ACC,T>;

  const callback _fn;
  const condition _cnd_fn;

  const ACC loop(const ACC &acc, const IT &it) const
  {
    if (it.is_empty())
      return acc;
    else if (_cnd_fn(acc, it()))
      return acc;
    else
      return loop(_fn(acc, it()), it.next());
  }

public:

  until_executor(const condition cnd_fn, const callback fn)
  : _cnd_fn(cnd_fn), _fn(fn)
  {}

  const ACC operator()(const IT &it, const ACC &acc) const
  { return loop(acc, it); }

};


template <typename IT, typename ACC, typename T>
class until
{
private:

  const IT _it;
  const ACC _acc;

public:

  using executor = mtr::until_executor<IT,ACC,T>;
  using callback = until_callback<ACC,T>;
  using condition = until_condition<ACC,T>;

  until(const IT &it, const ACC &acc)
  : _it(it), _acc(acc)
  {}

  const ACC operator()(const condition cnd_fn, const callback fn) const
  {
    const executor f = executor(cnd_fn, fn);
    return f(_it, _acc);
  }

};

} // namespace mtr
