#ifndef TREATMENT_H_
#define TREATMENT_H_

#include <armadillo>
#include <string>
#include <vector>

class Treatment {
public:
    std::vector<int> treat_vector;
    arma::Row<double> treat_vector_arma;
    int count;

    Treatment(size_t size);
    Treatment(const Treatment& treatment);
    Treatment flip(size_t idx) const;
    void flip_inplace(size_t idx);
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

    bool operator<(const TreatmentResult& other) const;
};

#endif