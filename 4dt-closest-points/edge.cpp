#include "edge.h"
#include <limits>

Edge::Edge(boost::shared_ptr<Point> a, boost::shared_ptr<Point> b) :
    m_a(a),
    m_b(b)
{
}

double Edge::intersect(const Edge& edge, double d) const
{
    double l = std::max(m_a->t(), edge.m_a->t());
    double r = std::min(m_b->t(), edge.m_b->t());
    if (l > r)
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
    double val1 = distance(edge, l);
    double val2 = distance(edge, r);
    std::cout << val1 << ' ' << val2 << std::endl;
    if (val1 > d && val2 > d)
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
    if (val1 < d && val2 < d)
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
    for (size_t i = 0; i < 100; ++i)
    {
        double m1 = (2.0 * l + r) / 3.0;
        double m2 = (l + 2.0 * r) / 3.0;

        double d1 = distance(edge, m1);
        double d2 = distance(edge, m2);

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
    double dval = distance(edge, tm);
    std::cout << "DVAL = " << dval << " " << d << std::endl;
    return (dval > d) ? std::numeric_limits<double>::quiet_NaN() : tm;
}

Point Edge::point(double t) const
{
    if (t < m_a->t() || m_b->t() < t)
    {
        return Point(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());
    }
    double t1 = m_a->t();
    double t2 = m_b->t();
    double k = (t - t1) / (t2 - t1);
    double x = m_a->x() * (1 - k) + m_b->x() * k;
    double y = m_a->y() * (1 - k) + m_b->y() * k;
    return Point(x, y, t);
}

boost::shared_ptr<Point> Edge::a() const
{
    return m_a;
}

boost::shared_ptr<Point> Edge::b() const
{
    return m_b;
}

double Edge::distance(const Edge& edge, double t) const
{
    Point p1 = point(t);
    Point p2 = edge.point(t);
    if (p1.infinity() || p2.infinity())
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return p1.distance_to(p2);
}
