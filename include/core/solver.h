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
    virtual TreatmentResult findTreatment(const Patient& p) = 0;
    std::vector<TreatmentResult> findTreatments(const PatientList& pl);
};

class BruteForceSolver : public BaseSolver {
    using BaseSolver::BaseSolver;
    virtual TreatmentResult findTreatment(const Patient& p);
};

class ProposedSolver : public BaseSolver {
    using BaseSolver::BaseSolver;
    virtual TreatmentResult findTreatment(const Patient& p);
};

#endif