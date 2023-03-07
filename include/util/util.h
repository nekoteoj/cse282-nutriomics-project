#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <vector>

std::vector<std::string> string_split(std::string s, std::string tokenizer);
std::vector<double> vector_string_to_double(const std::vector<std::string>& s_vector);
std::vector<int> vector_string_to_int(const std::vector<std::string>& s_vector);

#endif