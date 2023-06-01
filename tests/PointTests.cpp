#include <iostream>
#include <tuple>
#include "gtest/gtest.h"
#include "GeometryUtils.h"

using namespace Geometry;

namespace ConstructorTests {
    TEST(PointTest, DefaultConstructor) {
        Point p;
        EXPECT_EQ(p.getX(), 0);
        EXPECT_EQ(p.getY(), 0);
        EXPECT_EQ(p.getLabel(), "");
    }

    TEST(PointTest, ParameterizedConstructor) {
        Point p(1, 2, "A");
        EXPECT_EQ(p.getX(), 1);
        EXPECT_EQ(p.getY(), 2);
        EXPECT_EQ(p.getLabel(), "A");
    }

    TEST(PointTest, CopyConstructor) {
        Point p1(1, 2, "A");
        Point p2(p1);
        EXPECT_EQ(p1.getX(), p2.getX());
        EXPECT_EQ(p1.getY(), p2.getY());
        EXPECT_EQ(p1.getLabel(), p2.getLabel());
    }

    TEST(PointTest, MoveConstructor) {
        Point p1(1, 2, "A");
        Point p2{p1};
        EXPECT_EQ(p2.getX(), 1);
        EXPECT_EQ(p2.getY(), 2);
        EXPECT_EQ(p2.getLabel(), "A");
    }
}

TEST(PointTest, AssignmentOperator) {
    Point p1(1, 2, "A");
    Point p2 = p1;
    EXPECT_EQ(p1.getX(), p2.getX());
    EXPECT_EQ(p1.getY(), p2.getY());
    EXPECT_EQ(p1.getLabel(), p2.getLabel());

    p2 = Point();
    EXPECT_EQ(p2.getX(), 0);
    EXPECT_EQ(p2.getY(), 0);
    EXPECT_EQ(p2.getLabel(), "");
}

