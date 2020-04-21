/*
 * @brief
 * @author  qwertysun
 * @date    2020/04/19
 */
#include "vec3.h"
#include "vector.h"

using namespace std;

Vec3f vsqrt(const Vec3f & v)
{
  return {
    static_cast<float>(sqrt(v[0])),
    static_cast<float>(sqrt(v[1])),
    static_cast<float>(sqrt(v[2]))
  };
}

Vec3f Refract(const Vec3f &income, const Vec3f &n, double r)
{
  if (income.Parallel(n)) return income;
  double indot = income.Dot(n);
  double cos1 = indot / income.Length() / n.Length();
  Vec3f result;
  if (indot < 0)
  {
    double sin1 = sqrt(1 - cos1 * cos1);
    cos1 = -cos1;
    double sin2 = sin1 / r;
    double tan1 = abs(sin1 / cos1);
    double tan2 = abs(sin2 / std::sqrt(1 - sin2 * sin2));
    // 全反射
    if (abs(sin2) >= 1)
    {
      return Reflect(income, n);
    }
    Vec3f n2 = n / n.Length() * income.Length() * cos1;
    Vec3f delta = income + n2;
    delta = delta / tan1 * tan2;
    result = delta - n2;
  }
  else
  {
    double sin1 = sqrt(1 - cos1 * cos1);
    double sin2 = sin1 * r;
    double tan1 = abs(sin1 / cos1);
    double tan2 = abs(sin2 / std::sqrt(1 - sin2 * sin2));
    if (abs(sin2) >= 1)
    {
      return Reflect(income, n);
    }
    double cos1 = sqrt(1 - sin1 * sin1);
    Vec3f n2 = -n / n.Length() * income.Length() * cos1;
    Vec3f delta = income + n2;
    delta = delta / tan1 * tan2;
    result = delta - n2;
  }
  return result;
}