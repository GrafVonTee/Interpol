#include "gtest/gtest.h"
#include "GeometryUtils.h"
#include "StatesUtils.h"
#include "CalculateIntersections.h"
#include "Parsing.h"
#include "ConsoleInteraction.h"
#include "DrawImage.h"

using namespace Geometry;
using namespace Math;
using namespace Interaction;

TEST(ConsoleInteraction, ValidInputFormat) {
    std::istringstream input("(1.0, 2.0)\n");
    Point point = get<0>(getPoint(Geometry::Letters::A, input));
    ASSERT_EQ(point, Point(1.0, 2.0));
}

TEST(ConsoleInteraction, InvalidInputFormatPoint) {
    std::istringstream input("1,2\n(3.0, 4.0)\n");        
    testing::internal::CaptureStderr();    
    Point point = get<0>(getPoint(Geometry::Letters::A, input));    
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "Incorrect input! Please, enter values in CORRECT format '(x, y)'!\n");
    ASSERT_EQ(point, Point(0.0, 0.0));
}

TEST(ConsoleInteraction, EmptyString) {
    std::istringstream input("\n(3.0, 4.0)\n");       
    testing::internal::CaptureStderr();    
    Point point = get<0>(getPoint(Geometry::Letters::A, input));     
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "String is empty! Please, enter values in format '(x, y)'!\n");
    ASSERT_EQ(point, Point(0.0, 0.0));
}

TEST(ConsoleInteraction, ReenteredInvalidInputFormatTriangle) {
    std::istringstream input("1,2\n(3.0, 4.0)\n(1.0, 2.0)\n1,2\n(1.0, 4.0)\n");        
    testing::internal::CaptureStderr();    
    Polygon triangle = get<0>(getTriangle(1, input));    
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "Incorrect input! Please, enter values in CORRECT format '(x, y)'!\nIncorrect input! Please, enter values in CORRECT format '(x, y)'!\n");    
    EXPECT_EQ(triangle.size(), 3);
    ASSERT_EQ(triangle[0], Point(1.0, 2.0));
    ASSERT_EQ(triangle[1], Point(1.0, 4.0));
    ASSERT_EQ(triangle[2], Point(3.0, 4.0));
}

TEST(ConsoleInteraction, SamePointsTriangle) {
    std::istringstream input("(3.0, 4.0)\n(1.0, 2.0)\n(3.0, 4.0)\n");
    testing::internal::CaptureStderr();    
    Polygon triangle = get<0>(getTriangle(1, input));    
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "Points must be different!\n");
}

TEST(ConsoleInteraction, NotATriangle) {
    std::istringstream input("(0.0, 0.0)\n(0.0, 2.0)\n(0.0, 4.0)\n");
    testing::internal::CaptureStderr();    
    Polygon triangle = get<0>(getTriangle(1, input));    
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "Points are located in one line!\n");
}

TEST(ParserTest, ValidInput) {
    std::string input("(1.0, 2.0)");
    std::string result(" 1.0 2.0 ");

    // Parse the input
    std::string parsed = get<0>(Parsing::parsePoint(input));

    // Check if the parsed points match the expected points
    ASSERT_EQ(parsed, result);
}

// Test the parser with invalid input (missing comma)
TEST(ParserTest, InvalidInputMissingComma) {
    std::string input("(1.0 2.0)");

    // Parse the input
    ASSERT_EQ(get<1>(Parsing::parsePoint(input)), States::InputState::IncorrectInput);
}

// Test the parser with invalid input (missing parenthesis)
TEST(ParserTest, InvalidInputMissingParenthesis) {
    std::string input("1.0, 2.0)");

    ASSERT_EQ(get<1>(Parsing::parsePoint(input)), States::InputState::IncorrectInput);
}

TEST(IntersectionTest, NoIntersection) {
    // Create two triangles that do not intersect
    Polygon triangle1{{Point(0, 0), Point(1, 0), Point(0, 1)}};
    Polygon triangle2{{Point(2, 0), Point(3, 0), Point(2, 1)}};

    // Compute the intersection of the triangles
    Intersection intersection = findTriangleInter(triangle1, triangle2);

    // Check that the intersection is empty
    ASSERT_EQ(intersection.polygon.size(), 0);
}

TEST(IntersectionTest, SinglePointIntersection) {
    // Create two triangles that intersect at a single point
    Polygon triangle1{{Point(0, 0), Point(1, 0), Point(0, 1)}};
    Polygon triangle2{{Point(0.5, 0.5), Point(1.5, 0.5), Point(0.5, 1.5)}};

    // Compute the intersection of the triangles
    Intersection intersection = findTriangleInter(triangle1, triangle2);

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
    Intersection intersection = findTriangleInter(triangle1, triangle2);

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
    Intersection intersection = findTriangleInter(triangle1, triangle2);

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
    Intersection intersection = findTriangleInter(triangle1, triangle2);

    // Check that the intersection is the same as the smaller triangle
    ASSERT_EQ(intersection.polygon.size(), 3);
    ASSERT_EQ(intersection.state, States::IntersectionState::Nested);
    EXPECT_EQ(intersection.polygon, triangle1);
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
