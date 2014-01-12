#pragma once
#include <pthread.h>
#include <functional>
#include <list>
#include <thread>
#include "sequencer.h"


typedef std::function<void(std::list<int> &, const sequencer &, int)> thread_callback;


class mythread
{
public:

  static int MAX_TREE_DEPTH;
  static void set_max_tree_depth(void);

  mythread(thread_callback func, std::list<int> &acc, const sequencer &seq, int tree_depth);

  void join(void) const;


private:

  std::list<int> &_acc;
  const sequencer &_seq;
  const thread_callback _func;
  const int _tree_depth;
  const std::unique_ptr<std::thread> _thread;

  void callback(void);

};
