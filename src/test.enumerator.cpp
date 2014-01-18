#include "test.main.h"


static void test_default_constructor(void)
{
  using enum_int = mtr::forward_enumerator<int>;

  auto e = enum_int();
  SHOULD_BE_TRUE(e.is_done(), "Default constructor should give 'empty' enumerator");
}


static void test_range_constructor(void)
{
  using enum_int = mtr::forward_enumerator<int>;

  const int start = 1;
  const int end   = 2;
  auto e = enum_int(start, end);
  SHOULD_BE_FALSE(e.is_done(), "Enumerator should not be done");
  SHOULD_BE_EQ(e(), start, "Value should be equal to start value");
  SHOULD_BE_FALSE(e.next().is_done(), "Next position should not be done");
  SHOULD_BE_EQ(e.next()(), start+1, "Next value should equal start value + 1");
  SHOULD_BE_TRUE(e.next().next().is_done(), "Next, next position should be done");
}


void test_enumerator(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_default_constructor();
  test_range_constructor();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
