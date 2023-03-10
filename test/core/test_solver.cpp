#include <catch2/catch_test_macros.hpp>

#include "core/solver.h"
#include "ds/nim.h"
#include "ds/patient.h"

TEST_CASE("Test proposed solver's state expander")
{
    NIM nim;
    nim.load("../res/nims.csv");

    int k = 2;

    PatientList pl;
    pl.load("../res/patient_inputs.csv", k);

    ProposedSolver solver(nim, k, 2, 20, 10);
    Treatment t(solver.nim.nutrient_size);
    std::vector<double> max_threshold_at_depth(solver.k + 1, 2e9);
    auto states = solver.state_expander(t, pl.patients[3], 2, max_threshold_at_depth);
    for (const auto& state : states) {
        std::cout << "score: " << state.score << ", depth: " << state.treatment.count << std::endl;
    }
    REQUIRE(states.size() == 10);
}