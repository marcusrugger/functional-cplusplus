#pragma once


class json_parser_object : public json_parser_base
{
public:

  const json_pair_list _list;

  static json_parser_base *create(const json_parser_base *other);

  json_parser_object(const json_parser_base &other);
  json_parser_object(const json_parser_object &other);

  virtual json_stack operator ()(const json_stack &stack, const char c) const;
  virtual json_parser_base *clone(void) const;

};
