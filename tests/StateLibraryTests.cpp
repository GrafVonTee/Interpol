#include "gtest/gtest.h"
#include "StatesLibrary.h"
#include "GeometryUtils.h"

namespace StateLibTest {
    using namespace Manipulator;
    using namespace Geometry;

    class StatesLibTestInterface : public testing::Test {
    protected:
        StatesLibrary& statesLib = StatesLibrary::getInstance();
    };

    TEST_F(StatesLibTestInterface, StartStateLibTest) {
        EXPECT_EQ(statesLib.getSize(), 0);
        EXPECT_TRUE(statesLib.isEmpty());

        EXPECT_THROW({
             try {
                 FiguresState temp = statesLib.getStateCopy();
             }
             catch (const std::exception &e) {
                 EXPECT_STREQ("Library is empty! Nothing to get.", e.what());
                 throw;
             }
       }, std::underflow_error);
    }

    TEST_F(StatesLibTestInterface, StateLibInsntance) {
        StatesLibrary& tempLib = StatesLibrary::getInstance();
        EXPECT_EQ(&tempLib, &statesLib);
    }

    TEST_F(StatesLibTestInterface, AddStateTest) {
        FiguresState figuresState = FiguresState{};
        for (int i = 1; i <= 10; ++i) {
            figuresState.polygon1 = Polygon({Point(1, i)});
            statesLib.addState(figuresState);
            ASSERT_EQ(statesLib.getSize(), i);
            ASSERT_EQ(statesLib.getStateCopy().polygon1, figuresState.polygon1);
        }
    }

    TEST_F(StatesLibTestInterface, EmplaceStateRefTest) {
        FiguresState figuresState = FiguresState{};
        for (int i = 1; i <= 10; ++i) {
            figuresState.polygon1 = Polygon({Point(1, 10+i)});
            statesLib.emplaceState(figuresState);
            ASSERT_EQ(statesLib.getSize(), 10+i);
            ASSERT_EQ(statesLib.getStateCopy().polygon1, Polygon({Point(1, 10+i)}));
        }
    }

    TEST_F(StatesLibTestInterface, EmplaceStateMoveTest) {
        for (int i = 1; i <= 10; ++i) {
            statesLib.emplaceState(FiguresState{Polygon({Point(1, 20+i)})});
            ASSERT_EQ(statesLib.getSize(), 20+i);
            ASSERT_EQ(statesLib.getStateCopy().polygon1, Polygon({Point(1, 20+i)}));
        }
    }

    TEST_F(StatesLibTestInterface, GetStateViewTest) {
        for (size_t index : {0, 1, -10, -20, 29})
            try {
                FiguresState figuresState = statesLib.getStateView(index);
                ASSERT_EQ(figuresState.polygon1, Polygon({Point(1, index + 1)}));
                ASSERT_EQ(figuresState.polygon2, Polygon());
                ASSERT_EQ(figuresState.intersection.polygon, Polygon());
                ASSERT_EQ(figuresState.intersection.state, States::IntersectionState::NoIntersection);
            }
         catch (const std::exception &e) {
             EXPECT_STREQ("Invalid index of state!", e.what());
         }

         // Standard Index = -1
        FiguresState figuresState = statesLib.getStateView();

        ASSERT_EQ(figuresState.polygon1, Polygon({Point(1, 30)}));
        ASSERT_EQ(figuresState.polygon2, Polygon());
        ASSERT_EQ(figuresState.intersection.polygon, Polygon());
        ASSERT_EQ(figuresState.intersection.state, States::IntersectionState::NoIntersection);
    }

    TEST_F(StatesLibTestInterface, PopStateTest) {
        size_t size = statesLib.getSize();
        for (int i = 1; i <= 30; ++i) {
            statesLib.popState();
            ASSERT_EQ(statesLib.getSize(), size-i);
        }

        EXPECT_THROW({
         try {
             statesLib.popState();
         }
         catch (const std::exception &e) {
             EXPECT_STREQ("Library is empty! Nothing to pop.", e.what());
             throw;
         }
        }, std::underflow_error);
    }

    TEST_F(StatesLibTestInterface, GetStateViewAndRefEmptyTest) {
        EXPECT_THROW({
         try {
             FiguresState figuresState = statesLib.getStateView();
         }
         catch (const std::exception &e) {
             EXPECT_STREQ("Library is empty! Nothing to get.", e.what());
             throw;
         }}, std::underflow_error);

        EXPECT_THROW({
         try {
             FiguresState figuresState = statesLib.getStateRef();
         }
         catch (const std::exception &e) {
             EXPECT_STREQ("Library is empty! Nothing to get.", e.what());
             throw;
         }}, std::underflow_error);
    }

    TEST_F(StatesLibTestInterface, UpdateStateEmptyTest) {
        EXPECT_THROW({
         try {
             statesLib.updateStateWith(Polygon(), States::FigureName::Polygon1);
         }
         catch (const std::exception &e) {
             EXPECT_STREQ("Library is empty! Nothing to update.", e.what());
             throw;
         }}, std::underflow_error);
    }
}