#include <iostream>
#include <string>
#include "main.h"


int main(void)
{
  mtr::string somestring("upper case");
  auto to_lower = somestring.fmap();
  mtr::string mynewstring = to_lower([](char c) -> char { return c >= 'a' && c <= 'z' ? c - 32 : c; });
  mynewstring.foreach(0)([](int a, char c) -> int { printf("[%c]", c); });
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
