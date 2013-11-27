#include "route.h"
#include <iostream>
#include <boost/shared_ptr.hpp>

Route::Route(size_t size) :
    m_edges(size)
{
}

Route::Route() :
    Route(0)
{

}

boost::shared_ptr<Point> Route::point(size_t index) const
{
    return m_edges[index]->a();
}

const Point Route::get_position(double t) const
{
    int l = 0, r = size();
    while (l < r)
    {
        int m = (l + r) >> 1;
        if (m_edges[m]->b()->t() < t)
        {
            l = m + 1;
        }
        else
        {
            r = m;
        }
    }
    return edge(l)->point(t);
}

boost::shared_ptr<Edge> Route::edge(size_t index) const
{
    return m_edges[index];
}

size_t Route::size() const
{
    return m_edges.size();
}

std::istream& operator>> (std::istream &in, Route &route)
{
    int n;
    std::cout << "read route" << std::endl;
    in >> n;
    std::cout << n << " points" << std::endl;
    route.m_edges.clear();
    route.m_edges.reserve(n - 1);
    boost::shared_ptr<Point> prev_point;
    for (int i = 0; i < n; ++i)
    {
        std::cout << "read point " << i << std::endl;
        boost::shared_ptr<Point> cur_point(new Point());
        in >> *cur_point;
        if (i > 0)
        {
            boost::shared_ptr<Edge> cur_edge(new Edge(prev_point, cur_point));
            route.m_edges.push_back(cur_edge);
        }
        prev_point = cur_point;
    }
    return in;
}
