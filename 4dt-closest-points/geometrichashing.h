#pragma once

#include "route.h"
#include "conflictpredictor.h"
#include "point.h"
#include <vector>

const double vmax = 250.0;

struct Block
{
    Block(const Point& point, double d);

    int x() const;

    int y() const;

private:
    int m_x, m_y;
};

struct GeometricHashing :
        ConflictPredictor
{
    GeometricHashing(std::vector<Route> routes);

    std::vector< std::pair<double, double> > getConflict(size_t index1, size_t index2, double d);
};

