#pragma once

#include <istream>
#include <iostream>

struct __attribute__ ((visibility ("default")))  Point
{
    Point(double x, double y, double z, double vx, double vy, double vz, double t);

    Point(double x, double y, double z, double t);

    Point(double x, double y, double z);

    Point();

    double x() const;

    double y() const;

    double z() const;

    double vx() const;

    double vy() const;

    double vz() const;

    double t() const;

    double distance_to(const Point& point) const;

    friend std::istream& operator>> (std::istream &in, Point &point);
    friend std::ostream& operator<< (std::ostream &out, const Point &point);

private:

    double m_x, m_y, m_z;
    double m_vx, m_vy, m_vz;
    double m_t;
};

const Point min_point(0, 0, 0, 0);
const Point max_point(100000.0, 100000.0, 15000.0, 3600.0);
