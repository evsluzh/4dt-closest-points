#include "routesgenerator.h"
#include <cstdlib>
#include <ctime>

RoutesGenerator::RoutesGenerator(int based_points, int routes_count, int route_points)
    : m_based_points(based_points)
    , m_routes_count(routes_count)
    , m_route_points(route_points)
{
    srand(42134 * time(0) + 4328941);
}

std::vector<Route> RoutesGenerator::generate() const
{
    std::vector<Point> based_points = generate_points(m_based_points, max_point.x(), max_point.y());
    std::vector< std::vector<int> > g(m_based_points);
//    std::cout << "BASED_POINTS = "  << m_based_points << std::endl;
    for (int i = 1; i < m_based_points; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            int u = rand() % i;
            if (u != i)
            {
                g[u].push_back(i);
                g[i].push_back(u);
            }
        }
    }
    std::vector<Route> routes(m_routes_count);
    for (int i = 0; i < m_routes_count; ++i)
    {
        const int HALF_MAX_TIME = max_point.t() / 2;
        int start_time = rand() % HALF_MAX_TIME;
        int finish_time = HALF_MAX_TIME + rand() % HALF_MAX_TIME;
        double dt = 1.0 * (finish_time - start_time) / m_route_points;

        size_t cur = rand() % m_based_points;
        double cx = based_points[cur].x(), cy = based_points[cur].y();
        double time = start_time;

        std::vector<Point> points;
        Point init(cx, cy, 0, 0, start_time);
        points.push_back(init);
        time += dt;
        while ((int)points.size() < m_route_points)
        {
            int next = g[cur][rand() % g[cur].size()];
            double nx = based_points[next].x(), ny = based_points[next].y();
//            std::cout << "GOTO " << nx << ' ' << ny << " " << cx << " " << cy << " " << (fabs(cx - nx) + fabs(cy - ny) > 0.001) << std::endl;
            while (fabs(cx - nx) + fabs(cy - ny) > 0.01)
            {
                double dx = (nx - cx);
                double dy = (ny - cy);
                double l = sqrt(dx * dx + dy * dy);
                if (l / dt > vmax)
                {
                    dx *= vmax * dt / l;
                    dy *= vmax * dt / l;
                }
                cx += dx;
                cy += dy;
                Point cur(cx, cy, dx, dy, time);
                points.push_back(cur);
                time += dt;
//                std::cout << cx << " " << cy << ' ' << nx << ' ' << ny << std::endl;
//                if ((int)points.size() >= m_route_points)
//                {
//                    break;
//                }
            }
            cur = next;
        }

        routes[i] = Route(points);
//        std::cout << routes[i].size() << ": " << std::endl;
//        for (size_t j = 0; j < routes[i].size(); ++j)
//        {
//            std::cout << routes[i].edge(j)->a()->x() << " " << routes[i].edge(j)->a()->y() << std::endl;
//        }
    }
    return routes;
}

std::vector<Point> RoutesGenerator::generate_points(int n, int w, int h) const
{
    std::vector<Point> res(n);
    for (int i = 0; i < n; ++i)
    {
        res[i] = Point(rand() % w, rand() % h);
    }
    return res;
}
