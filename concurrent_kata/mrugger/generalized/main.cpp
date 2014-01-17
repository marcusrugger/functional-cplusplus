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
  mtr::vector<mtr::string> v1;
  auto v2 = v1.append(mtr::string("String one"));
  auto v3 = v2.append(mtr::string("String two"));
  v3.foreach(0)([](int a, const mtr::string &s) -> int { printf("string: %s\n", s.c_str()); });
}


int main(void)
{
  test_string();
  test_vector();

  test_vector_with_strings();

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
