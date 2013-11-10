#include "Point.h"

std::istream& operator>> (std::istream &in, Point &point)
{
    in >> point.x;
    in >> point.y;
    in >> point.vx;
    in >> point.vy;
    in >> point.t;
    return in;
}

