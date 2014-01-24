#pragma once


class json_parser_base
{
public:

  static const string number_set;
  static const string white_space_set;

  const json_stack _stack;


  json_parser_base(const json_parser_base &other);


public:

  json_parser_base(void);


  virtual json_parser_base *operator ()(const char c) const;
  virtual json_parser_base *clone(void) const;

};
