#pragma once
#include <memory>
#include "mtr.foreach.h"
#include "mtr.fmap.h"


namespace mtr
{

typedef int index;

template <typename OBJ, typename T> class index_forward_iterator;
template <typename OBJ, typename T> class index_backward_iterator;


template <typename OBJ, typename T>
class index_forward_iterator
{
private:

  const std::shared_ptr<const OBJ> _obj;

  const index _idx;
  const index _begin;
  const index _end;
  const index _step;

  void validate_index(void) const
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
  {}

  index_forward_iterator(const OBJ &obj, const index begin, const index end, const index step = 1)
  : _obj(new OBJ(obj)), _idx(begin), _begin(begin), _end(end), _step(step)
  {}

  T operator()(void) const
  { validate_index(); return (*_obj)[_idx]; }

  bool is_empty(void) const
  { return _idx > _end; }

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

  void validate_index(void) const
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
  {}

  index_backward_iterator(const OBJ &obj, const index begin, const index end, const index step = 1)
  : _obj(new OBJ(obj)), _idx(end), _begin(begin), _end(end), _step(step)
  {}

  T operator()(void) const
  { validate_index(); return (*_obj)[_idx]; }

  bool is_empty(void) const
  { return _idx < _begin; }

  index_backward_iterator next(void) const
  { return index_backward_iterator((*this), _idx-_step); }

  index to_i(void) const
  { return _idx; }

  template <typename ACC>
  using _foreach_ = mtr::foreach<index_backward_iterator,ACC,T>;

  template <typename ACC>
  _foreach_<ACC> foreach(const ACC &acc) const
  { return _foreach_<ACC>((*this), acc); }

};


template <typename STREAM, typename T>
class input_stream_iterator
{
private:

  const std::shared_ptr<STREAM> _stream;
  const T _c;

  input_stream_iterator(const input_stream_iterator &other, const T &c)
  : _stream(other._stream), _c(c)
  {}

public:

  input_stream_iterator(void)
  : _stream(NULL), _c(T())
  {}

  input_stream_iterator(const input_stream_iterator &other)
  : _stream(other._stream), _c(other._c)
  {}

  input_stream_iterator(STREAM *stream)
  : _stream(stream), _c(_stream ? _stream->get() : T())
  {} 

  ~input_stream_iterator(void)
  { if (_stream.unique()) _stream->close(); }

  T operator()(void) const
  { return _c; }

  bool is_empty(void) const
  { return _stream ? !_stream->good() : true; }

  input_stream_iterator next(void) const
  { return input_stream_iterator((*this), _stream ? _stream->get() : T()); }

  template <typename ACC>
  using _foreach_ = mtr::foreach<input_stream_iterator,ACC,T>;

  template <typename ACC>
  _foreach_<ACC> foreach(const ACC &acc) const
  { return _foreach_<ACC>((*this), acc); }

};

}
