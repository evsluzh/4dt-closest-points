#pragma once

#include "point.h"
#include "edge.h"
#include <istream>
#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>

struct Route
{
    Route(size_t size);

    Route();

    boost::shared_ptr<Point> point(size_t index) const;

    boost::shared_ptr<Edge> edge(size_t index) const;

    bool get_position(double t, Point& point) const;

    size_t size() const;

    friend std::istream& operator>> (std::istream &in, Route &route);

private:
    std::vector<boost::shared_ptr<Edge>> m_edges;
};
