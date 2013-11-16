#pragma once

#include <istream>
#include <iostream>

const double inf = 1.0e99;

struct Point
{

    Point(double x, double y, double t) :
        m_x(x),
        m_y(y),
        m_t(t)
    {
    }

    Point(double x, double y) :
        Point(x, y, 0.0)
    {
    }

    Point()
        : Point(0.0, 0.0)
    {
    }

    double x() const
    {
        return m_x;
    }

    double y() const
    {
        return m_y;
    }

    double vx() const
    {
        return m_vx;
    }

    double vy() const
    {
        return m_vy;
    }

    double t() const
    {
        return m_t;
    }

    friend std::istream& operator>> (std::istream &in, Point &point);

private:

    double m_x, m_y;
    double m_vx, m_vy;
    double m_t;
};
