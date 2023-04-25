#include <gtest/gtest.h>
#include "GeometryUtils.h"
#include "StatesUtils.h"
 using namespace Geometry;
// Tests for the Point class
TEST(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point p(1, 2);
    EXPECT_EQ(p.getX(), 1);
    EXPECT_EQ(p.getY(), 2);
}

TEST(PointTest, CopyConstructor) {
    Point p1(1, 2);
    Point p2(p1);
    EXPECT_EQ(p1.getX(), p2.getX());
    EXPECT_EQ(p1.getY(), p2.getY());
}

TEST(PointTest, MoveConstructor) {
    Point p1(1, 2);
    Point p2(std::move(p1));
    EXPECT_EQ(p2.getX(), 1);
    EXPECT_EQ(p2.getY(), 2);
}

TEST(PointTest, AssignmentOperator) {
    Point p1(1, 2);
    Point p2;
    p2 = p1;
    EXPECT_EQ(p1.getX(), p2.getX());
    EXPECT_EQ(p1.getY(), p2.getY());
}

TEST(PointTest, MoveAssignmentOperator) {
    Point p1(1, 2);
    Point p2;
    p2 = std::move(p1);
    EXPECT_EQ(p2.getX(), 1);
    EXPECT_EQ(p2.getY(), 2);
}

TEST(PointTest, AdditionOperator) {
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3 = p1 + p2;
    EXPECT_EQ(p3.getX(), 4);
    EXPECT_EQ(p3.getY(), 6);
}

TEST(PointTest, SubtractionOperator) {
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3 = p2 - p1;
    EXPECT_EQ(p3.getX(), 2);
    EXPECT_EQ(p3.getY(), 2);
}

// Tests for the Edge class
TEST(EdgeTest, DefaultConstructor) {
    Edge e;
    EXPECT_EQ(e.getLeft().getX(), 0);
    EXPECT_EQ(e.getLeft().getY(), 0);
    EXPECT_EQ(e.getRight().getX(), 0);
    EXPECT_EQ(e.getRight().getY(), 0);
}

TEST(EdgeTest, ParameterizedConstructor) {
    Point p1(1, 2);
    Point p2(3, 4);
    Edge e(p1, p2);
    EXPECT_EQ(e.getLeft().getX(), 1);
    EXPECT_EQ(e.getLeft().getY(), 2);
    EXPECT_EQ(e.getRight().getX(), 3);
    EXPECT_EQ(e.getRight().getY(), 4);
}

TEST(EdgeTest, MoveConstructor) {
    Point p1(1, 2);
    Point p2(3, 4);
    Edge e(Point(1, 2), Point(3, 4));
    Edge e2(std::move(e));
    EXPECT_EQ(e2.getLeft().getX(), 1);
    EXPECT_EQ(e2.getLeft().getY(), 2);
    EXPECT_EQ(e2.getRight().getX(), 3);
    EXPECT_EQ(e2.getRight().getY(), 4);
}

// TEST(EdgeTest, AssignmentOperator) {
//     Point p1(1, 2);
//     Point p2(3, 4);
//     Edge e1(p1, p2);
//     Edge e2;
//     e2 = e1;
//     EXPECT_EQ(e2.getLeft().getX(), 1);
//     EXPECT_EQ(e2.getLeft().getY(), 2);
//     EXPECT_EQ(e2.getRight().getX(), 3);
//     EXPECT_EQ(e2.getRight().getY(), 4);
//     EXPECT_NE(&e1.getLeft(), &e2.getLeft());
//     EXPECT_NE(&e1.getRight(), &e2.getRight());
// }
