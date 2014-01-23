#include <iostream>
#include <fstream>
#include <functional>
#include <mtr.string.h>
#include <mtr.vector.h>

class json_accumulator;
class json_parser_base;
class json_parser_object;
class json_parser_array;
class json_parser_string;

using string = mtr::string;
using json_list = mtr::vector<json_parser_base>;
using json_pair_list = mtr::vector<std::pair<string,json_parser_base>>;
using iterator = mtr::input_stream_iterator<std::ifstream, char>;
using foreach = mtr::foreach<iterator, json_accumulator, char>;


class json_parser_base
{
public:

  static const string number_set;
  static const string white_space_set;

  const json_list _list;


  json_parser_base(const json_parser_base &other)
  : _list(other._list)
  {}


public:

  json_parser_base(void)
  {}


  virtual json_parser_base *operator ()(const char c) const;

  virtual json_parser_base *clone(void) const
  { return new json_parser_base(*this); }

};


class json_parser_object : public json_parser_base
{
public:

  const json_pair_list _list;

  json_parser_object(const json_parser_base &other)
  : json_parser_base(other)
  { printf("Hello from json_parser_object\n"); }

  json_parser_object(const json_parser_object &other)
  : json_parser_base(other)
  { printf("Hello from json_parser_object copy constructor\n"); }

  virtual json_parser_base *operator ()(const char c) const;

  virtual json_parser_base *clone(void) const
  { return new json_parser_object(*this); }
};


class json_parser_array : public json_parser_base
{
public:

  json_parser_array(const json_parser_base &other)
  : json_parser_base(other)
  {}

  virtual json_parser_base *operator ()(const char c) const
  {}

  virtual json_parser_base *clone(void) const
  { return new json_parser_array(*this); }
};


class json_parser_string : public json_parser_base
{
public:

  const std::shared_ptr<const json_parser_base> _parent;
  const string _string;

  json_parser_string(const json_parser_base *parent)
  : json_parser_base(), _parent(parent)
  {}

  json_parser_string(const json_parser_string &other)
  : json_parser_base(other), _parent(other._parent), _string(other._string)
  {}

  json_parser_string(const json_parser_string &other, const string &s)
  : json_parser_base(other), _parent(other._parent), _string(s)
  {}

  virtual json_parser_base *operator ()(const char c) const
  {
    if ('"' == c)
      throw std::runtime_error("json_parser_string: all done");
    else
      return new json_parser_string((*this), _string.append(c));
  }

  virtual json_parser_base *clone(void) const
  { return new json_parser_string(*this); }
};


const string json_parser_base::number_set("-0123456789");
const string json_parser_base::white_space_set(" \t\n\r");


json_parser_base *json_parser_base::operator ()(const char c) const
{
  if (white_space_set.is_included(c))
    return new json_parser_base(*this);
  else if ('{' == c)
    return new json_parser_object(*this);
  else if ('[' == c)
    return new json_parser_array(*this);
  else
    throw std::runtime_error("unexpected character in json object");
}


json_parser_base *json_parser_object::operator ()(const char c) const
{
  if (c == '"')
    return new json_parser_string(this);
  else if (white_space_set.is_included(c))
    return new json_parser_object(*this);
  else
    throw std::runtime_error("expected '\"'");
}


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
