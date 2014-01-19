#include <mtr.enumerator.h>
#include "project-euler.h"


class fibonacci_generator
{
private:

  const int _n;
  const int _fib_of_n;
  const int _fib_of_n_minus_1;
  const int _max;

  const int calc_fib(int n, int f1, int f2) const
  {
    if (n == 0) return 1;
    if (n == 1) return 2;
    return f1 + f2;
  }


  fibonacci_generator(const int n,
                      const int fib_of_n_minus_1,
                      const int fib_of_n_minus_2,
                      const int max)
  : _n(n),
    _fib_of_n(calc_fib(n, fib_of_n_minus_1, fib_of_n_minus_2)),
    _fib_of_n_minus_1(fib_of_n_minus_1),
    _max(max)
  {}


public:

  fibonacci_generator(void)
  : _n(0), _fib_of_n(1), _fib_of_n_minus_1(0), _max(0)
  {}

  fibonacci_generator(const int end)
  : _n(0), _fib_of_n(1), _fib_of_n_minus_1(0), _max(end)
  {}

  int operator ()(void) const
  { return _fib_of_n; }

  bool is_empty(void) const
  { return _fib_of_n > _max; }

  fibonacci_generator next(void) const
  { return fibonacci_generator(_n+1, _fib_of_n, _fib_of_n_minus_1, _max); }

  template <typename ACC>
  using _foreach_ = mtr::foreach<fibonacci_generator,ACC,int>;

  template <typename ACC>
  _foreach_<ACC> foreach(const ACC &acc) const
  { return _foreach_<ACC>((*this), acc); }

};


// By considering the terms in the Fibonacci sequence whose values do not exceed four million,
// find the sum of the even-valued terms.
void problem_002(void)
{
  auto sum_fn = [](int a, int i)->int { return a + (i % 2 == 0 ? i : 0); };

  auto answer = fibonacci_generator(3999999).foreach(0)(sum_fn);

  SHOULD_BE_EQ(answer, 4613732, "Problem 002");
}
