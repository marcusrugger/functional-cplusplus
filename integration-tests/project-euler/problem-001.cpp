#include <mtr.enumerator.h>
#include "project-euler.h"

using enumerator = mtr::forward_enumerator<int>;


// Find the sum of all the multiples of 3 or 5 below 1000.
void problem_001(void)
{
  auto sum_fn = [](int a, int i)->int { return a + i; };

  auto sum_3  = enumerator(0, 999, 3).foreach(0)(sum_fn);
  auto sum_5  = enumerator(0, 999, 5).foreach(0)(sum_fn);
  auto sum_15 = enumerator(0, 999, 15).foreach(0)(sum_fn);

  auto answer = sum_3 + sum_5 - sum_15;

  SHOULD_BE_EQ(answer, 233168, "Problem 001");
}

