#include "Route.h"

std::istream& operator>> (std::istream &in, Route &route) {
    int n;
    in >> n;
    route.points.resize(n);
    for (int i = 0; i < n; ++i)
    {
        in >> route.points[i];
    }
    return in;
}
