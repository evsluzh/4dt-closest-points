#include "conflict.h"

Conflict::Conflict(size_t route1_index, size_t route2_index, double start_time, double finish_time)
    : m_route1_index(route1_index)
    , m_route2_index(route2_index)
    , m_start_time(start_time)
    , m_finish_time(finish_time)
{
}

size_t route1_index() const
{
    return m_route1_index;
}

size_t route2_index() const
{
    return m_route2_index;
}

double start_time() const
{
    return m_start_time;
}

double finish_time() const
{
    return m_finish_time;
}
