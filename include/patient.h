#ifndef PATIENT_H_
#define PATIENT_H_

#include <filesystem>
#include <string>
#include <vector>

class Patient {
public:
    std::string sample_id;
    double score;
    std::string group;
    int k;
    std::vector<int> qualifier;

    Patient(
        std::string sample_id,
        double score,
        std::string group,
        int k,
        std::vector<int> qualifier)
        : sample_id(sample_id)
        , score(score)
        , group(group)
        , k(k)
        , qualifier(qualifier)
    {
        for (auto i = 0; i < this->qualifier.size(); i++) {
            this->qualifier[i] *= this->k;
        }
    }
};

class PatientList {
public:
    std::vector<Patient> patients;
    std::vector<std::string> microbes;
    size_t patient_size;
    size_t microbe_size;

    bool load(std::filesystem::path p, int k = 10, std::string sep = ",");
};

#endif