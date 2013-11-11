#pragma once

#include "Point.h"
#include <istream>
#include <vector>

struct Route
{
    Route()
    {

    }

    Route(size_t size) :
        points(size)
    {
    }

    const Point& get_point(size_t index) const
    {
        return points[index];
    }

    const Point& get_point(double t) const
    {
        int l = 0, r = get_size();
        while (l < r)
        {
            int m = (l + r) >> 1;
            if (points[m].get_t() < t)
            {
                l = m + 1;
            }
            else
            {
                r = m;
            }
        }
        double x1 = points[l - 1].get_x();
        double y1 = points[l - 1].get_y();
        double t1 = points[l - 1].get_t();

        double x2 = points[l].get_x();
        double y2 = points[l].get_y();

        double cx = x1 + (x2 - x1) * (t - t1);
        double cy = y1 + (y2 - y1) * (t - t1);
        return Point(cx, cy);
    }

    const size_t get_size() const
    {
        return points.size();
    }

    friend std::istream& operator>> (std::istream &in, Route &route);

private:
    std::vector<Point> points;
};
