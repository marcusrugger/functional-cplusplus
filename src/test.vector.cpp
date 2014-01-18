#include "test.main.h"


static void test_vector_append_with_strings(void)
{
  using string = mtr::string;
  using vector = mtr::vector<string>;

  const char str1[] = "Hello world";
  const char str2[] = "Goodbye";
  const char str3[] = "Cruel world";

  vector v = vector(string(str1));
  SHOULD_BE_EQ((int) v.length(), 1, "Length of vector");

  auto x = v.append(string(str2));
  SHOULD_BE_EQ((int) x.length(), 2, "Length of vector");

  auto y = x.append(string(str3));
  SHOULD_BE_EQ((int) y.length(), 3, "Length of vector");

  auto it = y.iterator();
  SHOULD_BE_EQ(it(), string(str1), "First string should be the first one appended to vector");
  SHOULD_BE_EQ(it.next()(), string(str2), "Second string should be the second one appended to vector");
  SHOULD_BE_EQ(it.next().next()(), string(str3), "Third string should be the third one appended to vector");
}


static void test_vector_back_iterator(void)
{
  using string = mtr::string;
  using vector = mtr::vector<string>;

  const char str1[] = "Hello world";
  const char str2[] = "Goodbye";

  vector v;
  SHOULD_BE_EQ((int) v.length(), 0, "Length of vector");

  auto x = v.append(string(str1));
  SHOULD_BE_EQ((int) x.length(), 1, "Length of vector");

  auto y = x.append(string(str2));
  SHOULD_BE_EQ((int) y.length(), 2, "Length of vector");

  auto it = y.back_iterator();
  SHOULD_BE_EQ(it(), string(str2), "First string should be the second one appended to vector");
  SHOULD_BE_EQ(it.next()(), string(str1), "Second string should be the first one appended to vector");
}


void test_vector(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_vector_append_with_strings();
  test_vector_back_iterator();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
