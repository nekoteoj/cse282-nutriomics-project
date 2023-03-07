#ifndef SCORING_H_
#define SCORING_H_

#include <armadillo>

arma::Row<double> compute_qualifier(const arma::Mat<double>& impact_matrix, const arma::Row<double>& treatment);
double compute_distance(const arma::Row<double>& q1, const arma::Row<double>& q2);

#endif