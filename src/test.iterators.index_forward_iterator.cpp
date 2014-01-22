#include "test.main.h"


static void test_with_string_1(void)
{
  using string = mtr::string;
  using iterator = mtr::index_forward_iterator<string,char>;

  iterator it(string("Hello World"), 3, 3);

  SHOULD_BE_EQ(it.to_i(), 3, "Current position should be initial position");
  SHOULD_BE_FALSE(it.is_empty(), "The iterator should not be empty");
  SHOULD_BE_EQ(it(), 'l', "Current character");

  auto cnt_fn = [](int a, char c)->int { return a + 1; };
  auto cnt = it.foreach(0)(cnt_fn);

  SHOULD_BE_EQ(cnt, 1, "Should have iterated over 1 characters");
}


static void test_with_string_2(void)
{
  using string = mtr::string;
  using iterator = mtr::index_forward_iterator<string,char>;

  iterator it(string("Hello World"), 3, 4);

  SHOULD_BE_EQ(it.to_i(), 3, "Current position should be initial position");
  SHOULD_BE_EQ(it.next().to_i(), 4, "Next position should be initial position + 1");
  SHOULD_BE_FALSE(it.is_empty(), "The iterator should not be empty");
  SHOULD_BE_FALSE(it.next().is_empty(), "The next iterator should not be empty");
  SHOULD_BE_TRUE(it.next().next().is_empty(), "The next, next iterator should be empty");
  SHOULD_BE_EQ(it(), 'l', "Current character");
  SHOULD_BE_EQ(it.next()(), 'o', "Current character");

  auto cnt_fn = [](int a, char c)->int { return a + 1; };
  auto cnt = it.foreach(0)(cnt_fn);

  SHOULD_BE_EQ(cnt, 2, "Should have iterated over 2 characters");
}


static void test_with_string_5(void)
{
  using string = mtr::string;
  using iterator = mtr::index_forward_iterator<string,char>;

  iterator it(string("Hello World"), 3, 7);

  SHOULD_BE_EQ(it.to_i(), 3, "Current position should be initial position");
  SHOULD_BE_EQ(it.next().to_i(), 4, "Next position should be initial position + 1");
  SHOULD_BE_FALSE(it.is_empty(), "The iterator should not be empty");
  SHOULD_BE_FALSE(it.next().is_empty(), "The next iterator should not be empty");
  SHOULD_BE_EQ(it(), 'l', "Current character");
  SHOULD_BE_EQ(it.next()(), 'o', "Current character");

  auto cnt_fn = [](int a, char c)->int { return a + 1; };
  auto cnt = it.foreach(0)(cnt_fn);

  SHOULD_BE_EQ(cnt, 5, "Should have iterated over 5 characters");
}


static void test_skip(void)
{
  using string = mtr::string;

  auto cnt_fn = [](int a, char c)->int { return a + 1; };
  auto cnt = string("Hello World").iterator().skip(6).foreach(0)(cnt_fn);

  SHOULD_BE_EQ(cnt, 5, "Should have iterated over 5 characters");
}


static void test_drop(void)
{
  using string = mtr::string;

  auto cnt_fn = [](int a, char c)->int { return a + 1; };
  auto cnt = string("Hello World").iterator().drop(6).foreach(0)(cnt_fn);

  SHOULD_BE_EQ(cnt, 5, "Should have iterated over 5 characters");
}


static void test_take(void)
{
  using string = mtr::string;

  auto cnt_fn = [](int a, char c)->int { return a + 1; };
  auto cnt = string("Hello World").iterator().take(4).foreach(0)(cnt_fn);

  SHOULD_BE_EQ(cnt, 4, "Should have iterated over 4 characters");
}


static void test_is_empty(void)
{
  using string = mtr::string;
  using iterator = mtr::index_forward_iterator<string,char>;

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


void test_iterators_index_forward_iterator(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_with_string_1();
  test_with_string_2();
  test_with_string_5();
  test_skip();
  test_drop();
  test_take();
  test_is_empty();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
