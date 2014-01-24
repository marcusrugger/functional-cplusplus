#pragma once


class json_parser_array : public json_parser_base
{
public:

  json_parser_array(const json_parser_base &other);

  virtual json_parser_base *operator ()(const char c) const;
  virtual json_parser_base *clone(void) const;
  
};
