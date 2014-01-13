#pragma once
#include <memory>
#include <vector>


class shared_match_pair_accumulator
{
private:

  std::shared_ptr<match_pair_vector> _accumulator;


public:

  shared_match_pair_accumulator(void)
  : _accumulator(new match_pair_vector())
  {}

  shared_match_pair_accumulator(const shared_match_pair_accumulator &other)
  : _accumulator(other._accumulator)
  {}

  void append(const match_pair &p);
  void append(const shared_match_pair_accumulator &acc);

  const match_pair_vector &get_vector(void) const;

};


class unique_match_pair_accumulator
{
private:

  match_pair_vector _accumulator;


public:

  unique_match_pair_accumulator(void)
  {}

  unique_match_pair_accumulator(const unique_match_pair_accumulator &other)
  : _accumulator(other._accumulator)
  {}

  void append(const match_pair &p);
  void append(const unique_match_pair_accumulator &acc);

  const match_pair_vector &get_vector(void) const;

};
