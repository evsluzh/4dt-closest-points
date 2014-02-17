#pragma once

#include "conflictpredictor.h"
#include "conflict.h"
#include "route.h"
#include "point.h"
#include <vector>
#include <set>
#include <map>

const double dmax = 2000.0;
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
    void create_edge_coord_function(double x1, double x2, double t1, double t2, double& ka, double& kb);
    void create_edge_distance_coord_function(double t11, double t12, double t21, double t22, double x11, double x12, double x21, double x22,
                                                        double& a, double& b, double& c);
    bool calc_local(bool& open, double& open_time, std::pair<double, double>& conflict, double d, const Edge& edge1, const Edge& edge2);
    // Map from routes indices to set of edges indices
    std::map<std::pair<size_t, size_t>, std::vector<std::pair<double, double> > > m_potential_conflicts;
};

