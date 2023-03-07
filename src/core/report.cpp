#include "core/report.h"

#include <fstream>

bool export_treatment_to_csv(
    const std::vector<TreatmentResult>& treatment_results,
    const std::vector<Patient>& patients,
    const std::vector<std::string>& nutrients,
    const std::string& output_path)
{
    std::ofstream file(output_path);
    if (!file.is_open()) {
        return false;
    }

    // Output headers
    file << "sample-id\tscore";
    for (const auto& nutrient : nutrients) {
        file << "\t" << nutrient;
    }

    // Output patient treatments
    for (auto i = 0; i < treatment_results.size(); i++) {
        const auto& treatment_result = treatment_results[i];
        const auto& patient = patients[i];
        file << "\n"
             << patient.sample_id << "\t" << treatment_result.score;
        for (const auto& choose : treatment_result.treatment.treat_vector) {
            file << "\t" << choose;
        }
    }

    return true;
}