#pragma once


class json_parser_string : public json_parser_base
{
public:

  const std::shared_ptr<const json_parser_base> _parent;
  const string _string;

  json_parser_string(const json_parser_base *parent);
  json_parser_string(const json_parser_string &other);
  json_parser_string(const json_parser_string &other, const string &s);

  virtual json_parser_base *operator ()(const char c) const;
  virtual json_parser_base *clone(void) const;

};
