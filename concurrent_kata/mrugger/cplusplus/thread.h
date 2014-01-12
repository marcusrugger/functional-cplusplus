#pragma once
#include <pthread.h>
#include <functional>
#include <list>
#include <thread>
#include "sequencer.h"


typedef std::function<std::list<int>(const sequencer &, int)> thread_callback;


class mythread
{
public:

  static int MAX_TREE_DEPTH;
  static void set_max_tree_depth(void);

  mythread(thread_callback func, const sequencer &seq, int tree_depth);

  std::list<int> join(void) const;


private:

  const sequencer &_seq;
  const thread_callback _func;
  const int _tree_depth;
  const std::unique_ptr<std::thread> _thread;

  std::list<int> return_list;

  void *callback(void);

};
