#include "test.main.h"
#include <iostream>


static void test_default_constructor(void)
{
  using enumerator = mtr::backward_enumerator<int>;

  auto e = enumerator();
  SHOULD_BE_TRUE(e.is_empty(), "Default constructor should give 'empty' enumerator");
}


static void test_range_constructor(void)
{
  using enumerator = mtr::backward_enumerator<int>;

  const int start = 1;
  const int end   = 2;
  auto e = enumerator(start, end);
  SHOULD_BE_FALSE(e.is_empty(), "Enumerator should not be empty");
  SHOULD_BE_EQ(e(), end, "Value should be equal to end value");
  SHOULD_BE_FALSE(e.next().is_empty(), "Next position should not be empty");
  SHOULD_BE_EQ(e.next()(), end-1, "Next value should equal end - 1 value");
  SHOULD_BE_TRUE(e.next().next().is_empty(), "Next, next position should be empty");
}


static void test_enumeration(void)
{
  using enumerator = mtr::backward_enumerator<int>;

  const int start = 111;
  const int end   = 222;
  auto e = enumerator(start, end);

  auto fn = [](int a, int i)->int { return a + i; };
  auto a = e.foreach(0)(fn);
  SHOULD_BE_EQ(a, (end+1-start)*(start+end)/2, "Sum of the enumeration");
}


static void test_enumeration_with_chars(void)
{
  using enumerator = mtr::backward_enumerator<char>;
  using string = mtr::string;
  using foreach = mtr::foreach<enumerator,string,char>;

  auto en = enumerator('a', 'z');
  auto fe = foreach(en, string());
  auto fn = [](string a, char i)->string { return a.append(i); };
  auto st = fe(fn);

  SHOULD_BE_EQ(st, string("zyxwvutsrqponmlkjihgfedcba"), "Concatenation of characters");
}


static void test_enumeration_with_step(void)
{
  using enumerator = mtr::backward_enumerator<int>;
  auto fn = [](int a, int i)->int { return a + i; };

  {
    auto e = enumerator(3, 99, 2);
    auto a = e.foreach(0)(fn);
    SHOULD_BE_EQ(a, 2499, "Sum of the enumeration");
  }

  {
    auto e = enumerator(2, 99, 2);
    auto a = e.foreach(0)(fn);
    SHOULD_BE_EQ(a, 2499, "Sum of the enumeration");
  }
}


void test_backward_enumerator(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_default_constructor();
  test_range_constructor();
  test_enumeration();
  test_enumeration_with_chars();
  test_enumeration_with_step();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
