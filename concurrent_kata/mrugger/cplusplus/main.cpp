#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <chrono>
#include <iterator>
#include <algorithm>
#include "thread.h"
#include "sequencer.h"


int match_count(const int count, const char_iterator &char_it, const char val)
{
  const int new_val = val - char_it();
  if (new_val < 0)
    return 0;
  else if (new_val == 0)
    return count;
  else if (char_it.is_more())
    return match_count(count+1, char_it.next(), new_val);
  else
    return 0;
}


void for_each(std::list<int> &acc, const sequence_iterator &s_it, const std::function<int(const char_iterator &)> fn)
{
  if (fn(s_it()))
    acc.push_back(s_it.to_i());

  if (s_it.is_more())
    for_each(acc, s_it.next(), fn);
}


void split_sequence(std::list<int> &acc, const sequencer &seq, const int count)
{
  if (seq.length() > 256)
  {
    sequencer seq_front = seq.clone_front_half();
    mythread t(split_sequence, acc, seq_front, count+1);

    std::list<int> back_acc;
    sequencer seq_back = seq.clone_back_half();
    split_sequence(back_acc, seq_back, count+1);

    t.join();
    acc.splice(acc.end(), back_acc);
  }
  else
  {
    sequence_iterator seq_it = seq.get_sequence_iterator();
    for_each(acc, seq_it, [](const char_iterator &char_it) -> int {
      return char_it.is_more() ? match_count(0, char_it.next(), char_it()) : 0;
    });
  }
}


static void print_list(const std::list<int> &list)
{
  std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::cout << "Application done: " << ctime(&tt);
  std::cout << "list size: " << list.size() << std::endl;

  std::for_each(list.begin(), std::next(list.begin(), 10),
                [](int x) {std::cout << x << std::endl;} );
}


int main(int argc, char **argv)
{
  mythread::set_max_tree_depth();

  std::string str("8745648184845171326578518184151512461752149647129746915414816354846454");
  sequencer seq(str, 1000000);
  std::list<int> acc;
  split_sequence(acc, seq, 0);

  print_list(acc);
}
