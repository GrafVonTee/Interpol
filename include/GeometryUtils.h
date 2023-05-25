#ifndef TRIANGLE_INTERSECTIONS_GEOMETRYUTILS_H
#define TRIANGLE_INTERSECTIONS_GEOMETRYUTILS_H

#include <iostream>
#include <vector>
#include <string>
#include "StatesUtils.h"

// Type of coordinates
using coord_t = double;

namespace Geometry {
    class Point {
    /*
     2D Point Class
     Low-level class for other Geometric Structures
     Private fields: m_x, m_y

     @param m_x: X coordinate
     @type m_x: coord_t

     @param m_y: Y coordinate
     @type m_y: coord_t

     @param m_label: Point's label
     @type m_label: char
    */
    private:
        coord_t m_x{};
        coord_t m_y{};
        std::string m_label{};

    public:
        // Constructors
        Point() = default;
        Point(const coord_t &x, const coord_t &y);
        Point(const coord_t &x, const coord_t &y, std::string label);
        Point(const Point &other) = default;
        Point(Point &&other) noexcept;

        // Getters
        [[nodiscard]] coord_t getX() const;
        [[nodiscard]] coord_t getY() const;
        [[nodiscard]] std::string getLabel() const;

        // Setters
        void setX(const coord_t &x);
        void setY(const coord_t &y);
        void setLabel(const std::string &label);

        // Operators
        Point operator+(const Point &other) const;
        Point operator-(const Point &other) const;
        Point& operator+=(const Point &other);
        Point& operator-=(const Point &other);

        bool operator==(const Point &other) const;
        bool operator!=(const Point &other) const;
        bool operator==(Point&& other) const noexcept;
        bool operator!=(Point&& other) const noexcept;

        Point& operator=(const Point &other);
        Point& operator=(Point &&other) noexcept;

        friend std::ostream& operator<<(std::ostream &out, const Point &point);
    };

    class Polygon {
    /*
     High-level class for 2D Polygon with N points
     Private fields: m_pointList, m_state

     @param m_pointList: Vector of polygon's points
     @type m_pointList: std::vector<Point>

     @param m_state: Type of polygon
     @type m_state: PolygonState

     Methods:
     size(): return size of a vector
     sortPoints(): sort vector using atan2 function
     emplaceBack(const Point& | Point&&): emplace point in Polygon, auto-validator and auto-sort
    */
    private:
        std::vector<Point> m_pointList{};
        States::PolygonState m_state = States::PolygonState::NotPolygon;

        // Validator for vector of points in Polygon
        static void checkPolygon(const std::vector<Point> &points);

        // Subfunction for checkPolygon(const std::vector<Point> &points)
        static void checkPointsForPolygon(const Point &p1, const Point &p2, const Point &p3);
    public:
        // Constructors
        Polygon() = default;
        explicit Polygon(const std::vector<Point> &points);
        Polygon(const Polygon &other) = default;
        Polygon(Polygon &&other) noexcept;

        // Getters
        [[nodiscard]] States::PolygonState getState() const;
        [[nodiscard]] std::vector<Point> &getPointsRef();
        [[nodiscard]] std::vector<Point> getPointsCopy() const;

        // Methods
        [[nodiscard]] size_t size() const;
        void sortPoints();
        void emplaceBack(const Point& point);
        void emplaceBack(Point&& point) noexcept;

        // Operators
        friend std::ostream &operator<<(std::ostream &out, const Polygon &polygon);

        Point &operator[](size_t index);
        const Point &operator[](size_t index) const;

        Polygon &operator=(const Polygon &other);
        Polygon &operator=(Polygon &&other) noexcept;

        bool operator==(const Polygon &other) const;
        bool operator==(Polygon &&other) const noexcept;
        bool operator!=(const Polygon &other) const;
        bool operator!=(Polygon &&other) const noexcept;
    };


    struct Intersection {
    /*
     Struct of Intersection between 2 geometric figures

     @param state: Type of Intersection
     @type state: IntersectionState

     @param polygon: Polygon that is contained points of intersection
     @type polygon: Polygon
    */
        States::IntersectionState state = States::IntersectionState::NoIntersection;
        Polygon polygon;
    };
}

#endif //TRIANGLE_INTERSECTIONS_GEOMETRYUTILS_H