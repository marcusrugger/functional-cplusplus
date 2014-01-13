#pragma once
#include <pthread.h>
#include <functional>
#include <list>
#include <thread>
#include "main.h"


typedef std::function<accumulator(const accumulator, const sequencer, int)> thread_callback;


class mythread
{
public:

  static int MAX_TREE_DEPTH;
  static void set_max_tree_depth(void);

  mythread(const thread_callback func, const accumulator acc, const sequencer seq, int tree_depth);

  accumulator join(void) const;


private:

  const accumulator _acc;
  const sequencer _seq;
  const thread_callback _func;
  const int _tree_depth;
  const std::unique_ptr<std::thread> _thread;

  accumulator thread_return_accumulator;

  void callback(void);

};
