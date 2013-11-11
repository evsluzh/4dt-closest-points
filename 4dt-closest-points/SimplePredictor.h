#pragma once

#include "Route.h"
#include "ConflictPredictor.h"
#include <vector>

struct SimplePredictor : public ConflictPredictor
{
    SimplePredictor(const std::vector<Route>& routes) :
        routes(routes)
    {

    }

    virtual std::vector< std::pair<double, double> > getConflict(size_t index1, size_t index2, double d);
private:
    double findConfict(const Point& p1, const Point& p2, const Point& q1, const Point& q2, double d);
    double calculateDistance(const Point& p1, const Point& p2, const Point& q1, const Point& q2, double t);
    std::pair<double, double> getPosition(const Point& p1, const Point& p2, double t);

    std::vector<Route> routes;
};
