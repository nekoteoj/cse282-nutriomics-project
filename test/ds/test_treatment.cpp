#include <catch2/catch_test_macros.hpp>

#include "ds/treatment.h"

TEST_CASE("Test create empty treatment vector")
{
    size_t n = 10;
    Treatment t(n);
    REQUIRE(t.count == 0);
    for (auto i = 0; i < n; i++) {
        REQUIRE(t.treat_vector[i] == 0);
        REQUIRE(t.treat_vector_arma[i] == 0);
    }
}

TEST_CASE("Test copy constructor")
{
    size_t n = 5;
    Treatment t(n);
    t.treat_vector[2] = 1;
    t.treat_vector_arma[2] = 1;
    t.count = 1;
    Treatment t2(t);
    t.treat_vector[3] = 1;
    t.treat_vector_arma[3] = 1;
    t.count = 2;
    for (auto i = 0; i < n; i++) {
        auto expected_result = i == 2 ? 1 : 0;
        REQUIRE(t2.treat_vector[i] == expected_result);
        REQUIRE(t2.treat_vector_arma[i] == expected_result);
    }
    REQUIRE(t2.count == 1);
    REQUIRE(t.count == 2);
}

TEST_CASE("Test flip treatment vector")
{
    size_t n = 5;
    Treatment t(n);
    Treatment t2 = t.flip(0).flip(3).flip(3).flip(3);
    REQUIRE(t.count == 0);
    REQUIRE(t2.count == 2);
    for (auto i = 0; i < n; i++) {
        auto t2_expected_output = (i == 0 || i == 3) ? 1 : 0;
        REQUIRE(t.treat_vector[i] == 0);
        REQUIRE(t.treat_vector_arma[i] == 0);
        REQUIRE(t2.treat_vector[i] == t2_expected_output);
        REQUIRE(t2.treat_vector_arma[i] == t2_expected_output);
    }
}

TEST_CASE("Test flip inplace treatment vector")
{
    size_t n = 5;
    Treatment t(n);
    t.flip_inplace(0);
    t.flip_inplace(3);
    REQUIRE(t.count == 2);
    for (auto i = 0; i < n; i++) {
        auto t_expected_output = (i == 0 || i == 3) ? 1 : 0;
        REQUIRE(t.treat_vector[i] == t_expected_output);
        REQUIRE(t.treat_vector_arma[i] == t_expected_output);
    }
}