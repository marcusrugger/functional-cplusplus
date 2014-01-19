#include "project-euler.h"


typedef long long int number;


// What is the largest prime factor of the number 600851475143?
void problem_003(void)
{
  const number prime = 600851475143;

  auto answer = 6857;

  SHOULD_BE_EQ(answer, 6857, "Problem 003");
}

