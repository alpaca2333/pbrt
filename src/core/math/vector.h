/**
 * @author qwertsun
 * @date   2020/04/21
 */

#pragma once

#include <cmath>
#include <type_traits>
#include <vector>
#include <array>
#include <initializer_list>
#include <cassert>

#define VERY_SMALL_FLAOT 0.00000001

// D for dimensions, T for data type.
template <typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
class _VectorTrait { };

template <int D, typename T>
class Vector;

// We use Point/Normal as an alias for Vector, for sake of convenient conversions
// between them.
using Normal3f = Vector<3, float>;
using Vector3f = Vector<3, float>;
using Point3f = Vector<3, float>;
using Normal2f = Vector<2, float>;
using Vector2f = Vector<2, float>;
using Point2f = Vector<2, float>;


template <int D, typename T>
class Vector : _VectorTrait<T>
{
public:
  Vector();
  Vector(std::initializer_list<T> args);
  Vector(const std::array<T, D>& arr) : e(arr) { }

  T& operator[](int i) { return e[i]; }
  T operator[](int i) const { return e[i]; }

  // +-*/ operations between vectors and constants.

  // This '*' operator simply times each field of the 2 vectors.
  // Use 'Dot' or 'Cross' method for the real vector timing operations.
  Vector<D, T> operator*(const Vector<D, T>& vec);
  Vector<D, T> operator/(T k) const;
  Vector<D, T> operator/(const Vector<D, T>& vec);
  Vector<D, T>& operator+=(const Vector<D, T>& vec);
  Vector<D, T>& operator-=(const Vector<D, T>& vec);
  Vector<D, T>& operator*=(T k);
  Vector<D, T>& operator/=(T k);
  Vector<D, T>& operator=(const Vector<D, T>& vec);
  Vector<D, T> operator-() const;
  Vector<D, T> operator*(T k) const;

  // Dot product of this and vec.
  T Dot(const Vector<D, T> &vec) const;

  // Cross product of this and vec.
  // Currently only enabled for 3D vectors.
  template <int U = D, typename DTrait = typename std::enable_if<U == 3>::type>
  Vector<D, T> Cross(const Vector<D, T> &vec) const;

  // Normalized vector of itself
  Vector<D, T> N() const;

  [[nodiscard]] double Length() const;

  // Equalization between vectors.
  bool operator!=(const Vector<D, T>& v) const;
  bool operator==(const Vector<D, T>& v) const;
  bool Parallel(const Vector<D, T> &v) const;

  // Size of the data block.
  constexpr size_t DataSize() { return e.size() * sizeof(T); }
  T *Data() const { return e; }
protected:
  std::array<T, D> e;
};


// ======================= implementations =========================
template <int D, typename T>
Vector<D, T>::Vector(std::initializer_list<T> args)
{
  auto iter = e.begin();
  for (auto arg: args)
  {
    *iter = arg;
    if (++iter == e.end())
    {
      break;
    }
  }
}

template <int D, typename T>
Vector<D, T> &Vector<D, T>::operator=(const Vector<D, T> &vec) {
  if (&vec == this) return *this;
  memcpy(e.data(), vec.e.data(), this->DataSize());
  return *this;
}

template <int D, typename T>
Vector<D, T> Vector<D, T>::operator-() const
{
  std::array<T, D> res;
  for (int i = 0; i < D; ++i)
  {
    res[i] = -e[i];
  }
  return res;
}

template <int D, typename T>
Vector<D, T> operator+(const Vector<D, T> &vec1, const Vector<D, T> &vec2) {
  std::array<T, D> res;
  for (int i = 0; i < D; ++i)
  {
    res[i] = vec1[i] + vec2[i];
  }
  return res;
}

template <int D, typename T>
Vector<D, T> operator-(const Vector<D, T> &vec1, const Vector<D, T> &vec2) {
  std::array<T, D> res;
  for (int i = 0; i < D; ++i)
  {
    res[i] = vec1[i] - vec2[i];
  }
  return res;
}

template <int D, typename T>
Vector<D, T> Vector<D, T>::operator*(T k) const {
  std::array<T, D> res;
  for (int i = 0; i < D; ++i)
  {
    res[i] = e[i] * k;
  }
  return res;
}


