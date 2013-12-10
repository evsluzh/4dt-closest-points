#pragma once

#include "conflictpredictor.h"
#include "route.h"
#include "point.h"
#include <vector>
#include <set>
#include <map>

const double dmax = 200.0;
const double vmax = 250.0;

struct Block
{
    Block(int x, int y);

    Block(const Point& point, double d);

    int x() const;

    int y() const;

    friend bool operator < (const Block& a, const Block& b);

private:
    int m_x, m_y;
};

struct GeometricHashing :
        ConflictPredictor
{
    GeometricHashing(const std::vector<Route>& routes);

    std::vector< std::pair<double, double> > getConflict(size_t index1, size_t index2, double d);

private:
    // Map from routes indices to set of edges indices
    std::map<std::pair<size_t, size_t>, std::set< std::pair<size_t, size_t> > > m_conflicts;
};

