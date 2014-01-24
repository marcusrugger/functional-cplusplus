#include <iostream>
#include <fstream>
#include <functional>
#include "json.parser.h"

class json_accumulator;

using iterator = mtr::input_stream_iterator<std::ifstream, char>;
using foreach = mtr::foreach<iterator, json_accumulator, char>;

class json_accumulator
{
public:

  const std::shared_ptr<const json_parser_base> _parser;

  json_accumulator(void)
  : _parser(new json_parser_base())
  {}

  json_accumulator(const json_accumulator &other)
  : _parser(other._parser)
  {}

  json_accumulator(const json_parser_base *parser)
  : _parser(parser)
  {}

  json_accumulator operator ()(const char c) const
  { return json_accumulator((*_parser)(c)); }

};


int main(void)
{
  const auto filename = string("./sample.json");
  auto stream = new std::ifstream(filename.c_str(), std::ifstream::in);
  auto fn = [](const json_accumulator &a, char c)->json_accumulator { return a(c); };

  auto f = foreach(iterator(stream), json_accumulator());
  auto result = f(fn);
}
