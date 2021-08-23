// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
// 
// This file is part of Project Cherry.
// File Name   : matrix.cc
// Author      : QRWells
// Created at  : 2021/08/24 15:34
// Description :

#include "matrix.h"

namespace cherry::math {

template <Number T>
Matrix4<T>& Matrix4<T>::operator=(Matrix4<T> const& m) noexcept {
  if (this != &m) {
    this->last_index = m.last_index;
    std::copy(m.value, m.value + 16, value);
  }
  return *this;
}

template <Number T>
Matrix4<T>& Matrix4<T>::operator=(Matrix4<T>&& m) noexcept {
  if (this != &m) {
    this->last_index = m.last_index;
    std::copy(m.value, m.value + 16, value);

    m.last_index = 0;
  }
  return *this;
}

template <Number T>
Matrix4<T> Matrix4<T>::operator+(Matrix4<T> const& m) const {
  auto result = Matrix4<T>();
  for (auto i = 0; i < 16; ++i) result.value[i] = value[i] + m.value[i];
  return result;
}

template <Number T>
Matrix4<T> Matrix4<T>::operator-(Matrix4<T> const& m) const {
  auto result = Matrix4<T>();
  for (auto i = 0; i < 16; ++i) result.value[i] = value[i] - m.value[i];
  return result;
}

template <Number T>
Matrix4<T> Matrix4<T>::operator*(Matrix4<T> const& m) const {
  auto result = Matrix4<T>();
  for (auto i = 0; i < 4; ++i)
    for (auto j = 0; j < 4; ++j)
      result.value[i * 4 + j] = value[i * 4 + 0] * m.value[0 + j] +
                                value[i * 4 + 1] * m.value[4 + j] +
                                value[i * 4 + 2] * m.value[8 + j] +
                                value[i * 4 + 3] * m.value[12 + j];

  return result;
}

template <Number T>
Matrix4<T> Matrix4<T>::operator*(T const& v) const {
  auto result = Matrix4<T>();
  for (auto i = 0; i < 16; ++i) result.value[i] = value[i] * v;
  return result;
}

template <Number T>
Matrix4<T>& Matrix4<T>::operator+=(Matrix4<T> const& m) {
  *this = operator+(m);
  return *this;
}

template <Number T>
Matrix4<T>& Matrix4<T>::operator-=(Matrix4<T> const& m) {
  *this = operator-(m);
  return *this;
}

template <Number T>
Matrix4<T>& Matrix4<T>::operator*=(Matrix4<T> const& m) {
  *this = operator*(m);
  return *this;
}

template <Number T>
Matrix4<T>& Matrix4<T>::operator*=(T const& v) {
  *this = operator*(v);
  return *this;
}

template <Number T>
Matrix4<T>& Matrix4<T>::operator<<(T const& v) {
  value[last_index++] = v;
  last_index %= 16;
  return *this;
}

template <Number T>
Matrix4<T>&Matrix4<T>::operator,(T const&v) {
  this->operator<<(v);
  return *this;
}

template <Number T>
Matrix4<T> Matrix4<T>::ElementWiseProduct(Matrix4<T> const& m) {
  auto result = Matrix4<T>();
  for (auto i = 0; i < 16; ++i) result.value[i] = value[i] * m.value[i];
  return result;
}

template <Number T>
bool GluInvertMatrix(T const m[16], T inv_out[16]) {
  T inv[16] = {0};
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
Matrix4<T> Matrix4<T>::Inverse() const {
  auto result = Matrix4<T>();
  if (auto& v = result.value; GluInvertMatrix(value, v)) return result;
  return zero;
}

template <Number T>
Matrix4<T> Matrix4<T>::Transpose() const {
  auto result = Matrix4<T>();
  for (auto i = 0; i < 4; ++i)
    for (auto j = 0; j < 4; ++j) result.value[i * 4 + j] = value[j * 4 + i];
  return result;
}

template <Number T>
Matrix4<T> Matrix4<T>::zero(0);

template <Number T>
Matrix4<T> Matrix4<T>::identity(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

Matrix GetRotateMatrix(Vector3d const& axis, double const& rad) {
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
  Matrix r = Matrix::identity * std::cos(rad) + kAxt * (1 - std::cos(rad)) +
             kN * std::sin(rad);
  r(4, 4) = 1;
  return r;
}
Matrix GetTransformMatrix(Vector3d const& offset) {
  return Matrix(1, 0, 0, offset[0], 0, 1, 0, offset[1], 0, 0, 1, offset[2], 0,
                0, 0, 1);
}
Matrix GetScaleMatrix(double const& x, double const& y, double const& z) {
  return Matrix{x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1};
}
}  // namespace cherry::math
