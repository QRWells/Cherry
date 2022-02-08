// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : matrix.cc
// Author      : QRWells
// Created at  : 2021/08/24 15:34
// Description :

#include "math/matrix.h"
#include <array>

namespace cherry::math {

template <Number T>
auto Matrix4<T>::operator=(Matrix4<T> const& m) noexcept -> Matrix4<T>& {
  if (this != &m) {
    this->last_index = m.last_index;
    std::copy(m.value_, m.value_ + 16, value_);
  }
  return *this;
}

template <Number T>
auto Matrix4<T>::operator=(Matrix4<T>&& m) noexcept -> Matrix4<T>& {
  if (this != &m) {
    this->last_index_ = m.last_index_;
    std::copy(m.value_.begin(), m.value_.end(), value_.begin());

    m.last_index_ = 0;
  }
  return *this;
}

template <Number T>
auto Matrix4<T>::operator+(Matrix4<T> const& m) const -> Matrix4<T> {
  auto result = Matrix4<T>();
  for (auto i = 0; i < 16; ++i) result.value_[i] = value_[i] + m.value_[i];
  return result;
}

template <Number T>
auto Matrix4<T>::operator-(Matrix4<T> const& m) const -> Matrix4<T> {
  auto result = Matrix4<T>();
  for (auto i = 0; i < 16; ++i) result.value_[i] = value_[i] - m.value_[i];
  return result;
}

template <Number T>
auto Matrix4<T>::operator*(Matrix4<T> const& m) const -> Matrix4<T> {
  auto result = Matrix4<T>();
  for (auto i = 0; i < 4; ++i)
    for (auto j = 0; j < 4; ++j)
      result.value_[i * 4 + j] = value_[i * 4 + 0] * m.value_[0 + j] +
                                 value_[i * 4 + 1] * m.value_[4 + j] +
                                 value_[i * 4 + 2] * m.value_[8 + j] +
                                 value_[i * 4 + 3] * m.value_[12 + j];

  return result;
}

template <Number T>
auto Matrix4<T>::operator*(T const& v) const -> Matrix4<T> {
  auto result = Matrix4<T>();
  for (auto i = 0; i < 16; ++i) result.value_[i] = value_[i] * v;
  return result;
}

template <Number T>
auto Matrix4<T>::operator+=(Matrix4<T> const& m) -> Matrix4<T>& {
  *this = operator+(m);
  return *this;
}

template <Number T>
auto Matrix4<T>::operator-=(Matrix4<T> const& m) -> Matrix4<T>& {
  *this = operator-(m);
  return *this;
}

template <Number T>
auto Matrix4<T>::operator*=(Matrix4<T> const& m) -> Matrix4<T>& {
  *this = operator*(m);
  return *this;
}

template <Number T>
auto Matrix4<T>::operator*=(T const& v) -> Matrix4<T>& {
  *this = operator*(v);
  return *this;
}

template <Number T>
auto Matrix4<T>::operator<<(T const& v) -> Matrix4<T>& {
  value_[last_index_++] = v;
  last_index_ %= 16;
  return *this;
}

template <Number T>
auto Matrix4<T>::operator,(T const&v) -> Matrix4<T>& {
  this->operator<<(v);
  return *this;
}

template <Number T>
auto Matrix4<T>::ElementWiseProduct(Matrix4<T> const& m) -> Matrix4<T> {
  auto result = Matrix4<T>();
  for (auto i = 0; i < 16; ++i) result.value_[i] = value_[i] * m.value_[i];
  return result;
}

template <Number T>
auto GluInvertMatrix(std::array<T, 16> const m, std::array<T, 16> inv_out)
    -> bool {
  std::array<T, 16> inv{0};
  T det;

  inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] +
           m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];

  inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] -
           m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];

  inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] +
           m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];

  inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] -
            m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];

  inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] -
           m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];

  inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] +
           m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];

  inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] -
           m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];

  inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] +
            m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];

  inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] +
           m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];

  inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] -
           m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];

  inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] +
            m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];

  inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] -
            m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];

  inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] -
           m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];

  inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] +
           m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];

  inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] -
            m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];

  inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] +
            m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

  det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

  if (det == 0) return false;

  det = 1.0 / det;

  for (int i = 0; i < 16; i++) inv_out[i] = inv[i] * det;

  return true;
}

template <Number T>
auto Matrix4<T>::Inverse() const -> Matrix4<T> {
  auto result = Matrix4<T>();
  if (auto& v = result.value_; GluInvertMatrix(value_, v)) return result;
  return ZERO;
}

template <Number T>
auto Matrix4<T>::Transpose() const -> Matrix4<T> {
  auto result = Matrix4<T>();
  for (auto i = 0; i < 4; ++i)
    for (auto j = 0; j < 4; ++j) result.value_[i * 4 + j] = value_[j * 4 + i];
  return result;
}

template <Number T>
const Matrix4<T> Matrix4<T>::ZERO(0);

template <Number T>
const Matrix4<T> Matrix4<T>::IDENTITY(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
                                      0, 1);

auto GetRotateMatrix(Vector3d const& axis, double const& rad) -> Matrix {
  Matrix const kN{0,        -axis(2), axis(1), 0, axis(2), 0, -axis(0), 0,
                  -axis(1), axis(0),  0,       0, 0,       0, 0,        0};
  Matrix const kAxt{axis(0) * axis(0),
                    axis(0) * axis(1),
                    axis(0) * axis(2),
                    0,
                    axis(1) * axis(0),
                    axis(1) * axis(1),
                    axis(1) * axis(2),
                    0,
                    axis(2) * axis(0),
                    axis(2) * axis(1),
                    axis(2) * axis(2),
                    0,
                    0,
                    0,
                    0,
                    0};
  Matrix r = Matrix::IDENTITY * std::cos(rad) + kAxt * (1 - std::cos(rad)) +
             kN * std::sin(rad);
  r(4, 4) = 1;
  return r;
}
auto GetTransformMatrix(Vector3d const& offset) -> Matrix {
  return {1, 0, 0, offset[0], 0, 1, 0, offset[1],
          0, 0, 1, offset[2], 0, 0, 0, 1};
}
auto GetScaleMatrix(double const& x, double const& y, double const& z)
    -> Matrix {
  return Matrix{x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1};
}
}  // namespace cherry::math
