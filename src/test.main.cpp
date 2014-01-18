#include "test.main.h"


void should_be_true(bool test_result,
                    const char *filename, int linenumber,
                    const char *description)
{
  if (test_result)
    std::cout << "Success: "
              << description
              << std::endl;
  else
  {
    std::cout << "FAILURE: "
              << (description ? description : "(no description)")
              << std::endl
              << "\t"
              << "test result was false, but was expected to be true"
              << std::endl
              << "\t"
              << "File: "
              << filename
              << std::endl
              << "\t"
              << "Line: "
              << linenumber
              << std::endl;
    throw std::runtime_error(description);
  }
}


int main(int argc, char **argv)
{
  test_iterators_executor();
  test_iterators_foreach();
  test_iterators_fmap_executor();
}
