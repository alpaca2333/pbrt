/**
 * @author qwertsun
 * @date   2020/04/21
 */

#pragma once

#include <cmath>
#include <type_traits>
#include <vector>

template <int D, typename T>
class Vector
{
public:
  Vector() = default;
  Vector(T elements[D]);
  explicit Vector(std::vector<T> &&elements);
  template <typename DTrait = typename std::enable_if<D == 3>::type>
  Vector(T x, T y, T z) { e[0] = x; e[1] = y; e[2] = z; };

  double& operator[](int i) { return e[i]; }
  double operator[](int i) const { return e[i]; }
  Vector<D, T>& operator=(const Vector<D, T>& vec);
  Vector<D, T> operator-() const;
  Vector<D, T> operator*(T k) const;
  // This 'x' operator simply times each field of the 2 vectors.
  // Use 'Dot' or 'Cross' method for the read vector timing operations.
  Vector<D, T> operator*(const Vector<D, T>& vec);
  Vector<D, T> operator/(T k) const;
  Vector<D, T> operator/(const Vector<D, T>& vec);
  Vector<D, T>& operator+=(const Vector<D, T>& vec);
  Vector<D, T>& operator-=(const Vector<D, T>& vec);
  Vector<D, T>& operator*=(T k);
  Vector<D, T>& operator/=(T k);
  T Dot(const Vector<D, T> &vec) const;

  template <typename DTrait = typename std::enable_if<D == 3>::type>
  Vector<D, T> Cross(const Vector<D, T> &vec) const;

  Vector<D, T> N() const;
  [[nodiscard]] double Length() const;
  bool operator!=(const Vector<D, T>& v) const;
  bool operator==(const Vector<D, T>& v) const;
  bool Parallel(const Vector<D, T> &v) const;

  constexpr static size_t DataSize() { return sizeof(T) * D; }
  T *Data() const { return e; }
protected:
  T e[D];
};


// ======================= implementations =========================
template <int D, typename T>
Vector<D, T>::Vector(T elements[D])
{
  memcpy(e, elements, sizeof(T) * D);
}

template <int D, typename T>
Vector<D, T>::Vector(std::vector<T> &&vec)
{
  memcpy(e, vec.data(), sizeof(T) * D);
}

template <int D, typename T>
Vector<D, T> &Vector<D, T>::operator=(const Vector<D, T> &vec) {
  if (&vec == this) return *this;
  memcpy(e, vec.e, Vector::DataSize());
  return *this;
}

template <int D, typename T>
Vector<D, T> Vector<D, T>::operator-() const
{
  T res[D];
  for (int i = 0; i < D; ++i)
  {
    res[i] = -e[i];
  }
  return res;
}

template <int D, typename T>
Vector<D, T> operator+(const Vector<D, T> &vec1, const Vector<D, T> &vec2) {
  T res[D];
  for (int i = 0; i < D; ++i)
  {
    res[i] = vec1[i] + vec2[i];
  }
  return res;
}

template <int D, typename T>
Vector<D, T> operator-(const Vector<D, T> &vec1, const Vector<D, T> &vec2) {
  T res[D];
  for (int i = 0; i < D; ++i)
  {
    res[i] = vec1[i] - vec2[i];
  }
  return res;
}

template <int D, typename T>
Vector<D, T> Vector<D, T>::operator*(T k) const {
  T res[D];
  for (int i = 0; i < D; ++i)
  {
    res[i] = e[i] * k;
  }
  return res;
}


template <int D, typename T>
Vector<D, T> Vector<D, T>::operator*(const Vector<D, T> &vec) {
  T res[D];
  for (int i = 0; i < D; ++i)
  {
    res[i] = e[i] * vec[i];
  }
  return res;
}


template <int D, typename T>
Vector<D, T> Vector<D, T>::operator/(T k) const {
  T res[D];
  for (int i = 0; i < D; ++i)
  {
    res[i] = e[i] / k;
  }
  return res;
}


template <int D, typename T>
Vector<D, T> Vector<D, T>::operator/(const Vector<D, T> &vec) {
  T res[D];
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
template <typename DTrait>
Vector<D, T> Vector<D, T>::Cross(const Vector<D, T> &vec) const {
  T ele[3] = {static_cast<T>(e[1]*vec[2] - vec[1]*e[2]), static_cast<T>(e[2]*vec[0] - vec[2]*e[0]), static_cast<T>(e[0]*vec[1] - vec[0]*e[1])};
  return {ele};
}

template <int D, typename T>
Vector<D, T> Vector<D, T>::N() const {
  double len = Length();
  T res[D];
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
    if (std::abs(static_cast<double>(e[i] / vec[i] - scale)) > 0.0000001)
    {
      return false;
    }
  }
  return true;
}

template <int D, typename T>
std::ostream &operator<<(std::ostream &os, const Vector<D, T> &v) {
  os << "{ ";
  for (int i = 0; i < D; ++i)
  {
    os << v[i] << " ";
  }
  os << "}";
  return os;
}

template <int Df, typename Tf>
Vector<Df, Tf> operator*(Tf t, const Vector <Df, Tf> &vec2) {
  Tf res[Df];
  for (int i = 0; i < Df; ++i)
  {
    res[i] = static_cast<Tf>(vec2[i] * t);
  }
  return res;
}
