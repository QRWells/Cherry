// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
// 
// This file is part of Project Cherry.
// File Name   : matrix.h
// Author      : QRWells
// Created at  : 2021/08/24 15:34
// Description :

#ifndef CHERRY_MATH_MATRIX
#define CHERRY_MATH_MATRIX

#include <algorithm>

#include "vector.h"

namespace cherry::math {

template <Number T>
struct Matrix4 {
 public:
  Matrix4() : value{0}, last_index(0) {}
  Matrix4(T v) : last_index(0) {
    std::fill(std::begin(value), std::end(value), v);
  }
  Matrix4(T v11, T v22, T v33, T v44) : value{v11}, last_index(0) {
    value[5] = v22;
    value[10] = v33;
    value[15] = v44;
  }
  Matrix4(T v11, T v12, T v13, T v14, T v21, T v22, T v23, T v24, T v31, T v32,
          T v33, T v34, T v41, T v42, T v43, T v44)
      : last_index(0) {
    value[0] = v11, value[1] = v12, value[2] = v13, value[3] = v14;
    value[4] = v21, value[5] = v22, value[6] = v23, value[7] = v24;
    value[8] = v31, value[9] = v32, value[10] = v33, value[11] = v34;
    value[12] = v41, value[13] = v42, value[14] = v43, value[15] = v44;
  }
  Matrix4(Matrix4<T> const& that) : value(nullptr), last_index(0) {
    *this = that;
  }
  Matrix4(Matrix4<T>&& that) noexcept : last_index(0) {
    *this = std::move(that);
  }
  ~Matrix4() = default;

  static Matrix4<T> zero;
  static Matrix4<T> identity;

  Matrix4<T>& operator=(Matrix4<T> const&) noexcept;
  Matrix4<T>& operator=(Matrix4<T>&&) noexcept;

  T const& operator()(int const& i, int const& j) const {
    if (i < 1 || i > 4 || j < 1 || j > 4) return value[0];
    return value[(i - 1) * 4 + j - 1];
  }
  T& operator()(int const& i, int const& j) {
    if (i < 1 || i > 4 || j < 1 || j > 4) return value[0];
    return value[(i - 1) * 4 + j - 1];
  }

  Matrix4<T> operator+(Matrix4<T> const&) const;
  Matrix4<T> operator-(Matrix4<T> const&) const;
  Matrix4<T> operator*(Matrix4<T> const&) const;
  Matrix4<T> operator*(T const&) const;
  Matrix4<T>& operator+=(Matrix4<T> const&);
  Matrix4<T>& operator-=(Matrix4<T> const&);
  Matrix4<T>& operator*=(Matrix4<T> const&);
  Matrix4<T>& operator*=(T const&);

  Matrix4<T>& operator<<(T const&);
  Matrix4<T>& operator,(T const&);

  friend Vector4<T> operator*(Matrix4<T> const&, Vector4<T> const&);

  Matrix4<T> ElementWiseProduct(Matrix4<T> const&);
  [[nodiscard]] Matrix4<T> Inverse() const;
  [[nodiscard]] Matrix4<T> Transpose() const;

 private:
  T value[16];
  int last_index;
};

inline Vector4<double> operator*(Matrix4<double> const& m,
                                 Vector4<double> const& v) {
  auto& kValue = m.value;
  return {
      kValue[0] * v.x + kValue[1] * v.y + kValue[2] * v.z + kValue[3] * v.w,
      kValue[4] * v.x + kValue[5] * v.y + kValue[6] * v.z + kValue[7] * v.w,
      kValue[8] * v.x + kValue[9] * v.y + kValue[10] * v.z + kValue[11] * v.w,
      kValue[12] * v.x + kValue[13] * v.y + kValue[14] * v.z + kValue[15] * v.w,
  };
}

using Matrix4f = Matrix4<float>;
using Matrix4d = Matrix4<double>;
using Matrix4i = Matrix4<int>;
using Matrix = Matrix4d;

Matrix GetRotateMatrix(Vector3d const&, double const&);

Matrix GetTransformMatrix(Vector3d const&);

Matrix GetScaleMatrix(double const&, double const&, double const&);

}  // namespace cherry::math

// namespace cherry

#endif  // !CHERRY_MATH_MATRIX