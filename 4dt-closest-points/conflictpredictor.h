#pragma once

#include "route.h"
#include <vector>

struct ConflictPredictor
{
    ConflictPredictor(const std::vector<Route>& routes);

    virtual std::vector< std::pair<double, double> > getConflict(size_t index1, size_t index2, double d) = 0;

    virtual ~ConflictPredictor();

protected:
    std::vector<Route> m_routes;
};

