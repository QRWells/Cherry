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
  explicit Vector2(T const &value) : x(value), y(value) {}
  Vector2(T const &x, T const &y) : x(x), y(y) {}

  auto operator[](int const i) const -> T const & { return i == 0 ? x : y; }

  auto operator[](int const i) -> T & { return i == 0 ? x : y; }

  auto operator==(Vector2<T> const &v) const -> bool {
    return x == v.x && y == v.y;
  }

  auto operator!=(Vector2<T> const &v) const -> bool { return !operator==(v); }

  auto operator+(Vector2<T> const &v) const -> Vector2<T> {
    return {x + v.x, y + v.y};
  }

  auto operator-(Vector2<T> const &v) const -> Vector2<T> {
    return {x - v.x, y - v.y};
  }

  auto operator-() const -> Vector2<T> { return {-x, -y}; }

  template <typename V>
  auto operator*(V const &v) const -> Vector2<T> {
    return {x * v, y * v};
  }

  template <typename V>
  auto operator/(V const &v) const -> Vector2<T> {
    return {x / v, y / v};
  }

  auto operator+=(Vector2<T> const &v) -> Vector2<T> & {
    x += v.x;
    y += v.y;
    return *this;
  }

  auto operator-=(Vector2<T> const &v) -> Vector2<T> & {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  template <typename V>
  auto operator*=(V const &v) -> Vector2<T> & {
    x *= v;
    y *= v;
    return *this;
  }

  template <typename V>
  auto operator/=(V const &v) -> Vector2<T> & {
    x /= v;
    y /= v;
    return *this;
  }

  auto operator*(Vector2<T> const &v) -> Vector2<T> {
    return {x * v.x, y * v.y};
  }

  [[nodiscard]] auto Norm2() const -> double { return x * x + y * y; }
  [[nodiscard]] auto Norm() const -> double { return std::sqrt(Norm2()); }

  auto Normalized() -> Vector2<T> {
    auto vn = Norm();
    return *this / vn;
  }

  auto Inverse() -> Vector2<T> { return {1 / x, 1 / y}; }

  auto Dot(Vector2<T> const &v) const -> double { return x * v.x + y * v.y; }

  template <typename U>
  auto Lerp(Vector2<T> const &v, U const &t) const -> Vector2<T> {
    return *this * (1 - t) + v * t;
  }

  auto ProjectTo(Vector2<T> const &v) -> Vector2<T> {
    auto vn = v.Normalized();
    return vn * this->Dot(vn);
  }

  void Clamp(T const &min, T const &max) {
    x = std::clamp(x, min, max);
    y = std::clamp(y, min, max);
  }
};

template <typename T, typename V>
auto operator/(V const &v, Vector2<T> const vec) -> Vector2<T> {
  return {v / vec.x, v / vec.y};
}

template <typename T>
auto Max(Vector2<T> const &a, Vector2<T> const &b) -> Vector2<T> {
  return {std::max(a.x, b.x), std::max(a.y, b.y)};
}

