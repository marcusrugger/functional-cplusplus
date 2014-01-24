#include "json.parser.h"


const string json_parser_base::number_set("-0123456789");
const string json_parser_base::white_space_set(" \t\n\r");


json_parser_base::json_parser_base(const json_parser_base &other)
: _stack(other._stack)
{}


json_parser_base::json_parser_base(void)
{}


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


json_parser_base *json_parser_base::clone(void) const
{ return new json_parser_base(*this); }
