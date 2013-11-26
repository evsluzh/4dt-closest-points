#include "Point.h"

std::istream& operator>> (std::istream &in, Point &point)
{
    in >> point.m_x;
    in >> point.m_y;
    in >> point.m_vx;
    in >> point.m_vy;
    in >> point.m_t;
    return in;
}

