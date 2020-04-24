#include <iostream>

#include "core/math/matrix.h"

using namespace std;

using Vec4f = Vector<4, float>;

int main() {
  Vector3f v1{1, 2, 3};
  Matrix<3, 3, float> d{{1, 2, 3},
                       {1, 2, 3},
                       {1, 2, 3}};

  cout << d * d << endl;
  return 0;
}
