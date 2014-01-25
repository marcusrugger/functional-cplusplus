#include "json.doc.h"

using string = mtr::string;


json_doc_string::json_doc_string(void)
{}


json_doc_string::json_doc_string(const json_doc_string &other)
: _string(other._string)
{}


json_doc_string::json_doc_string(const string &s)
: _string(new string(s))
{}


string json_doc_string::to_s(void) const
{
  return string("\"").append(*_string).append('"');
}


json_doc_value *json_doc_string::clone(void) const
{ return new json_doc_string(*this); }
