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
#include <array>

#include "vector.h"

namespace cherry::math {

template <Number T>
struct Matrix4 {
 public:
  Matrix4() = default;
  explicit Matrix4(T v) { std::fill(std::begin(value_), std::end(value_), v); }
  Matrix4(T v11, T v22, T v33, T v44) : value_{v11} {
    value_[5] = v22;
    value_[10] = v33;
    value_[15] = v44;
  }
  Matrix4(T v11, T v12, T v13, T v14, T v21, T v22, T v23, T v24, T v31, T v32,
          T v33, T v34, T v41, T v42, T v43, T v44) {
    value_[0] = v11, value_[1] = v12, value_[2] = v13, value_[3] = v14;
    value_[4] = v21, value_[5] = v22, value_[6] = v23, value_[7] = v24;
    value_[8] = v31, value_[9] = v32, value_[10] = v33, value_[11] = v34;
    value_[12] = v41, value_[13] = v42, value_[14] = v43, value_[15] = v44;
  }
  Matrix4(Matrix4<T> const& that) : value_(nullptr) { *this = that; }
  Matrix4(Matrix4<T>&& that) noexcept { *this = std::move(that); }
  ~Matrix4() = default;

  static const Matrix4<T> ZERO;
  static const Matrix4<T> IDENTITY;

  auto operator=(Matrix4<T> const&) noexcept -> Matrix4<T>&;
  auto operator=(Matrix4<T>&&) noexcept -> Matrix4<T>&;

  auto operator()(int const& i, int const& j) const -> T const& {
    if (i < 1 || i > 4 || j < 1 || j > 4) return value_[0];
    return value_[(i - 1) * 4 + j - 1];
  }
  auto operator()(int const& i, int const& j) -> T& {
    if (i < 1 || i > 4 || j < 1 || j > 4) return value_[0];
    return value_[(i - 1) * 4 + j - 1];
  }

  auto operator+(Matrix4<T> const&) const -> Matrix4<T>;
  auto operator-(Matrix4<T> const&) const -> Matrix4<T>;
  auto operator*(Matrix4<T> const&) const -> Matrix4<T>;
  auto operator*(T const&) const -> Matrix4<T>;
  auto operator+=(Matrix4<T> const&) -> Matrix4<T>&;
  auto operator-=(Matrix4<T> const&) -> Matrix4<T>&;
  auto operator*=(Matrix4<T> const&) -> Matrix4<T>&;
  auto operator*=(T const&) -> Matrix4<T>&;

  auto operator<<(T const&) -> Matrix4<T>&;
  auto operator,(T const&) -> Matrix4<T>&;

  friend auto operator*(Matrix4<T> const&, Vector4<T> const&) -> Vector4<T>;

  auto ElementWiseProduct(Matrix4<T> const&) -> Matrix4<T>;
  [[nodiscard]] auto Inverse() const -> Matrix4<T>;
  [[nodiscard]] auto Transpose() const -> Matrix4<T>;

 private:
  std::array<T, 16> value_{};
  int last_index_{};
};

inline auto operator*(Matrix4<double> const& m, Vector4<double> const& v)
    -> Vector4<double> {
  auto const& value = m.value_;
  return {
      value[0] * v.x + value[1] * v.y + value[2] * v.z + value[3] * v.w,
      value[4] * v.x + value[5] * v.y + value[6] * v.z + value[7] * v.w,
      value[8] * v.x + value[9] * v.y + value[10] * v.z + value[11] * v.w,
      value[12] * v.x + value[13] * v.y + value[14] * v.z + value[15] * v.w,
  };
}

using Matrix4f = Matrix4<float>;
using Matrix4d = Matrix4<double>;
using Matrix4i = Matrix4<int>;
using Matrix = Matrix4d;

auto GetRotateMatrix(Vector3d const&, double const&) -> Matrix;

auto GetTransformMatrix(Vector3d const&) -> Matrix;

auto GetScaleMatrix(double const&, double const&, double const&) -> Matrix;

}  // namespace cherry::math

// namespace cherry

#endif  // !CHERRY_MATH_MATRIX