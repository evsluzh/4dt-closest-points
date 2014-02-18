#pragma once

#include "route.h"
#include "conflict.h"
#include <vector>

struct __attribute__ ((visibility ("default"))) ConflictPredictor
{
    ConflictPredictor(const std::vector<Route>& routes);

    virtual std::vector<Conflict> getConflicts(size_t route1_index, size_t route2_index, double threshold) = 0;
    virtual std::vector<Conflict> getConflicts(double threshold);

    virtual ~ConflictPredictor();

protected:
    std::vector<Route> m_routes;
};
