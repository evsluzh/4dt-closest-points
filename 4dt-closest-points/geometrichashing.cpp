#include "geometrichashing.h"
#include <algorithm>
#include <limits>

Block::Block(int x, int y)
    : m_x(x)
    , m_y(y)
{

}

Block::Block(const Point& point, double d)
    : m_x(point.x() / d)
    , m_y(point.y() / d)
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

bool operator < (const Block& a, const Block& b)
{
    if (a.m_x != b.m_x)
    {
        return a.m_x < b.m_x;
    }
    return a.m_y < b.m_y;
}


GeometricHashing::GeometricHashing(const std::vector<Route>& routes) :
    ConflictPredictor(routes)
{
    std::cout << "Ok" << std::endl;
    double dt = dmax / vmax;
    double start_time = routes[0].edge(0)->a()->t();
    double finish_time = routes[0].edge(routes[0].size() - 1)->b()->t();
    std::cout << "OK " << std::endl;
    for (size_t i = 0; i < routes.size(); ++i)
    {
//        const Route cur = m_routes[i];
        start_time = std::min(start_time, routes[i].edge(0)->a()->t());
        finish_time = std::max(finish_time, routes[i].edge(routes[i].size() - 1)->b()->t());
    }
    std::cout << "Ok2" << std::endl;
    std::vector<size_t> pointers(routes.size(), 0);
    for (double t = start_time; t < finish_time; t += dt)
    {
        std::cout << "CUR T = " << t << std::endl;
        std::map<Block, std::vector< std::pair<size_t, size_t> > > blocks;
        for (size_t i = 0; i < routes.size(); ++i)
        {
            Point point = routes[i].get_position(t);
            if (point.x() == point.x())
            {
                while (pointers[i] < routes[i].size() && routes[i].edge(pointers[i])->b()->t() < t)
                {
                    ++pointers[i];
                }
                Block block(point, dmax);
                for (int dx = -1; dx <= 1; ++dx)
                {
                    for (int dy = -1; dy <= 1; ++dy)
                    {
                        Block cur(block.x() + dx, block.y() + dy);
                        const auto& positions = blocks[cur];
                        for (auto it = positions.begin(); it != positions.end(); ++it)
                        {
//                            std::cout << "Add " << i << ' ' << it->first << std::endl;
                            m_conflicts[std::make_pair(i, it->first)].insert(std::make_pair(pointers[i], it->second));
                            m_conflicts[std::make_pair(it->first, i)].insert(std::make_pair(it->second, pointers[i]));
                        }
                    }
                }
                blocks[block].push_back(std::make_pair(i, pointers[i]));
            }
        }
    }
}

std::vector< std::pair<double, double> > GeometricHashing::getConflict(size_t index1, size_t index2, double d)
{
    std::cout << "IN" << std::endl;
    std::vector< std::pair<double, double> > res;
    std::set< std::pair<size_t, size_t> > current_conflicts = m_conflicts[std::make_pair(index1, index2)];
    double lt = std::numeric_limits<double>::quiet_NaN();
    for (auto it = current_conflicts.begin(); it != current_conflicts.end(); ++it)
    {
        double ct = m_routes[index1].edge(it->first)->intersect(*m_routes[index2].edge(it->second), d);
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
    std::cout << "OUT" << std::endl;
    /*double dt = d / vmax;
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
    }*/
    return res;
}
