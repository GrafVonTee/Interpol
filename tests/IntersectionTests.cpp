#include "gtest/gtest.h"
#include "GeometryUtils.h"
#include "CalculateIntersections.h"

using namespace Geometry;
using namespace Math;

TEST(IntersectionTest, FourPointIntersection) {
    // Create two triangles that do not intersect
    Polygon triangle1{{Point(100.0, 200.0), Point(100.0, 400.0), Point(300.0, 400.0)}};
    Polygon triangle2{{Point(100.0, 100.0), Point(100.0, 500.0), Point(500.0, 100.0)}};

    // Compute the intersection of the triangles
    Intersection intersection = findPolygonsInter(triangle1, triangle2);

    // Check that the intersection is empty
    ASSERT_EQ(intersection.polygon.size(), 4);
}

TEST(IntersectionTest, SinglePointIntersection) {
    // Create two triangles that intersect at a single point
    Polygon triangle1{{Point(0, 0), Point(1, 0), Point(0, 1)}};
    Polygon triangle2{{Point(0.5, 0.5), Point(1.5, 0.5), Point(0.5, 1.5)}};

    // Compute the intersection of the triangles
    Intersection intersection = findPolygonsInter(triangle1, triangle2);

    // Check that the intersection contains a single point
    ASSERT_EQ(intersection.polygon.size(), 1);
    ASSERT_EQ(intersection.state, States::IntersectionState::Polygon);
    EXPECT_EQ(intersection.polygon[0], Point(0.5, 0.5));
}

TEST(IntersectionTest, SingleLineIntersection) {
    // Create two triangles that intersect along a single edge
    Polygon triangle1{{Point(0, 0), Point(0, 1), Point(1, 0)}};
    Polygon triangle2{{Point(0, 0), Point(1, 0), Point(0, -1)}};

    // Compute the intersection of the triangles
    Intersection intersection = findPolygonsInter(triangle1, triangle2);

    // Check that the intersection contains a single edge
    ASSERT_EQ(intersection.polygon.size(), 2);
    ASSERT_EQ(intersection.state, States::IntersectionState::Polygon);
    EXPECT_EQ(intersection.polygon[1], Point(1, 0));
}

TEST(IntersectionTest, PolygonIntersection) {
    // Create two triangles that intersect along a single edge
    Polygon triangle1{{Point(0, 0), Point(1, 0), Point(0, 1)}};
    Polygon triangle2{{Point(0, 0), Point(1, 0), Point(1, 1)}};

    // Compute the intersection of the triangles
    Intersection intersection = findPolygonsInter(triangle1, triangle2);

    // Check that the intersection contains a single edge
    ASSERT_EQ(intersection.polygon.size(), 3);
    ASSERT_EQ(intersection.state, States::IntersectionState::Polygon);
    EXPECT_EQ(intersection.polygon[1], Point(0.5, 0.5));
}

TEST(IntersectionTest, OverlappingTriangle) {
    // Create two triangles where one is completely contained in the other
    Polygon triangle1{{Point(0, 0), Point(0, 2), Point(2, 0)}};
    Polygon triangle2{{Point(0, 0), Point(0, 3), Point(3, 0)}};

    // Compute the intersection of the triangles
    Intersection intersection = findPolygonsInter(triangle1, triangle2);

    // Check that the intersection is the same as the smaller triangle
    ASSERT_EQ(intersection.polygon.size(), 3);
    ASSERT_EQ(intersection.state, States::IntersectionState::Nested);
    EXPECT_EQ(intersection.polygon, triangle1);
}