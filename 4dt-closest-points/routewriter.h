#pragma once

#include "route.h"
#include <fstream>
#include <vector>
#include <iostream>

struct RouteWriter
{
    RouteWriter(const std::string& filename);

    void write(const std::vector<Route>& routes);

    virtual ~RouteWriter();

private:
    RouteWriter(const RouteWriter& src);
    RouteWriter& operator = (const RouteWriter& src);

    std::ofstream m_out;
};
