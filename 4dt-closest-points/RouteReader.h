#pragma once

#include "Route.h"
#include <fstream>
#include <vector>
#include <iostream>

struct RouteReader
{
    RouteReader(const std::string& filename) :
        in(filename)
    {
        std::cout << "Opening file " << filename << std::endl;
    }

    std::vector<Route> read()
    {
        int n;
        in >> n;
        std::vector<Route> routes(n);
        for (int i = 0; i < n; ++i)
        {
            in >> routes[i];
        }
        return routes;
    }

    virtual ~RouteReader()
    {
        in.close();
    }


private:
    RouteReader(const RouteReader& src);
    RouteReader& operator = (const RouteReader& src);

    std::ifstream in;
};
