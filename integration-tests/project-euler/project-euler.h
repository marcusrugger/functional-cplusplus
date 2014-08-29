#include <iostream>

/* Helper functions */

#define SHOULD_BE_EQ(a,b,c) should_be_eq(a,b,__FILE__,__LINE__,c)

template <typename T>
void should_be_eq(T test_result, T expected_value,
                  const char *filename, int linenumber,
                  const char *description = NULL)
{
  if (test_result == expected_value)
  {
    std::cout << "Success: "
              << description
              << ": "
              << test_result
              << " == "
              << expected_value
              << std::endl;
  }
  else
  {
    std::cerr << "FAILURE: "
              << (description ? description : "(no description)")
              << std::endl
              << "\t"
              << "Expected value:\t"
              << expected_value
              << std::endl
              << "\t"
              << "Test result:\t"
              << test_result
              << std::endl
              << "\t"
              << "File name:\t"
              << filename
              << std::endl
              << "\t"
              << "Line number:\t"
              << linenumber
              << std::endl;
  }
}


/* Project Euler methods */

void problem_001(void);
void problem_002(void);
void problem_003(void);
