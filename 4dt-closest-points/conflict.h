#pragma once

struct Conflict
{
    Conflict(size_t route1_index, size_t route2_index, double start_time, double finish_time);
    size_t route1_index() const;
    size_t route2_index() const;
    double start_time() const;
    double finish_time() const;

private:
    size_t m_route1_index;
    size_t m_route2_index;
    double m_start_time;
    double m_finish_time;
};

