#ifndef TREATMENT_H_
#define TREATMENT_H_

#include <armadillo>
#include <string>
#include <vector>

class Treatment {
public:
    std::vector<int> treat_vector;
    arma::Row<double> treat_vector_arma;

    Treatment(size_t size);
    Treatment(const Treatment& treatment);
    Treatment flip(size_t idx);
};

class TreatmentResult {
public:
    Treatment treatment;
    double score;

    TreatmentResult(const Treatment& treatment, double score)
        : treatment(treatment)
        , score(score)
    {
    }
};

#endif