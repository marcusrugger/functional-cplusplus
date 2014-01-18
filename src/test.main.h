#include <iostream>
#include "mtr.iterators.h"
#include "mtr.string.h"
#include "mtr.vector.h"


/* Helper functions */

#define SHOULD_BE_EQ(a,b,c) should_be_eq(a,b,__FILE__,__LINE__,c)

template <typename T>
void should_be_eq(T test_result, T expected_value,
                  const char *filename, int linenumber,
                  const char *description = NULL)
{
  if (test_result == expected_value)
    std::cout << "Success: "
              << test_result
              << " == "
              << expected_value
              << ", "
              << description
              << std::endl;
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


#define SHOULD_BE_TRUE(a,b) should_be_true(a,__FILE__,__LINE__,b)

void should_be_true(bool test_result,
                    const char *filename, int linenumber,
                    const char *description = NULL);


#define SHOULD_BE_FALSE(a,b) should_be_false(a,__FILE__,__LINE__,b)

void should_be_false(bool test_result,
                     const char *filename, int linenumber,
                     const char *description = NULL);


/* Test functions */

void test_iterators_executor(void);
void test_iterators_foreach(void);
void test_iterators_fmap_executor(void);
void test_iterators_fmap(void);
void test_iterators_index_forward_iterator(void);
void test_iterators_index_backward_iterator(void);
void test_string_string(void);
