#pragma once
#include <functional>


namespace mtr
{


template <typename SRC_T, typename DST_T=SRC_T>
using fmap_callback = std::function<DST_T(SRC_T)>;


template <typename COLLECTION, typename IT, typename SRC_T, typename DST_T=SRC_T>
class fmap
{
private:

  const COLLECTION _collection;
  const IT _it;

public:

  using callback = fmap_callback<SRC_T,DST_T>;

  fmap(const COLLECTION &collection)
  : _collection(collection), _it(collection.iterator())
  {}

  fmap(const COLLECTION &collection, const IT &it)
  : _collection(collection), _it(it)
  {}

  const COLLECTION operator()(const callback fn) const
  {
    using foreach = mtr::foreach<IT,COLLECTION,SRC_T>;

    auto f = foreach(_it, _collection);
    auto f_fn = [fn](const COLLECTION &col, const SRC_T &x)->COLLECTION
    { return col.append(fn(x)); };
    return f(f_fn);
  }

};


} // namespace mtr
