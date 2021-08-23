// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : mesh.h
// Author      : QRWells
// Created at  : 2021/08/31 23:51
// Description :

#ifndef CHERRY_OBJECT_MESH
#define CHERRY_OBJECT_MESH

#include <memory>
#include <string>
#include <vector>

#include "../acceleration/bvh.h"
#include "../core/object.h"
#include "primitive/triangle.h"

namespace cherry {
class Mesh final : public Object {
 public:
  void LoadObj(const std::string&);
  Box GetBounds() override;
  bool Intersect(const Ray&, Intersection&) const override;
  void Sample(Intersection&, double&) override;
  [[nodiscard]] bool HasEmission() const override;
  [[nodiscard]] double GetSurfaceArea() const override;

  uint32_t num_triangles_;
  double area_;
  Box bounding_box_;
  Bvh bvh_;
  std::shared_ptr<Material> material_;
  std::vector<math::Vector3d> vertices_;
  std::vector<uint32_t> vertex_index_;
  std::vector<math::Vector2d> st_coordinates_;
  std::vector<Triangle> triangles_;
};
}  // namespace cherry

#endif  // !CHERRY_OBJECT_MESH_TRIANGLE
