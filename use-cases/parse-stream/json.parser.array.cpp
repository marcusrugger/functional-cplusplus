#include "json.parser.h"


json_parser_array::json_parser_array(const json_parser_base &other)
: json_parser_base(other)
{}


json_parser_base *json_parser_array::operator ()(const char c) const
{}


json_parser_base *json_parser_array::clone(void) const
{ return new json_parser_array(*this); }
