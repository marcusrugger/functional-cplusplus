#pragma once


class json_doc_number : public json_doc_value
{
public:

  virtual double to_f(void) const = 0;
  virtual int to_i(void) const = 0;
  virtual string to_s(void) const = 0;
  virtual json_doc_value *clone(void) const = 0;

};


class json_doc_integer : public json_doc_value
{
private:

  using number = long long int;
  const number _number;

public:

  json_doc_integer(const json_doc_integer &other) : _number(other._number) {}
  json_doc_integer(const int n) : _number(static_cast<number>(n)) {}
  json_doc_integer(const double n) : _number(static_cast<number>(n)) {}

  double to_f(void) const;
  int to_i(void) const;
  string to_s(void) const;

  virtual json_doc_value *clone(void) const
  { return new json_doc_integer(*this); }
};


class json_doc_floating_point : public json_doc_value
{
private:

  using number = double;
  const number _number;

public:

  json_doc_floating_point(const json_doc_floating_point &other) : _number(other._number) {}
  json_doc_floating_point(const int n) : _number(static_cast<number>(n)) {}
  json_doc_floating_point(const double n) : _number(static_cast<number>(n)) {}

  double to_f(void) const;
  int to_i(void) const;
  string to_s(void) const;

  virtual json_doc_value *clone(void) const
  { return new json_doc_floating_point(*this); }
};
