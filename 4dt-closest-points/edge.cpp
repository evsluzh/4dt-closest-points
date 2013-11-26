#include "edge.h"

Edge::Edge(boost::shared_ptr<Point> a, boost::shared_ptr<Point> b) :
    m_a(a),
    m_b(b)
{
}


boost::shared_ptr<Point> Edge::a() const
{
    return m_a;
}

boost::shared_ptr<Point> Edge::b() const
{
    return m_b;
}
