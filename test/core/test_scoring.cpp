#include <catch2/catch_test_macros.hpp>

#include "core/scoring.h"

#include <armadillo>
#include <vector>

TEST_CASE("Test compute distance")
{
    arma::Row<double> v1 { 1, 2, 3 };
    arma::Row<double> v2 { 1, 3, 1 };
    REQUIRE(compute_distance(v1, v2) == 5);
}

TEST_CASE("Test compute qualifier vector")
{
    arma::Mat<double> impact_matrix = arma::ones(4, 3);
    impact_matrix.at(0, 0) = 0;
    impact_matrix.at(3, 2) = 0.5;
    arma::Row<double> treatment { 1, 0, 1, 1 };
    auto qualifier = compute_qualifier(impact_matrix, treatment);
    std::vector<double> expected_outputs { 2.0, 3.0, 2.5 };
    REQUIRE(qualifier.n_cols == 3);
    REQUIRE(qualifier.n_rows == 1);
    for (auto i = 0; i < expected_outputs.size(); i++) {
        REQUIRE(qualifier[i] == expected_outputs[i]);
    }
}