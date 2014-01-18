#include "test.main.h"


static void test_with_string(void)
{
  using string = mtr::string;
  using iterator = mtr::index_forward_iterator<string,char>;

  iterator it(string("Hello World"), 3, 7);

  SHOULD_BE_EQ(it.to_i(), 3, "Current position should be initial position");
  SHOULD_BE_EQ(it.next().to_i(), 4, "Next position should be initial position + 1");
  SHOULD_BE_TRUE(it.is_more(), "There should be more");
  SHOULD_BE_EQ(it(), 'l', "Current character");
  SHOULD_BE_EQ(it.next()(), 'o', "Current character");

  auto cnt_fn = [](int a, char c)->int { return a + 1; };
  auto cnt = it.foreach(0)(cnt_fn);

  SHOULD_BE_EQ(cnt, 5, "Should have iterated over 5 characters");
}


void test_iterators_index_forward_iterator(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_with_string();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
