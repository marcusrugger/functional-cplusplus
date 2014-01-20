#include <iostream>
#include <fstream>
#include <functional>
#include <mtr.string.h>
#include <mtr.vector.h>

class line_accumulator;

using string = mtr::string;
using vector = mtr::vector<string>;
using iterator = mtr::input_stream_iterator<std::ifstream, char>;
using foreach = mtr::foreach<iterator, line_accumulator, char>;


class line_accumulator
{
public:

  const string _string;
  const vector _vector;


  line_accumulator(const string &s, const vector &v)
  : _string(s), _vector(v)
  {}


public:

  line_accumulator(void)
  {}

  line_accumulator(const line_accumulator &other)
  : _string(other._string), _vector(other._vector)
  {}

  line_accumulator fn(char c) const
  {
    if (c == '\n')
      return line_accumulator(string(), _vector.append(_string));
    else
      return line_accumulator(_string.append(c), _vector);
  }

};


int main(void)
{
  const auto filename = string("file");//"/home/marcus/tmp/intel_display.c");
  auto stream = new std::ifstream(filename.c_str(), std::ifstream::in);
  iterator it(stream);
  auto fn = [](const line_accumulator &a, char c)->line_accumulator
  { return a.fn(c); };

  auto f = foreach(it, line_accumulator());
  auto new_lacc = f(fn);

  printf("cnt: %d\n", (int) new_lacc._vector.length());
  auto v = new_lacc._vector;
  v.foreach(0)([](int, const string &s)->int { printf("%s\n", s.c_str()); });
}
