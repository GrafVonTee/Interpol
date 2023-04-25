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
        return m_x == other.m_x && m_y == other.m_y;
    }

    bool Point::operator!=(const Point &other) const {
        return !(*this == other);
    }

    std::ostream& operator<<(std::ostream &out, const Point &point) {
        out << "(" << point.m_x << ", " << point.m_y << ")";
        return out;
    }

    // Edge Implementation
    Edge::Edge(const Point &left, const Point &right)
            : m_left(left), m_right(right) {
        assert(left != right);
    }

    Edge::Edge(Point &&left, Point &&right)
            : m_left(std::move(left)), m_right(std::move(right)) {
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
        assert(left != this->m_right);
        m_left = left;
    }

    void Edge::setRight(const Point &right) {
        assert(right != this->m_left);
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
}