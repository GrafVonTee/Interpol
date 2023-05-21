#include <cmath>
#include "GetImVecFromPolygon.h"
#include "ConstantsForDrawing.h"

namespace DrawUtils {
    ImVec2 getImVec2(const Geometry::Point &p) {
        return ImVec2{(float)p.getX(), (float)p.getY()};
    }

    ImVec2 getOffsetImVec2(const Geometry::Point &p, ImVec2 offset) {
        return ImVec2{(float)p.getX() + offset.x, (float)p.getY() + offset.y};
    }

    im_vec_triangle_t getOffsetTupleOfPointsFromPolygon(const Geometry::Polygon &triangle) {
        if (triangle.size() != 3)
            throw std::logic_error("Functions \'getTupleFromPolygon\' got not a triangle argument!");

        return std::make_tuple(
                getImVec2(triangle[0]),
                getImVec2(triangle[1]),
                getImVec2(triangle[2])
        );
    }

    im_vec_triangle_t getOffsetTupleOfPointsFromPolygon(const Geometry::Polygon &triangle, ImVec2 offset) {
        if (triangle.size() != 3)
            throw std::logic_error("Functions \'getTupleFromPolygon\' got not a triangle argument!");

        return std::make_tuple(
                getOffsetImVec2(triangle[0], offset),
                getOffsetImVec2(triangle[1], offset),
                getOffsetImVec2(triangle[2], offset)
        );
    }

    std::vector<ImVec2> getVectorOfPointsFromPolygon(const Geometry::Polygon& polygon) {
        std::vector<ImVec2> pointsVector;
        pointsVector.reserve(polygon.size());
        for (auto &point : polygon.getPointsCopy())
            pointsVector.emplace_back(getImVec2(point));
        return pointsVector;
    }

    std::vector<ImVec2> getOffsetVectorOfPointsFromPolygon(const Geometry::Polygon& polygon, ImVec2 offset) {
        std::vector<ImVec2> pointsVector;
        pointsVector.reserve(polygon.size());
        for (auto &point : polygon.getPointsCopy())
            pointsVector.emplace_back(getOffsetImVec2(point, offset));
        return pointsVector;
    }

    void findParameters(const Geometry::Polygon &tr1, const Geometry::Polygon &tr2,
                        const coord_t squareSideSize,
                        double& scale_x, double& scale_y, double& delta_x, double& delta_y,
                        double& min_x, double& min_y) {

        std::vector<coord_t> arrayX, arrayY;
        for (auto &triangle: {tr1, tr2}) {
            for (size_t i = 0; i < triangle.size(); ++i) {
                arrayX.push_back(triangle[i].getX());
                arrayY.push_back(triangle[i].getY());
            }
        }

        min_x = *std::min_element(arrayX.begin(), arrayX.end());
        double max_x = *std::max_element(arrayX.begin(), arrayX.end());
        min_y = *std::min_element(arrayY.begin(), arrayY.end());
        double max_y = *std::max_element(arrayY.begin(), arrayY.end());

        scale_x = squareSideSize / (max_x - min_x);
        scale_y = squareSideSize / (max_y - min_y);

        delta_x = (squareSideSize - (max_x - min_x) * scale_x) / 2;
        delta_y = (squareSideSize - (max_y - min_y) * scale_y) / 2;
    }

    Geometry::Polygon scaleAndTranslate(Geometry::Polygon &polygon,
                           double& scale_x, double& scale_y, double& delta_x, double& delta_y,
                           double& min_x, double& min_y)
   {       
        Geometry::Polygon newPolygon = polygon;
        for (Geometry::Point &point: newPolygon.getPointsRef()) {
            point.setX((point.getX() - min_x) * scale_x + delta_x);
            point.setY((point.getY() - min_y) * scale_y + delta_y);
        }
        return newPolygon;
    }

    Geometry::Polygon addIndents(Geometry::Polygon &polygon, Geometry::Polygon &tr2,
                    Geometry::Intersection& intersection,
                    const coord_t indentSize)
    {
        Geometry::Polygon newPolygon = polygon;
        Geometry::Point indentation{indentSize, indentSize};
        for (Geometry::Point &point: newPolygon.getPointsRef()) {
            char pointLabel = point.getLabel();
            point += indentation;
            point.setLabel(pointLabel);
        }
        
    }

    void setActualPointsLabels(Geometry::Polygon &triangle1,
                               Geometry::Polygon &triangle2,
                               Geometry::Intersection &intersection)
    {
        std::vector<Geometry::Point*> allPoints;
        size_t letterIndex = 0;
        for (Geometry::Polygon* figurePtr: {&triangle1, &triangle2, &intersection.polygon}) {
            for (Geometry::Point &point: figurePtr->getPointsRef()) {
                if (point.getLabel() == 0) {
                    point.setLabel((char) ((size_t) 'A' + letterIndex));
                    letterIndex++;
                } else {
                    letterIndex = (letterIndex > (point.getLabel() - 'A' + 1))
                            ? letterIndex : (point.getLabel() - 'A' + 1);
                }
                allPoints.push_back(&point);
            }
        }

        for (size_t i = 0; i < allPoints.size(); ++i)
            for (size_t j = i + 1; j < allPoints.size(); ++j)
                if (std::pow(allPoints[i]->getX() - allPoints[j]->getX(), 2) +
                    std::pow(allPoints[i]->getY() - allPoints[j]->getY(), 2)
                    <= std::numeric_limits<coord_t>::epsilon())

                    allPoints[j]->setLabel(allPoints[i]->getLabel());
    }
}
