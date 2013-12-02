#include "point.h"
#include <limits>
#include <cstdlib>
#include <cmath>

Point::Point(double x, double y, double t) :
    m_x(x),
    m_y(y),
    m_t(t)
{
}

Point::Point(double x, double y) :
    m_x(x),
    m_y(y),
    m_t(0.0)
{
}

Point::Point() :
    m_x(0.0),
    m_y(0.0),
    m_t(0.0)
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

bool Point::infinity() const
{
    return (m_x != m_x);
}


double Point::distance_to(const Point& point) const
{
    int dx = m_x - point.m_x;
    int dy = m_y - point.m_y;
    return sqrt(dx * dx + dy * dy);
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

