#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <chrono>
#include <iterator>
#include <algorithm>
#include "thread.h"
#include "sequencer.h"


int match_count(int count, const char_iterator &char_it, char val)
{
  int new_val = val - char_it();
  if (new_val < 0)
    return 0;
  else if (new_val == 0)
    return count;
  else if (char_it.is_more())
    return match_count(count+1, char_it.next(), new_val);
  else
    return 0;
}


std::list<int> for_each(const sequence_iterator &s_it, std::function<int(const char_iterator &)> fn)
{
  std::list<int> list;
  const int cnt = fn(s_it());
  if (cnt) list.push_back(s_it.to_i());
  if (s_it.is_more()) list.splice(list.end(), for_each(s_it.next(), fn));
  return list;
}


std::list<int> split_sequence(const sequencer &seq, int count)
{
  if (seq.length() > 1000)
  {
    sequencer seq_front = seq.clone_front_half();
    mythread t(split_sequence, seq_front, count+1);

    sequencer seq_back = seq.clone_back_half();
    std::list<int> back_list = split_sequence(seq_back, count+1);

    std::list<int> list = t.join();
    list.splice(list.end(), back_list);

    return list;
  }
  else
  {
    sequence_iterator seq_it = seq.get_sequence_iterator();
    return for_each(seq_it, [](const char_iterator &char_it) -> int {
      return char_it.is_more() ? match_count(0, char_it.next(), char_it()) : 0;
    });
  }
}


static void print_list(std::list<int> &list)
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
  std::list<int> list = split_sequence(seq, 0);

  print_list(list);
}
