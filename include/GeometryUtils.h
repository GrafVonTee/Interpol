#ifndef TRIANGLE_INTERSECTIONS_GEOMETRYUTILS_H
#define TRIANGLE_INTERSECTIONS_GEOMETRYUTILS_H

#include <iostream>

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
        friend std::ostream& operator<<(std::ostream &out, const Point &point);
        Point& operator=(const Point &other);
        Point& operator=(Point &&other) noexcept;
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
        Edge& operator=(Edge &&other) noexcept;
        friend std::ostream& operator<<(std::ostream &out, const Edge &edge);
        bool operator==(const Edge &other) const;
        bool operator!=(const Edge &other) const;
    };
}
#endif //TRIANGLE_INTERSECTIONS_GEOMETRYUTILS_H