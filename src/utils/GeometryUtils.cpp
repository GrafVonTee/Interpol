#include "GeometryUtils.h"
#include <cmath>
#include <algorithm>

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
            throw std::logic_error("Points must be different!");

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
            throw std::logic_error("Points must be different!");
        m_left = left;
    }

    void Edge::setRight(const Point &right) {
        if (right == m_left)
            throw std::logic_error("Points must be different!");
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

    // Polygon Implementation
    Polygon::Polygon(const std::vector<Point> &points) {
        if (points.size()>1)
            checkPolygon(points);
        m_pointList = points;
        if (!points.empty())
            sortPoints();
        m_state = States::PolygonState(points.size());
    }

    Polygon::Polygon(Polygon &&other) noexcept {
        m_state = other.m_state;
        m_pointList = std::move(other.m_pointList);
    }

    States::PolygonState Polygon::getState() const {
        return m_state;
    }

    std::vector<Point>& Polygon::getPointsRef() {
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
            throw std::range_error("Invalid index!");
        return m_pointList[index];
    }

    const Point& Polygon::operator[](size_t index) const {
        if (index >= this->size())
            throw std::range_error("Invalid index!");
        return m_pointList[index];
    }

    size_t Polygon::size() const {
        return m_pointList.size();
    }

    std::vector<Point> Polygon::getPointsCopy() {
        return m_pointList;
    }

    Polygon& Polygon::operator=(const Polygon &other) {
        if (this != &other) {
            m_pointList = other.m_pointList;
            m_state = other.m_state;
        }
        return *this;
    }

    Polygon& Polygon::operator=(Polygon &&other) noexcept {
        if (this != &other) {
            m_pointList = std::move(other.m_pointList);
            m_state = other.m_state;
            other.m_state = States::PolygonState::NotPolygon;
        }
        return *this;
    }

    bool Polygon::operator==(const Polygon &other) const {
        if (this->size() != other.size())
            return false;

        for (size_t i = 0; i < this->size(); ++i)
            if (this->m_pointList[i] != other[i])
                return false;
        return true;
    }

    bool Polygon::operator==(Polygon &&other) const noexcept {
        if (this->size() != other.size())
            return false;

        for (size_t i = 0; i < this->size(); ++i)
            if (this->m_pointList[i] != other[i])
                return false;
        return true;
    }

    bool Polygon::operator!=(const Polygon &other) const {
        return !(*this == other);
    }

    bool Polygon::operator!=(Polygon &&other) const noexcept {
        return !(*this == other);
    }

    void Polygon::checkPolygon(const std::vector<Point>& points) {
        if (points.size() > 6)
            throw std::length_error("Invalid number of points!");

        for (size_t i = 0; i < points.size(); ++i)
            for (size_t j = i + 1; j < points.size(); ++j)
                if (points[i] == points[j])
                    throw std::logic_error("Points must be different!");

        for (size_t i = 0; i < points.size() - 3; ++i)
            checkPointsForPolygon(points[i], points[i+1], points[i+2]);

        checkPointsForPolygon(points[points.size() - 1], points[0], points[1]); // FAB
        checkPointsForPolygon(points[points.size() - 2], points[points.size() - 1], points[0]); // EFA
    }

    void Polygon::checkPointsForPolygon(const Point &p1, const Point &p2, const Point &p3) {
        long double eps = 1e-20;
        if (std::pow((p3.getX() - p1.getX()) / (p2.getX() - p1.getX())
                     - (p3.getY() - p1.getY()) / (p2.getY() - p1.getY()), 2) <= eps)
            throw std::logic_error("Points are located in one line!");
    }

    bool MinKey(const Point& first, const Point& second) {
        if (first.getY() < second.getY())
            return true;
        if ((first.getY() == second.getY()) && (first.getX() < second.getX()))
            return true;
        return false;
    }


    void Polygon::sortPoints() {
        auto iterator = std::min_element(m_pointList.begin(),
                                                        m_pointList.end(),
                                                        MinKey);
        Point center = *iterator;
        m_pointList.erase(iterator);

        std::sort(m_pointList.begin(),
                  m_pointList.end(),
                  [center](const Point &first, const Point &second)\
 {
                      return atan2(first.getY() - center.getY(), first.getX() - center.getX()) >
                             atan2(second.getY() - center.getY(), second.getX() - center.getX());
                  });
        m_pointList.insert(m_pointList.begin(), center);
    }
}