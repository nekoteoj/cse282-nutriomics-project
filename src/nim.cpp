#include "nim.h"

#include "util.h"

bool NIM::load(std::filesystem::path path, std::string sep)
{
    std::string line;
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    // Get column name
    std::getline(file, line);
    auto columns = string_split(line, sep);
    this->microbes = { columns.begin() + 1, columns.end() };

    while (std::getline(file, line)) {
        auto nutrient_row = string_split(line, sep);
        this->nutrients.emplace_back(nutrient_row[0]);
        this->impact_matrix.push_back(vector_string_to_double({ nutrient_row.begin() + 1, nutrient_row.end() }));
    }

    this->nutrient_size = this->nutrients.size();
    this->microbe_size = this->microbes.size();

    file.close();
    return true;
}