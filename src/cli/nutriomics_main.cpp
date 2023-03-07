#include <iostream>

#include "cli/argument.h"

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
    return 0;
}
