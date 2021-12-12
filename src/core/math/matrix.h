//
// Created by 孙浩 on 2020/4/23.
//

#pragma once

#include <type_traits>

#include "vector.h"

template <typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
class MatrixTrait { };

template <int N, int M, typename T>
class Matrix;

using Matrix3f = Matrix<3, 3, float>;

template <int N, int M, typename DT>
class Matrix : MatrixTrait<DT>
{
public:
  Matrix() = default;
  template <int U = N, typename = typename std::enable_if<U == 1>::type>
  Matrix(std::initializer_list<DT> args);
  template <int U = N, typename = typename std::enable_if<U == 1>::type>
  Matrix(const Vector<M, DT>& vec);

  Matrix(std::initializer_list<std::initializer_list<DT>> args);

  Vector<M, DT>& operator[](int i) { return e[i]; }
  Vector<M, DT> operator[](int i) const { return e[i]; }

  Matrix<M, N, DT> T();

  // N1 M1 is the dimension of the other metrix
  // MA is the alias of M
  template <int N1, int M1, int MA = M,
      typename Tr = typename std::enable_if<N1 == MA>::type>
  Matrix<N, M1, DT> operator*(const Matrix<N1, M1, DT>& m);

protected:
  std::array<Vector<M, DT>, N> e;
};

template<int N, int M, typename DT>
std::ostream &operator<<(std::ostream& o, const Matrix<N, M, DT> &m);

// ======================= implementations =========================
template <int N, int M, typename DT>
Matrix<M, N, DT> Matrix<N, M, DT>::T()
{
  Matrix<M, N, DT> result;
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < M; ++j)
    {
      result[j][i] = e[i][j];
    }
  }
  return result;
}


template <int N, int M, typename DT>
template <int N1, int M1, int MA, typename Tr>
Matrix<N, M1, DT> Matrix<N, M, DT>::operator*(const Matrix<N1, M1, DT> &m) {
  Matrix<N, M1, DT> result;
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < M1; ++j)
    {
      result[i][j] = 0;
      for (int k = 0; k < M; ++k)
      {
        result[i][j] += e[i][k] * m[k][j];
      }
    }
  }
  return result;
}

template <int N, int M, typename DT>
template <int U, typename>
inline Matrix<N, M, DT>::Matrix(std::initializer_list<DT> args)
{
  int i = 0;
  for (auto arg: args)
  {
    e[0][i] = arg;
    if (++i >= M)
    {
      break;
    }
  }
}

template <int N, int M, typename DT>
template <int U, typename>
Matrix<N, M, DT>::Matrix(const Vector<M, DT>& vec)
{
  e[0] = vec;
}

template<int N, int M, typename DT>
std::ostream &operator<<(std::ostream& o, const Matrix<N, M, DT> &m)
{
  o << "[";
  for (int i = 0; i < N; ++i)
  {
    if (i != 0) o << " ";
    o << m[i];
    if (i != N - 1) o << "\n";
  }
  o << "]" << std::endl;
  return o;
}

template <int N, int M, typename DT>
Matrix<N, M, DT>::Matrix(
    std::initializer_list<std::initializer_list<DT>> args)
{
  auto iter = e.begin();
  for (const auto &arg: args)
  {
    int i = 0;
    for (auto e: arg)
    {
      (*iter)[i] = e;
      if (++i >= M)
      {
        break;
      }
    }
    if (++iter == e.end())
    {
      break;
    }
  }
}