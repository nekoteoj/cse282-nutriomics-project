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
    int depth;
    int top_level;
    int top_overall;

    RunConfig(
        std::filesystem::path nim_path,
        std::filesystem::path patient_path,
        std::string algo,
        std::filesystem::path output_path,
        int k,
        int depth,
        int top_level,
        int top_overall)
        : nim_path(nim_path)
        , patient_path(patient_path)
        , algo(algo)
        , output_path(output_path)
        , k(k)
        , depth(depth)
        , top_level(top_level)
        , top_overall(top_overall)
    {
    }
};

RunConfig parse_arguments(int argc, char* argv[]);

#endif