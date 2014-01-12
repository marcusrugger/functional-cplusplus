#pragma once
#include <list>
#include <functional>

class sequencer;


class char_iterator
{
private:

  const sequencer &_sequencer;
  const int _idx;
  const int _end_idx;

public:

  char_iterator(const sequencer &seq, int idx, int end_idx)
  : _sequencer(seq), _idx(idx), _end_idx(end_idx)
  {}

  char_iterator(const char_iterator &other)
  : _sequencer(other._sequencer), _idx(other._idx), _end_idx(other._end_idx)
  {}

  char operator()(void) const;
  bool is_more(void) const;
  char_iterator next(void) const;
  int to_i(void) const;

};


class sequence_iterator
{
private:

  const sequencer &_sequencer;
  const int _idx;
  const int _end_idx;

public:

  sequence_iterator(const sequencer &seq, int idx, int end_idx)
  : _sequencer(seq), _idx(idx), _end_idx(end_idx)
  {}


  char_iterator operator()(void) const;
  bool is_more(void) const;
  sequence_iterator next(void) const;
  int to_i(void) const;

};
