#include "json.parser.h"


json_parser_base *json_parser_object::create(const json_parser_base *other)
{ return new json_parser_object(*other); }


json_parser_object::json_parser_object(const json_parser_base &other)
: json_parser_base(other)
{}


json_parser_object::json_parser_object(const json_parser_object &other)
: json_parser_base(other)
{}


json_stack json_parser_object::operator ()(const json_stack &stack, const char c) const
{
  if (c == '"')
    return stack.push_tail(new json_parser_string(this));
  else if (white_space_set.is_included(c))
    return stack.put_tail(new json_parser_object(*this));
  else
    throw std::runtime_error("expected '\"'");
}


json_parser_base *json_parser_object::clone(void) const
{ return new json_parser_object(*this); }
