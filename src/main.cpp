#include <iostream>

#include "math/matrix.h"
#include "math/transform.h"
#include "camera/ray.h"
#include "shape/bound.h"

#include "spdlog/spdlog.h"

using namespace std;
using namespace Transform;
using namespace spdlog;

using Vec4f = Vector<4, float>;

void test()
{
    unique_ptr<int> p1 = make_unique<int>(3);
    auto p2 = std::move(p1); // 合法
}

int main() {
    Vector3f v1{1, 2, 3};
    spdlog::set_level(spdlog::level::trace);
    debug("{}", Translatef(1, 2, 3).Append(Translatef(1, 2, 3).Inverse())(v1).ToString());
    info("hahahahaha fucking started");
    debug(1 > (-1.0) / 0);

    Bound b({-1, -1, -1}, {1, 1, 1});
    Ray r({0, 0, 0}, {1, 1, 1});
    debug(b.IsHit(r));
    return 0;
}
