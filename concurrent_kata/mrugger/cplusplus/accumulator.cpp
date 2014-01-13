#include "main.h"


void shared_match_pair_accumulator::append(const match_pair &pair)
{
  _accumulator->push_back(pair);
}


void shared_match_pair_accumulator::append(const shared_match_pair_accumulator &acc)
{
  _accumulator->insert(_accumulator->end(), acc._accumulator->begin(), acc._accumulator->end());
}


const match_pair_vector &shared_match_pair_accumulator::get_vector(void) const
{
  return *_accumulator;
}


void unique_match_pair_accumulator::append(const match_pair &pair)
{
  _accumulator.push_back(pair);
}


void unique_match_pair_accumulator::append(const unique_match_pair_accumulator &acc)
{
  _accumulator.insert(_accumulator.end(), acc._accumulator.begin(), acc._accumulator.end());
}


const match_pair_vector &unique_match_pair_accumulator::get_vector(void) const
{
  return _accumulator;
}
