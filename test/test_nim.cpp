#include <catch2/catch_test_macros.hpp>

#include "nim.h"

#include <filesystem>

TEST_CASE("Test loading NIM matrix")
{
    std::filesystem::path p { "../res/nims.csv" };
    NIM nim;
    nim.load(p);
    REQUIRE(nim.microbe_size == 400);
    REQUIRE(nim.nutrient_size == 92);
    REQUIRE(nim.microbes[0] == "Faecalibacterium prausnitzii");
    REQUIRE(nim.microbes[nim.microbe_size - 1] == "Sellimonas intestinalis/Drancourtella massiliensis");
    REQUIRE(nim.nutrients[0] == "Thr_D");
    REQUIRE(nim.nutrients[nim.nutrient_size - 1] == "K");
    REQUIRE(nim.impactMatrix[0][0] == 0);
    REQUIRE(nim.impactMatrix[nim.nutrient_size - 1][2] == 0.0074);
    REQUIRE(nim.impactMatrix[nim.nutrient_size - 1][nim.microbe_size - 1] == 1.0);
}
