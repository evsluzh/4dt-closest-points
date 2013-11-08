#ifndef GEOMTRICHASHING_H
#define GEOMTRICHASHING_H

#include "Route.h"
#include <vector>

struct GeometricHashing : ConflictPredictor {
    GeometricHashing(std::vector<Route> routes) {
    }

    std::vector< std::pair<double, double> > calculate(size_t index1, size_t index2, double d) {

    }
};

#endif // GEOMTRICHASHING_H
