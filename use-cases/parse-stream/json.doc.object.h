#pragma once


class json_doc_object_pair : public json_doc_value
{
public:

  using string = mtr::string;

  const std::shared_ptr<json_doc_string> _name;
  const std::shared_ptr<json_doc_value> _value;


  json_doc_object_pair(void)
  {}

  json_doc_object_pair(const json_doc_object_pair &other)
  : _name(other._name), _value(other._value)
  {}

  json_doc_object_pair(const json_doc_string &name, const json_doc_value &value)
  : _name(new json_doc_string(name)), _value(value.clone())
  {}


  virtual string to_s(void) const
  { return _name->to_s().append(string(":")).append(_value->to_s()); }

  virtual json_doc_value *clone(void) const
  { return new json_doc_object_pair(*this); }

};


class json_doc_object : public json_doc_value
{
public:

  using string = mtr::string;
  using pairs = mtr::vector<json_doc_object_pair>;
  using forward_iterator = mtr::index_forward_iterator<json_doc_object, json_doc_object_pair>;

private:

  const pairs _pairs;

public:

  json_doc_object(void);
  json_doc_object(const json_doc_object &);
  json_doc_object(const pairs &);

  forward_iterator iterator(void) const;

  virtual string to_s(void) const;
  virtual json_doc_value *clone(void) const;

};
