#include "cli/argument.h"

#include <argparse/argparse.hpp>
#include <string>
#include <vector>

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

    program.add_argument("-o", "--output")
        .default_value(std::string { "treatment_result.csv" })
        .help("specify csv output path");

    program.add_argument("-a", "--algorithm")
        .default_value(std::string { "bruteforce" })
        .help("specify the algorithm between bruteforce and proposed")
        .action([](const std::string& value) {
            static const std::vector<std::string> choices = { "bruteforce",
                "proposed" };
            if (std::find(choices.begin(), choices.end(), value) != choices.end()) {
                return value;
            }
            return std::string { "bruteforce" };
        });

    program.add_argument("-d", "--depth")
        .default_value(2)
        .help("specify the subtree expanding depth for proposed algorithm")
        .scan<'i', int>();

    program.add_argument("-l", "--top-level")
        .default_value(10)
        .help("specify the number of top states to keep at each level during subtree expanding for proposed algorithm")
        .scan<'i', int>();

    program.add_argument("-v", "--top-overall")
        .default_value(10)
        .help("specify the number of top states to keep in the subtree during subtree expanding for proposed algorithm")
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
        program.get<std::string>("--algorithm"),
        program.get<std::string>("--output"),
        program.get<int>("-k"),
        program.get<int>("--depth"),
        program.get<int>("--top-level"),
        program.get<int>("--top-overall")
    };
}