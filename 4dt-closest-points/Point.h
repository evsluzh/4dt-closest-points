#pragma once

struct Point
{
    Point()
        : x(0.0), y(0.0)
    {
    }

    Point(double m_x, double m_y)
        : x(m_x), y(m_y)
    {
    }

    double get_x() const
    {
        return x;
    }

    double get_y() const
    {
        return y;
    }

    double get_vx() const
    {
        return vx;
    }

    double get_vy() const
    {
        return vy;
    }

    double get_t() const
    {
        return t;
    }

private:
    double x, y;
    double vx, vy;
    double t;
};
