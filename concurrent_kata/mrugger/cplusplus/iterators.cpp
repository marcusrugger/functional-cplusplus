#include "iterators.h"
#include "sequencer.h"


char char_iterator::operator()(void) const
{ return _sequencer(_idx); }


char_iterator char_iterator::next(void) const
{ return char_iterator(_sequencer, _idx-1); }


int char_iterator::to_i(void) const
{ return _idx; }


char_iterator sequence_iterator::operator()(void) const
{ return char_iterator(_sequencer, _idx); }


sequence_iterator sequence_iterator::next(void) const
{ return sequence_iterator(_sequencer, _idx+1); }


int sequence_iterator::to_i(void) const
{ return _idx; }
