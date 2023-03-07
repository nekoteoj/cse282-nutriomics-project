#include <iostream>

#include "cli/argument.h"
#include "core/report.h"
#include "core/solver.h"
#include "ds/nim.h"
#include "ds/patient.h"

int main(int argc, char* argv[])
{
    auto run_config = parse_arguments(argc, argv);
    std::cout << "Welcome to Treatment Vector Solver!" << std::endl
              << std::endl;
    std::cout << "NIM path: " << run_config.nim_path << std::endl;
    std::cout << "Patient path: " << run_config.patient_path << std::endl;
    std::cout << "Maximum nutrient allowance: " << run_config.k << std::endl;
    std::cout << "Algorithm: " << run_config.algo << std::endl;
    std::cout << "Output: " << run_config.output_path << std::endl;

    // Load nutrient impact matrix
    NIM nim;
    nim.load(run_config.nim_path, ",");

    // Load patient matrix
    PatientList patient_list;
    patient_list.load(run_config.patient_path, run_config.k, ",");

    // Solve the problem
    BaseSolver* solver = new BruteForceSolver(nim, run_config.k);
    if (run_config.algo == "proposed") {
        delete solver;
        solver = new ProposedSolver(nim, run_config.k);
    }
    auto treatment_results = solver->findTreatments(patient_list);
    delete solver;

    // Save the result
    export_treatment_to_csv(
        treatment_results, patient_list.patients,
        nim.nutrients, run_config.output_path);

    return 0;
}
