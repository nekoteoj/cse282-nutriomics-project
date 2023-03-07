#ifndef REPORT_H_
#define REPORT_H_

#include "ds/patient.h"
#include "ds/treatment.h"

#include <filesystem>
#include <string>
#include <utility>
#include <vector>

bool export_treatment_to_csv(
    const std::vector<TreatmentResult>& treatment_results,
    const std::vector<Patient>& patients,
    const std::vector<std::string>& nutrients,
    const std::filesystem::path& output_path);

#endif