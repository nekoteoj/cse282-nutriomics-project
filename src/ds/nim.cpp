#include "ds/nim.h"

#include "util/util.h"

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

    this->update_impact_matrix_arma(this->impact_matrix);

    this->nutrient_size = this->nutrients.size();
    this->microbe_size = this->microbes.size();

    file.close();
    return true;
}

void NIM::update_impact_matrix_arma(const std::vector<std::vector<double>>& impact_matrix)
{
    if (impact_matrix.size() == 0) {
        this->impact_matrix_arma = arma::zeros(0, 0);
        return;
    }
    this->impact_matrix_arma = arma::zeros(impact_matrix.size(), impact_matrix[0].size());
    for (auto i = 0; i < impact_matrix.size(); i++) {
        for (auto j = 0; j < impact_matrix[0].size(); j++) {
            this->impact_matrix_arma.at(i, j) = impact_matrix[i][j];
        }
    }
}
