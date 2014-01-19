#include "test.main.h"


static void test_with_string(void)
{
  using string = mtr::string;

  auto fmap = string("Hello World").fmap();

  auto to_lower_case = [](char c)->char { return c >= 'A' && c <= 'Z' ? c+32 : c; };
  auto to_upper_case = [](char c)->char { return c >= 'a' && c <= 'z' ? c-32 : c; };

  auto count_lower_case = [](int a, char c)->int { return a + (c >= 'a' && c <= 'z' ? 1 : 0); };
  auto count_upper_case = [](int a, char c)->int { return a + (c >= 'A' && c <= 'Z' ? 1 : 0); };

  auto lower_case = fmap(to_lower_case);
  SHOULD_BE_EQ((int) lower_case.length(), 11, "Resulting string should be same length as original");

  auto upper_case = fmap(to_upper_case);
  SHOULD_BE_EQ((int) upper_case.length(), 11, "Resulting string should be same length as original");

  {
    auto lower_case_count = lower_case.foreach(0)(count_lower_case);
    SHOULD_BE_EQ(lower_case_count, 10, "All alpha-characters should be lower case");

    auto upper_case_count = upper_case.foreach(0)(count_upper_case);
    SHOULD_BE_EQ(upper_case_count, 10, "All alpha-characters should be upper case");
  }

  {
    auto lower_case_count = upper_case.foreach(0)(count_lower_case);
    SHOULD_BE_EQ(lower_case_count, 0, "There should be no lower case characters");

    auto upper_case_count = lower_case.foreach(0)(count_upper_case);
    SHOULD_BE_EQ(upper_case_count, 0, "There should be no upper case characters");
  }
}


void test_iterators_fmap(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_with_string();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
