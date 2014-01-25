#include "json.doc.h"


using string = mtr::string;
using forward_iterator = mtr::index_forward_iterator<json_doc_object, json_doc_object_pair>;


json_doc_object::json_doc_object(void)
{}


json_doc_object::json_doc_object(const json_doc_object &other)
: _pairs(other._pairs)
{}


json_doc_object::json_doc_object(const pairs &pairs)
: _pairs(pairs)
{}


forward_iterator json_doc_object::iterator(void) const
{ return forward_iterator(*this, 0, _pairs.length()-1); }


string json_doc_object::to_s(void) const
{
  using iterator = mtr::index_forward_iterator<pairs,json_doc_object_pair>;
  using foreach = mtr::foreach<iterator,string,json_doc_object_pair>;

  if (_pairs.length() > 0)
  {
    auto sfn = [](string a, const json_doc_object_pair pair) -> string
    { return a.append(',').append(pair.to_s()); };

    auto f = foreach(_pairs.iterator().skip(1), string());
    return string("{").append(_pairs.head().to_s()).append(f(sfn)).append("}");
  }
  else
    return string("{}");
}


json_doc_value *json_doc_object::clone(void) const
{ return new json_doc_object(*this); }
