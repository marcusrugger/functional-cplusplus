#include "test.main.h"


static void test_with_string(void)
{
  using string = mtr::string;
  using iterator = mtr::index_forward_iterator<string,char>;
  using executor = mtr::fmap_executor<string,iterator,char>;

  string s("Hello World");
  auto to_lower_case = [](char c)->char
                       { return c >= 'a' && c <= 'z' ? c-32 : c; };

  executor fmap_exec(string(), s.iterator(), to_lower_case);
  auto result = fmap_exec();
  SHOULD_BE_EQ((int) result.length(), (int) s.length(), "Resulting string should be same length as original");

  auto count_upper_case = [](int a, char c)->int
                          { return a + (c >= 'A' && c <= 'Z' ? 1 : 0); };

  auto cnt = result.foreach(0)(count_upper_case);

  SHOULD_BE_EQ(cnt, (int) s.length()-1, "All alpha-characters should now be upper case");
}


void test_fmap_fmap_executor(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_with_string();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