TEST(PointTest, MoveAssignmentOperator) {
    Point p1(1, 2, "A");
    Point p2;
    p2 = std::move(p1);
    EXPECT_EQ(p2.getX(), 1);
    EXPECT_EQ(p2.getY(), 2);
    EXPECT_EQ(p2.getLabel(), "A");
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

namespace SetXTests {
    using test_cases_t = std::pair<coord_t , coord_t>;
    class PointSetXTestInterface : public ::testing::TestWithParam<test_cases_t> {
    protected:
        Point p {3, 2, "A"};
    };
    TEST_P(PointSetXTestInterface, EqualityOperator) {
        auto expected = std::get<1>(GetParam());
        auto input = std::get<0>(GetParam());

        SCOPED_TRACE("Test");
        p.setX(input);
        EXPECT_EQ(expected, p.getX())
        << "Test: "
        << p << ".setX(" << input << ")" << ".getX()"
        << "\nExpected: " << expected
        << std::endl;
    }
    INSTANTIATE_TEST_SUITE_P(
            TestCases,
            PointSetXTestInterface,
            ::testing::Values(
                    std::make_pair(3, 3),
                    std::make_pair(2.5, 2.5),
                    std::make_pair(10000000, 10000000)
            ));
}

namespace SetYTests {
    using test_cases_t = std::pair<coord_t , coord_t>;
    class PointSetYTestInterface : public ::testing::TestWithParam<test_cases_t> {
    protected:
        Point p {3, 2, "A"};
    };
    TEST_P(PointSetYTestInterface, EqualityOperator) {
        auto expected = std::get<1>(GetParam());
        auto input = std::get<0>(GetParam());

        SCOPED_TRACE("Test");
        p.setY(input);
        EXPECT_EQ(expected, p.getY())
                            << "Test: "
                            << p << ".setY(" << input << ")" << ".getY()"
                            << "\nExpected: " << expected
                            << std::endl;
    }
    INSTANTIATE_TEST_SUITE_P(
            TestCases,
            PointSetYTestInterface,
            ::testing::Values(
                    std::make_pair(2, 2),
                    std::make_pair(2.5, 2.5),
                    std::make_pair(10000000, 10000000)
            ));

}

namespace SetLabelTests {
    using test_cases_t = std::pair<std::string, std::string>;
    class PointSetLabelTestInterface : public ::testing::TestWithParam<test_cases_t> {
    protected:
        Point p {3, 2, "A"};
    };
    TEST_P(PointSetLabelTestInterface, EqualityOperator) {
        auto expected = std::get<1>(GetParam());
        auto input = std::get<0>(GetParam());

        SCOPED_TRACE("Test");
        p.setLabel(input);
        EXPECT_EQ(expected, p.getLabel())
                            << "Test: "
                            << p << ".setLabel('" << input << "')" << ".getLabel()"
                            << "\nExpected: " << expected
                            << std::endl;
    }
    INSTANTIATE_TEST_SUITE_P(
            TestCases,
            PointSetLabelTestInterface,
            ::testing::Values(
                    std::make_pair("A", "A"),
                    std::make_pair("", ""),
                    std::make_pair("AKNSJFKNSKJFNDJKFNSKDMSKFNSFJKSNF", "AKNSJFKNSKJFNDJKFNSKDMSKFNSFJKSNF")
            ));

};

namespace EqualityOperatorTest {
    using test_cases_t = std::tuple <std::pair<Point, Point>, bool>;

    class PointEqualityOperatorTestInterface : public ::testing::TestWithParam<test_cases_t> {
    };

    TEST_P(PointEqualityOperatorTestInterface, EqualityOperator) {
        auto expected = std::get<1>(GetParam());
        auto input = std::get<0>(GetParam());

        SCOPED_TRACE("Test");
        EXPECT_EQ(expected, input.first == input.second)
                            << "Test: "
                            << input.first << " == " << input.second
                            << "\nExpected: " << std::boolalpha << expected
                            << std::endl;
    }

    INSTANTIATE_TEST_SUITE_P(
            EqualityTestCases,
            PointEqualityOperatorTestInterface,
            ::testing::Values(
                    std::make_tuple(std::make_pair(Point(3, 2, "A"), Point{3, 2, "A"}), true),
                    std::make_tuple(std::make_pair(Point(3, 2, "A"), Point{3, 2, "B"}), true),
                    std::make_tuple(std::make_pair(Point(13, 2, "A"), Point{3, 2, "B"}), false),
                    std::make_tuple(std::make_pair(Point(), Point{0, 0, ""}), true),
                    std::make_tuple(std::make_pair(Point{}, Point{0, 3211, ""}), false),
                    std::make_tuple(std::make_pair(Point{0.3333, 0.4444}, Point{0, 3211, ""}), false),
                    std::make_tuple(std::make_pair(Point{0.000000000001, 0.4444}, Point{0.000000000002, 0.4444, ""}),
                                    false),
                    std::make_tuple(std::make_pair(Point{0.0123456789123456789, 0.4444},
                                                   Point{0.0123456789123456789, 0.4444, ""}), true)
            ));
}

namespace InequalityOperatorTest {
    using test_cases_t = std::tuple <std::pair<Point, Point>, bool>;

    class PointInequalityOperatorTestInterface : public ::testing::TestWithParam<test_cases_t> {
    };

    TEST_P(PointInequalityOperatorTestInterface, InequalityOperator) {
        auto expected = std::get<1>(GetParam());
        auto input = std::get<0>(GetParam());

        SCOPED_TRACE("Test");
        EXPECT_EQ(expected, input.first != input.second)
                            << "Test: "
                            << input.first << " != " << input.second
                            << "\nExpected: " << std::boolalpha << expected
                            << std::endl;
    }

    INSTANTIATE_TEST_SUITE_P(
            InequalityTestCases,
            PointInequalityOperatorTestInterface,
            ::testing::Values(
                    std::make_tuple(std::make_pair(Point(3, 2, "A"), Point{3, 2, "A"}), false),
                    std::make_tuple(std::make_pair(Point(3, 2, "A"), Point{3, 2, "B"}), false),
                    std::make_tuple(std::make_pair(Point(13, 2, "A"), Point{3, 2, "B"}), true),
                    std::make_tuple(std::make_pair(Point(), Point{0, 0, ""}), false),
                    std::make_tuple(std::make_pair(Point{}, Point{0, 3211, ""}), true),
                    std::make_tuple(std::make_pair(Point{0.3333, 0.4444}, Point{0, 3211, ""}), true),
                    std::make_tuple(std::make_pair(Point{0.000000000001, 0.4444}, Point{0.000000000002, 0.4444, ""}),
                                    true),
                    std::make_tuple(std::make_pair(Point{0.0123456789123456789, 0.4444},
                                                   Point{0.0123456789123456789, 0.4444, ""}), false)
            ));
}

TEST(PointTest, OutOperator) {
    Point p = {1, 2, "A"};
    testing::internal::CaptureStdout();
    std::cout << p;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(1, 2, A)")
    << "Test: "
    <<  "std::cout << " << output
    << "\nExpected: " << output
    << std::endl;;

    testing::internal::CaptureStdout();
    p = Point();
    std::cout << p << std::endl;
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(0, 0, )\n")
    << "Test: "
    <<  "std::cout << " << output
    << "\nExpected: " << output << "\n"
    << std::endl;;
}