// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : intersection.h
// Author      : QRWells
// Created at  : 2021/08/23 19:10
// Description :

#ifndef INTERSECTION
#define INTERSECTION

#include <memory>

#include "../math/vector.h"
#include "../utility/constant.h"
#include "shading_point.h"

namespace cherry {
class Object;
class Material;
struct Intersection {
 public:
  Intersection() = default;
  math::Point3 coordinate;
  math::Vector3d normal;
  ShadingPoint shading_point;
  std::shared_ptr<Material> material = nullptr;
  double distance = INFINITY;
};
}  // namespace cherry

#endif  // !INTERSECTION
