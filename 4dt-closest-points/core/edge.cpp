#include "edge.h"
#include <limits>
#include <cmath>

Edge::Edge(boost::shared_ptr<Point> a, boost::shared_ptr<Point> b)
    : m_a(a)
    , m_b(b)
{
}

bool Edge::intersect(const Edge& edge, double d, double& time) const
{
    const int TERNARY_ITERATIONS = 100;
    const double EPS = 1.0e-9;
    double l = std::max(m_a->t(), edge.m_a->t());
    double r = std::min(m_b->t(), edge.m_b->t());
    if (l > r)
    {
        return false;
    }
    double val1, val2;
    if (!distance(edge, l, val1) || !distance(edge, r, val2))
    {
        return false;
    }
    val1 -= d; val2 -= d;
//    std::cout << l << ' ' << r << ' ' << val1 << ' ' << val2 << std::endl;
    if (val1 * val2 > 0)
    {
        return false;
    }
    if (val1 <= 0 && val2 <= 0)
    {
        return false;
    }
    if (fabs(val1) < EPS && fabs(val2) < EPS)
    {
        return false;
    }
//    std::cout << "Go" << std::endl;
    for (size_t i = 0; i < TERNARY_ITERATIONS; ++i)
    {
        double m = 0.5 * (l + r);
        double dist;
        distance(edge, m, dist);
        dist -= d;
        if (val1 * dist <= 0)
        {
            r = m;
            val2 = dist;
        }
        else
        {
            l = m;
            val1 = dist;
        }
    }
    double tm = 0.5 * (l + r);
//    std::cout << "TIME = " << tm << std::endl;
    time = tm;
    return true;
}

bool Edge::get_point(double t, Point& point) const
{
    if (t < m_a->t() || m_b->t() < t)
    {
        return false;
    }
    double t1 = m_a->t();
    double t2 = m_b->t();
    double k1 = (t2 - t) / (t2 - t1);
    double k2 = 1.0 - k1;
    double x = m_a->x() * k1 + m_b->x() * k2;
    double y = m_a->y() * k1 + m_b->y() * k2;
    double z = m_a->z() * k1 + m_b->z() * k2;
    point = Point(x, y, z, t1 * k1 + t2 * k2);
    return true;
}

boost::shared_ptr<Point> Edge::a() const
{
    return m_a;
}

boost::shared_ptr<Point> Edge::b() const
{
    return m_b;
}

bool Edge::distance(const Edge& edge, double t, double& dist) const
{
    Point p1, p2;
    if (!get_point(t, p1) || !edge.get_point(t, p2))
    {
        return false;
    }
    dist = p1.distance_to(p2);
    return true;
}
