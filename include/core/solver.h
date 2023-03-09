#ifndef SOLVER_H_
#define SOLVER_H_

#include "ds/nim.h"
#include "ds/patient.h"
#include "ds/treatment.h"

#include <vector>

class BaseSolver {
public:
    NIM nim;
    int k;

    BaseSolver(const NIM& nim, int k)
        : nim(nim)
        , k(k)
    {
    }
    virtual ~BaseSolver() { }
    virtual TreatmentResult find_treatment(const Patient& p) = 0;
    std::vector<TreatmentResult> find_treatments(const PatientList& pl);
    double find_distance(const Patient& p, const Treatment& t);
};

class BruteForceSolver : public BaseSolver {
private:
    TreatmentResult find_treatment(Treatment& t, int start_idx, int depth, const Patient& p);

public:
    using BaseSolver::BaseSolver;
    virtual TreatmentResult find_treatment(const Patient& p);
};

class ProposedSolver : public BaseSolver {
private:
    int depth;
    int top_level;
    int top_overall;

public:
    ProposedSolver(const NIM& nim, int k, int depth, int top_level, int top_overall)
        : BaseSolver(nim, k)
        , depth(depth)
        , top_level(top_level)
        , top_overall(top_overall)
    {
    }
    std::vector<TreatmentResult> state_expander(
        const Treatment& t, const Patient& p, int remain_depth, double max_threshold);
    virtual TreatmentResult find_treatment(const Patient& p);
};

#endif