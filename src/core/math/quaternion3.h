//
// Created by black on 2020/8/30.
//

#pragma once

#include "vector.h"

/*
 * 3-D quaternion.
 */
class Quaternion3
{
public:
  Quaternion3() : v{0, 0, 0}, w(0) { }
  Quaternion3& operator+=(const Quaternion3& q);
  Quaternion3 operator+(const Quaternion3& q);
protected:
  Vector3f v;
  float w;
};
