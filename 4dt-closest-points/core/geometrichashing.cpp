#include "geometrichashing.h"
#include "conflict.h"
#include <algorithm>
#include <limits>
#include <cassert>
#include <boost/shared_ptr.hpp>

Block::Block(int x, int y, int z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
{

}

Block::Block(const Point& point, double d)
    : m_x(point.x() / d)
    , m_y(point.y() / d)
    , m_z(point.z() / d)
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

int Block::z() const
{
    return m_z;
}

bool operator < (const Block& a, const Block& b)
{
    if (a.m_x != b.m_x)
    {
        return a.m_x < b.m_x;
    }
    if (a.m_y != b.m_y)
    {
        return a.m_y < b.m_y;
    }
    return a.m_z < b.m_z;
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
    int iterations = 0;
    for (double t = start_time; t <= finish_time;)
    {
        ++iterations;
        double next_time = t + dt;
        std::map<Block, std::vector<size_t> > blocks;
        for (size_t i = 0; i < routes.size(); ++i)
        {
            while (pointers[i] < routes[i].size() && routes[i].edge(pointers[i])->b()->t() < t)
            {
                ++pointers[i];
            }
            Point point;
            if (pointers[i] < routes[i].size() && routes[i].edge(pointers[i])->a()->t() <= t && routes[i].edge(pointers[i])->get_point(t, point))
            {
                Block block(point, dmax);
                for (int dx = -1; dx <= 1; ++dx)
                {
                    for (int dy = -1; dy <= 1; ++dy)
                    {
                        for (int dz = -1; dz <= 1; ++dz)
                        {
                            Block cur(block.x() + dx, block.y() + dy, block.z() + dz);
                            const auto& positions = blocks[cur];
                            for (auto it = positions.begin(); it != positions.end(); ++it)
                            {
                                std::vector< std::pair<double, double> >& current_conflicts = m_potential_conflicts[std::make_pair(*it, i)];
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
                }
                blocks[block].push_back(i);
            }
        }
        previous_time = t;
        t = next_time;
    }
    std::cout << "Iterations = " << iterations << std::endl;
}

std::vector<Conflict> GeometricHashing::getConflicts(size_t index1, size_t index2, double d)
{
    if (index1 > index2)
    {
        std::swap(index1, index2);
    }
    const Route& route1 = m_routes[index1];
    const Route& route2 = m_routes[index2];
    const std::vector< std::pair<double, double> >& potential_conflicts = m_potential_conflicts[std::make_pair(index1, index2)];

    std::vector<Conflict> conflicts;
    for (const std::pair<double, double>& potential_conflict : potential_conflicts)
    {
        double start_time = std::max(potential_conflict.first, std::max(route1.point(0)->t(), route2.point(0)->t()));
        double finish_time = std::min(potential_conflict.second, std::min(route1.point(route1.size())->t(), route2.point(route2.size())->t()));
        if (start_time > finish_time)
        {
            continue;
        }
        int pointer1 = route1.find_edge_by_time(start_time);
        int pointer2 = route2.find_edge_by_time(start_time);
        if (pointer1 == -1 || pointer2 == -1)
        {
            continue;
        }
        double open_time = 0.0;
        bool in_conflict = false;

        double t = std::max(route1.point(pointer1)->t(), route2.point(pointer2)->t());
        double dist;
        if (route1.edge(pointer1)->distance(*route2.edge(pointer2), t, dist) && dist <= d)
        {
            in_conflict = true;
            open_time = t;
        }

//        std::cout << "GO " << open_time << ' ' << dist * dist << ' ' << (in_conflict ? "open" : "close") << std::endl;
//        std::cout << "start_time = " << start_time << std::endl;
//        if (pointer1 < route1.size())
//        {
//            std::cout << "First edge: " << pointer1 << " " << route1.edge(pointer1)->a()->t() << " " << route1.edge(pointer1)->b()->t() << std::endl;
//        }
//        if (pointer2 < route2.size())
//        {
//            std::cout << "Second edge: " << pointer2 << " " << route2.edge(pointer2)->a()->t() << " " << route2.edge(pointer2)->b()->t() << std::endl;
//        }
        while (pointer1 < (int)route1.size() && pointer2 < (int)route2.size() && route1.edge(pointer1)->a()->t() < finish_time && route2.edge(pointer2)->a()->t() < finish_time)
        {
            std::pair<double, double> conflict;
            if (calc_local(in_conflict, open_time, conflict, d, *route1.edge(pointer1), *route2.edge(pointer2)))
            {
                conflicts.push_back(Conflict(index1, index2, conflict.first, conflict.second));
            }
            if (route1.edge(pointer1)->b()->t() < route2.edge(pointer2)->b()->t())
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

void GeometricHashing::create_edge_coord_function(double x1, double x2, double t1, double t2, double& ka, double& kb)
{
    double dt = t2 - t1;
    ka = x2 - x1;
    kb = x1 * t2 - x2 * t1;
    ka /= dt;
    kb /= dt;
}

void GeometricHashing::create_edge_distance_coord_function(double t11, double t12, double t21, double t22, double x11, double x12, double x21, double x22,
                                                    double& a, double& b, double& c)
{
    double ka1, ka2;
    double kb1, kb2;
    create_edge_coord_function(x11, x12, t11, t12, ka1, kb1);
    create_edge_coord_function(x21, x22, t21, t22, ka2, kb2);
    double ka = ka1 - ka2;
    double kb = kb1 - kb2;
    a = ka * ka;
    b = 2 * ka * kb;
    c = kb * kb;
}

bool GeometricHashing::calc_local(bool& open, double& open_time, std::pair<double, double>& conflict, double d, const Edge& edge1, const Edge& edge2)
{
    double t11 = edge1.a()->t(), t12 = edge1.b()->t();
    double t21 = edge2.a()->t(), t22 = edge2.b()->t();
    double x11 = edge1.a()->x(), x12 = edge1.b()->x();
    double x21 = edge2.a()->x(), x22 = edge2.b()->x();
    double y11 = edge1.a()->y(), y12 = edge1.b()->y();
    double y21 = edge2.a()->y(), y22 = edge2.b()->y();


    double start_time = std::max(t11, t21), finish_time = std::min(t12, t22);

    double a1, b1, c1;
    double a2, b2, c2;
    create_edge_distance_coord_function(t11, t12, t21, t22, x11, x12, x21, x22, a1, b1, c1);
    create_edge_distance_coord_function(t11, t12, t21, t22, y11, y12, y21, y22, a2, b2, c2);
    double ka = a1 + a2;
    double kb = b1 + b2;
    double kc = c1 + c2;
    kc -= d * d;

    double start_value = (ka * start_time + kb) * start_time + kc;
    double end_value = (ka * finish_time + kb) * finish_time + kc;
//    std::cout << "Distances: (" << start_time << ", " << finish_time << "): (" << start_value << ", " << end_value << ")" << std::endl;

    const double EPS = 1.0e-10;

    if (open && start_value > 0)
    {
        assert(false);
    }
    double kd = kb * kb - 4.0 * ka * kc;
    if (kd < EPS)
    {
        return false;
    }
    kd = sqrt(kd);
    double t1 = (- kb - kd) / 2.0 / ka;
    double t2 = (- kb + kd) / 2.0 / ka;
    bool res = false;
    if (start_time <= t1 && t1 <= finish_time)
    {
        if (open)
        {
            conflict = std::make_pair(open_time, t1);
            res = true;
        }
        else
        {
            open_time = t1;
        }
        open ^= true;
    }
    if (start_time <= t2 && t2 <= finish_time)
    {
        if (open)
        {
            conflict = std::make_pair(open_time, t2);
            res = true;
        }
        else
        {
            open_time = t2;
        }
        open ^= true;
    }
    if (open)
    {
        assert(end_value < 0);
    }
    else
    {
        assert(end_value > 0);
    }
    return res;
}
