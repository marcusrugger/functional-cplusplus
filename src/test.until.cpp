#include "test.main.h"


static void test_with_string(void)
{
  using string = mtr::string;
  using iterator = mtr::index_forward_iterator<string,char>;
  using until = mtr::until<iterator,int,char>;

  string s("Hello World");
  until u(s.iterator(), 0);

  auto cnd_fn = [](int a, char c)->int { return ' ' == c; };
  auto fn = [](int a, char c)->int { return a + 1; };
  auto cnt = u(cnd_fn, fn);

  SHOULD_BE_EQ(cnt, 5, "Call function correct number of times");
}


void test_until(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_with_string();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
