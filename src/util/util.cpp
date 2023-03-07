#include "util/util.h"

std::vector<std::string> string_split(std::string s, std::string tokenizer)
{
    std::vector<std::string> tokens;
    size_t idx = 0;
    size_t idx_next = s.find(tokenizer);
    while (true) {
        tokens.emplace_back(s.substr(idx, idx_next - idx));
        if (idx_next == std::string::npos) {
            break;
        }
        idx = idx_next + tokenizer.size();
        idx_next = s.find(tokenizer, idx);
    }
    return tokens;
}

std::vector<double> vector_string_to_double(const std::vector<std::string>& s_vector)
{
    std::vector<double> results;
    for (const auto c : s_vector) {
        results.emplace_back(std::stod(c));
    }
    return results;
}

std::vector<int> vector_string_to_int(const std::vector<std::string>& s_vector)
{
    std::vector<int> results;
    for (const auto c : s_vector) {
        results.emplace_back(std::stoi(c));
    }
    return results;
}