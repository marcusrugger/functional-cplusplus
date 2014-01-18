#include <iostream>
#include <string>
#include "main.h"


void test_string(void)
{
  auto to_upper = [](char c) -> char { return c >= 'a' && c <= 'z' ? c - 32 : c; };
  auto to_lower = [](char c) -> char { return c >= 'A' && c <= 'Z' ? c + 32 : c; };
  auto print_with_brackets = [](int a, char c) -> int { printf("[%c]", c); };

  mtr::string somestring("SoMe StRiNg");

  auto fmap = somestring.fmap();
  mtr::string uppercase = fmap(to_upper);
  mtr::string lowercase = fmap(to_lower);

  uppercase.foreach(0)(print_with_brackets);
  printf("\n");
  lowercase.foreach(0)(print_with_brackets);
  printf("\n");
  somestring.foreach(0)(print_with_brackets);
  printf("\n");

  mtr::string howdy("Howdy ");
  mtr::string doody("doody");
  mtr::string string = howdy.append(doody);

  string.foreach(0)([](int a, char c) -> int { printf("[%c]", c); });
  printf("\n");

  string.iterator().foreach(0)([](int a, char c) -> int { printf(">%c<", c); });
  printf("\n");
  
  auto g = string.back_iterator().foreach(0);
  g([](int a, char c) -> int { printf("<%c>", c); });
  printf("\n");

  std::string str = "Hello world!";
}

#if 0
class shared_object
{
public:

  static int _count;

  shared_object(void)
  : _count(0)
  {
    printf("shared_object::constructor\n");
  }

  shared_object

  ~shared_object(void)
  {
    printf("shared_object::destructor\n");
  }

};
#endif

class test_class
{
public:

  static int _instances;
  static int _live_instances;

  int _instance;
  int _copied_from;

  test_class(void)
  : _instance(_instances), _copied_from(_instances)
  {
    ++_instances;
    ++_live_instances;
    printf("test_class void constructor:    %3d, %3d, %3d.\n", _instance, _live_instances, _copied_from);
  }

  test_class(const test_class &other)
  : _instance(_instances), _copied_from(other._instance)
  {
    ++_instances;
    ++_live_instances;
    printf("test_class copy constructor:    %3d, %3d, %3d.\n", _instance, _live_instances, _copied_from);
  }

  ~test_class(void)
  {
    --_live_instances;
    printf("test_class destructor:          %3d, %3d, %3d.\n", _instance, _live_instances, _copied_from);
  }

#if 0
  test_class &operator = (const test_class &other)
  {
    _assigned_from = other._instance;
    printf("test_class assignment operator: %3d, %3d, %3d.\n", _instance, _copied_from, _assigned_from);
    return (*this);
  }
#endif
};

int test_class::_instances;
int test_class::_live_instances;

void test_vector(void)
{
  auto sum_the_ints = [](int a, int i) -> int { return a + i; };
  auto sum_the_squares = [](int a, int i) -> int { return a + i*i; };

  int some_ints[] = { 1, 2, 3, 4, 5 };
  mtr::vector<int> integers(some_ints, 5);
  auto array = integers.append(6);
  int sum = array.foreach(0)(sum_the_ints);
  int sum_of_squares = array.foreach(0)(sum_the_squares);
  std::cout << "array count: " << array.length() << ", " << sum << ", " << sum_of_squares << std::endl;

  mtr::vector<test_class> v1;
  auto v2 = v1.append(test_class());
  auto v3 = v2.append(test_class());
  printf("All done with test_vector.\n");
}


void test_vector_with_strings(void)
{
  {
    mtr::vector<mtr::string> v1;
    auto v2 = v1.append(mtr::string("String one"))
                .append(mtr::string("String two"))
                .append(mtr::string("String three"))
                .append(mtr::string("String four"))
                .append(mtr::string("String five"))
                .append(mtr::string("String six"));

    v2.foreach(0)([](int a, const mtr::string &s) -> int { std::cout << s << std::endl; });
  }
}


void test_vector_with_string_pointers(void)
{
  using shared_string = std::shared_ptr<mtr::string>;
  {
    mtr::vector<shared_string> v1;
    auto v2 = v1.append(shared_string(new mtr::string("Shared string one")))
                .append(shared_string(new mtr::string("Shared string two")))
                .append(shared_string(new mtr::string("Shared string three")))
                .append(shared_string(new mtr::string("Shared string four")))
                .append(shared_string(new mtr::string("Shared string five")))
                .append(shared_string(new mtr::string("Shared string six")));

    v2.foreach(0)([](int a, const shared_string &s) -> int { std::cout << *s << std::endl; });
    v2.foreach(0)([](int, const shared_string &s) -> int { std::cout << *s << std::endl; });
  }
}


class curry_f
{
public:

  const int _x, _y;

  curry_f(int x, int y)
  : _x(x), _y(y)
  {}

  int operator ()(int z) const
  { return _x * _y + z; }

};


class curry_g
{
public:

  const int _x;

  curry_g(int x)
  : _x(x)
  {}

  curry_f operator ()(int y) const
  { return curry_f(_x, y); }

};


class curry_h
{
public:

  curry_h(void)
  {}

  curry_g operator ()(int x) const
  { return curry_g(x); }

};


int main(void)
{
  curry_h h;
  auto g = h(2);
  auto f = g(3);
  printf("f = %d\n", f(4));

  printf("3 * 4 + 5 = %d\n", h(3)(4)(5));
  //test_string();
  //test_vector();

  //test_vector_with_strings();
  //test_vector_with_string_pointers();

//  printf("live instances: %d\n", test_class::_live_instances);

#if 0
  {
    auto it = mtr::index_forward_iterator<const std::string, const char>(str, 0, str.length()-1);
    std::cout << it() << std::endl;
    std::cout << it.next()() << std::endl;
    std::cout << it.next()() << std::endl;

    auto f = it.foreach(0);
    f([](int a, char c) -> int { printf("%c", c); });
    printf("\n");
    auto r = f([](int a, char c) -> int { return a+c; });
    printf("Result: %d\n", r);
    auto s = f([](int a, char c) -> int { return a+c*c; });
    printf("Result: %d\n", s);
  }

  {
    auto it = mtr::index_backward_iterator<const std::string, const char>(str, 0, str.length()-1);
    std::cout << it() << std::endl;
    std::cout << it.next()() << std::endl;
    std::cout << it.next()() << std::endl;

    auto f = it.foreach(0);
    f([](int a, char c) -> int { printf("%c", c); });
    printf("\n");
    auto r = f([](int a, char c) -> int { return a+c; });
    printf("Result: %d\n", r);
    auto s = f([](int a, char c) -> int { return a+c*c; });
    printf("Result: %d\n", s);
  }
#endif
}
