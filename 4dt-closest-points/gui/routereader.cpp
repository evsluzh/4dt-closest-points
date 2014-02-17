#include "routereader.h"

RouteReader::RouteReader(const std::string& filename)
    : m_in(filename)
{
    std::cout << "Opening file " << filename << std::endl;
}

std::vector<Route> RouteReader::read()
{
    int n;
    m_in >> n;
    std::vector<Route> routes(n);
    for (int i = 0; i < n; ++i)
    {
        m_in >> routes[i];
    }
    return routes;
}

RouteReader::~RouteReader()
{
    m_in.close();
}
