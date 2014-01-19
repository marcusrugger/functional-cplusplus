#include "test.main.h"


static void test_with_string(void)
{
  using string = mtr::string;
  using iterator = mtr::index_forward_iterator<string,char>;
  using foreach = mtr::foreach<iterator,int,char>;

  string s("Hello World");
  foreach f(s.iterator(), 0);

  auto fn = [](int a, char c)->int { return a + 1; };
  auto cnt = f(fn);

  SHOULD_BE_EQ(cnt, (int) s.length(), "Call function correct number of times");
}


void test_foreach_foreach(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_with_string();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
