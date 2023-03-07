#include <catch2/catch_test_macros.hpp>

#include "util/util.h"

#include <cmath>
#include <string>
#include <vector>

TEST_CASE("String splits into list of string")
{
    std::string input = "abc,def,ghi";
    std::vector<std::string> results { "abc", "def", "ghi" };

    auto outputs = string_split(input, ",");
    REQUIRE(outputs.size() == results.size());
    for (auto i = 0; i < outputs.size(); i++) {
        REQUIRE(outputs[i] == results[i]);
    }
}

TEST_CASE("Convert vector of string to vector of double")
{
    std::vector<std::string> inputs { "1.0", "2.5", "3.0" };
    std::vector<double> results { 1.0, 2.5, 3.0 };

    auto outputs = vector_string_to_double(inputs);
    REQUIRE(outputs.size() == results.size());
    for (auto i = 0; i < outputs.size(); i++) {
        REQUIRE(std::abs(outputs[i] - results[i]) < 1e-9);
    }
}
