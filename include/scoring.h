#ifndef SCORING_H_
#define SCORING_H_

#include <armadillo>

arma::Col<double> compute_qualifier(const arma::Mat<double>& impact_matrix, const arma::Col<double>& treatment);
double compute_distance(const arma::Col<double>& q1, const arma::Col<double>& q2);

#endif