// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
// 
// This file is part of Project Cherry.
// File Name   : box.cc
// Author      : QRWells
// Created at  : 2021/08/24 15:10
// Description :

#include "box.h"

#include <algorithm>

namespace cherry {

int Box::MaxExtent() const {
  auto const kDiagonal = Diagonal();
  if (kDiagonal.x > kDiagonal.y && kDiagonal.x > kDiagonal.z) return 0;
  return kDiagonal.y > kDiagonal.z ? 1 : 2;
}

math::Vector3d Box::Offset(math::Point3 const& p) const {
  auto o = p - min;
  if (max.x > min.x) o.x /= max.x - min.x;
  if (max.y > min.y) o.y /= max.y - min.y;
  if (max.z > min.z) o.z /= max.z - min.z;
  return o;
}

bool Box::Intersect(Ray const& ray, Intersection& intersection) const {
  auto const kTMin = (min - ray.origin) * ray.direction_inv;
  auto const kTMax = (max - ray.origin) * ray.direction_inv;

  auto const kT0 = Min(kTMin, kTMax);
  auto const kT1 = Max(kTMin, kTMax);

  auto const kTEnter = std::max({kT0.x, kT0.y, kT0.z});
  auto const kTExit = std::min({kT1.x, kT1.y, kT1.z});

  return kTEnter < kTExit && kTExit > 0;
}

Box Box::Union(Box const& box) const {
  auto _min = Min(this->min, box.min);
  auto _max = Max(this->max, box.max);
  return {_min, _max};
}
bool Box::Overlaps(Box const& box) const {
  auto const kX = (max.x > box.min.x) && (min.x < box.max.x);
  auto const kY = (max.y > box.min.y) && (min.y < box.max.y);
  auto const kZ = (max.z > box.min.z) && (min.z < box.max.z);
  return kX && kY && kZ;
}
bool Box::Inside(math::Point3 const& p) const {
  return p.x > min.x && p.x < max.x && p.y > min.y && p.y < max.y &&
         p.z > min.z && p.z < max.z;
}
}  // namespace cherry
