#pragma once

#include "Point.h"

struct Route
{
    Route(size_t size)
        : points(size)
    {
    }

    const Point& get_point(size_t index) const
    {
        return points[index];
    }

public:
    std::vector<Point> points;
};
