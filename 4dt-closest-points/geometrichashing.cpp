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
    double dt = dmax / vmax;
    double start_time = routes[0].edge(0)->a()->t();
    double finish_time = routes[0].edge(routes[0].size() - 1)->b()->t();
    for (size_t i = 0; i < routes.size(); ++i)
    {
//        const Route cur = m_routes[i];
        start_time = std::min(start_time, routes[i].edge(0)->a()->t());
        finish_time = std::max(finish_time, routes[i].edge(routes[i].size() - 1)->b()->t());
//        for (size_t j = 0; j != routes[i].size(); ++j)
//        {
//            dt = std::min(dt, routes[i].edge(j)->b()->t() - routes[i].edge(j)->a()->t());
//        }
    }
    std::vector<size_t> pointers(routes.size(), 0);

    double previous_time = start_time;
    for (double t = start_time; t <= finish_time;)
    {
        double next_time = t + dt;
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
                            std::vector< std::pair<double, double> >& current_conflicts = m_conflicts[std::make_pair(it->first, i)];
                            if (!current_conflicts.empty() && previous_time <= current_conflicts.back().second)
                            {
                                current_conflicts.back().second = next_time;
                            }
                            else
                            {
                                current_conflicts.push_back(std::make_pair(previous_time, next_time));
                            }
                        }
                    }
                }
                blocks[block].push_back(std::make_pair(i, pointers[i]));
            }
        }
        previous_time = t;
        t = next_time;
    }
}

std::vector<Conflict> GeometricHashing::getConflicts(size_t index1, size_t index2, double d)
{
    if (index1 > index2)
    {
        std::swap(index1, index2);
    }
    const Route& route1 = m_routes[index1];
    const Route& route2 = m_routes[index2];
    std::vector< std::pair<double, double> > potential_conflicts = m_conflicts[std::make_pair(index1, index2)];
    size_t pointer1 = 0, pointer2 = 0;

    std::vector<Conflict> conflicts;
    for (const std::pair<double, double>& potential_conflict : potential_conflicts)
    {
        double start_time = potential_conflict.first, finish_time = potential_conflict.second;
        while (pointer1 < route1.size() && route1.edge(pointer1)->a()->t() < start_time)
        {
            ++pointer1;
        }
        while (pointer2 < route2.size() && route2.edge(pointer2)->a()->t() < start_time)
        {
            ++pointer2;
        }
        double open_time = 0.0;
        bool in_conflict = false;

        if (pointer1 == route1.size() || pointer2 == route2.size())
        {
            continue;
        }
        double t = std::max(route1.point(pointer1)->t(), route2.point(pointer2)->t());
        double dist;
        if (route1.edge(pointer1)->distance(*route2.edge(pointer2), t, dist) && dist <= d)
        {
            in_conflict = true;
            open_time = t;
        }

        while (pointer1 < route1.size() && pointer2 < route2.size() && route1.edge(pointer1)->a()->t() < finish_time && route2.edge(pointer2)->a()->t() < finish_time)
        {
            double intersect_time;
            if (route1.edge(pointer1)->intersect(*route2.edge(pointer2), d, intersect_time))
            {
                if (in_conflict)
                {
                    conflicts.push_back(Conflict(index1, index2, open_time, intersect_time));
                    in_conflict = false;
                }
                else
                {
                    open_time = intersect_time;
                    in_conflict = true;
                }
            }
            if (route1.edge(pointer1)->a()->t() < route2.edge(pointer2)->a()->t())
            {
                ++pointer1;
            }
            else
            {
                ++pointer2;
            }
        }

        if (in_conflict)
        {
            double finish_time = std::min(route1.point(route1.size())->t(), route2.point(route2.size())->t());
            conflicts.push_back(Conflict(index1, index2, open_time, finish_time));
        }
    }
    return conflicts;
}
