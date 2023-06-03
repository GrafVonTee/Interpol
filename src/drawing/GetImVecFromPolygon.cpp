#include <cmath>
#include "GetImVecFromPolygon.h"

namespace DrawUtils {    

    ImVec2 getImVec2(const Geometry::Point &p, ImVec2 offset) {
        return ImVec2{(float)p.getX() + offset.x, (float)p.getY() + offset.y};
    }

    std::vector<ImVec2> getVectorOfPointsFromPolygon(const Geometry::Polygon& polygon, ImVec2 offset) {
        std::vector<ImVec2> pointsVector;
        pointsVector.reserve(polygon.size());
        for (auto &point : polygon.getPointsCopy())
            pointsVector.emplace_back(getImVec2(point, offset));
        return pointsVector;
    }

    scalingParameters findParameters(const Geometry::Polygon &tr1, 
                        const Geometry::Polygon &tr2,
                        const coord_t squareSideSize) {
        std::vector<coord_t> arrayX, arrayY;
        for (auto &triangle: {tr1, tr2}) {
            for (size_t i = 0; i < triangle.size(); ++i) {
                arrayX.push_back(triangle[i].getX());
                arrayY.push_back(triangle[i].getY());
            }
        }

        scalingParameters result;
        result.min_x = (float) *std::min_element(arrayX.begin(), arrayX.end());
        float max_x = (float) *std::max_element(arrayX.begin(), arrayX.end());
        result.min_y = (float) *std::min_element(arrayY.begin(), arrayY.end());
        float max_y = (float) *std::max_element(arrayY.begin(), arrayY.end());

        result.scale_x = (float) squareSideSize / (max_x - result.min_x);
        result.scale_y = (float) squareSideSize / (max_y - result.min_y);

        result.delta_x = (float) (squareSideSize - (max_x - result.min_x) * result.scale_x) / 2;
        result.delta_y = (float) (squareSideSize - (max_y - result.min_y) * result.scale_y) / 2;

        return result;
    }

    Geometry::Polygon scaleAndTranslate(const Geometry::Polygon &polygon, const scalingParameters& parameters) {
        Geometry::Polygon newPolygon = polygon;
        for (Geometry::Point &point: newPolygon.getPointsRef()) {
            point.setX((point.getX() - parameters.min_x) * parameters.scale_x + parameters.delta_x);
            point.setY((point.getY() - parameters.min_y) * parameters.scale_y + parameters.delta_y);
        }
        return newPolygon;
    }

    void setDuplicatesFromIntersectionSameLetter(const Geometry::Polygon &polygon1,
                                                 const Geometry::Polygon &polygon2,
                                                       Geometry::Polygon &intersectionPolygon)
    {
        std::vector<Geometry::Point> polygonPoints1 = polygon1.getPointsCopy();
        std::vector<Geometry::Point> polygonPoints2 = polygon2.getPointsCopy();
        std::vector<Geometry::Point> intersectionPointsVector = intersectionPolygon.getPointsRef();

        std::vector<Geometry::Point> allPoints;
        allPoints.insert(allPoints.end(), polygonPoints1.begin(), polygonPoints1.end());
        allPoints.insert(allPoints.end(), polygonPoints2.begin(), polygonPoints2.end());

        for (Geometry::Point &intersectionPoint: intersectionPointsVector)
            for (const Geometry::Point &comparisonPoint: allPoints)
                if (std::pow(intersectionPoint.getX() - comparisonPoint.getX(), 2) +
                    std::pow(intersectionPoint.getY() - comparisonPoint.getY(), 2)
                    <= std::numeric_limits<coord_t>::epsilon())
                {
                    intersectionPoint.setLabel(comparisonPoint.getLabel());
                    break;
                }
    }

    void setActualLabels(Geometry::Polygon &polygon, char polygonLetter = 0, bool isIntersection = false) {
        if (polygon.size() == 0)
            return;

        if (polygonLetter == 0)
            polygonLetter = polygon.getPointsRef().front().getLabel()[0];

        int currentLabelNumber = 1;
        for (size_t i = 0; i < polygon.size(); i++) {
            if (polygon[i].getLabel().empty())
                polygon[i].setLabel(std::string(1, polygonLetter) + std::to_string(currentLabelNumber++));
            if (isIntersection)
                currentLabelNumber--;
            currentLabelNumber++;
        }
    }

    void setActualPointsLabels(Geometry::Polygon &polygon1,
                               Geometry::Polygon &polygon2,
                               Geometry::Intersection &intersection)
    {
        setActualLabels(polygon1);
        setActualLabels(polygon2);
        setDuplicatesFromIntersectionSameLetter(polygon1, polygon2, intersection.polygon);
        setActualLabels(intersection.polygon, 'C', true);
    }
}