#include "FiguresStateLibrary.h"

namespace Manipulator {

    const FiguresState&
    FiguresStateLibrary::getState(size_t stateIndex) const {
        if (isEmpty())
            throw std::range_error("Library is empty!");

        if (stateIndex == -1)
            return m_states.back();

        try {
            return m_states[stateIndex];
        } catch (const std::range_error& err) {
            throw std::range_error("Invalid index of state!");
        }
    }

    FiguresState&
    FiguresStateLibrary::getStateRef(size_t stateIndex) {
        if (isEmpty())
            throw std::range_error("Library is empty!");

        if (stateIndex == -1)
            return m_states.back();

        try {
            return m_states[stateIndex];
        } catch (const std::range_error& err) {
            throw std::range_error("Invalid index of state!");
        }
    }

    void
    FiguresStateLibrary::addState(const FiguresState& state) {
        m_states.push_back(state);
    }

    void
    FiguresStateLibrary::emplaceState(FiguresState&& state) {
        m_states.emplace_back(state);
    }

    void
    FiguresStateLibrary::popState() {
        if (isEmpty())
            throw std::underflow_error("Library is empty!");

        m_states.pop_back();
    }
}