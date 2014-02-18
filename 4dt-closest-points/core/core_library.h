#pragma once
#include "conflict.h"
#include "conflictpredictor.h"
#include "geometrichashing.h"

struct __declspec (dllexport) GeometricHashing
    : ConflictPredictor
{
     GeometricHashing(const std::vector<Route>& routes);
     virtual std::vector<Conflict> getConflicts(size_t index1, size_t index2, double d);
};
