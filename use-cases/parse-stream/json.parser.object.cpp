#include "json.parser.h"


json_parser_base *json_parser_object::create(const json_parser_base *other)
{ return new json_parser_object(*other); }


json_parser_object::json_parser_object(const json_parser_base &other)
: json_parser_base(other)
{}


json_parser_object::json_parser_object(const json_parser_object &other)
: json_parser_base(other)
{}


json_parser_base *json_parser_object::operator ()(const char c) const
{
  if (c == '"')
    return new json_parser_string(this);
  else if (white_space_set.is_included(c))
    return new json_parser_object(*this);
  else
    throw std::runtime_error("expected '\"'");
}


json_parser_base *json_parser_object::clone(void) const
{ return new json_parser_object(*this); }
