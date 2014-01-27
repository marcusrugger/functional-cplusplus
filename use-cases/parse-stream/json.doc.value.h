#pragma once


class json_doc_value
{
public:

  using string = mtr::string;
  using input_iterator = mtr::index_forward_iterator<mtr::string,char>;

  virtual string to_s(void) const = 0;
  virtual json_doc_value *clone(void) const = 0;

};
