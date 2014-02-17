#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include "core/route.h"

struct RouteReader
{
    RouteReader(const std::string& filename);

    std::vector<Route> read();

    virtual ~RouteReader();

private:
    RouteReader(const RouteReader& src);
    RouteReader& operator = (const RouteReader& src);

    std::ifstream m_in;
};
