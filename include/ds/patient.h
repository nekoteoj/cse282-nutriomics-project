#ifndef PATIENT_H_
#define PATIENT_H_

#include <armadillo>
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
    arma::Row<double> qualifier_arma;

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
        std::vector<double> qualifier_double;
        for (auto i = 0; i < this->qualifier.size(); i++) {
            this->qualifier[i] *= this->k;
            qualifier_double.emplace_back(this->qualifier[i]);
        }
        this->qualifier_arma = qualifier_double;
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