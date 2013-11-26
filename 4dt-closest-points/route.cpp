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
        if (m_edges[m]->a()->t() > t)
        {
            l = m + 1;
        }
        else
        {
            r = m;
        }
    }
    double x1 = m_edges[l]->a()->x();
    double y1 = m_edges[l]->a()->y();
    double t1 = m_edges[l]->a()->t();

    double x2 = m_edges[l]->b()->x();
    double y2 = m_edges[l]->b()->y();
    double t2 = m_edges[l]->b()->t();

    double cx = x1 + (x2 - x1) * (t - t1) / (t2 - t1);
    double cy = y1 + (y2 - y1) * (t - t1) / (t2 - t1);
//        std::cout << ">1 " << t1 << ' ' << t2 << ' ' << t << std::endl;
//        std::cout << ">2 " << x1 << ' ' << y1 << std::endl;
//        std::cout << ">3 " << x2 << ' ' << y2 << std::endl;
//        std::cout << ">4 " << cx << ' ' << cy << std::endl;
//        Point res(cx, cy, t);
    return Point(cx, cy, t);
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
