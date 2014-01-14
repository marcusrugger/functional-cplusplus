#include "main.h"


shared_match_pair_accumulator::shared_match_pair_accumulator(const shared_match_pair_accumulator &front,
                                                             const match_pair &pair)
: _accumulator(front._accumulator)
{
  _accumulator->push_back(pair);
}


shared_match_pair_accumulator::shared_match_pair_accumulator(const shared_match_pair_accumulator &front,
                                                             const shared_match_pair_accumulator &back)
: _accumulator(front._accumulator)
{
  _accumulator->insert(_accumulator->end(),
                       back._accumulator->begin(),
                       back._accumulator->end());
}


shared_match_pair_accumulator shared_match_pair_accumulator::append(const match_pair &pair) const
{
  return shared_match_pair_accumulator(*this, pair);
}


shared_match_pair_accumulator shared_match_pair_accumulator::append(const shared_match_pair_accumulator &acc) const
{
  return shared_match_pair_accumulator(*this, acc);
}


const match_pair_vector &shared_match_pair_accumulator::get_vector(void) const
{
  return *_accumulator;
}




immutable_match_pair_accumulator::immutable_match_pair_accumulator(const immutable_match_pair_accumulator &front,
                                                             const match_pair &pair)
: _accumulator(front._accumulator)
{
  _accumulator.push_back(pair);
}


immutable_match_pair_accumulator::immutable_match_pair_accumulator(const immutable_match_pair_accumulator &front,
                                                             const immutable_match_pair_accumulator &back)
: _accumulator(front._accumulator)
{
  _accumulator.insert(_accumulator.end(),
                      back._accumulator.begin(),
                      back._accumulator.end());
}


immutable_match_pair_accumulator immutable_match_pair_accumulator::append(const match_pair &pair) const
{
  return immutable_match_pair_accumulator(*this, pair);
}


immutable_match_pair_accumulator immutable_match_pair_accumulator::append(const immutable_match_pair_accumulator &acc) const
{
  return immutable_match_pair_accumulator(*this, acc);
}


const match_pair_vector &immutable_match_pair_accumulator::get_vector(void) const
{
  return _accumulator;
}
