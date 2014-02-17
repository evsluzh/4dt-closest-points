#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include "core/route.h"

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
