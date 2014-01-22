#include "test.main.h"


static void test_with_string_1(void)
{
  using string = mtr::string;
  using iterator = mtr::index_backward_iterator<string,char>;

  iterator it(string("Hello World"), 7, 7);

  SHOULD_BE_EQ(it.to_i(), 7, "Current position should be initial position");
  SHOULD_BE_FALSE(it.is_empty(), "The iterator is not empty");
  SHOULD_BE_TRUE(it.next().is_empty(), "The next iterator should be empty");
  SHOULD_BE_EQ(it(), 'o', "Current character");

  auto cnt_fn = [](int a, char c)->int { return a + 1; };
  auto cnt = it.foreach(0)(cnt_fn);

  SHOULD_BE_EQ(cnt, 1, "Should have iterated over 1 character");
}


static void test_with_string_2(void)
{
  using string = mtr::string;
  using iterator = mtr::index_backward_iterator<string,char>;

  iterator it(string("Hello World"), 6, 7);

  SHOULD_BE_EQ(it.to_i(), 7, "Current position should be initial position");
  SHOULD_BE_EQ(it.next().to_i(), 6, "Next position should be initial position - 1");
  SHOULD_BE_FALSE(it.is_empty(), "The iterator should not be empty");
  SHOULD_BE_FALSE(it.next().is_empty(), "The next iterator should not be empty");
  SHOULD_BE_TRUE(it.next().next().is_empty(), "The next, next iterator should be empty");
  SHOULD_BE_EQ(it(), 'o', "Current character");
  SHOULD_BE_EQ(it.next()(), 'W', "Current character");

  auto cnt_fn = [](int a, char c)->int { return a + 1; };
  auto cnt = it.foreach(0)(cnt_fn);

  SHOULD_BE_EQ(cnt, 2, "Should have iterated over 2 characters");
}


static void test_with_string_5(void)
{
  using string = mtr::string;
  using iterator = mtr::index_backward_iterator<string,char>;

  iterator it(string("Hello World"), 3, 7);

  SHOULD_BE_EQ(it.to_i(), 7, "Current position should be initial position");
  SHOULD_BE_EQ(it.next().to_i(), 6, "Next position should be initial position - 1");
  SHOULD_BE_FALSE(it.is_empty(), "The iterator should not be empty");
  SHOULD_BE_FALSE(it.next().is_empty(), "The next iterator should not be empty");
  SHOULD_BE_EQ(it(), 'o', "Current character");
  SHOULD_BE_EQ(it.next()(), 'W', "Current character");

  auto cnt_fn = [](int a, char c)->int { return a + 1; };
  auto cnt = it.foreach(0)(cnt_fn);

  SHOULD_BE_EQ(cnt, 5, "Should have iterated over 5 characters");
}


static void test_skip(void)
{
  using string = mtr::string;

  auto cnt_fn = [](int a, char c)->int { return a + 1; };
  auto cnt = string("Hello World").back_iterator().skip(6).foreach(0)(cnt_fn);

  SHOULD_BE_EQ(cnt, 5, "Should have iterated over 5 characters");
}


static void test_is_empty(void)
{
  using string = mtr::string;
  using iterator = mtr::index_backward_iterator<string,char>;

  {
    iterator it(string("Hello World"), 3, 7);
    SHOULD_BE_FALSE(it.is_empty(), "is_empty() on iterator that isn't empty");
  }

  {
    iterator it(string("Hello World"), 3, 2);
    SHOULD_BE_TRUE(it.is_empty(), "is_empty() on iterator that is empty");
  }

  {
    iterator it(string("Hello World"), 3, 3);
    SHOULD_BE_FALSE(it.is_empty(), "is_empty() on iterator that has one item");
    SHOULD_BE_TRUE(it.next().is_empty(), "is_empty() on next of iterator that has one item");
  }
}


void test_iterators_index_backward_iterator(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_with_string_1();
  test_with_string_2();
  test_with_string_5();
  test_skip();
  test_is_empty();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
