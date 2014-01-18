#pragma once
#include <memory>


namespace mtr
{

typedef int index;

template <typename OBJ, typename T> class index_forward_iterator;
template <typename OBJ, typename T> class index_backward_iterator;
template <typename IT, typename ACC, typename T> class executor;
template <typename IT, typename ACC, typename T> class foreach;

template <typename SRC_T, typename DST_T=SRC_T>
using fmap_callback = std::function<DST_T(SRC_T)>;

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
    if (it.is_more())
      return loop(_fn(acc, it()), it.next());
    else
      return _fn(acc, it());
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
    if (it.is_more())
      return loop(collection.append(_fn(it())), it.next());
    else
      return collection.append(_fn(it()));
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


template <typename OBJ, typename T>
class index_forward_iterator
{
private:

  const std::shared_ptr<const OBJ> _obj;

  const index _idx;
  const index _begin;
  const index _end;
  const index _step;

  void validate_index(void)
  { if (_idx < 0 || _idx > _end) throw std::runtime_error("index is out of range in index_forward_iterator"); }

public:

  index_forward_iterator(const index_forward_iterator &other)
  : _obj(other._obj), _idx(other._idx), _begin(other._begin), _end(other._end), _step(other._step)
  {}

  index_forward_iterator(const index_backward_iterator<OBJ,T> &other)
  : _obj(other._obj), _idx(other._idx), _begin(other._begin), _end(other._end), _step(other._step)
  {}

  index_forward_iterator(const index_forward_iterator &other, const index idx)
  : _obj(other._obj), _idx(idx), _begin(other._begin), _end(other._end), _step(other._step)
  { validate_index(); }

  index_forward_iterator(const OBJ &obj, const index begin, const index end, const index step = 1)
  : _obj(new OBJ(obj)), _idx(begin), _begin(begin), _end(end), _step(step)
  { validate_index(); }

  T operator()(void) const
  { return (*_obj)[_idx]; }

  bool is_more(void) const
  { return _idx+_step <= _end; }

  index_forward_iterator next(void) const
  { return index_forward_iterator((*this), _idx+_step); }

  index to_i(void) const
  { return _idx; }

  template <typename ACC>
  using _foreach_ = mtr::foreach<index_forward_iterator,ACC,T>;

  template <typename ACC>
  _foreach_<ACC> foreach(const ACC &acc) const
  { return _foreach_<ACC>((*this), acc); }

};


template <typename OBJ, typename T>
class index_backward_iterator
{
private:

  const std::shared_ptr<const OBJ> _obj;

  const index _idx;
  const index _begin;
  const index _end;
  const index _step;

  void validate_index(void)
  { if (_idx < 0 || _idx > _end) throw std::runtime_error("index is out of range in index_backward_iterator"); }

public:

  index_backward_iterator(const index_backward_iterator &other)
  : _obj(other._obj), _idx(other._idx), _begin(other._begin), _end(other._end), _step(other._step)
  {}

  index_backward_iterator(const index_forward_iterator<OBJ,T> &other)
  : _obj(other._obj), _idx(other._idx), _begin(other._begin), _end(other._end), _step(other._step)
  {}

  index_backward_iterator(const index_backward_iterator &other, const index idx)
  : _obj(other._obj), _idx(idx), _begin(other._begin), _end(other._end), _step(other._step)
  { validate_index(); }

  index_backward_iterator(const OBJ &obj, const index begin, const index end, const index step = 1)
  : _obj(new OBJ(obj)), _idx(end), _begin(begin), _end(end), _step(step)
  { validate_index(); }

  T operator()(void) const
  { return (*_obj)[_idx]; }

  bool is_more(void) const
  { return _idx-_step >= _begin; }

  index_backward_iterator next(void) const
  { return index_backward_iterator((*this), _idx-_step); }

  index to_i(void) const
  { return _idx; }

  template <typename ACC>
  using _foreach_ = mtr::foreach<index_backward_iterator,ACC,T>;

  template <typename ACC>
  _foreach_<ACC> foreach(const ACC &acc) const
  {
    return _foreach_<ACC>((*this), acc);
  }

};

}
