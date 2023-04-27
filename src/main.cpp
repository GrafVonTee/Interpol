#include <tuple>
#include "GeometryUtils.h"
#include "ConsoleInteraction.h"

int main() {
    using namespace Interaction;
    greeting(getUserName());
    auto [tr1, tr2] = getBothTriangles();
    printTriangle(tr1, 1);
    printTriangle(tr2, 2);
    return 0;
}