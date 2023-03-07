#include "ds/patient.h"

#include "util/util.h"

#include <fstream>

bool PatientList::load(std::filesystem::path p, int k, std::string sep)
{
    std::string line;
    std::ifstream file(p);
    if (!file.is_open()) {
        return false;
    }

    // Get column name
    std::getline(file, line);
    auto columns = string_split(line, sep);
    this->microbes = { columns.begin() + 3, columns.end() };

    while (std::getline(file, line)) {
        auto patient_row = string_split(line, sep);
        auto sample_id = patient_row[0];
        auto score = std::stod(patient_row[1]);
        auto group = patient_row[2];
        auto qualifier = vector_string_to_int({ patient_row.begin() + 3, patient_row.end() });
        Patient patient { sample_id, score, group, k, qualifier };
        this->patients.emplace_back(patient);
    }

    this->microbe_size = this->microbes.size();
    this->patient_size = this->patients.size();

    return true;
}