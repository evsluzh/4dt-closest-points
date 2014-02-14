#include "simplepredictor.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>

SimplePredictor::SimplePredictor(const std::vector<Route>& routes)
    : ConflictPredictor(routes)
{

}

std::vector<Conflict> SimplePredictor::getConflict(size_t index1, size_t index2, double d)
{
    std::cout << "getConflict " << d << std::endl;
    size_t ptr1 = 0, ptr2 = 0;
    const Route& route1 = m_routes[index1];
    const Route& route2 = m_routes[index2];

    std::vector<Conflict> conflicts;
    double open_time = 0.0;
    bool in_conflict = false;
    while (ptr1 < route1.size() && ptr2 < route2.size())
    {
//        std::cout << "GO " << ptr1 << ' ' << ptr2 << std::endl;
        size_t nptr1 = ptr1;
        size_t nptr2 = ptr2;
        if (ptr2 == route2.size() || (ptr1 < route1.size() && route1.edge(ptr1)->b()->t() < route2.edge(ptr2)->b()->t()))
        {
            ++nptr1;
        }
        else
        {
            ++nptr2;
        }
        if (ptr1 == 0)
        {
            double t = route1.point(0)->t();
            double dist = 0.0;
            if (route1.edge(ptr1)->distance(*route2.edge(ptr2), t, dist) && dist <= d)
            {
                in_conflict = true;
                open_time = t;
            }
        }
        if (ptr2 == 0) {
            double t = route2.point(0)->t();
            double dist = 0.0;
            if (route1.edge(ptr1)->distance(*route2.edge(ptr2), t, dist) && dist <= d)
            {
                in_conflict = true;
                open_time = t;
            }
        }
        double t;
        if (route1.edge(ptr1)->intersect(*route2.edge(ptr2), d, t))
        {
            std::cout << "T = " << t << std::endl;
            if (in_conflict)
            {
                conflicts.push_back(Conflict(index1, index2, open_time, t));
                in_conflict = false;
            }
            else
            {
                open_time = t;
                in_conflict = true;
            }
        }
        ptr1 = nptr1;
        ptr2 = nptr2;
    }
    if (in_conflict)
    {
        double finish_time = std::min(route1.point(route1.size())->t(), route2.point(route2.size())->t());
        conflicts.push_back(Conflict(index1, index2, open_time, finish_time));
    }
    return conflicts;
}
