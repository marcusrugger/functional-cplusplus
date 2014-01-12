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


mythread::mythread(thread_callback func, const sequencer &seq, int tree_depth)
: _func(func),
  _seq(seq),
  _tree_depth(tree_depth),
  _thread(tree_depth < MAX_TREE_DEPTH ? new std::thread(&mythread::callback, this) : NULL)
{
  if (_thread == NULL) return_list = _func(_seq, _tree_depth);
}


std::list<int> mythread::join(void) const
{
  if (_thread) _thread->join();
  return return_list;
}


void *mythread::callback(void)
{
  return_list = _func(_seq, _tree_depth);
  std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::cout << "Thread done: " << ctime(&tt);
  return NULL;
}
