#include "core/solver.h"

#include "core/scoring.h"

#include <limits>
#include <queue>
#include <utility>
#include <vector>

std::vector<TreatmentResult> BaseSolver::find_treatments(const PatientList& ps)
{
    std::vector<TreatmentResult> treatments;
    for (const auto& p : ps.patients) {
        treatments.emplace_back(this->find_treatment(p));
    }
    return treatments;
}

TreatmentResult BruteForceSolver::find_treatment(Treatment& t, int start_idx, int depth, const Patient& p)
{
    if (depth > this->k) {
        return { Treatment { t }, std::numeric_limits<double>::infinity() };
    }

    auto qualifier_hat = compute_qualifier(this->nim.impact_matrix_arma, t.treat_vector_arma);
    auto best_distance = compute_distance(p.qualifier_arma, qualifier_hat);
    auto best_treatment = Treatment { t };

    for (auto i = start_idx; i < t.treat_vector.size() && depth < this->k; i++) {
        t.flip_inplace(i);
        auto treatment_result = this->find_treatment(t, i + 1, depth + 1, p);
        if (treatment_result.score < best_distance) {
            best_distance = treatment_result.score;
            best_treatment = treatment_result.treatment;
        }
        t.flip_inplace(i);
    }

    return { best_treatment, best_distance };
}

TreatmentResult BruteForceSolver::find_treatment(const Patient& p)
{
    Treatment t(this->nim.nutrient_size);
    return this->find_treatment(t, 0, 0, p);
}

TreatmentResult ProposedSolver::find_treatment(const Patient& p)
{
    Treatment t(this->nim.nutrient_size);
    return { t, 0 };
}