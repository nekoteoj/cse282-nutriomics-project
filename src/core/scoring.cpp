#include "core/scoring.h"

arma::Row<double> compute_qualifier(
    const arma::Mat<double>& impact_matrix,
    const arma::Row<double>& treatment)
{
    return treatment * impact_matrix;
}

double compute_distance(const arma::Row<double>& q1, const arma::Row<double>& q2)
{
    return arma::sum(arma::pow(q1 - q2, 2));
}