template <typename T>
auto Min(Vector2<T> const &a, Vector2<T> const &b) -> Vector2<T> {
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
  explicit Vector3(T const &v) : x(v), y(v), z(v) {}
  Vector3(T const &x, T const &y, T const &z) : x(x), y(y), z(z) {}

  auto operator[](int const &i) const -> T const & { return (&x)[i]; }

  auto operator[](int const &i) -> T & { return (&x)[i]; }

  auto operator()(int const &i) const -> T const & { return operator[](i); }

  auto operator==(Vector3 const &vec) const -> bool {
    return x == vec.x && y == vec.y && z == vec.z;
  }

  auto operator!=(Vector3 const &vec) const -> bool { return !*this == vec; }

  auto operator+(Vector3<T> const &v) const -> Vector3<T> {
    return {x + v.x, y + v.y, z + v.z};
  }

  auto operator-(Vector3<T> const &v) const -> Vector3<T> {
    return {x - v.x, y - v.y, z - v.z};
  }

  auto operator-() const -> Vector3<T> { return {-x, -y, -z}; }

  template <typename V>
  auto operator*(V const &v) const -> Vector3<T> {
    return {x * v, y * v, z * v};
  }

  template <typename V>
  friend auto operator*(V const &v, Vector3<T> const &vec) -> Vector3<T> {
    return {vec.x * v, vec.y * v, vec.z * v};
  }

  template <typename V>
  auto operator/(V const &v) const -> Vector3<T> {
    return {x / v, y / v, z / v};
  }

  template <typename V>
  friend auto operator/(V const &v, Vector3<T> const &vec) -> Vector3<T> {
    return {v / vec.x, v / vec.y, v / vec.z};
  }

  auto operator+=(Vector3<T> const &v) -> Vector3<T> & {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  auto operator-=(Vector3<T> const &v) -> Vector3<T> & {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  template <typename V>
  auto operator*=(V const &v) -> Vector3<T> & {
    x *= v;
    y *= v;
    z *= v;
    return *this;
  }

  auto operator*=(Vector3<T> const &v) -> Vector3<T> & {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }

  template <typename V>
  auto operator/=(V const &v) -> Vector3<T> & {
    x /= v;
    y /= v;
    z /= v;
    return *this;
  }

  auto operator*(Vector3<T> const &v) -> Vector3<T> {
    return {x * v.x, y * v.y, z * v.z};
  }

  [[nodiscard]] auto Norm2() const -> double { return x * x + y * y + z * z; }

  [[nodiscard]] auto Norm() const -> double { return std::sqrt(Norm2()); }

  [[nodiscard]] auto Normalized() const -> Vector3<T> {
    double len = Norm();
    return *this / len;
  }

  void Normalize() {
    auto &&len = Norm();
    x /= len;
    y /= len;
    z /= len;
  }

  auto Inverse() -> Vector3<T> { return {1 / x, 1 / y, 1 / z}; }

  [[nodiscard]] auto Dot(Vector3<T> const &v) const -> double {
    return x * v.x + y * v.y + z * v.z;
  }

  [[nodiscard]] auto Cross(Vector3<T> const &v) const -> Vector3<T> {
    return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
  }

  template <typename U>
  auto Lerp(Vector3<T> const &v, U const &t) const -> Vector3<T> {
    return *this * (1 - t) + v * t;
  }

  [[nodiscard]] auto ProjectTo(Vector3<T> const &v) const -> Vector3<T> {
    auto vn = v.Normalized();
    return vn * this->Dot(vn);
  }

  [[nodiscard]] auto AngleBetween(Vector3<T> const &v) const -> double {
    auto cos = this->Dot(v) / (this->Norm() * v.Norm());
    return std::acos(cos);
  }

  void Clamp(T const &min, T const &max) {
    x = std::clamp(x, min, max);
    y = std::clamp(y, min, max);
    z = std::clamp(z, min, max);
  }

  auto MaxElement() -> T { return std::max({x, y, z}); }

  void Formalize() { Clamp(0.0, 1.0); }

  auto Abs() -> Vector3<T> { return {std::abs(x), std::abs(y), std::abs(z)}; }

  [[nodiscard]] auto AsPoint() const -> Vector4<T> { return {*this, true}; }
  [[nodiscard]] auto AsVector() const -> Vector4<T> { return {*this, false}; }
};

template <Number T>
auto Max(Vector3<T> const &a, Vector3<T> const &b) -> Vector3<T> {
  return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
}

template <Number T>
auto Min(Vector3<T> const &a, Vector3<T> const &b) -> Vector3<T> {
  return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
}

using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
using Vector3i = Vector3<int>;
using Color = Vector3<double>;
using Point3 = Vector3<double>;

template <Number T>
struct Vector4 {
  Vector4(Vector3<T> const &vector3, bool const &is_point)
      : x(vector3.x), y(vector3.y), z(vector3.z), w(is_point ? 1 : 0) {}
  Vector4(T const &x, T const &y, T const &z, T const &w)
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