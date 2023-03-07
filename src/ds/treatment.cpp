#include "ds/treatment.h"

Treatment::Treatment(size_t size)
{
    this->treat_vector.assign(size, 0);
    this->treat_vector_arma = arma::zeros(1, size);
}

Treatment::Treatment(const Treatment& treatment)
{
    this->treat_vector = std::vector<int> { treatment.treat_vector };
    this->treat_vector_arma = arma::Row<double> { treatment.treat_vector_arma };
}

Treatment Treatment::flip(size_t idx)
{
    if (idx > this->treat_vector.size()) {
        return Treatment { *this };
    }
    auto flippedTreatment { *this };
    flippedTreatment.treat_vector[idx] = 1 - flippedTreatment.treat_vector[idx];
    flippedTreatment.treat_vector_arma[idx] = flippedTreatment.treat_vector[idx];
    return flippedTreatment;
}

void Treatment::flip_inplace(size_t idx)
{
    if (idx > this->treat_vector.size()) {
        return;
    }
    auto flip_result = 1 - this->treat_vector[idx];
    this->treat_vector[idx] = flip_result;
    this->treat_vector_arma[idx] = flip_result;
}