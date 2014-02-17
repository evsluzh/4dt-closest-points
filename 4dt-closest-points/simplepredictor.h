#pragma once

#include "route.h"
#include "conflictpredictor.h"
#include <vector>

struct SimplePredictor
        : ConflictPredictor
{
    SimplePredictor(const std::vector<Route>& routes);

    virtual std::vector<Conflict> getConflicts(size_t index1, size_t index2, double d);
};
