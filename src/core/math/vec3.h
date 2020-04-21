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

#define VERY_SMALL_FLAOT 0.00000001

using Vec3f = Vector<3, float>;

Vec3f vsqrt(const Vec3f & v);

inline Vec3f Reflect(const Vec3f &income, const Vec3f &n)
{
  Vec3f n2 = income.Dot(n) < 0 ? -n : n;
  return income - 2 * income.Dot(n2) * n2;
}

Vec3f Refract(const Vec3f &income, const Vec3f &n, double r);