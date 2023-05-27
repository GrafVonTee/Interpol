#include <cmath>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <utility>
#include "GeometryUtils.h"

namespace Geometry {
    Point::Point(const coord_t &x, const coord_t &y)
            : m_x(x), m_y(y) {}

    Point::Point(const coord_t &x, const coord_t &y, std::string label)
            : m_x(x), m_y(y), m_label(std::move(label)) {}

    Point::Point(Point &&other) noexcept
            : m_x(other.m_x), m_y(other.m_y), m_label(std::move(other.m_label)) {
        other.m_x = 0;
        other.m_y = 0;
        other.m_label = "#";
    }

    coord_t Point::getX() const {
        return m_x;
    }

    coord_t Point::getY() const {
        return m_y;
    }

    std::string Point::getLabel() const {
        return m_label;
    }

    void Point::setX(const coord_t &x) {
        m_x = x;
    }

    void Point::setY(const coord_t &y) {
        m_y = y;
    }

    void Point::setLabel(const std::string &label) {
        m_label = label;
    }

    Point& Point::operator=(const Point &other) {
        if (this != &other) {
            m_x = other.m_x;
            m_y = other.m_y;
            m_label = other.m_label;
        }
        return *this;
    }

    Point& Point::operator=(Point &&other) noexcept {
        if (this != &other) {
            m_x = other.m_x;
            m_y = other.m_y;
            m_label = other.m_label;
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
        return (
                std::abs(m_x - other.m_x) <= std::numeric_limits<coord_t>::epsilon() and
                std::abs(m_y - other.m_y) <= std::numeric_limits<coord_t>::epsilon()
        );
    }

    bool Point::operator!=(const Point &other) const {
        return !(*this == other);
    }

    std::ostream& operator<<(std::ostream &out, const Point &point) {
        out << "(" << point.m_x << ", " << point.m_y << ")";
        return out;
    }

    bool Point::operator==(Point &&other) const noexcept {
        return (
                std::abs(m_x - other.m_x) < std::numeric_limits<coord_t>::epsilon() and
                std::abs(m_y - other.m_y) < std::numeric_limits<coord_t>::epsilon()
        );
    }

    bool Point::operator!=(Point &&other) const noexcept {
        return !(*this != other);
    }

    // Polygon Implementation
    Polygon::Polygon(const std::vector<Point> &points) {

        if (points.size() > 1 && !(points.size() == 2 && points[0] != points[1]))
            checkPolygon(points);

        m_pointList = points;
        if (!points.empty())
            sortPoints();

        m_state = States::PolygonState(
                (points.size() < (size_t)States::PolygonState::AllStates)
                ? points.size() : (size_t)States::PolygonState::OtherPolygon);
    }

    Polygon::Polygon(Polygon &&other) noexcept {
        m_state = other.m_state;
        m_pointList = std::move(other.m_pointList);

        other.m_state = States::PolygonState::NotPolygon;
        other.m_pointList.clear();
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

    std::vector<Point> Polygon::getPointsCopy() const {
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
        for (size_t i = 0; i < points.size(); ++i)
            for (size_t j = i + 1; j < points.size(); ++j)
                if (points[i] == points[j])
                {
                    std::string errorType = "Points: ";
                    errorType = errorType + points[i].getLabel() + " and " + points[j].getLabel() + " are equal!";
                    throw std::logic_error(errorType);
                }

        for (size_t i = 0; i < points.size() - 3; ++i)
            checkPointsForPolygon(points[i], points[i+1], points[i+2]);

        checkPointsForPolygon(points[points.size() - 1], points[0], points[1]); // ZAB
        checkPointsForPolygon(points[points.size() - 2], points[points.size() - 1], points[0]); // YZA
    }

    void Polygon::checkPointsForPolygon(const Point &p1, const Point &p2, const Point &p3) {
        if (std::pow(
                ((p3.getX() - p1.getX()) * (p2.getY() - p1.getY())) -
                        (p3.getY() - p1.getY()) * (p2.getX() - p1.getX()), 2)
                <= std::numeric_limits<coord_t>::epsilon())
        {
            std::string errorType = "Points: ";
            errorType = errorType + p1.getLabel() + ", " + p2.getLabel() + ", " + p3.getLabel() +
                    " are located in one line!";

            throw std::logic_error(errorType);
        }
    }

    // We decide that the minimal point is the point, that located below than another (has minimal Y coord).
    // If we had a point with the same Y coord, we take the point that located lefter than another (has minimal X coord).

    bool isMinPoint(const Point& first, const Point& second) {
        if (first.getY() < second.getY())
            return true;
        if ((first.getY() == second.getY()) && (first.getX() < second.getX()))
            return true;
        return false;
    }


    // We sort point so, that we can build a convex polygon when we iterate by points in sorted order.
    // (We believe that it is possible to create a convex polygon with these points as vertex of this polygon)
    void Polygon::sortPoints() {

        // At the beginning, we choose the starting point as a minimal point.

        auto iterator = std::min_element(m_pointList.begin(),m_pointList.end(), isMinPoint);
        Point center = *iterator;
        m_pointList.erase(iterator);

        // We use atan function as monotone function, that shows us the order of point relative to the starting point.

        std::sort(m_pointList.begin(), m_pointList.end(), [center](const Point &first, const Point &second) {
            return atan2(first.getY() - center.getY(), first.getX() - center.getX()) >
                   atan2(second.getY() - center.getY(), second.getX() - center.getX());});

        m_pointList.insert(m_pointList.begin(), center);
    }
}