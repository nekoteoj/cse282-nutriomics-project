#include "nim.h"

#include "util.h"

void NIM::load(std::filesystem::path path, std::string sep)
{
    std::string line;
    std::ifstream file(path);
    if (!file.is_open()) {
        return;
    }

    // Get column name
    std::getline(file, line);
    auto columns = string_split(line, sep);
    this->microbes = { columns.begin() + 1, columns.end() };

    while (std::getline(file, line)) {
        auto nutrientRow = string_split(line, sep);
        this->nutrients.emplace_back(nutrientRow[0]);
        this->impactMatrix.push_back(vector_string_to_double({ nutrientRow.begin() + 1, nutrientRow.end() }));
    }

    this->nutrient_size = this->nutrients.size();
    this->microbe_size = this->microbes.size();

    file.close();
}