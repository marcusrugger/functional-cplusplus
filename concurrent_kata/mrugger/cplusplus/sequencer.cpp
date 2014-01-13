#include "sequencer.h"


char sequencer::operator()(int idx) const
{
  if (idx >= 0 && idx < _end_idx)
    return _sequence[idx % _sequence_length];
  else
    return '\0';
}


sequence_iterator sequencer::get_sequence_iterator(void) const
{ return sequence_iterator((*this), _start_idx, _end_idx); }


sequencer sequencer::clone_front_half(void) const
{
  int new_end_idx = _start_idx + (_end_idx - _start_idx) / 2;
  return sequencer((*this), _start_idx, new_end_idx);
}


sequencer sequencer::clone_back_half() const
{
  int new_start_idx = _start_idx + (_end_idx - _start_idx) / 2;
  return sequencer((*this), new_start_idx, _end_idx);
}


sequencer sequencer::clone_block(int start, int length) const
{ return sequencer((*this), start, start + length); }



int sequencer::length(void) const
{ return _end_idx - _start_idx; }


std::string sequencer::to_s(void) const
{
  std::string rv;
  append_to_string(rv, _start_idx, _end_idx - _start_idx);
  return rv;
}


void sequencer::append_to_string(std::string &s, int idx, int count) const
{
  if (count > 0 && idx < _end_idx)
  {
    s.push_back((*this)(idx));
    append_to_string(s, idx+1, count-1);
  }
}