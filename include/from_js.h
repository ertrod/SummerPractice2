#ifndef FJSON
#define FJSON

#include "practice.h"

namespace practice
{
    std::string start_prop(bool is_more, std::string prop, std::map<std::string, std::string>& values, int lvl = 1);
    std::string obj_to_json(std::string prop, std::map<std::string, std::string>& values, int lvl = 1);
    std::string close_prop(std::string prop, std::map<std::string, std::string>& values, int lvl = 1);
    std::string get_prop(std::ifstream& file);
    std::map<std::string, std::string> next_pair(std::ifstream& file);
}

#endif