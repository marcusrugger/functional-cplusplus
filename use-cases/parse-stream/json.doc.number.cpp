#include "json.doc.h"
#include <string>

double json_doc_integer::to_f(void) const
{ return static_cast<double>(_number); }


int json_doc_integer::to_i(void) const
{ return static_cast<int>(_number); }


json_doc_value::string json_doc_integer::to_s(void) const
{ return string(std::to_string(_number).c_str()); }


double json_doc_floating_point::to_f(void) const
{ return static_cast<double>(_number); }


int json_doc_floating_point::to_i(void) const
{ return static_cast<int>(_number); }


json_doc_value::string json_doc_floating_point::to_s(void) const
{ return string(std::to_string(_number).c_str()); }
