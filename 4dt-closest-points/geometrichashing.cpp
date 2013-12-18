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
//    std::cout << "Ok2" << std::endl;
    std::vector<size_t> pointers(routes.size(), 0);
    for (double t = start_time; t < finish_time; t += dt)
    {
//        std::cout << "CUR T = " << t << std::endl;
        std::map<Block, std::vector< std::pair<size_t, size_t> > > blocks;
        for (size_t i = 0; i < routes.size(); ++i)
        {
            Point point;
            if (routes[i].get_position(t, point))
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
    const Route& route1 = m_routes[index1];
    const Route& route2 = m_routes[index2];
    std::set< std::pair<size_t, size_t> > current_conflicts = m_conflicts[std::make_pair(index1, index2)];
    double lt;
    bool in_conflict = false;

    for (auto it = current_conflicts.begin(); it != current_conflicts.end(); ++it)
    {
        double ct;
        int ptr1 = it->first, ptr2 = it->second;

        if (ptr1 == 0)
        {
            double t = route1.point(0)->t();
            double dist = 0.0;
            if (route1.edge(ptr1)->distance(*route2.edge(ptr2), t, dist) && dist <= d)
            {
                in_conflict = true;
                lt = t;
            }
        }
        if (ptr2 == 0)
        {
            double t = route2.point(0)->t();
            double dist = 0.0;
            if (route1.edge(ptr1)->distance(*route2.edge(ptr2), t, dist) && dist <= d)
            {
                in_conflict = true;
                lt = t;
            }
        }
        if (route1.edge(it->first)->intersect(*route2.edge(it->second), d, ct))
        {
            if (in_conflict)
            {
                res.push_back(std::make_pair(lt, ct));
                in_conflict = false;
            }
            else
            {
                lt = ct;
                in_conflict = true;
            }
        }

    }
    if (in_conflict)
    {
        res.push_back(std::make_pair(lt, std::min(route1.point(route1.size())->t(), route2.point(route2.size())->t())));
    }
    std::cout << "OUT" << std::endl;
    return res;
}
