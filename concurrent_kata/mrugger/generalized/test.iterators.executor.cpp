#include "test.main.h"


static void test(void)
{
  using string = mtr::string;
  using iterator = mtr::index_forward_iterator<string,char>;
  using executor = mtr::executor<iterator,int,char>;

  auto fn = [](int a, char c)->int { return a + 1; };
  executor exec(fn);
  string s("Hello World");

  auto cnt = exec(s.iterator(), 0);

  SHOULD_BE_EQ(cnt, 11, "Call function correct number of times");
}


void test_iterators_executor(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
