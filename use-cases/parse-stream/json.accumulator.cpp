#include "json.parser.h"


json_accumulator::json_accumulator(void)
: _stack(new json_stack(json_parser_base::create()))
{}


json_accumulator::json_accumulator(const json_accumulator &other)
: _stack(other._stack)
{}


json_accumulator::json_accumulator(const json_parser_base *parser)
: _stack(new json_stack(parser))
{}


json_accumulator json_accumulator::operator ()(const char c) const
{ return json_accumulator( (*_stack->tail()) (c) ); }
