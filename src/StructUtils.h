#ifndef TRIANGLE_INTERSECTIONS_STRUCTUTILS_H
#define TRIANGLE_INTERSECTIONS_STRUCTUTILS_H

#include <iostream>

using new_t = long double;

namespace Utils {
    namespace Geometry {
        class Point {
        private:
            new_t m_x{};
            new_t m_y{};
        public:
            // Constructors
            Point() = default;
            Point(const new_t &x, const new_t &y);
            Point(const Point &other) = default;
            Point(Point &&other) noexcept;

            // Getters
            [[nodiscard]] new_t getX() const;
            [[nodiscard]] new_t getY() const;

            // Setters
            void setX(const new_t &x);
            void setY(const new_t &y);

            // Operators
            Point operator+(const Point &other) const;
            Point operator-(const Point &other) const;
            Point &operator+=(const Point &other);
            Point &operator-=(const Point &other);
            bool operator==(const Point &other) const;
            bool operator!=(const Point &other) const;
            friend std::ostream &operator<<(std::ostream &in, const Point &point);
            Point &operator=(const Point &other);
            Point &operator=(Point &&other) noexcept;
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

            [[nodiscard]] new_t length() const;

            // Operators
            Edge &operator=(const Edge &other);
            Edge &operator=(Edge &&other) noexcept;
            friend std::ostream &operator<<(std::ostream &in, const Edge &edge);
            bool operator==(const Edge &other) const;
            bool operator!=(const Edge &other) const;
        };

        class Triangle {
        private:
            Point m_pointA {};
            Point m_pointB {};
            Point m_pointC {};

            Edge m_edgeAB {};
            Edge m_edgeBC {};
            Edge m_edgeAC {};
        public:
            Triangle() = default;
            Triangle(const Point& A, const Point& B, const Point& C);
            Triangle(const Edge& AB, const Edge& BC, const Edge& AC);

            // Getters
            [[nodiscard]] Point getA() const;
            [[nodiscard]] Point getB() const;
            [[nodiscard]] Point getC() const;

            [[nodiscard]] Edge getAB() const;
            [[nodiscard]] Edge getBC() const;
            [[nodiscard]] Edge getAC() const;

            // Setters
            void setA(const Point& A);
            void setB(const Point& B);
            void setC(const Point& C);

            void setAB(const Edge& AB);
            void setBC(const Edge& BC);
            void setAC(const Edge& AC);

            new_t area();
        };
    }

    namespace States {
        enum class InputState {
            IncorrectInput,
            IncorrectFormat,
            NegativeNumbers
        };

        enum class IntersectionState {
            Point,
            Edge,
            Triangle,
            Polygon,
            NoIntersection
        };

        enum class UnitTestState {
            // TODO
        };
    }
}
#endif //TRIANGLE_INTERSECTIONS_STRUCTUTILS_H
