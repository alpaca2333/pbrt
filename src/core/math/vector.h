/*
 * @brief   Fundamental math definitions.
 * @author  qwertysun
 * @date    2020/04/19
 */

#pragma once

#include <cmath>
#include <iostream>
#include <cstdlib>


#define VERY_SMALL_FLAOT 0.00000001

/**
 * Common 3-d vector definition
 */
class Vector3
{
public:
  Vector3() = default;
  Vector3(double a, double b, double c);
  inline double& operator[](int i) { return e[i]; }
  inline double operator[](int i) const { return e[i]; }
  inline Vector3& operator=(const Vector3& vec);
  inline Vector3 operator-() const;
  friend inline Vector3 operator+(const Vector3& vec1, const Vector3& vec2);
  friend inline Vector3 operator-(const Vector3& vec1, const Vector3& vec2);
  inline Vector3 operator*(double k) const;
  // This 'x' operator simply times each field of the 2 vectors.
  // Use 'Dot' or 'Cross' method for the read vector timing operations.
  inline Vector3 operator*(const Vector3& vec);
  inline Vector3 operator/(double k) const;
  inline Vector3 operator/(const Vector3& vec);
  inline Vector3& operator+=(const Vector3& vec);
  inline Vector3& operator-=(const Vector3& vec);
  inline Vector3& operator*=(double k);
  inline Vector3& operator/=(double k);
  inline double Dot(const Vector3 &vec) const;
  inline Vector3 Cross(const Vector3 &vec) const;
  inline Vector3 UnitVector() const;
  inline double Length() const;
  inline bool operator!=(const Vector3& v);
  inline bool Parallel(const Vector3 &v) const;
  friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
protected:
  double e[3];
};

Vector3 vsqrt(const Vector3& v);

using Point3 = Vector3;

//=========================== inline function definitions ==============================

inline double Dot(const Vector3 &vec1, const Vector3 &vec2)
{
  return vec1.Dot(vec2);
}

inline Vector3 Cross(const Vector3 &vec1, const Vector3 &vec2)
{
  return vec1.Cross(vec2);
}

inline Vector3 Vector3::operator-() const
{
  return {-e[0], -e[1], -e[2]};
}

inline Vector3 operator+(const Vector3& vec1, const Vector3& vec2)
{
  return {vec1.e[0] + vec2.e[0], vec1.e[1] + vec2.e[1], vec1.e[2] + vec2.e[2]};
}

inline Vector3 operator-(const Vector3& vec1, const Vector3& vec2)
{
  return {vec1.e[0] - vec2.e[0], vec1.e[1] - vec2.e[1], vec1.e[2] - vec2.e[2]};
}

inline Vector3 Vector3::operator*(double k) const
{
  return {e[0] * k, e[1] * k, e[2] * k};
}

inline Vector3 Vector3::operator/(double k) const
{
  return {e[0] / k, e[1] / k, e[2] / k};
}

inline Vector3 &Vector3::operator=(const Vector3 &vec)
{
  e[0] = vec.e[0];
  e[1] = vec.e[1];
  e[2] = vec.e[2];
  return *this;
}

inline double Vector3::Dot(const Vector3 &vec) const
{
  return e[0] * vec.e[0] + e[1] * vec.e[1] + e[2] * vec.e[2];
}

inline Vector3 Vector3::Cross(const Vector3 &vec) const
{
  return {
      e[1] * vec.e[2] - e[2] * vec.e[1],
      e[2] * vec.e[0] - e[0] * vec.e[2],
      e[0] * vec.e[1] - e[1] * vec.e[0]
  };
}

inline double Vector3::Length() const
{
  return std::sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
}

inline Vector3 Vector3::UnitVector() const
{
  return (*this) / Length();
}

inline Vector3 &Vector3::operator+=(const Vector3 &vec)
{
  e[0] += vec.e[0];
  e[1] += vec.e[1];
  e[2] += vec.e[2];
  return *this;
}

inline Vector3 &Vector3::operator-=(const Vector3 &vec)
{
  e[0] -= vec.e[0];
  e[1] -= vec.e[1];
  e[2] -= vec.e[2];
  return *this;
}

inline Vector3 &Vector3::operator*=(double k)
{
  e[0] *= k;
  e[1] *= k;
  e[2] *= k;
  return *this;
}

inline Vector3 &Vector3::operator/=(double k)
{
  e[0] /= k;
  e[1] /= k;
  e[2] /= k;
  return *this;
}

Vector3 Vector3::operator*(const Vector3 &vec)
{
  return {e[0] * vec.e[0], e[1] * vec.e[1], e[2] * vec.e[2]};
}

Vector3 Vector3::operator/(const Vector3 &vec)
{
  return {e[0] / vec.e[0], e[1] / vec.e[1], e[2] / vec.e[2]};
}

inline bool Vector3::operator!=(const Vector3 &v)
{
  return e[0] == v.e[0] && e[0] == v.e[1] && e[2] == v.e[2];
}

inline bool Vector3::Parallel(const Vector3 &v) const
{
  double delta = std::abs(v.UnitVector().Dot(UnitVector()) - 1);
  return delta < VERY_SMALL_FLAOT;
}

inline Vector3 operator*(double k, const Vector3& vec)
{
  return vec * k;
}

inline Vector3 Reflect(const Vector3& income, const Vector3& n)
{
  Vector3 n2 = income.Dot(n) < 0 ? -n : n;
  return income - 2 * income.Dot(n2) * n2;
}

Vector3 Refract(const Vector3 &income, const Vector3 &n, double r);