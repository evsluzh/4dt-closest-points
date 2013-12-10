#include "edge.h"
#include <limits>

Edge::Edge(boost::shared_ptr<Point> a, boost::shared_ptr<Point> b)
    : m_a(a)
    , m_b(b)
{
}

bool Edge::intersect(const Edge& edge, double d, double& time) const
{
    double l = std::max(m_a->t(), edge.m_a->t());
    double r = std::min(m_b->t(), edge.m_b->t());
    if (l > r)
    {
        return false;
    }
    double val1, val2;
    if (!distance(edge, l, val1) || !distance(edge, r, val2)) {
        return false;
    }
    std::cout << val1 << ' ' << val2 << std::endl;
    if (val1 > d && val2 > d)
    {
        return false;
    }
    if (val1 < d && val2 < d)
    {
        return false;
    }
    for (size_t i = 0; i < 100; ++i)
    {
        double m1 = (2.0 * l + r) / 3.0;
        double m2 = (l + 2.0 * r) / 3.0;

        double d1, d2;
        distance(edge, m1, d1);
        distance(edge, m2, d2);

        if (d1 > d2)
        {
            l = m1;
        }
        else
        {
            r = m2;
        }
    }
    double tm = 0.5 * (l + r);
    double dval;
    distance(edge, tm, dval);
    std::cout << "DVAL = " << dval << " " << d << std::endl;
    if (dval > d) {
        return false;
    }
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
    double k = (t - t1) / (t2 - t1);
    double x = m_a->x() * (1 - k) + m_b->x() * k;
    double y = m_a->y() * (1 - k) + m_b->y() * k;
    point = Point(x, y, t);
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
    if (!get_point(t, p1) || !edge.get_point(t, p2)) {
        return false;
    }
    dist = p1.distance_to(p2);
    return true;
}
