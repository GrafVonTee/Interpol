#ifndef TRIANGLE_INTERSECTIONS_GEOMETRYUTILS_H
#define TRIANGLE_INTERSECTIONS_GEOMETRYUTILS_H

#include <iostream>
#include <vector>
#include <string>
#include "StatesUtils.h"

using coord_t = long double;

namespace Geometry {
    class Point {
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
    private:
        std::vector<Point> m_pointList {};
        States::PolygonState m_state = States::PolygonState::NotPolygon;

    public:
        // Constructors
        Polygon() = default;
        explicit Polygon(const std::vector<Point>& points);
        Polygon(const Polygon& other) = default;
        Polygon(Polygon&& other) noexcept;

        // Getters
        [[nodiscard]] States::PolygonState getState() const;
        [[nodiscard]] std::vector<Point>& getPointsRef();
        [[nodiscard]] std::vector<Point> getPointsCopy();

        [[nodiscard]] size_t size() const;

        // operators
        friend std::ostream& operator<<(std::ostream &out, const Polygon &polygon);
        Point& operator[](size_t index);
        Polygon& operator=(const Polygon& other);
        Polygon& operator=(Polygon&& other) noexcept;
        const Point& operator[](size_t index) const;

        bool operator==(const Polygon& other) const;
        bool operator==(Polygon&& other) const noexcept;
        bool operator!=(const Polygon &other) const;
        bool operator!=(Polygon&& other) const noexcept;
    };

    struct Intersection {
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