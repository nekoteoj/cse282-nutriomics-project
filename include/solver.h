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

    virtual Treatment findTreatment(const Patient& p) = 0;
    std::vector<Treatment> findTreatments(const PatientList& pl);
};

class BruteForceSolver : public BaseSolver {
    virtual Treatment findTreatment(const Patient& p);
};

class ProposedSolver : public BaseSolver {
    virtual Treatment findTreatment(const Patient& p);
};

#endif