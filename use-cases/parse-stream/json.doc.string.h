#pragma once

#include <mtr.string.h>


class json_doc_string : public json_doc_value
{
private:

  using string = mtr::string;
  const std::shared_ptr<string> _string;


public:

  json_doc_string(void);
  json_doc_string(const json_doc_string &);
  json_doc_string(const string &);

  virtual string to_s(void) const;
  virtual json_doc_value *clone(void) const;

};
