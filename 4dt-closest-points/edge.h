#pragma once

#include "point.h"
#include <boost/shared_ptr.hpp>

struct Edge
{
    Edge(boost::shared_ptr<Point> a, boost::shared_ptr<Point> b);

    boost::shared_ptr<Point> a() const;

    boost::shared_ptr<Point> b() const;

    double intersect(const Edge& edge, double d) const;

    Point point(double t) const;
private:
    double distance(const Edge& edge, double t) const;

    boost::shared_ptr<Point> m_a;
    boost::shared_ptr<Point> m_b;
};

