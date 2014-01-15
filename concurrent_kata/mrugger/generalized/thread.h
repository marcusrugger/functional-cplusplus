#pragma once
#include <pthread.h>
#include <functional>
#include <list>
#include <thread>
#include "parallelizer.h"
#include "main.h"


template <typename SEQ, typename ACC, typename OBJ> class parallelizer;


typedef std::function<const accumulator(const parallelizer<sequencer,accumulator,char_iterator> &, const accumulator &, const sequencer &, int) const> thread_callback;


class mythread
{
public:

  static int MAX_TREE_DEPTH;
  static void set_max_tree_depth(void);

  mythread(const thread_callback func, const accumulator &acc, const sequencer &seq, int tree_depth);

  const accumulator join(void) const;


private:

  const accumulator _acc;
  const sequencer _seq;
  const thread_callback _func;
  const int _tree_depth;
  const std::unique_ptr<std::thread> _thread;

  accumulator thread_return_accumulator;

  void callback(void);

};
