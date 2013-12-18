#pragma once
#include "route.h"
#include "point.h"
#include <vector>

struct RoutesGenerator
{
    RoutesGenerator(int based_points, int routes_count, int route_points);
    std::vector<Route> generate() const;

private:
    std::vector<Point> generate_points(int n, int w, int h) const;

    int m_based_points;
    int m_routes_count;
    int m_route_points;

    const int MAX_TIME = 100;
    const int MAX_X = 100;
    const int MAX_Y = 100;
    const double vmax = 10.0;
};

