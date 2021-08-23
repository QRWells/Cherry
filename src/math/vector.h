// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
// 
// This file is part of Project Cherry.
// File Name   : vector.h
// Author      : QRWells
// Created at  : 2021/08/24 15:56
// Description :

#ifndef CHERRY_MATH_VECTOR
#define CHERRY_MATH_VECTOR

#include <algorithm>
#include <cmath>
#include <variant>

namespace cherry::math {

template <typename T>
concept Number = std::is_arithmetic_v<T>;

template <Number T>
struct Vector2;

template <Number T>
struct Vector3;

template <Number T>
struct Vector4;

template <Number T>
struct Vector2 {
  T x, y;

  Vector2() : x(0), y(0) {}
  explicit Vector2(T const& value) : x(value), y(value) {}
  Vector2(T const& x, T const& y) : x(x), y(y) {}

  T const& operator[](int const i) const { return i == 0 ? x : y; }

  T& operator[](int const i) { return i == 0 ? x : y; }

  bool operator==(Vector2<T> const& v) const { return x == v.x && y == v.y; }

  bool operator!=(Vector2<T> const& v) const { return !operator==(v); }

  Vector2<T> operator+(Vector2<T> const& v) const { return {x + v.x, y + v.y}; }

  Vector2<T> operator-(Vector2<T> const& v) const { return {x - v.x, y - v.y}; }

  Vector2<T> operator-() const { return {-x, -y}; }

  template <typename V>
  Vector2<T> operator*(V const& v) const {
    return {x * v, y * v};
  }

  template <typename V>
  Vector2<T> operator/(V const& v) const {
    return {x / v, y / v};
  }

