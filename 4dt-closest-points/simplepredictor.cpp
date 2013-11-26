#include "simplepredictor.h"
#include <algorithm>
#include <cmath>
#include <iostream>

SimplePredictor::SimplePredictor(const std::vector<Route>& routes) :
    routes(0)
{

}

std::vector< std::pair<double, double> > SimplePredictor::getConflict(size_t index1, size_t index2, double d)
{
//    std::vector< boost::shared_ptr<Edge> > current_edges(routes.size());
    std::vector<size_t> iterators(routes.size(), 0);
    while (true)
    {
        int next_routes = -1;
        for (size_t i = 0; i < routes.size(); ++i)
        {
            if (iterators[i] == routes[i].size())
            {
                continue;
            }
            if (next_routes == -1 || routes[i].edge(iterators[i])->b()->t() < routes[i].edge(iterators[next_routes])->b()->t())
            {
                next_routes = i;
            }
        }
        if (next_routes == -1)
        {
            break;
        }
    }


    std::cout << "getConflict " << d << std::endl;
    size_t ptr1 = 0, ptr2 = 0;
    const Route& route1 = routes[index1];
    const Route& route2 = routes[index2];



    std::vector< std::pair<double, double> > res;
    double t1 = inf;
    while (ptr1 + 1 < route1.size() || ptr2 + 1 < route2.size())
    {
//        std::cout << ptr1 << ' ' << ptr2 << std::endl;
        if (ptr2 + 1 == route2.size() || (ptr1 + 1 < route1.size() && route1.point(ptr1 + 1)->t() < route2.point(ptr2 + 1)->t()))
        {
            ++ptr1;
        }
        else
        {
            ++ptr2;
        }
        if (ptr1 && ptr2)
        {
            double t = findConfict(*route1.point(ptr1 - 1), *route1.point(ptr1), *route2.point(ptr2 - 1), *route2.point(ptr2), d);
            if (t < inf)
            {
                std::cout << "T = " << t << std::endl;
                if (t1 < inf)
                {
                    res.push_back(std::make_pair(t1, t));
                    t1 = inf;
                }
                else
                {
                    t1 = t;
                }
            }
        }
    }
    return res;
}


double SimplePredictor::findConfict(const Point& p1, const Point& p2, const Point& q1, const Point& q2, double d)
{
    // Finding intersection using ternary search
    double l = std::max(p1.t(), q1.t());
    double r = std::min(p2.t(), q2.t());
    if (l >= r)
    {
        return inf;
    }
    for (size_t i = 0; i < 100; ++i)
    {
        double m1 = (2.0 * l + r) / 3.0;
        double m2 = (l + 2.0 * r) / 3.0;

        double d1 = calculateDistance(p1, p2, q1, q2, m1);
        double d2 = calculateDistance(p1, p2, q1, q2, m2);

        if (d1 > d2)
        {
            l = d1;
        }
        else
        {
            r = d2;
        }
    }
    double tm = 0.5 * (l + r);
    double dval = calculateDistance(p1, p2, q1, q2, tm);
    return (dval > d) ? inf : tm;
}

double SimplePredictor::calculateDistance(const Point& p1, const Point& p2, const Point& q1, const Point& q2, double t)
{
    std::pair<double, double> pos1 = getPosition(p1, p2, t);
    std::pair<double, double> pos2 = getPosition(q1, q2, t);
    double dx = pos1.first - pos2.first;
    double dy = pos1.second - pos2.second;
    return sqrt(dx * dx + dy * dy);
}

std::pair<double, double> SimplePredictor::getPosition(const Point& p1, const Point& p2, double t)
{
    double dt = p2.t() - p1.t();
    double cx = p1.x() + (p2.x() - p1.x()) * (t - p1.t()) / dt;
    double cy = p1.y() + (p2.y() - p1.y()) * (t - p1.t()) / dt;
    return std::make_pair(cx, cy);
}
