#ifndef TREATMENT_H_
#define TREATMENT_H_

#include <armadillo>
#include <string>
#include <vector>

class Treatment {
public:
    std::vector<int> treat_vector;
    arma::Col<double> treat_vector_arma;

    Treatment(size_t size);
    Treatment(const Treatment& treatment);
    Treatment flip(size_t idx);
};

#endif