#include "simplepredictor.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>

SimplePredictor::SimplePredictor(const std::vector<Route>& routes)
    : ConflictPredictor(routes)
{

}

std::vector< std::pair<double, double> > SimplePredictor::getConflict(size_t index1, size_t index2, double d)
{
/*    std::vector< boost::shared_ptr<Edge> > current_edges(routes.size());
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

        ++iterators[next_routes];
    }*/


    std::cout << "getConflict " << d << std::endl;
    size_t ptr1 = 0, ptr2 = 0;
    Route route1 = m_routes[index1];
    Route route2 = m_routes[index2];
    std::cout << route1.size() << ' ' << route2.size() << std::endl;

    std::vector< std::pair<double, double> > res;
    double t1 = 0.0;
    bool in_conflict = false;
    while (ptr1 < route1.size() && ptr2 < route2.size())
    {
//        std::cout << ptr1 << ' ' << ptr2 << std::endl;
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
        if (ptr1 && ptr2)
        {
            double t;
            if (route1.edge(ptr1)->intersect(*route2.edge(ptr2), d, t))
            {
                std::cout << "T = " << t << std::endl;
                if (in_conflict)
                {
                    res.push_back(std::make_pair(t1, t));
                    in_conflict = false;
                }
                else
                {
                    t1 = t;
                    in_conflict = true;
                }
            }
        }
        ptr1 = nptr1;
        ptr2 = nptr2;
    }
    return res;
}
