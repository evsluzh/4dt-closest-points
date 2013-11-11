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
    double findConfict(Point p1, Point p2, Point q1, Point q2, double d);
    double calculateDistance(Point p1, Point p2, Point q1, Point q2, double t);
    std::pair<double, double> getPosition(Point p1, Point p2, double t);

    std::vector<Route> routes;
};
