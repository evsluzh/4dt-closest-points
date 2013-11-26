#pragma once

#include "Point.h"
#include <istream>
#include <iostream>
#include <vector>

struct Route
{
    Route(size_t size) :
        m_points(size)
    {
    }

    Route() :
        Route(0)
    {

    }

    const Point& point(size_t index) const
    {
        return m_points[index];
    }

    const Point get_position(double t) const
    {
//        int l = 0, r = get_size();
//        while (l < r)
//        {
//            int m = (l + r) >> 1;
//            if (points[m].get_t() < t)
//            {
//                l = m + 1;
//            }
//            else
//            {
//                r = m;
//            }
//
        size_t l = 1;
        while (l < m_points.size() && t > m_points[l - 1].t())
        {
           ++l;
        }
//        std::cout << "index point" << l << ' ' << t << std::endl;
        double x1 = m_points[l - 1].x();
        double y1 = m_points[l - 1].y();
        double t1 = m_points[l - 1].t();

        double x2 = m_points[l].x();
        double y2 = m_points[l].y();
        double t2 = m_points[l].t();

        double cx = x1 + (x2 - x1) * (t - t1) / (t2 - t1);
        double cy = y1 + (y2 - y1) * (t - t1) / (t2 - t1);
//        std::cout << ">1 " << t1 << ' ' << t2 << ' ' << t << std::endl;
//        std::cout << ">2 " << x1 << ' ' << y1 << std::endl;
//        std::cout << ">3 " << x2 << ' ' << y2 << std::endl;
//        std::cout << ">4 " << cx << ' ' << cy << std::endl;
//        Point res(cx, cy, t);
        return Point(cx, cy, t);
    }

    size_t size() const
    {
        return m_points.size();
    }

    friend std::istream& operator>> (std::istream &in, Route &route);

private:
    std::vector<Point> m_points;
};
