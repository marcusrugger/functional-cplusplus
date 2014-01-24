#pragma once


class json_parser_string : public json_parser_base
{
private:

  const std::shared_ptr<const json_parser_base> _parent;
  const string _string;

  json_parser_string(const json_parser_string &other, const string &s);

public:

  json_parser_string(const json_parser_base *parent);
  json_parser_string(const json_parser_string &other);

  virtual json_stack operator ()(const json_stack &stack, const char c) const;
  virtual json_parser_base *clone(void) const;

};
