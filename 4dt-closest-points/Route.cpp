#include "Route.h"
#include <iostream>

std::istream& operator>> (std::istream &in, Route &route) {
    int n;
    std::cout << "read route" << std::endl;
    in >> n;
    std::cout << n << " points" << std::endl;
    route.points.resize(n);
    for (int i = 0; i < n; ++i)
    {
        std::cout << "read point " << i << std::endl;
        in >> route.points[i];
    }
    return in;
}
