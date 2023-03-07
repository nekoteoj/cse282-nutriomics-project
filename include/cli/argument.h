#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include <filesystem>
#include <string>

class RunConfig {
public:
    std::filesystem::path nim_path;
    std::filesystem::path patient_path;
    std::string algo;
    std::filesystem::path output_path;
    int k;

    RunConfig(
        std::filesystem::path nim_path,
        std::filesystem::path patient_path,
        std::string algo,
        std::filesystem::path output_path,
        int k)
        : nim_path(nim_path)
        , patient_path(patient_path)
        , algo(algo)
        , output_path(output_path)
        , k(k)
    {
    }
};

RunConfig parse_arguments(int argc, char* argv[]);

#endif