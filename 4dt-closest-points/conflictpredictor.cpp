#include "conflictpredictor.h"

ConflictPredictor::ConflictPredictor(const std::vector<Route>& routes)
    : m_routes(routes)
{

}

std::vector<Conflict> ConflictPredictor::getConflicts(double threshold)
{
    std::vector<Conflict> conflicts;
    for (size_t i = 0; i != m_routes.size(); ++i)
    {
        for (size_t j = i + 1; j != m_routes.size(); ++j)
        {
            std::vector<Conflict> current_conflicts = getConflicts(i, j, threshold);
            // Append vector
            conflicts.insert(conflicts.end(), current_conflicts.begin(), current_conflicts.end());
        }
    }
    return conflicts;
}

ConflictPredictor::~ConflictPredictor()
{

}
