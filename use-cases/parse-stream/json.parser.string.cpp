#include "json.parser.h"


json_parser_string::json_parser_string(const json_parser_base *parent)
: json_parser_base(), _parent(parent)
{}


json_parser_string::json_parser_string(const json_parser_string &other)
: json_parser_base(other), _parent(other._parent), _string(other._string)
{}


json_parser_string::json_parser_string(const json_parser_string &other, const string &s)
: json_parser_base(other), _parent(other._parent), _string(s)
{}


json_parser_base *json_parser_string::operator ()(const char c) const
{
  if ('"' == c)
    throw std::runtime_error("json_parser_string: all done");
  else
    return new json_parser_string((*this), _string.append(c));
}


json_parser_base *json_parser_string::clone(void) const
{ return new json_parser_string(*this); }
