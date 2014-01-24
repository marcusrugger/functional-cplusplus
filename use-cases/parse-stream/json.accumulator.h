#pragma once


class json_accumulator
{
public:

  const std::shared_ptr<const json_stack> _stack;

  json_accumulator(void);
  json_accumulator(const json_accumulator &other);
  json_accumulator(const json_parser_base *parser);

  json_accumulator operator ()(const char c) const;

};
