#pragma once

#include "point.h"
#include <boost/shared_ptr.hpp>

struct Edge
{
    Edge(boost::shared_ptr<Point> a, boost::shared_ptr<Point> b);

    boost::shared_ptr<Point> a() const;

    boost::shared_ptr<Point> b() const;

    bool intersect(const Edge& edge, double d, double& time) const;

    bool get_point(double t, Point& point) const;

    bool distance(const Edge& edge, double t, double& dist) const;

private:
    boost::shared_ptr<Point> m_a;
    boost::shared_ptr<Point> m_b;
};

