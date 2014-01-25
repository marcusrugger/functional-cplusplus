#pragma once


class json_doc_value
{
public:

  using string = mtr::string;

  virtual string to_s(void) const = 0;
  virtual json_doc_value *clone(void) const = 0;

};
