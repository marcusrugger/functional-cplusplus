#include "test.main.h"


static void test_string_append_string(void)
{
  using string = mtr::string;

  string s("Hello world");
  SHOULD_BE_EQ((int) s.length(), 11, "Length of string");

  auto r = s.append(string(", today is a good day to die."));
  SHOULD_BE_EQ((int) r.length(), 40, "Length of string");
  SHOULD_BE_EQ((int) s.length(), 11, "Length of string");
}


static void test_wstring_append_string(void)
{
  using string = mtr::wstring;

  string s(L"Hello world");
  SHOULD_BE_EQ((int) s.length(), 11, "Length of string");

  auto r = s.append(string(L", today is a good day to die."));
  SHOULD_BE_EQ((int) r.length(), 40, "Length of string");
  SHOULD_BE_EQ((int) s.length(), 11, "Length of string");
}


static void test_string_append_char(void)
{
  using string = mtr::string;

  string s("Hello world");
  SHOULD_BE_EQ((int) s.length(), 11, "Length of string");

  auto t = s.append(',');
  SHOULD_BE_EQ((int) t.length(), 12, "Length of string");
  SHOULD_BE_EQ((int) s.length(), 11, "Length of string");

  auto u = t.append(' ');
  SHOULD_BE_EQ((int) u.length(), 13, "Length of string");
  SHOULD_BE_EQ((int) t.length(), 12, "Length of string");
  SHOULD_BE_EQ((int) s.length(), 11, "Length of string");
}


static void test_wstring_append_wchar(void)
{
  using string = mtr::wstring;

  string s(L"Hello world");
  SHOULD_BE_EQ((int) s.length(), 11, "Length of string");

  auto t = s.append(L',');
  SHOULD_BE_EQ((int) t.length(), 12, "Length of string");
  SHOULD_BE_EQ((int) s.length(), 11, "Length of string");

  auto u = t.append(L' ');
  SHOULD_BE_EQ((int) u.length(), 13, "Length of string");
  SHOULD_BE_EQ((int) t.length(), 12, "Length of string");
  SHOULD_BE_EQ((int) s.length(), 11, "Length of string");
}


static void test_string_compare(void)
{
  using string = mtr::string;

  string r("Hello planet");
  string s("Hello world");
  string t("Hello world");
  string u("Hello world, another day!");
  string v("Hello zenith");

  SHOULD_BE_TRUE(s.compare(r) >  0, "s is >  r");
  SHOULD_BE_TRUE(s.compare(t) == 0, "s is == t");
  SHOULD_BE_TRUE(s.compare(u) <  0, "s is <  u");
  SHOULD_BE_TRUE(s.compare(v) <  0, "s is <  u");
}


static void test_wstring_compare(void)
{
  using string = mtr::wstring;

  string r(L"Hello planet");
  string s(L"Hello world");
  string t(L"Hello world");
  string u(L"Hello world, another day!");
  string v(L"Hello zenith");

  SHOULD_BE_TRUE(s.compare(r) >  0, "compare(): s is >  r");
  SHOULD_BE_TRUE(s.compare(t) == 0, "compare(): s is == t");
  SHOULD_BE_TRUE(s.compare(u) <  0, "compare(): s is <  u");
  SHOULD_BE_TRUE(s.compare(v) <  0, "compare(): s is <  u");
}


static void test_string_operator_equality(void)
{
  using string = mtr::string;

  string r("Hello planet");
  string s("Hello world");
  string t("Hello world");
  string u("Hello world, another day!");
  string v("Hello zenith");

  SHOULD_BE_FALSE(s == r, "operator ==(): s is >  r");
  SHOULD_BE_TRUE (s == t, "operator ==(): s is == t");
  SHOULD_BE_FALSE(s == u, "operator ==(): s is <  u");
  SHOULD_BE_FALSE(s == v, "operator ==(): s is <  u");
}


void test_string_string(void)
{
  std::cout << "BEGIN: ***** " << __FILE__ << " *****" << std::endl;
  test_string_append_string();
  test_wstring_append_string();
  test_string_append_char();
  test_wstring_append_wchar();
  test_string_compare();
  test_wstring_compare();
  test_string_operator_equality();
  std::cout << "END:   ***** " << __FILE__ << " *****" << std::endl;
}
