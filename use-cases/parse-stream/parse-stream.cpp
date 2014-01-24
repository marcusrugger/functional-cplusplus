#include <iostream>
#include <fstream>
#include <functional>
#include "json.parser.h"


using iterator = mtr::input_stream_iterator<std::ifstream, char>;
using foreach = mtr::foreach<iterator, json_accumulator, char>;


int main(void)
{
  const auto filename = string("./sample.json");
  auto stream = new std::ifstream(filename.c_str(), std::ifstream::in);
  auto fn = [](const json_accumulator &a, char c)->json_accumulator { printf("lambda: 0x%02x\n", c); return a(c); };

  auto f = foreach(iterator(stream), json_accumulator());
  auto result = f(fn);
}
