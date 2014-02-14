#pragma once
#include "point.h"
#include "conflict.h"
#include "route.h"
#include <vector>
#include <QtGui/QLabel>
#include <QtGui/QPainter>
#include <boost/function.hpp>

struct Drawer
{
    struct Graph
    {
        Graph(boost::function<double (Point)> abscissa, boost::function<double (Point)> ordinate,
              QLabel* label);
        boost::function<double (Point)> abscissa() const;
        boost::function<double (Point)> ordinate() const;
        QLabel* label() const;
        QPoint to_qpoint(const Point& point) const;
    private:
        boost::function<double (Point)> m_abscissa;
        boost::function<double (Point)> m_ordinate;
        QLabel* m_label;
    };

    void add_graph(const Graph& graph);
    void draw(const std::vector<Route>& routes, double t, const std::vector<Conflict>& conflict);

private:
    void draw(const Graph& graph, const std::vector<Route>& routes, double t,
              const std::vector<Conflict>& conflicts);

    void draw_routes(const Graph& graph, QPainter* painter, const std::vector<Route>& routes);
    void draw_routes_indicators(const Graph& graph, QPainter* painter, const std::vector<Route>& routes, double t);
    void draw_conflicts(const Graph& graph, QPainter* painter, const std::vector<Route>& routes, const std::vector<Conflict>& conflicts);
    std::vector<Graph> m_graphs;
};

