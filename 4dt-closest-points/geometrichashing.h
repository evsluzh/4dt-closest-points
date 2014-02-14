#pragma once

#include "conflictpredictor.h"
#include "conflict.h"
#include "route.h"
#include "point.h"
#include <vector>
#include <set>
#include <map>

const double dmax = 500.0;
const double vmax = 220.0;

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

    virtual std::vector<Conflict> getConflicts(size_t index1, size_t index2, double d);

private:
    // Map from routes indices to set of edges indices
    std::map<std::pair<size_t, size_t>, std::vector<std::pair<double, double> > > m_conflicts;
};

