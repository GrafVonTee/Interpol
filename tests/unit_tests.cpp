#include "gtest/gtest.h"
#include "GeometryUtils.h"
#include "StatesUtils.h"
#include "CalculateIntersections.h"
 using namespace Geometry;
 using namespace Math;

TEST(IntersectionTest, NoIntersection) {
    // Create two triangles that do not intersect
    Polygon triangle1{{Point(0, 0), Point(1, 0), Point(0, 1)}};
    Polygon triangle2{{Point(2, 0), Point(3, 0), Point(2, 1)}};

    // Compute the intersection of the triangles
    Polygon intersection = findIntersection(triangle1, triangle2);

    // Check that the intersection is empty
    ASSERT_TRUE(intersection.points.empty());
}

TEST(IntersectionTest, SinglePointIntersection) {
    // Create two triangles that intersect at a single point
    Polygon triangle1{{Point(0, 0), Point(1, 0), Point(0, 1)}};
    Polygon triangle2{{Point(0.5, 0.5), Point(1.5, 0.5), Point(0.5, 1.5)}};

    // Compute the intersection of the triangles
    Polygon intersection = findIntersection(triangle1, triangle2);

    // Check that the intersection contains a single point
    ASSERT_EQ(intersection.points.size(), 1);
    EXPECT_EQ(intersection.points[0], Point(0.5, 0.5));
}

TEST(IntersectionTest, SingleLineIntersection) {
    // Create two triangles that intersect along a single edge
    Polygon triangle1{{Point(0, 0), Point(1, 0), Point(0, 1)}};
    Polygon triangle2{{Point(0, 0), Point(1, 0), Point(1, 1)}};

    // Compute the intersection of the triangles
    Polygon intersection = findIntersection(triangle1, triangle2);

    // Check that the intersection contains a single edge
    ASSERT_EQ(intersection.points.size(), 2);
    EXPECT_EQ(intersection.points[0], Point(0, 0));
    EXPECT_EQ(intersection.points[1], Point(1, 0));
}

TEST(IntersectionTest, OverlappingTriangle) {
    // Create two triangles where one is completely contained in the other
    Polygon triangle1{{Point(0, 0), Point(2, 0), Point(0, 2)}};
    Polygon triangle2{{Point(1, 1), Point(3, 1), Point(1, 3)}};

    // Compute the intersection of the triangles
    Polygon intersection = findIntersection(triangle1, triangle2);

    // Check that the intersection is the same as the smaller triangle
    ASSERT_EQ(intersection.points.size(), 3);
    EXPECT_EQ(intersection, triangle2);
}

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
