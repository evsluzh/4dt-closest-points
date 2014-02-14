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

    friend std::istream& operator>> (std::istream &in, Point &point);
    friend std::ostream& operator<< (std::ostream &out, const Point &point);

private:

    double m_x, m_y;
    double m_vx, m_vy;
    double m_t;
};

const Point min_point(0, 0, 0);
const Point max_point(3600, 100000, 100000);
