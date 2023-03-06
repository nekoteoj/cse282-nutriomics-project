#include "scoring.h"

arma::Col<double> compute_qualifier(
    const arma::Mat<double>& impact_matrix,
    const arma::Col<double>& treatment)
{
    return impact_matrix * treatment;
}

double compute_distance(const arma::Col<double>& q1, const arma::Col<double>& q2)
{
    return arma::sum(arma::pow(q1 - q2, 2));
}