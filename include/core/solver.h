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
};

class BruteForceSolver : public BaseSolver {
private:
    TreatmentResult find_treatment(Treatment& t, int start_idx, int depth, const Patient& p);

public:
    using BaseSolver::BaseSolver;
    virtual TreatmentResult find_treatment(const Patient& p);
};

class ProposedSolver : public BaseSolver {
    using BaseSolver::BaseSolver;
    virtual TreatmentResult find_treatment(const Patient& p);
};

#endif