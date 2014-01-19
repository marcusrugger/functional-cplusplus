#include "test.main.h"


static void test_with_string(void)
{
  using string = mtr::string;

  auto to_lower_case = [](char c)->char { return c >= 'A' && c <= 'Z' ? c+32 : c; };
  auto to_upper_case = [](char c)->char { return c >= 'a' && c <= 'z' ? c-32 : c; };

  auto count_lower_case = [](int a, char c)->int { return a + (c >= 'a' && c <= 'z' ? 1 : 0); };
  auto count_upper_case = [](int a, char c)->int { return a + (c >= 'A' && c <= 'Z' ? 1 : 0); };

  auto mixed_case_string = string("Hello World");
  auto lower_case_string = string("hello world");
  auto upper_case_string = string("HELLO WORLD");

  auto fmap = mixed_case_string.fmap();

  auto lower_case = fmap(to_lower_case);
  SHOULD_BE_EQ((int) lower_case.length(), 11, "Resulting string should be same length as original");
  SHOULD_BE_EQ(lower_case, lower_case_string, "String should be all lower case");
  SHOULD_NOT_BE_EQ(lower_case, upper_case_string, "String should not be upper case");

  auto upper_case = fmap(to_upper_case);
  SHOULD_BE_EQ((int) upper_case.length(), 11, "Resulting string should be same length as original");
  SHOULD_BE_EQ(upper_case, upper_case_string, "String should be all upper case");
  SHOULD_NOT_BE_EQ(upper_case, lower_case_string, "String should not be lower case");
}


void test_fmap_fmap(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_with_string();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
