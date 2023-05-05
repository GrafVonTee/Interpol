#ifndef TRIANGLE_INTERSECTIONS_GEOMETRYUTILS_H
#define TRIANGLE_INTERSECTIONS_GEOMETRYUTILS_H

#include <iostream>
#include <vector>
#include <string>
#include "StatesUtils.h"

// Type of coordinates
using coord_t = long double;

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
    */
    private:
        coord_t m_x{};
        coord_t m_y{};

    public:
        // Constructors
        Point() = default;
        Point(const coord_t &x, const coord_t &y);
        Point(const Point &other) = default;
        Point(Point &&other) noexcept;

        // Getters
        [[nodiscard]] coord_t getX() const;
        [[nodiscard]] coord_t getY() const;

        // Setters
        void setX(const coord_t &x);
        void setY(const coord_t &y);

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

    class Edge {
    /*
     2D Edge
     Low-level class for other Geometric Structures
     Private fields: m_left, m_right

     @param m_left: Start point
     @type m_left: Point

     @param m_right: Finish point
     @type m_right: Point
    */
    private:
        Point m_left{};
        Point m_right{};

    public:
        Edge() = default;
        Edge(const Point &left, const Point &right);
        Edge(Point &&left, Point &&right);
        Edge(const Edge &other) = default;
        Edge(Edge &&other) noexcept;

        // Getters
        [[nodiscard]] Point getLeft() const;
        [[nodiscard]] Point getRight() const;

        // Setters
        void setLeft(const Point &left);
        void setRight(const Point &right);

        // Operators
        Edge& operator=(const Edge &other);
        Edge& operator=(Edge&& other) noexcept;

        friend std::ostream& operator<<(std::ostream &out, const Edge &edge);

        bool operator==(const Edge &other) const;
        bool operator!=(const Edge &other) const;
        bool operator==(Edge&& other) const noexcept;
        bool operator!=(Edge&& other) const noexcept;
    };

    class Polygon {
    /*
     2D Polygon with N points (1 < n <= 6)
     High-level class for Intersection between 2 triangles
     Private fields: m_pointList, m_state

     @param m_pointList: Vector of polygon's points
     @type m_pointList: std::vector<Point>

     @param m_state: Type of polygon
     @type m_state: PolygonState

     Methods:
     * size(): return size of a vector
     * sortPoints(): sort vector using atan2 function
    */
    private:
        std::vector<Point> m_pointList{};
        States::PolygonState m_state = States::PolygonState::NotPolygon;

        static void checkPolygon(const std::vector<Point> &points);
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
        [[nodiscard]] std::vector<Point> getPointsCopy();

        // Methods
        [[nodiscard]] size_t size() const;
        void sortPoints();

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

    enum Letters {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        K,
        L,
        M,
        N,
        AllLetters,
    };
}

#endif //TRIANGLE_INTERSECTIONS_GEOMETRYUTILS_H