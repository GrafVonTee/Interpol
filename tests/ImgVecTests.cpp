#include <gtest/gtest.h>
#include "imgui.h"
#include "GeometryUtils.h"
#include "GetImVecFromPolygon.h"
#include "CalculateIntersections.h"

namespace DrawUtils {
    void setDuplicatesFromIntersectionSameLetter(const Geometry::Polygon &polygon1,
                                                 const Geometry::Polygon &polygon2,
                                                       Geometry::Polygon &intersectionPolygon);
}


namespace GetImVecTests {
    using namespace Geometry;
    class GetImVecTestInterface : public testing::Test {
    public:
        static bool areVecImEqual(const std::vector<ImVec2>& vec1, const std::vector<ImVec2>& vec2) {
            if (vec1.size() != vec2.size())
                return false;
            for (size_t i = 0; i < vec1.size(); ++i)
                if (!(vec1[i].x == vec2[i].x && vec1[i].y == vec2[i].y))
                    return false;
            return true;
        }

        static bool areLabelsEqual(const size_t* label1, const size_t* label2, int size) {
            for (size_t i = 0; i < size; ++i)
                if (label1[i] != label2[i])
                    return false;
            return true;
        }

        static bool arePolygonsLabelsEqual(const Polygon& p1, const Polygon& p2) {
            if (p1.size() != p2.size())
                return false;

            for (size_t i = 0; i < p1.size(); ++i) {
                if (p1[i].getLabel() != p2[i].getLabel())
                    return false;
            }
            return true;
        }
    };

    TEST_F(GetImVecTestInterface, getVectorOfPointsFromPolygonTest) {
        Polygon polygon {{Point(), Point(1.32, 0.3131)}};
        std::vector<ImVec2> vecIm {ImVec2(0, 0), ImVec2(1.32, 0.3131)};
        EXPECT_TRUE(areVecImEqual(DrawUtils::getVectorOfPointsFromPolygon(polygon), vecIm));

        polygon = Polygon();
        vecIm = {};
        EXPECT_TRUE(areVecImEqual(DrawUtils::getVectorOfPointsFromPolygon(polygon), vecIm));
    }

    TEST_F(GetImVecTestInterface, checkAvailableLabelsTest) {
        Polygon polygon {{Point(1, 2, "A1"), Point(2, 40, "A2")}};

//        label[i] = i + 1 - значит (i+1)-й номер точки свободен
//        label[i] = -1 - значит (i+1)-й номер несвободен
//        label[i] = size+1 - заглушка, при которой всегда можно поместить точку в конец полигона

        size_t* labels = DrawUtils::checkAvailableLabels(polygon);
        size_t* expectedLabels = new size_t[3];
        expectedLabels[0] = -1;
        expectedLabels[1] = -1;
        expectedLabels[2] = 3;
        EXPECT_TRUE(areLabelsEqual(labels, expectedLabels, 3));
        delete[] expectedLabels;
        delete[] labels;

        polygon = Polygon({Point(1, 2, "A2"),
                                 Point(2, 40, "A3"),
                                 Point(-1, -1, "A5")});
        labels = DrawUtils::checkAvailableLabels(polygon);
        expectedLabels = new size_t[4];
        expectedLabels[0] = 1;
        expectedLabels[1] = -1;
        expectedLabels[2] = -1;
        expectedLabels[3] = 4;

        EXPECT_TRUE(areLabelsEqual(labels, expectedLabels, 4));

        delete[] labels;
        labels = nullptr;
        delete[] expectedLabels;
        expectedLabels = nullptr;
    }

    TEST_F(GetImVecTestInterface, setDuplicatesFromIntersectionSameLetterTest) {
        Polygon polygon1 {{Point(1, 2, "A1"),
                                  Point(3, 0, "A2"),
                                  Point(0, 0, "A3")}};

        Polygon polygon2 {{Point(1.0000000000000000000000000000001, 2.00000000000000000000000001, "B1"),
                           Point(3, 0, "B2"),
                           Point(0, 0, "B3")}};

        Intersection inter = Math::findPolygonsInter(polygon1, polygon2);
        DrawUtils::setDuplicatesFromIntersectionSameLetter(polygon1, polygon2, inter.polygon);

        Polygon expectedPolygon {{Point(0, 0, "A3"),
                                  Point(1, 2, "A1"),
                                  Point(3, 0, "A2")}};

        EXPECT_TRUE(arePolygonsLabelsEqual(inter.polygon, expectedPolygon));
    }
}