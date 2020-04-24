/*
 * @brief   Fundamental math definitions.
 * @author  qwertysun
 * @date    2020/04/19
 */

#pragma once

#include <cmath>
#include <iostream>
#include <cstdlib>

#include "vector.h"


Vector3f Vsqrt(const Vector3f & v);
Vector3f Refract(const Vector3f &income, const Vector3f &n, double r);
Vector3f Reflect(const Vector3f &income, const Vector3f &n);

// ======================= implementations =========================
inline Vector3f Reflect(const Vector3f &income, const Vector3f &n)
{
  Vector3f n2 = income.Dot(n) < 0 ? -n : n;
  return income - 2 * income.Dot(n2) * n2;
}
