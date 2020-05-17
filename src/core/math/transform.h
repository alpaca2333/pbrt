//
// Created by 孙浩 on 2020/4/24.
//

#pragma once

#include "vector.h"
#include "matrix.h"


// This multiplication operation between a matrix and a vector will
// be used for transformations. So the vector is always on the right
// side of "x" and is transposed. The matrix is D x D and the vector
// is 1 x D (but transposed). Normally, the form of the equation is:
//
//   | a b c |   | x |   | u |
//   | d e f | x | y | = | v |
//   | g h i |   | z |   | w |
//
namespace Transform
{

// All transformations should have a inverse transformation.
template <typename T>
class _transform
{
public:
  _transform() = default;
  _transform(const Matrix<4, 4, T> &t) : t_(t) { }
  Vector<3, T> operator()(const Vector<3, T> &m);
  virtual _transform Inverse() { return *this; };
  _transform<T> Append(const _transform<T>& t) { return t_ * t.t_; }
protected:
  Matrix<4, 4, T> t_;
};


// Translation.
template <typename T>
class Translate : public _transform<T>
{
public:
  Translate(T dx, T dy, T dz);
  virtual _transform<T> Inverse() { return Translate(-dx, -dy, -dz); }

protected:
  T dx, dy, dz;
};

// Scaling
template <typename T>
class Scale : public _transform<T>
{
public:
  Scale(T sx, T sy, T sz);
  virtual _transform<T> Inverse() { return Scale(1 / sx, 1 / sy, 1 / sz); }
protected:
  T sx, sy, sz;
};

using Translatef = Translate<float>;
using Scalef = Scale<float>;

}


template <int D, typename T>
Vector<D, T> operator*(const Matrix<D, D, T> &m, const Vector<D, T> &vec);

// Here, we only define some transformations for points and vectors
// in 3d coordinates.


// ======================= implementations =========================
template <int D, typename T>
Vector<D, T> operator*(const Matrix<D, D, T> &m, const Vector<D, T> &vec)
{
  std::array<T, D> res;
  for (int i = 0; i < D; ++i)
  {
    res[i] = 0;
    for (int j = 0; j < D; ++j)
    {
      res[i] += m[i][j] * vec[j];
    }
  }
  return res;
}

namespace Transform
{
template <typename T>
Vector<3, T> _transform<T>::operator()(const Vector<3, T> & m)
{
  Matrix<4, 1, T> hv{{m[0]}, {m[1]}, {m[2]}, {1}};
  auto hres = t_ * hv;
  std::cout << t_ << std::endl;
  std::cout << hv << std::endl;
  std::cout << hres << std::endl;
  return {hres[0][0], hres[1][0], hres[2][0]};
}

template <typename T>
Translate<T>::Translate(T dx, T dy, T dz) : dx(dx), dy(dy), dz(dz)
{
  for (int i = 0; i < 4; ++i)
  {
    this->t_[i][i] = 1;
  }
  this->t_[0][3] = dx;
  this->t_[1][3] = dy;
  this->t_[2][3] = dz;
}

template <typename T>
Scale<T>::Scale(T sx, T sy, T sz) : sx(sx), sy(sy), sz(sz)
{
  this->t_[0][0] = sx;
  this->t_[1][3] = sy;
  this->t_[2][3] = sz;
  this->t_[3][3] = 1;
}

}