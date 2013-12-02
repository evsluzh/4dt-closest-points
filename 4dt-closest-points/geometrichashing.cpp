#include "geometrichashing.h"
#include <algorithm>
#include <limits>

Block::Block(const Point& point, double d) :
    m_x(point.x() / d),
    m_y(point.y() / d)
{
}

int Block::x() const
{
    return m_x;
}

int Block::y() const
{
    return m_y;
}

GeometricHashing::GeometricHashing(std::vector<Route> routes) :
    ConflictPredictor(routes)
{
}

std::vector< std::pair<double, double> > GeometricHashing::getConflict(size_t index1, size_t index2, double d)
{
    double dt = d / vmax;
    Route route1 = m_routes[index1];
    Route route2 = m_routes[index2];
    double start_time = std::min(route1.edge(0)->a()->t(), route2.edge(0)->a()->t());
    double end_time = std::max(route1.edge(route1.size() - 1)->b()->t(), route2.edge(route2.size() - 1)->b()->t());
    size_t ptr1 = 0;
    size_t ptr2 = 0;
    size_t last_ptr1 = -1;
    size_t last_ptr2 = -1;
    std::vector< std::pair<double, double> > res;
    double lt = std::numeric_limits<double>::quiet_NaN();
    for (double t = start_time; t < end_time; t += dt)
    {
        Point p1 = route1.get_position(t);
        Point p2 = route2.get_position(t);
        if (p1.infinity() || p2.infinity())
        {
            continue;
        }
        Block b1(p1, d);
        Block b2(p2, d);
//        std::cout << b1.x() << ", " << b1.y() << " - " << b2.x() << ", " << b2.y() << "  " <<
//                  abs(b1.x() - b2.x()) << " " << abs(b1.y() - b2.y()) << std::endl;
        int cd = std::max(abs(b1.x() - b2.x()), abs(b1.y() - b2.y()));
//        std::cout << "R = " << cd << std::endl;
        if (cd <= 1)
        {
            while (ptr1 < route1.size() && route1.edge(ptr1)->b()->t() < t)
            {
                ++ptr1;
            }
            while (ptr2 < route2.size() && route2.edge(ptr2)->b()->t() < t)
            {
                ++ptr2;
            }
//            std::cout << " > " << ptr1 << " " << ptr2 << std::endl;
            if (ptr1 != last_ptr1 || ptr2 != last_ptr2)
            {
                if (ptr1 < route1.size() && ptr2 < route2.size())
                {
                    double ct = route1.edge(ptr1)->intersect(*route2.edge(ptr2), d);
                    if (ct == ct)
                    {
                        if (lt == lt)
                        {
                            res.push_back(std::make_pair(lt, ct));
                            lt = std::numeric_limits<double>::quiet_NaN();
                        }
                        else
                        {
                            lt = ct;
                        }
                    }
                }
                last_ptr1 = ptr1;
                last_ptr2 = ptr2;
            }
        }
    }
    return res;
}
