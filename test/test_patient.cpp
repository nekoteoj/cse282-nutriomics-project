#include <catch2/catch_test_macros.hpp>

#include "patient.h"

TEST_CASE("Test loading PatientList")
{
    std::filesystem::path p { "../res/patient_inputs.csv" };
    PatientList patient_list;
    auto load_pass = patient_list.load(p);
    auto first_patient = patient_list.patients[0];
    auto last_patient = patient_list.patients[patient_list.patient_size - 1];
    REQUIRE(load_pass);
    REQUIRE(patient_list.microbe_size == 400);
    REQUIRE(patient_list.patient_size == 142);
    REQUIRE(first_patient.sample_id == "ERR1072712");
    REQUIRE(last_patient.sample_id == "ERR2092610");
    REQUIRE(first_patient.qualifier[0] == 10);
    REQUIRE(last_patient.qualifier[last_patient.qualifier.size() - 1] == 0);
}
