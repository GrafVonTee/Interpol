#include "StructUtils.h"

namespace Utils::Geometry {

        Point::Point(const new_t &x, const new_t &y)
                : m_x(x), m_y(y) {}

        Point::Point(Point &&other) noexcept
                : m_x(other.m_x), m_y(other.m_y) {
            other.m_x = 0;
            other.m_y = 0;
        }

        new_t Point::getX() const {
            return m_x;
        }

        new_t Point::getY() const {
            return m_y;
        }

        void Point::setX(const new_t &x) {
            m_x = x;
        }

        void Point::setY(const new_t &y) {
            m_y = y;
        }

        Point &Point::operator=(const Point &other) {
            if (this != &other) {
                m_x = other.m_x;
                m_y = other.m_y;
            }
            return *this;
        }

        Point &Point::operator=(Point &&other) noexcept {
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

        Point &Point::operator+=(const Point &other) {
            m_x += other.m_x;
            m_y += other.m_y;
            return *this;
        }

        Point &Point::operator-=(const Point &other) {
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

        std::ostream &operator<<(std::ostream &in, const Point &point) {
            in << "(" << point.m_x << ", " << point.m_y << ")";
            return in;
        }

        // Edge Implementation
        Edge::Edge(const Point &left, const Point &right)
                : m_left(left), m_right(right) {}

        Edge::Edge(Point &&left, Point &&right)
                : m_left(std::move(left)), m_right(std::move(right)) {}

        Edge::Edge(Edge &&other) noexcept
                : m_left(std::move(other.m_left)), m_right(std::move(other.m_right)) {}

        Point Edge::getLeft() const {
            return m_left;
        }

        Point Edge::getRight() const {
            return m_right;
        }

        void Edge::setLeft(const Point &left) {
            m_left = left;
        }

        void Edge::setRight(const Point &right) {
            m_right = right;
        }

        new_t Edge::length() const {
            return std::sqrt(
                    std::pow(m_right.getX() - m_left.getX(), 2) +
                    std::pow(m_right.getY() - m_left.getY(), 2));
        }

        std::ostream &operator<<(std::ostream &os, const Edge &edge) {
            os << "[" << edge.getLeft() << ", " << edge.getRight() << "]";
            return os;
        }

        Edge &Edge::operator=(const Edge &other) {
            if (this != &other) {
                m_left = other.m_left;
                m_right = other.m_right;
            }
            return *this;
        }

        Edge &Edge::operator=(Edge &&other) noexcept {
            if (this != &other) {
                m_left = std::move(other.m_left);
                m_right = std::move(other.m_right);
            }
            return *this;
        }

        bool Edge::operator==(const Edge &other) const {
            return m_left == other.m_left && m_right == other.m_right;
        }

        bool Edge::operator!=(const Edge &other) const {
            return !(*this == other);
        }

        // Triangle Implementation
        Triangle::Triangle(const Point &A, const Point &B, const Point &C)
                : m_pointA(A), m_pointB(B), m_pointC(C),
                  m_edgeAB(Edge(A, B)),
                  m_edgeBC(Edge(B, C)),
                  m_edgeAC(Edge(A, C)) {}

        Triangle::Triangle(const Edge &AB, const Edge &BC, const Edge &AC)
                : m_edgeAB(AB), m_edgeBC(BC), m_edgeAC(AC),
                  m_pointA(AB.getLeft()), m_pointB(BC.getLeft()), m_pointC(AC.getRight()) {}

        Point Triangle::getA() const {
            return m_pointA;
        }

        Point Triangle::getB() const {
            return m_pointB;
        }

        Point Triangle::getC() const {
            return m_pointC;
        }

        Edge Triangle::getAB() const {
            return m_edgeAB;
        }

        Edge Triangle::getBC() const {
            return m_edgeBC;
        }

        Edge Triangle::getAC() const {
            return m_edgeAC;
        }

        void Triangle::setA(const Point& A) {
            m_pointA = A;
            m_edgeAB.setLeft(A);
            m_edgeAC.setRight(A);
        }

        void Triangle::setB(const Point& B) {
            m_pointB = B;
            m_edgeAB.setRight(B);
            m_edgeBC.setLeft(B);
        }

        void Triangle::setC(const Point& C) {
            m_pointC = C;
            m_edgeBC.setRight(C);
            m_edgeAC.setLeft(C);
        }

        void Triangle::setAB(const Edge& AB) {
            m_edgeAB = AB;
            m_pointA = AB.getLeft();
            m_pointB = AB.getRight();
            m_edgeAC.setRight(m_pointA);
            m_edgeBC.setLeft(m_pointB);
        }

        void Triangle::setBC(const Edge& BC) {
            m_edgeBC = BC;
            m_pointB = BC.getLeft();
            m_pointC = BC.getRight();
            m_edgeAB.setRight(m_pointB);
            m_edgeAC.setLeft(m_pointC);
        }

        void Triangle::setAC(const Edge& AC) {
            m_edgeAC = AC;
            m_pointA = AC.getLeft();
            m_pointC = AC.getRight();
            m_edgeAB.setLeft(m_pointA);
            m_edgeAC.setRight(m_pointC);
        }

        new_t Triangle::area() {
            new_t s = (m_edgeAB.length() + m_edgeBC.length() + m_edgeAC.length()) / 2.0;
            return std::sqrt(s * (s - m_edgeAB.length()) * (s - m_edgeBC.length()) * (s - m_edgeAC.length()));
        }
    }
