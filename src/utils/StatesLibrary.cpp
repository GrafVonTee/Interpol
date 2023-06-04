#include "StatesLibrary.h"
#include "CalculateIntersections.h"
#include "GetImVecFromPolygon.h"

namespace Manipulator {
    const FiguresState &
    StatesLibrary::getState(size_t stateIndex) const {
        if (isEmpty())
            throw std::range_error("Library is empty!");

        if (stateIndex == -1)
            return m_states.back();

        if (stateIndex == -2)
            return m_states.at(m_states.size() - 2);

        if (stateIndex == -3)
            return m_states.at(m_states.size() - 3);

        try {
            return m_states.at(stateIndex);
        } catch (const std::range_error &err) {
            throw std::range_error("Invalid index of state!");
        }
    }

    FiguresState
    StatesLibrary::getStateCopy(size_t stateIndex){
        if (isEmpty())
            throw std::range_error("Library is empty!");

        if (stateIndex == -1)
            return m_states.back();
        
        if (stateIndex == -2)
            return m_states.at(m_states.size() - 2);

        if (stateIndex == -3)
            return m_states.at(m_states.size() - 3);

        try {
            return m_states.at(stateIndex);
        } catch (const std::range_error &err) {
            throw std::range_error("Invalid index of state!");
        }
    }

    FiguresState &
    StatesLibrary::getStateRef(size_t stateIndex) {
        if (isEmpty())
            throw std::range_error("Library is empty!");

        if (stateIndex == -1)
            return m_states.back();

        if (stateIndex == -2)
            return m_states.at(m_states.size() - 2);

        if (stateIndex == -3)
            return m_states.at(m_states.size() - 3);
        try {
            return m_states.at(stateIndex);
        } catch (const std::range_error &err) {
            throw std::range_error("Invalid index of state!");
        }
    }

    void
    StatesLibrary::addState(const FiguresState &state) {
        m_states.push_back(state);
    }

    void
    StatesLibrary::emplaceState(FiguresState &state) {
        m_states.emplace_back(std::move(state));
    }

    void
    StatesLibrary::emplaceState(FiguresState&& state) {
        m_states.emplace_back(state);
    }

    void
    StatesLibrary::addState(const Geometry::Polygon &poly1,
                            const Geometry::Polygon &poly2,
                            const Geometry::Intersection &inter) {
        m_states.push_back(FiguresState{poly1, poly2, inter});
    }

    void
    StatesLibrary::emplaceState(Geometry::Polygon &poly1,
                                Geometry::Polygon &poly2,
                                Geometry::Intersection &inter) {
        m_states.emplace_back(FiguresState{
                std::move(poly1),
                std::move(poly2),
                std::move(inter),
        });
    }

    void
    StatesLibrary::popState() {
        if (isEmpty())
            throw std::underflow_error("Library is empty!");

        m_states.pop_back();
    }

    void
    StatesLibrary::addInputState(const Geometry::Polygon &polygon1, const Geometry::Polygon &polygon2) {
        auto poly1 = polygon1;
        auto poly2 = polygon2;
        auto intersection = Math::findPolygonsInter(poly1, poly2);
        DrawUtils::setActualPointsLabels(poly1,
                                         poly2,
                                         intersection);
        StatesLibrary::getInstance().addState(poly1, poly2, intersection);
    }

    void
    StatesLibrary::emplaceInputState(Geometry::Polygon &poly1, Geometry::Polygon &poly2) {
        auto intersection = Math::findPolygonsInter(poly1, poly2);
        DrawUtils::setActualPointsLabels(poly1,
                                         poly2,
                                         intersection);
        StatesLibrary::getInstance().emplaceState(poly1, poly2, intersection);
    }

    void
    StatesLibrary::updateState() {
        auto &manipulator = StatesLibrary::getInstance();
        if (manipulator.isEmpty())
            return;
        auto &state = manipulator.getStateRef();
        state.intersection = Math::findPolygonsInter(state.polygon1, state.polygon2);
        DrawUtils::setActualPointsLabels(state.polygon1,
                                         state.polygon2,
                                         state.intersection);
    }
}