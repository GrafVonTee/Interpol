#include "GeometryUtils.h"
#include <cassert>

namespace Geometry {
    Point::Point(const coord_t &x, const coord_t &y)
            : m_x(x), m_y(y) {}

    Point::Point(Point &&other) noexcept
            : m_x(other.m_x), m_y(other.m_y) {
        other.m_x = 0;
        other.m_y = 0;
    }

    coord_t Point::getX() const {
        return m_x;
    }

    coord_t Point::getY() const {
        return m_y;
    }

    void Point::setX(const coord_t &x) {
        m_x = x;
    }

    void Point::setY(const coord_t &y) {
        m_y = y;
    }

    Point& Point::operator=(const Point &other) {
        if (this != &other) {
            m_x = other.m_x;
            m_y = other.m_y;
        }
        return *this;
    }

    Point& Point::operator=(Point &&other) noexcept {
        if (this != &other) {
            m_x = other.m_x;
            m_y = other.m_y;
        }
        return *this;
    }

    Point Point::operator+(const Point &other) const {
        return Point{m_x + other.m_x, m_y + other.m_y};
    }

    Point Point::operator-(const Point &other) const {
        return Point{m_x - other.m_x, m_y - other.m_y};
    }

    Point& Point::operator+=(const Point &other) {
        m_x += other.m_x;
        m_y += other.m_y;
        return *this;
    }

    Point& Point::operator-=(const Point &other) {
        m_x -= other.m_x;
        m_y -= other.m_y;
        return *this;
    }

    bool Point::operator==(const Point &other) const {
        return (m_x == other.m_x) && (m_y == other.m_y);
    }

    bool Point::operator!=(const Point &other) const {
        return !(*this == other);
    }

    std::ostream& operator<<(std::ostream &out, const Point &point) {
        out << "(" << point.m_x << ", " << point.m_y << ")";
        return out;
    }

    bool Point::operator==(Point &&other) const noexcept {
        return (m_x == other.m_x) && (m_y == other.m_y);
    }

    bool Point::operator!=(Point &&other) const noexcept {
        return !(*this != other);
    }

    // Edge Implementation
    Edge::Edge(const Point &left, const Point &right)
    {
        if (left == right)
            throw std::runtime_error("Points must be different!");
        m_left = left;
        m_right = right;
    }

    Edge::Edge(Point &&left, Point &&right)
    {
        if (left == right)
            throw std::runtime_error("Points must be different!");

        m_left = std::move(left);
        m_right = std::move(right);
    }

    Edge::Edge(Edge &&other) noexcept
            : m_left(std::move(other.m_left)), m_right(std::move(other.m_right)) {}

    Point Edge::getLeft() const {
        return m_left;
    }

    Point Edge::getRight() const {
        return m_right;
    }

    void Edge::setLeft(const Point &left) {
        if (left == m_right)
            throw std::runtime_error("Points must be different!");
        m_left = left;
    }

    void Edge::setRight(const Point &right) {
        if (right == m_left)
            throw std::runtime_error("Points must be different!");
        m_right = right;
    }


    std::ostream& operator<<(std::ostream &out, const Edge &edge) {
        out << "[" << edge.getLeft() << ", " << edge.getRight() << "]";
        return out;
    }

    Edge& Edge::operator=(const Edge &other) {
        if (this != &other) {
            m_left = other.m_left;
            m_right = other.m_right;
        }
        return *this;
    }

    Edge& Edge::operator=(Edge &&other) noexcept {
        if (this != &other) {
            m_left = std::move(other.m_left);
            m_right = std::move(other.m_right);
        }
        return *this;
    }

    bool Edge::operator==(const Edge &other) const {
        return (m_left == other.m_left) && (m_right == other.m_right);
    }

    bool Edge::operator!=(const Edge &other) const {
        return !(*this == other);
    }

    bool Edge::operator==(Edge &&other) const noexcept {
        return (m_left == other.m_left) && (m_right == other.m_right);
    }
    bool Edge::operator!=(Edge &&other) const noexcept {
        return !(*this == other);
    }

    Polygon::Polygon(const std::vector<Point> &points) {
        if (points.size() > 6)
            throw std::runtime_error("Invalid number of points!");

        m_pointList = points;
        m_state = States::PolygonState(points.size());
    }

    Polygon::Polygon(Polygon &&other) noexcept {
        m_state = other.m_state;
        m_pointList = std::move(other.m_pointList);
    }

    States::PolygonState Polygon::getState() const {
        return m_state;
    }

    std::vector<Point> Polygon::getPoints() const {
        return m_pointList;
    }

    std::ostream& operator<<(std::ostream &out, const Polygon &polygon) {
        out << "Polygon[";
        for (auto i = 0; i < polygon.size(); ++i) {
            if (i == polygon.size() - 1) {
                out << polygon[i];
                continue;
            }
            out << polygon[i] << ", ";
        }
        out << "]";
        return out;
    }

    Point& Polygon::operator[](size_t index) {
        if (index >= this->size())
            throw std::runtime_error("Invalid index!");
        return m_pointList[index];
    }

    const Point& Polygon::operator[](size_t index) const {
        if (index >= this->size())
            throw std::runtime_error("Invalid index!");
        return m_pointList[index];
    }

    size_t Polygon::size() const {
        return m_pointList.size();
    }
}