  Vector2<T>& operator+=(Vector2<T> const& v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  Vector2<T>& operator-=(Vector2<T> const& v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  template <typename V>
  Vector2<T>& operator*=(V const& v) {
    x *= v;
    y *= v;
    return *this;
  }

  template <typename V>
  Vector2<T>& operator/=(V const& v) {
    x /= v;
    y /= v;
    return *this;
  }

  Vector2<T> operator*(Vector2<T> const& v) { return {x * v.x, y * v.y}; }

  [[nodiscard]] double Norm2() const { return x * x + y * y; }
  [[nodiscard]] double Norm() const { return std::sqrt(Norm2()); }

  Vector2<T> Normalized() {
    auto vn = Norm();
    return *this / vn;
  }

  Vector2<T> Inverse() { return {1 / x, 1 / y}; }

  double Dot(Vector2<T> const& v) const { return x * v.x + y * v.y; }

  template <typename U>
  Vector2<T> Lerp(Vector2<T> const& v, U const& t) const {
    return *this * (1 - t) + v * t;
  }

  Vector2<T> ProjectTo(Vector2<T> const& v) {
    auto vn = v.Normalized();
    return vn * this->Dot(vn);
  }

  void Clamp(T const& min, T const& max) {
    x = std::clamp(x, min, max);
    y = std::clamp(y, min, max);
  }
};

template <typename T, typename V>
Vector2<T> operator/(V const& v, Vector2<T> const vec) {
  return {v / vec.x, v / vec.y};
}

template <typename T>
Vector2<T> Max(Vector2<T> const& a, Vector2<T> const& b) {
  return {std::max(a.x, b.x), std::max(a.y, b.y)};
}

template <typename T>
Vector2<T> Min(Vector2<T> const& a, Vector2<T> const& b) {
  return {std::min(a.x, b.x), std::min(a.y, b.y)};
}

using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
using Vector2i = Vector2<int>;
using Point2 = Vector2<double>;

template <Number T>
struct Vector3 {
  T x, y, z;

  Vector3() : x(0), y(0), z(0) {}
  explicit Vector3(T const& v) : x(v), y(v), z(v) {}
  Vector3(T const& x, T const& y, T const& z) : x(x), y(y), z(z) {}

  T const& operator[](int const& i) const { return (&x)[i]; }

  T& operator[](int const& i) { return (&x)[i]; }

  T const& operator()(int const& i) const { return operator[](i); }

  bool operator==(Vector3 const& vec) const {
    return x == vec.x && y == vec.y && z == vec.z;
  }

  bool operator!=(Vector3 const& vec) const { return !*this == vec; }

  Vector3<T> operator+(Vector3<T> const& v) const {
    return {x + v.x, y + v.y, z + v.z};
  }

  Vector3<T> operator-(Vector3<T> const& v) const {
    return {x - v.x, y - v.y, z - v.z};
  }

  Vector3<T> operator-() const { return {-x, -y, -z}; }

  template <typename V>
  Vector3<T> operator*(V const& v) const {
    return {x * v, y * v, z * v};
  }

  template <typename V>
  friend Vector3<T> operator*(V const& v, Vector3<T> const& vec) {
    return {vec.x * v, vec.y * v, vec.z * v};
  }

  template <typename V>
  Vector3<T> operator/(V const& v) const {
    return {x / v, y / v, z / v};
  }

  template <typename V>
  friend Vector3<T> operator/(V const& v, Vector3<T> const& vec) {
    return {v / vec.x, v / vec.y, v / vec.z};
  }

  Vector3<T>& operator+=(Vector3<T> const& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  Vector3<T>& operator-=(Vector3<T> const& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  template <typename V>
  Vector3<T>& operator*=(V const& v) {
    x *= v;
    y *= v;
    z *= v;
    return *this;
  }

  Vector3<T>& operator*=(Vector3<T> const& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }

  template <typename V>
  Vector3<T>& operator/=(V const& v) {
    x /= v;
    y /= v;
    z /= v;
    return *this;
  }

  Vector3<T> operator*(Vector3<T> const& v) {
    return {x * v.x, y * v.y, z * v.z};
  }

  [[nodiscard]] double Norm2() const { return x * x + y * y + z * z; }

  [[nodiscard]] double Norm() const { return std::sqrt(Norm2()); }

  [[nodiscard]] Vector3<T> Normalized() const {
    double len = Norm();
    return *this / len;
  }

  void Normalize() {
    auto&& len = Norm();
    x /= len;
    y /= len;
    z /= len;
  }

  Vector3<T> Inverse() { return {1 / x, 1 / y, 1 / z}; }

  [[nodiscard]] double Dot(Vector3<T> const& v) const {
    return x * v.x + y * v.y + z * v.z;
  }

  [[nodiscard]] Vector3<T> Cross(Vector3<T> const& v) const {
    return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
  }

  template <typename U>
  Vector3<T> Lerp(Vector3<T> const& v, U const& t) const {
    return *this * (1 - t) + v * t;
  }

  [[nodiscard]] Vector3<T> ProjectTo(Vector3<T> const& v) const {
    auto vn = v.Normalized();
    return vn * this->Dot(vn);
  }

  [[nodiscard]] double AngleBetween(Vector3<T> const& v) const {
    auto cos = this->Dot(v) / (this->Norm() * v.Norm());
    return std::acos(cos);
  }

  void Clamp(T const& min, T const& max) {
    x = std::clamp(x, min, max);
    y = std::clamp(y, min, max);
    z = std::clamp(z, min, max);
  }

  T MaxElement() { return std::max({x, y, z}); }

  void Formalize() { Clamp(0.0, 1.0); }

  [[nodiscard]] Vector4<T> AsPoint() const { return {*this, true}; }
  [[nodiscard]] Vector4<T> AsVector() const { return {*this, false}; }
};

template <Number T>
Vector3<T> Max(Vector3<T> const& a, Vector3<T> const& b) {
  return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
}

template <Number T>
Vector3<T> Min(Vector3<T> const& a, Vector3<T> const& b) {
  return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
}

using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
using Vector3i = Vector3<int>;
using Color = Vector3<double>;
using Point3 = Vector3<double>;

template <Number T>
struct Vector4 {
  Vector4(Vector3<T> const& vector3, bool const& is_point)
      : x(vector3.x), y(vector3.y), z(vector3.z), w(is_point ? 1 : 0) {}
  Vector4(T const& x, T const& y, T const& z, T const& w)
      : x(x), y(y), z(z), w(w) {}
  T x, y, z, w;

  void Regularize() {
    if (w) {
      x /= w;
      y /= w;
      z /= w;
      w = 1;
    }
  }
};

using Vector4d = Vector4<double>;

}  // namespace cherry::math

#endif  // !CHERRY_MATH_VECTOR