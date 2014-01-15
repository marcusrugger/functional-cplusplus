#pragma once


class mythread;


template <typename SEQ, typename ACC, typename OBJ>
class parallelizer
{
private:

  const std::function<ACC(ACC&,OBJ&)> _fn;

  const ACC fork_sequence(const ACC &acc, const SEQ &seq, const int depth) const
  {
    SEQ seq_front = seq.clone_front_half();
    mythread t(process_sequence, acc, seq_front, depth+1);

    SEQ seq_back = seq.clone_back_half();
    ACC back_acc = process_sequence(ACC(), seq_back, depth+1);

    return t.join().append(back_acc);
  }

  const ACC iterate_sequence(const ACC &acc, const SEQ &seq) const
  {
    sequence_iterator seq_it = seq.get_sequence_iterator();
    return seq_it.foreach<ACC>(acc, _fn);
  }

  const ACC process_sequence(const ACC &acc, const SEQ &seq, const int depth) const
  {
    if (seq.length() > 1024)
      return fork_sequence(acc, seq, depth);
    else
      return iterate_sequence(acc, seq);
  }

public:

  parallelizer(const std::function<ACC(ACC&,OBJ&)> fn)
  : _fn(fn)
  {}

  ACC operator()(const ACC &acc, const SEQ &seq) const
  {
    return process_sequence(acc, seq, 0);
  }

};
