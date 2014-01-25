#include <iostream>
#include <fstream>
#include <functional>
#include "json.doc.h"
#include "json.parser.h"


using iterator = mtr::input_stream_iterator<std::ifstream, char>;
using foreach = mtr::foreach<iterator, json_accumulator, char>;


static void run_parser(void)
{
  const auto filename = string("./sample.json");
  auto stream = new std::ifstream(filename.c_str(), std::ifstream::in);
  auto fn = [](const json_accumulator &a, char c)->json_accumulator { printf("lambda: 0x%02x\n", c); return a(c); };

  auto f = foreach(iterator(stream), json_accumulator());
  auto result = f(fn);
}


int main(void)
{
  using pairs = mtr::vector<json_doc_object_pair>;

  {
    auto empty_json = json_doc_object();
    printf("json: %s\n", empty_json.to_s().c_str());
  }

  {
    auto one_pair = pairs().push_tail(json_doc_object_pair(json_doc_string(string("name 1")), json_doc_string(string("value 1"))));
    auto json = json_doc_object(one_pair);
    printf("json: %s\n", json.to_s().c_str());
  }

  {
    auto list_of_sub_pairs = pairs().push_tail(json_doc_object_pair(json_doc_string(string("name 1")), json_doc_string(string("value 1"))))
                                    .push_tail(json_doc_object_pair(json_doc_string(string("name 2")), json_doc_string(string("value 2"))))
                                    .push_tail(json_doc_object_pair(json_doc_string(string("name 3")), json_doc_integer(42)))
                                    .push_tail(json_doc_object_pair(json_doc_string(string("name 4")), json_doc_floating_point(186282.3976)));

    auto json_sub_object = json_doc_object(list_of_sub_pairs);

    auto list_of_pairs = pairs().push_tail(json_doc_object_pair(json_doc_string(string("name 1")), json_doc_string(string("value 1"))))
                                .push_tail(json_doc_object_pair(json_doc_string(string("name 2")), json_doc_string(string("value 2"))))
                                .push_tail(json_doc_object_pair(json_doc_string(string("sub-object")), json_sub_object))
                                .push_tail(json_doc_object_pair(json_doc_string(string("name 3")), json_doc_integer(42)))
                                .push_tail(json_doc_object_pair(json_doc_string(string("name 4")), json_doc_floating_point(186282.3976)));

    auto json = json_doc_object(list_of_pairs);
    printf("json: %s\n", json.to_s().c_str());
  }
}
