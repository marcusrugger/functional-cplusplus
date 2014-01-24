#include "json.parser.h"


const string json_parser_base::number_set("-0123456789");
const string json_parser_base::white_space_set(" \t\n\r");


json_parser_base *json_parser_base::create(void)
{ return new json_parser_base(); }


json_parser_base *json_parser_base::create(const json_parser_base *other)
{ return new json_parser_base(*other); }


json_parser_base::json_parser_base(const json_parser_base &other)
: _stack(other._stack)
{}


json_parser_base::json_parser_base(void)
: _stack(new json_stack(this))
{}


json_stack json_parser_base::operator ()(const json_stack &stack, const char c) const
{
  printf("json_parser_base: 0x%02x, included?: %s\n", c, white_space_set.is_included(c) ? "true" : "false");
  if (white_space_set.is_included(c))
    return stack.pop_tail().push_tail(json_parser_base::create(this));
  else if ('{' == c)
    return stack.push_tail(json_parser_object::create(this));
  else if ('[' == c)
    return stack.push_tail(new json_parser_array(*this));
  else
    throw std::runtime_error("unexpected character in json object");
}


json_parser_base *json_parser_base::clone(void) const
{ return new json_parser_base(*this); }
