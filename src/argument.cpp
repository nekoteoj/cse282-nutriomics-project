#include "argument.h"

#include <argparse/argparse.hpp>

RunConfig parse_arguments(int argc, char* argv[])
{
    argparse::ArgumentParser program("nutriomics_main");

    program.add_argument("-n", "--nim")
        .required()
        .help("specify the nutrient impact matrix file");

    program.add_argument("-p", "--patient")
        .required()
        .help("specify the patient input file");

    program.add_argument("-k")
        .required()
        .help("specify the maximum nutrient allowance")
        .scan<'i', int>();

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    return {
        program.get<std::string>("--nim"),
        program.get<std::string>("--patient"),
        program.get<int>("-k")
    };
}