#include "test.main.h"


static void test_with_string(void)
{
  using string = mtr::string;
  using iterator = mtr::index_forward_iterator<string,char>;
  using executor = mtr::fmap_executor<string,iterator,char>;

  string s("Hello World");
  auto fn = [](char c)->int { return c >= 'a' && c <= 'z' ? c-32 : c; };

  executor fmap(string(), s.iterator(), fn);
  auto result = fmap();

  SHOULD_BE_EQ((int) result.length(), (int) s.length(), "Resulting string should be same length as original");
}


void test_iterators_fmap_executor(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_with_string();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
