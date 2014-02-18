#pragma once

#include "point.h"
#include "edge.h"
#include <istream>
#include <ostream>
#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

struct __attribute__ ((visibility ("default"))) Route
{
    Route(size_t size);

    explicit Route(const std::vector<Point>& points);

    Route();

    boost::shared_ptr<Point> point(size_t index) const;

    boost::shared_ptr<Edge> edge(size_t index) const;

    bool get_position(double t, Point& point) const;

    size_t size() const;

    int find_edge_by_time(double t) const;

    double get_min_value(boost::function<double (Point)> functor);

    double get_max_value(boost::function<double (Point)> functor);

    friend std::istream& operator>> (std::istream &in, Route &route);

    friend std::ostream& operator<< (std::ostream &out, const Route &route);

private:
    std::vector<boost::shared_ptr<Edge> > m_edges;
};
