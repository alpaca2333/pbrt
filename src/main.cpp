#include <iostream>

#include "core/math/matrix.h"
#include "core/math/transform.h"

using namespace std;
using namespace Transform;

using Vec4f = Vector<4, float>;

int main() {
  Vector3f v1{1, 2, 3};
  cout << Translatef(1, 2, 3).Append(Translatef(1, 2, 3).Inverse())(v1) << endl;
  return 0;
}
