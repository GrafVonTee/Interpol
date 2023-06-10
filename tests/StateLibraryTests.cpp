#include "gtest/gtest.h"
#include "StatesLibrary.h"
#include "GeometryUtils.h"

namespace StateLibTest {
    using namespace Manipulator;
    using namespace Geometry;

    using test_cases_t = FiguresState;

    class StatesLibTestInterface : public testing::TestWithParam<test_cases_t> {
    protected:
        StatesLibrary& statesLib = StatesLibrary::getInstance();
        size_t size = 0;
    };

    TEST_F(StatesLibTestInterface, StartStateLibTest) {
        EXPECT_EQ(statesLib.getSize(), 0);
        EXPECT_TRUE(statesLib.isEmpty());

        EXPECT_THROW({
             try {
                 FiguresState temp = statesLib.getState();
             }
             catch (const std::exception &e) {
                 EXPECT_STREQ("Library is empty!", e.what());
                 throw;
             }
       }, std::range_error);
    }

    TEST_P(StatesLibTestInterface, addState) {
        auto input = GetParam();

        statesLib.addState(input);
        size += 1;
        SCOPED_TRACE("Test");
        ASSERT_EQ(statesLib.getSize(), size);

        FiguresState addedFigure = statesLib.getState();
        ASSERT_EQ(addedFigure.polygon1, input.polygon1);
        ASSERT_EQ(addedFigure.polygon2, input.polygon2);
        ASSERT_EQ(addedFigure.intersection.polygon, input.intersection.polygon);
        ASSERT_EQ(addedFigure.intersection.state, input.intersection.state);
    }

    INSTANTIATE_TEST_SUITE_P(
            TestCases,
            StatesLibTestInterface,
            ::testing::Values(
                    FiguresState{Polygon(),
                                 Polygon(),
                                 {States::IntersectionState::NoIntersection, Polygon()}
                    }
            )
    );

}