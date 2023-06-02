#include "StatesLibrary.h"

namespace Manipulator {
    const FiguresState &
    StatesLibrary::getState(size_t stateIndex) const {
        if (isEmpty())
            throw std::range_error("Library is empty!");

        if (stateIndex == -1)
            return m_states.back();

        try {
            return m_states[stateIndex];
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

        try {
            return m_states[stateIndex];
        } catch (const std::range_error &err) {
            throw std::range_error("Invalid index of state!");
        }
    }

    void
    StatesLibrary::addState(const FiguresState &state) {
        m_states.push_back(state);
    }

    void
    StatesLibrary::emplaceState(FiguresState &&state) {
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
}