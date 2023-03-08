#include "core/solver.h"

#include "core/scoring.h"
#include "util/util.h"

#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <utility>
#include <vector>

std::vector<TreatmentResult> BaseSolver::find_treatments(const PatientList& ps)
{
    std::vector<TreatmentResult> treatments;
    size_t i = 0;
    for (const auto& p : ps.patients) {
        std::cout << "Solving treatment for patient " << i + 1 << "/" << ps.patients.size() << '\r' << std::flush;
        treatments.emplace_back(this->find_treatment(p));
        i++;
    }
    std::cout << std::endl;
    return treatments;
}

TreatmentResult BruteForceSolver::find_treatment(Treatment& t, int start_idx, int depth, const Patient& p)
{
    if (depth > this->k) {
        return { Treatment { t }, std::numeric_limits<double>::infinity() };
    }

    auto best_distance = this->find_distance(p, t);
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

double BaseSolver::find_distance(const Patient& p, const Treatment& t)
{
    auto qualifier_hat = compute_qualifier(this->nim.impact_matrix_arma, t.treat_vector_arma);
    auto distance = compute_distance(p.qualifier_arma, qualifier_hat);
    return distance;
}

TreatmentResult BruteForceSolver::find_treatment(const Patient& p)
{
    Treatment t(this->nim.nutrient_size);
    return this->find_treatment(t, 0, 0, p);
}

std::vector<TreatmentResult> ProposedSolver::state_expander(
    const Treatment& t, const Patient& p, int depth, int top_level,
    int top_overall, double max_threshold)
{
    if (depth == 0) {
        TreatmentResult treatment_result { Treatment { t }, this->find_distance(p, t) };
        if (treatment_result.score < max_threshold) {
            return { treatment_result };
        }
        return {};
    }
    // Map heap for storing top scoring states in the same level
    std::priority_queue<TreatmentResult> level_pq;
    for (auto i = 0; i < t.treat_vector.size(); i++) {
        if (t.treat_vector[i] == 1) {
            continue;
        }
        auto t_next = t.flip(i);
        auto distance_next = this->find_distance(p, t_next);
        TreatmentResult treatment_result_next { t_next, distance_next };
        if (level_pq.size() == top_level) {
            if (level_pq.top() < treatment_result_next) {
                continue;
            }
            level_pq.pop();
        }
        level_pq.push(treatment_result_next);
    }

    std::priority_queue<TreatmentResult> overall_pq;
    std::set<std::string> seen_state;
    overall_pq.push({ Treatment { t }, this->find_distance(p, t) });
    seen_state.emplace(vector_int_serialize(t.treat_vector));
    while (!level_pq.empty()) {
        auto treatment_result_next = level_pq.top();
        level_pq.pop();
        auto treatment_result_nexts = this->state_expander(
            treatment_result_next.treatment, p, depth - 1, top_level, top_overall, max_threshold);
        for (auto& treatment_result_next : treatment_result_nexts) {
            auto serialized_state = vector_int_serialize(treatment_result_next.treatment.treat_vector);
            if (seen_state.contains(serialized_state)) {
                continue;
            }
            if (overall_pq.size() == top_overall) {
                if (overall_pq.top() < treatment_result_next) {
                    continue;
                }
                overall_pq.pop();
            }
            overall_pq.push(treatment_result_next);
            seen_state.emplace(serialized_state);
        }
    }

    std::vector<TreatmentResult> expanded_states;
    while (!overall_pq.empty()) {
        if (overall_pq.top().score < max_threshold) {
            expanded_states.push_back(overall_pq.top());
        }
        overall_pq.pop();
    }

    return expanded_states;
}

TreatmentResult ProposedSolver::find_treatment(const Patient& p)
{
    Treatment t(this->nim.nutrient_size);
    TreatmentResult best_treatment_result { t, this->find_distance(p, t) };

    // Min heap
    std::priority_queue<TreatmentResult, std::vector<TreatmentResult>, std::greater<TreatmentResult>> pq;
    pq.push(best_treatment_result);

    while (pq.size() > 0) {
        auto treatment_result = pq.top();
        pq.pop();
        auto expand_depth = this->k - treatment_result.treatment.count < 2
            ? this->k - treatment_result.treatment.count
            : 2;
        auto max_threshold = best_treatment_result.score < treatment_result.score
            ? best_treatment_result.score
            : treatment_result.score;
        auto states = this->state_expander(
            treatment_result.treatment, p, expand_depth,
            10, 10, max_threshold);
        for (const auto& state : states) {
            pq.push(state);
            if (state < best_treatment_result) {
                best_treatment_result = state;
            }
        }
    }

    return best_treatment_result;
}