/*
 * @brief
 * @author  qwertysun
 * @date    2020/04/19
 */
#include "vector.h"

using namespace std;

Vector3::Vector3(double a, double b, double c)
{
  e[0] = a;
  e[1] = b;
  e[2] = c;
}

Vector3 vsqrt(const Vector3& v)
{
  return {sqrt(v[0]), sqrt(v[1]), sqrt(v[2])};
}


Vector3 Refract(const Vector3 &income, const Vector3 &n, double r)
{
  if (income.Parallel(n)) return income;
  double indot = income.Dot(n);
  double cos1 = indot / income.Length() / n.Length();
  Vector3 result;
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
    Vector3 n2 = n / n.Length() * income.Length() * cos1;
    Vector3 delta = income + n2;
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
    Vector3 n2 = -n / n.Length() * income.Length() * cos1;
    Vector3 delta = income + n2;
    delta = delta / tan1 * tan2;
    result = delta - n2;
  }
  return result;
}

std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
  os << "{" << v.e[0] << ", " << v.e[1] << ", " << v.e[2] << "}";
  return os;
}