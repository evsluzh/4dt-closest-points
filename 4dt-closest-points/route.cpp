#include "route.h"
#include <iostream>
#include <boost/shared_ptr.hpp>

Route::Route(size_t size)
    : m_edges(size)
{
}

Route::Route(const std::vector<Point>& points)
{
    m_edges.reserve(points.size() - 1);
    boost::shared_ptr<Point> prev_point;
    for (size_t i = 0; i < points.size(); ++i)
    {
        boost::shared_ptr<Point> cur_point(new Point(points[i]));
        if (i > 0)
        {
            boost::shared_ptr<Edge> cur_edge(new Edge(prev_point, cur_point));
            m_edges.push_back(cur_edge);
        }
        prev_point = cur_point;
    }
}

Route::Route()
    : m_edges(0)
{
}

boost::shared_ptr<Point> Route::point(size_t index) const
{
    if (index < m_edges.size())
    {
        return m_edges[index]->a();
    }
    return m_edges.back()->b();
}

bool Route::get_position(double t, Point& p) const
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
    if (r < 0 || r >= (int)size())
    {
        return false;
    }
    return edge(r)->get_point(t, p);
}

boost::shared_ptr<Edge> Route::edge(size_t index) const
{
    return m_edges[index];
}

size_t Route::size() const
{
    return m_edges.size();
}

double Route::get_min_value(boost::function<double (Point)> functor)
{
    double res = std::numeric_limits<double>::max();
    for (size_t i = 0; i <= size(); ++i)
    {
        res = std::min(res, functor(*point(i)));
    }
    return res;
}

double Route::get_max_value(boost::function<double (Point)> functor)
{
    double res = std::numeric_limits<double>::min();
    for (size_t i = 0; i <= size(); ++i)
    {
        res = std::max(res, functor(*point(i)));
    }
    return res;
}

std::istream& operator >> (std::istream &in, Route &route)
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

std::ostream& operator << (std::ostream &out, const Route &route)
{
    out << (route.size() + 1) << std::endl;
    for (size_t i = 0; i <= route.size(); ++i)
    {
        out << *route.point(i) << std::endl;
    }
    return out;
}
