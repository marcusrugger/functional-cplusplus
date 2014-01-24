#include "test.main.h"


static void test_vector_push_tail_with_strings(void)
{
  using string = mtr::string;
  using vector = mtr::vector<string>;

  const char str1[] = "Hello world";
  const char str2[] = "Goodbye";
  const char str3[] = "Cruel world";

  vector v = vector(string(str1));
  SHOULD_BE_EQ((int) v.length(), 1, "Length of vector");

  auto x = v.push_tail(string(str2));
  SHOULD_BE_EQ((int) x.length(), 2, "Length of vector");

  auto y = x.push_tail(string(str3));
  SHOULD_BE_EQ((int) y.length(), 3, "Length of vector");

  auto it = y.iterator();
  SHOULD_BE_EQ(it(), string(str1), "First string should be the first one appended to vector");
  SHOULD_BE_EQ(it.next()(), string(str2), "Second string should be the second one appended to vector");
  SHOULD_BE_EQ(it.next().next()(), string(str3), "Third string should be the third one appended to vector");
}


static void test_vector_push_head_with_strings(void)
{
  using string = mtr::string;
  using vector = mtr::vector<string>;

  const char str1[] = "Hello world";
  const char str2[] = "Goodbye";
  const char str3[] = "Cruel world";

  vector v = vector(string(str1));
  SHOULD_BE_EQ((int) v.length(), 1, "Length of vector");

  auto x = v.push_head(string(str2));
  SHOULD_BE_EQ((int) x.length(), 2, "Length of vector");

  auto y = x.push_head(string(str3));
  SHOULD_BE_EQ((int) y.length(), 3, "Length of vector");

  auto it = y.iterator();
  SHOULD_BE_EQ(it(), string(str3), "First string should be the first one appended to vector");
  SHOULD_BE_EQ(it.next()(), string(str2), "Second string should be the second one appended to vector");
  SHOULD_BE_EQ(it.next().next()(), string(str1), "Third string should be the third one appended to vector");
}


static void test_vector_back_iterator(void)
{
  using string = mtr::string;
  using vector = mtr::vector<string>;

  const char str1[] = "Hello world";
  const char str2[] = "Goodbye";

  vector v;
  SHOULD_BE_EQ((int) v.length(), 0, "Length of vector");

  auto x = v.push_tail(string(str1));
  SHOULD_BE_EQ((int) x.length(), 1, "Length of vector");

  auto y = x.push_tail(string(str2));
  SHOULD_BE_EQ((int) y.length(), 2, "Length of vector");

  auto it = y.back_iterator();
  SHOULD_BE_EQ(it(), string(str2), "First string should be the second one appended to vector");
  SHOULD_BE_EQ(it.next()(), string(str1), "Second string should be the first one appended to vector");
}


static void test_append_vector(void)
{
  using string = mtr::string;
  using vector = mtr::vector<string>;

  const char *strs[] = { "string 1",
                         "string 2",
                         "string 3",
                         "string 4" };

  vector a = vector().push_tail(string(strs[0]))
                     .push_tail(string(strs[1]));

  vector b = vector().push_tail(string(strs[2]))
                     .push_tail(string(strs[3]));

  SHOULD_BE_EQ((int) a.length(), 2, "vector a should have two items");
  SHOULD_BE_EQ((int) b.length(), 2, "vector b should have two items");

  vector c = a.append(b);

  SHOULD_BE_EQ((int) a.length(), 2, "vector a should have two items");
  SHOULD_BE_EQ((int) b.length(), 2, "vector b should have two items");
  SHOULD_BE_EQ((int) c.length(), 4, "vector c should have four items");

  auto cmp_fn = [&](int a, string s)
  {
    SHOULD_BE_EQ(s, string(strs[a]), "Strings should be equal");
    return a+1;
  };
  c.foreach(0)(cmp_fn);
}


static void test_head_and_tail(void)
{
  using string = mtr::string;
  using vector = mtr::vector<string>;

  const char *strs[] = { "string 1",
                         "string 2",
                         "string 3",
                         "string 4" };

  auto v = vector().push_tail(string(strs[0]))
                   .push_tail(string(strs[1]))
                   .push_tail(string(strs[2]))
                   .push_tail(string(strs[3]));

  SHOULD_BE_EQ(v.head(), string(strs[0]), "head should equal first string");
  SHOULD_BE_EQ(v.tail(), string(strs[3]), "tail should equal last string");
}


static void test_pop_tail(void)
{
  using string = mtr::string;
  using vector = mtr::vector<string>;

  const char *strs[] = { "string 1",
                         "string 2",
                         "string 3",
                         "string 4" };

  auto v = vector().push_tail(string(strs[0]))
                   .push_tail(string(strs[1]))
                   .push_tail(string(strs[2]))
                   .push_tail(string(strs[3]));

  SHOULD_BE_EQ(v.tail(), string(strs[3]), "tail should equal last string");
  auto x = v.pop_tail();
  SHOULD_BE_EQ(x.tail(), string(strs[2]), "tail should equal next to last string");
}


static void test_pop_head(void)
{
  using string = mtr::string;
  using vector = mtr::vector<string>;

  const char *strs[] = { "string 1",
                         "string 2",
                         "string 3",
                         "string 4" };

  auto v = vector().push_tail(string(strs[0]))
                   .push_tail(string(strs[1]))
                   .push_tail(string(strs[2]))
                   .push_tail(string(strs[3]));

  SHOULD_BE_EQ(v.head(), string(strs[0]), "tail should equal first string");
  auto x = v.pop_head();
  SHOULD_BE_EQ(x.head(), string(strs[1]), "tail should equal second string");
}


static void test_put_tail(void)
{
  using string = mtr::string;
  using vector = mtr::vector<string>;

  const char *strs[] = { "string 1",
                         "string 2",
                         "string 3",
                         "string 4" };

  const char put_str[] = "put string";

  auto v = vector().push_tail(string(strs[0]))
                   .push_tail(string(strs[1]))
                   .push_tail(string(strs[2]))
                   .push_tail(string(strs[3]));

  SHOULD_BE_EQ(v.tail(), string(strs[3]), "tail should equal last string");
  auto x = v.put_tail(string(put_str));
  SHOULD_BE_EQ(x.tail(), string(put_str), "tail should equal put string");
}


void test_vector(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_vector_push_tail_with_strings();
  test_vector_push_head_with_strings();
  test_vector_back_iterator();
  test_append_vector();
  test_head_and_tail();
  test_pop_tail();
  test_put_tail();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
