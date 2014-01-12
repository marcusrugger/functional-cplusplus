#pragma once
#include <pthread.h>
#include <functional>
#include <list>
#include <thread>
#include "main.h"


typedef std::function<void(accumulator &, const sequencer &, int)> thread_callback;


class mythread
{
public:

  static int MAX_TREE_DEPTH;
  static void set_max_tree_depth(void);

  mythread(thread_callback func, accumulator &acc, const sequencer &seq, int tree_depth);

  void join(void) const;


private:

  accumulator &_acc;
  const sequencer &_seq;
  const thread_callback _func;
  const int _tree_depth;
  const std::unique_ptr<std::thread> _thread;

  void callback(void);

};
