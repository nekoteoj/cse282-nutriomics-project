#include "ds/treatment.h"

Treatment::Treatment(size_t size)
{
    this->treat_vector.assign(size, 0);
    this->treat_vector_arma = arma::zeros(1, size);
    this->count = 0;
}

Treatment::Treatment(const Treatment& treatment)
{
    this->treat_vector = std::vector<int> { treatment.treat_vector };
    this->treat_vector_arma = arma::Row<double> { treatment.treat_vector_arma };
    this->count = treatment.count;
}

Treatment Treatment::flip(size_t idx) const
{
    auto flippedTreatment { *this };
    flippedTreatment.flip_inplace(idx);
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
    if (flip_result == 1) {
        this->count++;
    } else {
        this->count--;
    }
}

bool TreatmentResult::operator<(const TreatmentResult& other) const
{
    if (this->score != other.score) {
        return this->score < other.score;
    }
    return this->treatment.count > other.treatment.count;
}

bool TreatmentResult::operator>(const TreatmentResult& other) const
{
    return other < *this;
}