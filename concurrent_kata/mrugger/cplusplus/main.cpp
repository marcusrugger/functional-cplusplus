#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <chrono>
#include "thread.h"
#include "sequencer.h"


int match_count(int count, const char_iterator char_it, char val)
{
  char c = char_it();
  if (c)
  {
    val -= c;
    if (val < 0)
      return 0;
    else if (val == 0)
      return count;
    else
      return match_count(count+1, char_it.next(), val);
  }
  else
    return 0;
}


std::list<int> for_each_apply_match_count(const sequence_iterator seq_it)
{
  std::list<int> list;

  char_iterator char_it = seq_it();
  char c = char_it();
  if (c)
  {
    int cnt = match_count(1, char_it.next(), c);
    if (cnt) list.push_back(seq_it.to_i());
    list.splice(list.end(), for_each_apply_match_count(seq_it.next()));
  }

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
    return for_each_apply_match_count(seq_it);
  }
}


static void print_list(std::list<int> &list)
{
  std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::cout << "Application done: " << ctime(&tt);
  std::cout << "list size: " << list.size() << std::endl;

  std::list<int>::iterator it;
  int max_print = 10;
  for (it = list.begin(); max_print > 0 && it != list.end(); it++, max_print--)
    std::cout << *it << std::endl;
}


int main(int argc, char **argv)
{
  mythread::set_max_tree_depth();

  std::string str("8745648184845171326578518184151512461752149647129746915414816354846454");
  sequencer seq(str, 1000000);
  std::list<int> list = split_sequence(seq, 0);

  print_list(list);
}
