#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include "thread.h"


int mythread::MAX_TREE_DEPTH;


void mythread::set_max_tree_depth(void)
{
  int cores = std::thread::hardware_concurrency();
  MAX_TREE_DEPTH = ((int) log2((double) (cores))) + 1;
}


mythread::mythread(thread_callback func, std::list<int> &acc, const sequencer &seq, int tree_depth)
: _func(func),
  _acc(acc),
  _seq(seq),
  _tree_depth(tree_depth),
  _thread(tree_depth < MAX_TREE_DEPTH ? new std::thread(&mythread::callback, this) : NULL)
{
  if (_thread == NULL) _func(_acc, _seq, _tree_depth);
}


void mythread::join(void) const
{
  if (_thread) _thread->join();
}


void mythread::callback(void)
{
  _func(_acc, _seq, _tree_depth);
  std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::cout << "Thread done: " << ctime(&tt);
}
