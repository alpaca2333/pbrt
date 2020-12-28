#include <iostream>

#include "core/math/matrix.h"
#include "core/math/transform.h"

#include "spdlog/spdlog.h"

using namespace std;
using namespace Transform;
using namespace spdlog;

using Vec4f = Vector<4, float>;

int main() {
  Vector3f v1{1, 2, 3};
  spdlog::set_level(spdlog::level::trace);
  debug("{}", Translatef(1, 2, 3).Append(Translatef(1, 2, 3).Inverse())(v1).ToString());
  info("hahahahaha fucking started");
  return 0;
}
