#pragma once

#include <vector>
#include "GeometryUtils.h"

namespace Manipulator {
    struct FiguresState {
        Geometry::Polygon polygon1;
        Geometry::Polygon polygon2;
        Geometry::Intersection intersection;
    };

    class FiguresStateLibrary {
    private:
        std::vector<FiguresState> m_states;

        FigureLibrary() {}
        FigureLibrary(const FigureLibrary&) = delete;
        FigureLibrary& operator=(FigureLibrary&) = delete;

    public:
        static FigureLibrary& getInstance() {
            static FigureLibrary instance;
            return instance;
        }

        bool isEmpty() const { return m_states.empty() }
        size_t getSize() const { return m_states.size() }

        const FiguresState& getState(size_t stateIndex = -1) const;
        FiguresState& getStateRef(size_t stateIndex = -1);

        void addState(const FiguresState& state);
        void emplaceState(FiguresState&& state);

        void popState();
        }
    };
}