#include "json.parser.h"


json_accumulator::json_accumulator(void)
: _stack(json_parser_base::create())
{}


json_accumulator::json_accumulator(const json_stack &stack)
: _stack(stack)
{}


json_accumulator::json_accumulator(const json_accumulator &other)
: _stack(other._stack)
{}


json_accumulator::json_accumulator(const json_parser_base *parser)
: _stack(parser)
{}


json_accumulator json_accumulator::operator ()(const char c) const
{ printf("json_accumulator: 0x%02x\n", c); return json_accumulator( (*_stack.tail()) (_stack, c) ); }
