#pragma once

#include <istream>
#include <iostream>

struct Point
{
    Point(double x, double y, double vx, double vy, double t);

    Point(double x, double y, double t);

    Point(double x, double y);

    Point();

    double x() const;

    double y() const;

    double vx() const;

    double vy() const;

    double t() const;

    double distance_to(const Point& point) const;

    bool infinity() const;

    friend std::istream& operator>> (std::istream &in, Point &point);

private:

    double m_x, m_y;
    double m_vx, m_vy;
    double m_t;
};
