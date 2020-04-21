#include <iostream>

#include "core/math/vec3.h"

using namespace std;

int main() {
  Vec3f v1{1, 2, 3};
  cout << v1.Length() << endl;
  return 0;
}
