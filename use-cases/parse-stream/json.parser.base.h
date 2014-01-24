#pragma once


class json_parser_base
{
protected:

  static const string number_set;
  static const string white_space_set;

  const std::shared_ptr<json_stack> _stack;

  json_parser_base(void);


public:

  static json_parser_base *create(void);
  static json_parser_base *create(const json_parser_base *other);

  json_parser_base(const json_parser_base &other);


  virtual json_stack operator ()(const json_stack &stack, const char c) const;
  virtual json_parser_base *clone(void) const;

};
