#include "geometrichashing.h"

GeometricHashing::GeometricHashing(std::vector<Route> routes) :
    ConflictPredictor(routes)
{
}

std::vector< std::pair<double, double> > GeometricHashing::calculate(size_t index1, size_t index2, double d)
{
    double dt = d / vmax;
    double start_time = m_routes[index1].edge(0)->a()->t();
}
