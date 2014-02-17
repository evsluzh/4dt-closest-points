#include "routewriter.h"
#include "core/route.h"

RouteWriter::RouteWriter(const std::string& filename)
    : m_out(filename)
{
    std::cout << "Opening file " << filename << std::endl;
}

void RouteWriter::write(const std::vector<Route>& routes)
{
    m_out << routes.size() << std::endl;
    for (size_t i = 0; i != routes.size(); ++i)
    {
        m_out << routes[i] << std::endl;
    }
}

RouteWriter::~RouteWriter()
{
    m_out.close();
}
