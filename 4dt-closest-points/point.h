#pragma once

#include <istream>
#include <iostream>

const double inf = 1.0e99;

struct Point
{

    Point(double x, double y, double t);

    Point(double x, double y);

    Point();

    double x() const;

    double y() const;

    double vx() const;

    double vy() const;

    double t() const;

    friend std::istream& operator>> (std::istream &in, Point &point);

private:

    double m_x, m_y;
    double m_vx, m_vy;
    double m_t;
};
