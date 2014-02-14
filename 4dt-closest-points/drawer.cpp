#include "drawer.h"

Drawer::Graph::Graph(boost::function<double (Point)> abscissa,boost::function<double (Point)> ordinate,
      QLabel* label)
    : m_abscissa(abscissa)
    , m_ordinate(ordinate)
    , m_label(label)
{

}

boost::function<double (Point)> Drawer::Graph::abscissa() const
{
    return m_abscissa;
}

boost::function<double (Point)> Drawer::Graph::ordinate() const
{
    return m_ordinate;
}

QLabel* Drawer::Graph::label() const
{
    return m_label;
}

QPoint Drawer::Graph::to_qpoint(const Point& point) const
{
    double x = abscissa()(point), y = ordinate()(point);
    double width = abscissa()(max_point) - abscissa()(min_point);
    double height = ordinate()(max_point) - ordinate()(min_point);
    x -= abscissa()(min_point);
    y -= ordinate()(min_point);
    return QPoint(label()->width() * x / width, label()->height() * y / height);
}

void Drawer::add_graph(const Graph& graph)
{
    m_graphs.push_back(graph);
}

void Drawer::draw(const std::vector<Route>& routes, double t, const std::vector<Conflict>& conflicts)
{
    for (const Graph& graph : m_graphs)
    {
        draw(graph, routes, t, conflicts);
    }
}

void Drawer::draw(const Graph& graph, const std::vector<Route>& routes, double t, const std::vector<Conflict>& conflicts)
{
    QLabel* label = graph.label();
    QPixmap pm(QSize(label->width(), label->height()));
    pm.fill(label, 0, 0);

    QPainter painter(&pm);
    painter.fillRect(painter.viewport(), QColor(255, 255, 255));

    draw_routes(graph, &painter, routes);
    draw_routes_indicators(graph, &painter, routes, t);
    draw_conflicts(graph, &painter, routes, conflicts);

    label->setPixmap(pm);
}

void Drawer::draw_routes(const Graph& graph, QPainter* painter, const std::vector<Route>& routes)
{
    painter->setPen(QPen(Qt::black));
    for (const Route& route : routes)
    {
        for (size_t i = 0; i != route.size(); ++i)
        {
            boost::shared_ptr<Edge> edge = route.edge(i);
            QPoint a = graph.to_qpoint(*edge->a());
            QPoint b = graph.to_qpoint(*edge->b());
            painter->drawLine(a, b);
        }
    }
}

void Drawer::draw_routes_indicators(const Graph& graph, QPainter* painter, const std::vector<Route>& routes, double t)
{
    painter->setPen(QPen(Qt::red));
    for (const Route& route : routes)
    {
        Point indicator;
        if (route.get_position(t, indicator))
        {
            QPoint p = graph.to_qpoint(indicator);
            painter->drawEllipse(p, 3, 3);
        }
    }
}

void Drawer::draw_conflicts(const Graph& graph, QPainter* painter, const std::vector<Route>& routes, const std::vector<Conflict>& conflicts)
{
    painter->setPen(QPen(Qt::red));
    for (const Conflict& conflict : conflicts)
    {
        size_t index1 = conflict.route1_index();
        size_t index2 = conflict.route2_index();
        double start_time = conflict.start_time();
        double finish_time = conflict.finish_time();
        for (size_t i = 0; i < 2; ++i)
        {
            size_t index = (i ? index2 : index1);
            const Route& route = routes[index];
            size_t pointer = 0;
            while (pointer < route.size() && route.edge(pointer)->b()->t() < start_time)
            {
                ++pointer;
            }
            while (pointer < route.size() && route.edge(pointer)->a()->t() < finish_time)
            {
                boost::shared_ptr<Edge> edge = route.edge(pointer);
                double time_a = std::max(edge->a()->t(), start_time);
                double time_b = std::min(edge->b()->t(), finish_time);
                Point pa, pb;
                if (time_a <= time_b && edge->get_point(time_a, pa) && edge->get_point(time_b, pb))
                {
                    QPoint a = graph.to_qpoint(pa);
                    QPoint b = graph.to_qpoint(pb);
                    painter->drawLine(a, b);
                }
                ++pointer;
            }
        }
    }
}