template <int D, typename T>
Vector<D, T> Vector<D, T>::operator*(const Vector<D, T> &vec) {
  std::array<T, D> res;
  for (int i = 0; i < D; ++i)
  {
    res[i] = e[i] * vec[i];
  }
  return res;
}


template <int D, typename T>
Vector<D, T> Vector<D, T>::operator/(T k) const {
  std::array<T, D> res;
  for (int i = 0; i < D; ++i)
  {
    res[i] = e[i] / k;
  }
  return res;
}


template <int D, typename T>
Vector<D, T> Vector<D, T>::operator/(const Vector<D, T> &vec) {
  std::array<T, D> res;
  for (int i = 0; i < D; ++i)
  {
    res[i] = e[i] / vec[i];
  }
  return res;
}


template <int D, typename T>
Vector<D, T> &Vector<D, T>::operator+=(const Vector<D, T> &vec) {
  for (int i = 0; i < D; ++i)
  {
    e[i] = e[i] + vec[i];
  }
  return *this;
}

template <int D, typename T>
Vector<D, T> &Vector<D, T>::operator-=(const Vector<D, T> &vec) {
  for (int i = 0; i < D; ++i)
  {
    e[i] = e[i] - vec[i];
  }
  return *this;
}

template <int D, typename T>
Vector<D, T> &Vector<D, T>::operator*=(T k) {
  for (int i = 0; i < D; ++i)
  {
    e[i] = e[i] * k;
  }
  return *this;
}

template <int D, typename T>
Vector<D, T> &Vector<D, T>::operator/=(T k) {
  for (int i = 0; i < D; ++i)
  {
    e[i] = e[i] / k;
  }
  return *this;
}

template <int D, typename T>
T Vector<D, T>::Dot(const Vector<D, T> &vec) const {
  T res = 0;
  for (int i = 0; i < D; ++i)
  {
    res += e[i] * vec[i];
  }
  return res;
}

template <int D, typename T>
template <int U, typename DTrait>
Vector<D, T> Vector<D, T>::Cross(const Vector<D, T> &vec) const {
  T ele[3] = {static_cast<T>(e[1]*vec[2] - vec[1]*e[2]), static_cast<T>(e[2]*vec[0] - vec[2]*e[0]), static_cast<T>(e[0]*vec[1] - vec[0]*e[1])};
  return {ele};
}

template <int D, typename T>
Vector<D, T> Vector<D, T>::N() const {
  double len = Length();
  std::array<T, D> res;
  for (int i = 0; i < D; ++i)
  {
    res[i] = e[i] / len;
  }
  return res;
}

template <int D, typename T>
double Vector<D, T>::Length() const {
  double sum = 0;
  for (int i = 0; i < D; ++i)
  {
    sum += e[i] * e[i];
  }
  return std::sqrt(sum);
}

template <int D, typename T>
bool Vector<D, T>::operator==(const Vector<D, T> &vec) const {
  for (int i = 0; i < D; ++i)
  {
    if (e[i] != vec[i])
    {
      return false;
    }
  }
  return true;
}

template <int D, typename T>
bool Vector<D, T>::operator!=(const Vector<D, T> &vec) const {
  return !this->operator==(vec);
}

template <int D, typename T>
bool Vector<D, T>::Parallel(const Vector<D, T> &vec) const {
  double vec_len = vec.Length();
  if (vec_len == 0)
  {
    return true;
  }
  double scale = Length() / vec_len;
  for (int i = 0; i < D; ++i)
  {
    if (e[i] == 0 && vec[i] == 0)
    {
      continue;
    }
    if (std::abs(static_cast<double>(e[i] / vec[i] - scale)) > VERY_SMALL_FLAOT)
    {
      return false;
    }
  }
  return true;
}

template <int D, typename T>
Vector<D, T>::Vector()
{
  memset(e.data(), 0, DataSize());
}

template <int D, typename T>
std::ostream &operator<<(std::ostream &os, const Vector<D, T> &v) {
  os << "[ ";
  for (int i = 0; i < D; ++i)
  {
    os << v[i] << " ";
  }
  os << "]";
  return os;
}

template <int Df, typename Tf>
Vector<Df, Tf> operator*(Tf t, const Vector <Df, Tf> &vec2) {
  std::array<Tf, Df> res;
  for (int i = 0; i < Df; ++i)
  {
    res[i] = static_cast<Tf>(vec2[i] * t);
  }
  return res;
}
