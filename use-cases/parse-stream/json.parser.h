#pragma once

#include <mtr.string.h>
#include <mtr.vector.h>

class json_parser_base;
class json_parser_string;
class json_parser_object;
class json_parser_array;

using string = mtr::string;
using json_list = mtr::vector<json_parser_base>;
using json_pair_list = mtr::vector<std::pair<string,json_parser_base>>;

#include "json.parser.base.h"
#include "json.parser.string.h"
#include "json.parser.object.h"
#include "json.parser.array.h"
