#pragma once

#include "route.h"
#include "conflictpredictor.h"
#include <vector>

const double vmax = 250.0;

struct GeometricHashing :
        ConflictPredictor
{
    GeometricHashing(std::vector<Route> routes);

    std::vector< std::pair<double, double> > calculate(size_t index1, size_t index2, double d);
};

