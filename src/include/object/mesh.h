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
  void LoadObj(const std::string &);

  auto Intersect(const Ray &ray, Intersection &intersection) const
      -> bool override;
  auto GetBounds() -> Box override;
  void Sample(Intersection &intersection, double &pdf) override;
  [[nodiscard]] auto HasEmission() const -> bool override;
  [[nodiscard]] auto GetSurfaceArea() const -> double override;

  uint32_t num_triangles;
  double area;
  Box bounding_box;
  Bvh bvh;
  std::shared_ptr<Material> material;
  std::vector<math::Vector3d> vertices;
  std::vector<uint32_t> vertex_index;
  std::vector<math::Vector2d> st_coordinates;
  std::vector<Triangle> triangles;
};
}  // namespace cherry

#endif  // !CHERRY_OBJECT_MESH_TRIANGLE
