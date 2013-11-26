#pragma once

#include "Route.h"
#include "ConflictPredictor.h"
#include <vector>

struct GeometricHashing : ConflictPredictor
{
    GeometricHashing(std::vector<Route> routes)
    {
    }

    std::vector< std::pair<double, double> > calculate(size_t index1, size_t index2, double d)
    {
    }
};

