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
        result.minX = (float) *std::min_element(arrayX.begin(), arrayX.end());
        float max_x = (float) *std::max_element(arrayX.begin(), arrayX.end());
        result.minY = (float) *std::min_element(arrayY.begin(), arrayY.end());
        float max_y = (float) *std::max_element(arrayY.begin(), arrayY.end());

        result.scaleX = (float) squareSideSize / (max_x - result.minX);
        result.scaleY = (float) squareSideSize / (max_y - result.minY);

        result.deltaX = (float) (squareSideSize - (max_x - result.minX) * result.scaleX) / 2;
        result.deltaY = (float) (squareSideSize - (max_y - result.minY) * result.scaleY) / 2;

        return result;
    }

    Geometry::Polygon scaleAndTranslate(const Geometry::Polygon &polygon, const scalingParameters& parameters) {
        Geometry::Polygon newPolygon = polygon;
        for (Geometry::Point &point: newPolygon.getPointsRef()) {
            point.setX((point.getX() - parameters.minX) * parameters.scaleX + parameters.deltaX);
            point.setY((point.getY() - parameters.minY) * parameters.scaleY + parameters.deltaY);
        }
        return newPolygon;
    }

    Geometry::Point scaleAndTranslatePoint(const Geometry::Point &point, const scalingParameters& parameters) {
        Geometry::Point newPoint = point;
        newPoint.setX((point.getX() - parameters.minX) * parameters.scaleX + parameters.deltaX);
        newPoint.setY((point.getY() - parameters.minY) * parameters.scaleY + parameters.deltaY);
        return newPoint;
    }

    void setDuplicatesFromIntersectionSameLetter(const Geometry::Polygon &polygon1,
                                                 const Geometry::Polygon &polygon2,
                                                       Geometry::Polygon &intersectionPolygon)
    {
        std::vector<Geometry::Point> polygonPoints1 = polygon1.getPointsCopy();
        std::vector<Geometry::Point> polygonPoints2 = polygon2.getPointsCopy();
        std::vector<Geometry::Point> &intersectionPointsVector = intersectionPolygon.getPointsRef();

        std::vector<Geometry::Point> allPoints;
        allPoints.insert(allPoints.end(), polygonPoints1.begin(), polygonPoints1.end());
        allPoints.insert(allPoints.end(), polygonPoints2.begin(), polygonPoints2.end());

        for (Geometry::Point &intersectionPoint: intersectionPointsVector)
            for (const Geometry::Point &comparisonPoint: allPoints)
                if (std::abs(intersectionPoint.getX() - comparisonPoint.getX()) +
                    std::abs(intersectionPoint.getY() - comparisonPoint.getY())
                    < std::numeric_limits<coord_t>::epsilon())
                {
                    intersectionPoint.setLabel(comparisonPoint.getLabel());
                    break;
                }
    }

    size_t *checkAvailableLabels(Geometry::Polygon &polygon) {
        size_t *labelChoices = new size_t[polygon.size() + 1];

        for (size_t i = 0; i < polygon.size() + 1; i++)
            labelChoices[i] = i + 1;

        for (size_t i = 0; i < polygon.size(); i++) {
            if (!polygon[i].getLabel().empty()) {
                std::string label = polygon[i].getLabel();
                label.erase(label.begin());
                size_t labelNumber = stoi(label);
                if (labelNumber < polygon.size() + 1)
                    labelChoices[labelNumber - 1] = -1; // -1 stands for taken label number
            }
        }
        return labelChoices;
    }

    void setActualLabels(Geometry::Polygon &polygon, char polygonLetter) {
        if (polygon.size() == 0)
            return;

        if (polygonLetter == 0)
            polygonLetter = polygon.getPointsRef().front().getLabel()[0];

        size_t *labelChoices = checkAvailableLabels(polygon);        
        // labeling with regard to possible missing numbers in point labels
        for (size_t i = 0; i < polygon.size(); i++) {
            if (polygon[i].getLabel().empty())
                for (size_t j = 0; j < polygon.size() + 1; j++) {
                    if (labelChoices[j] != -1){
                        polygon[i].setLabel(std::string(1, polygonLetter) + std::to_string(labelChoices[j]));
                        labelChoices[j] = -1;
                        break;
                    }            
            }
        }
    }

    void setActualPointsLabels(Geometry::Polygon &polygon1,
                               Geometry::Polygon &polygon2,
                               Geometry::Intersection &intersection)
    {
        setActualLabels(polygon1);
        setActualLabels(polygon2);
        setDuplicatesFromIntersectionSameLetter(polygon1, polygon2, intersection.polygon);
        setActualLabels(intersection.polygon, 'C');
    }
}