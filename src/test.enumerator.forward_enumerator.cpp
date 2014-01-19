#include "test.main.h"


static void test_default_constructor(void)
{
  using enum_int = mtr::forward_enumerator<int>;

  auto e = enum_int();
  SHOULD_BE_TRUE(e.is_empty(), "Default constructor should give 'empty' enumerator");
}


static void test_range_constructor(void)
{
  using enum_int = mtr::forward_enumerator<int>;

  const int start = 1;
  const int end   = 2;
  auto e = enum_int(start, end);
  SHOULD_BE_FALSE(e.is_empty(), "Enumerator should not be empty");
  SHOULD_BE_EQ(e(), start, "Value should be equal to start value");
  SHOULD_BE_FALSE(e.next().is_empty(), "Next position should not be empty");
  SHOULD_BE_EQ(e.next()(), start+1, "Next value should equal start value + 1");
  SHOULD_BE_TRUE(e.next().next().is_empty(), "Next, next position should be empty");
}


static void test_enumeration(void)
{
  using enumerator = mtr::forward_enumerator<int>;

  const int start = 111;
  const int end   = 222;
  auto e = enumerator(start, end);

  auto fn = [](int a, int i)->int { return a + i; };
  auto a = e.foreach(0)(fn);
  SHOULD_BE_EQ(a, (end+1-start)*(start+end)/2, "Sum of the enumeration");
}


static void test_enumeration_with_chars(void)
{
  using enumerator = mtr::forward_enumerator<char>;
  using string = mtr::string;
  using foreach = mtr::foreach<enumerator,string,char>;

  auto en = enumerator('a', 'z');
  auto fe = foreach(en, string());
  auto fn = [](string a, char i)->string { return a.append(i); };
  auto st = fe(fn);

  SHOULD_BE_EQ(st, string("abcdefghijklmnopqrstuvwxyz"), "Concatenation of characters");
}


void test_forward_enumerator(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_default_constructor();
  test_range_constructor();
  test_enumeration();
  test_enumeration_with_chars();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
