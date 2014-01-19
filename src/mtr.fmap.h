#pragma once
#include <functional>


namespace mtr
{


template <typename SRC_T, typename DST_T=SRC_T>
using fmap_callback = std::function<DST_T(SRC_T)>;


template <typename COLLECTION, typename IT, typename SRC_T, typename DST_T=SRC_T>
class fmap_executor
{
private:

  using callback = fmap_callback<SRC_T,DST_T>;

  const COLLECTION _collection;
  const IT _it;
  const callback _fn;

  const COLLECTION loop(const COLLECTION &collection, const IT &it) const
  {
    if (it.is_empty())
      return collection;
    else
      return loop(collection.append(_fn(it())), it.next());
  }

public:

  fmap_executor(const COLLECTION &collection, const IT &it, const callback fn)
  : _collection(collection), _it(it), _fn(fn)
  {}

  const COLLECTION operator()(void) const
  {
    return loop(_collection, _it);
  }

};


template <typename COLLECTION, typename IT, typename SRC_T, typename DST_T=SRC_T>
class fmap
{
private:

  const COLLECTION _collection;
  const IT _it;

public:

  using executor = fmap_executor<COLLECTION,IT,SRC_T,DST_T>;
  using callback = fmap_callback<SRC_T,DST_T>;

  fmap(const COLLECTION &collection)
  : _collection(collection), _it(collection.iterator())
  {}

  fmap(const COLLECTION &collection, const IT &it)
  : _collection(collection), _it(it)
  {}

  const COLLECTION operator()(const callback fn) const
  {
    executor exec(_collection, _it, fn);
    return exec();
  }

};


} // namespace mtr
