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
    std::cerr << "FAILURE: "
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
  }
}


void should_be_false(bool test_result,
                     const char *filename, int linenumber,
                     const char *description)
{
  if (!test_result)
    std::cout << "Success: "
              << description
              << std::endl;
  else
  {
    std::cerr << "FAILURE: "
              << (description ? description : "(no description)")
              << std::endl
              << "\t"
              << "test result was true, but was expected to be false"
              << std::endl
              << "\t"
              << "File: "
              << filename
              << std::endl
              << "\t"
              << "Line: "
              << linenumber
              << std::endl;
  }
}


int main(int argc, char **argv)
{
  test_enumerator();
  test_iterators_executor();
  test_iterators_foreach();
  test_iterators_fmap_executor();
  test_iterators_fmap();
  test_iterators_index_forward_iterator();
  test_iterators_index_backward_iterator();
  test_string_string();
  test_vector();
}
