// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : bvh.h
// Author      : QRWells
// Created at  : 2021/08/24 5:48
// Description :

#ifndef CHERRY_ACCELERATION_BVH
#define CHERRY_ACCELERATION_BVH

#include "common/intersection.h"
#include "common/ray.h"
#include "core/object.h"

namespace cherry {
struct BvhNode {
  BvhNode() : left(nullptr), right(nullptr), object(nullptr) { bounds = Box(); }
  std::shared_ptr<BvhNode> left;
  std::shared_ptr<BvhNode> right;
  std::shared_ptr<Object> object;
  Box bounds;
  double area{};
};
class Bvh {
 public:
  Bvh() : root_(nullptr) {}
  void Construct(const std::vector<std::shared_ptr<Object>> &objects);
  auto Intersect(const Ray &ray, Intersection &intersection) const -> bool;
  [[nodiscard]] static auto Build(
      const std::vector<std::shared_ptr<Object>> &objects)
      -> std::shared_ptr<BvhNode>;
  [[nodiscard]] static auto GetIntersection(const Ray &,
                                            const std::shared_ptr<BvhNode> &,
                                            Intersection &) -> bool;

 private:
  std::shared_ptr<BvhNode> root_;
};
}  // namespace cherry

#endif  // !CHERRY_ACCELERATION_BVH