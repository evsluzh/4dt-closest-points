#include "point.h"

Point::Point(double x, double y, double t) :
    m_x(x),
    m_y(y),
    m_t(t)
{
}

Point::Point(double x, double y) :
    Point(x, y, 0.0)
{
}

Point::Point()
    : Point(0.0, 0.0)
{
}

double Point::x() const
{
    return m_x;
}

double Point::y() const
{
    return m_y;
}

double Point::vx() const
{
    return m_vx;
}

double Point::vy() const
{
    return m_vy;
}

double Point::t() const
{
    return m_t;
}

std::istream& operator>> (std::istream &in, Point &point)
{
    in >> point.m_x;
    in >> point.m_y;
    in >> point.m_vx;
    in >> point.m_vy;
    in >> point.m_t;
    return in;
}

