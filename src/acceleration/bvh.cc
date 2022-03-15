// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : bvh.cc
// Author      : QRWells
// Created at  : 2021/08/24 5:48
// Description :

#include <map>

#include "acceleration/bvh.h"
#include "common/box.h"

namespace cherry {
void Bvh::Construct(std::vector<std::shared_ptr<Object>> const& objects) {
  root_ = Build(objects);
}

auto Bvh::Intersect(Ray const& ray, Intersection& intersection) const -> bool {
  if (root_ == nullptr) return false;
  return GetIntersection(ray, root_, intersection);
}

auto Bvh::Build(std::vector<std::shared_ptr<Object>> const& objects)
    -> std::shared_ptr<BvhNode> {
  auto node = std::make_shared<BvhNode>();

  Box bound;
  for (auto const& k_o : objects) bound = bound.Union(k_o->GetBounds());
  std::vector<std::shared_ptr<Object>> left_shapes;
  std::vector<std::shared_ptr<Object>> right_shapes;
  switch (objects.size()) {
    case 1:
      node->bounds = objects[0]->GetBounds();
      node->object = objects[0];
      node->left = nullptr;
      node->right = nullptr;
      node->area = objects[0]->GetSurfaceArea();
      return node;
    case 2:
      node->left = Build(std::vector{objects[0]});
      node->right = Build(std::vector{objects[1]});
      node->bounds = node->left->bounds.Union(node->right->bounds);
      node->area = node->bounds.SurfaceArea();
      return node;
      [[likely]] default : Box centroid;
      for (auto const& k_o : objects)
        centroid = centroid.Union(Box(k_o->GetBounds().Centroid()));
      auto total_area = centroid.SurfaceArea();
      size_t min_cost_coords = 0;
      size_t min_cost_index = 0;
      auto min_cost = std::numeric_limits<double>::infinity();
      std::map<size_t, std::map<size_t, size_t>> index_map;
      for (int i = 0; i < 3; i++) {
        int constexpr kBucketCount = 12;
        std::vector<Box> bounds_buckets;
        std::vector<int> count_bucket;
        for (int j = 0; j < kBucketCount; j++) {
          bounds_buckets.emplace_back();
          count_bucket.push_back(0);
        }

        std::map<size_t, size_t> obj_map;

        for (size_t j = 0; j < objects.size(); j++) {
          int bid = kBucketCount * static_cast<int>(centroid.Offset(
                                       objects[j]->GetBounds().Centroid())[i]);
          if (bid > kBucketCount - 1) bid = kBucketCount - 1;

          Box b = bounds_buckets[bid];
          b = b.Union(Box(objects[j]->GetBounds().Centroid()));
          bounds_buckets[bid] = b;
          count_bucket[bid] = count_bucket[bid] + 1;
          obj_map.insert({j, bid});
        }

        index_map.emplace(i, obj_map);

        for (size_t j = 1; j < bounds_buckets.size(); j++) {
          Box a;
          Box b;
          int count_a = 0;
          int count_b = 0;
          for (size_t k = 0; k < j; k++) {
            a = a.Union(bounds_buckets[k]);
            count_a += count_bucket[k];
          }

          for (size_t k = j; k < bounds_buckets.size(); k++) {
            b = b.Union(bounds_buckets[k]);
            count_b += count_bucket[k];
          }

          if (auto cost =
                  (count_a * a.SurfaceArea() + count_b * b.SurfaceArea()) /
                  total_area;
              cost < min_cost) {
            min_cost = cost;
            min_cost_index = j;
            min_cost_coords = i;
          }
        }
      }

      for (size_t i = 0; i < objects.size(); i++)
        if (index_map[min_cost_coords][i] < min_cost_index)
          left_shapes.push_back(objects[i]);
        else
          right_shapes.push_back(objects[i]);
      break;
  }
  node->left = Build(left_shapes);
  node->right = Build(right_shapes);
  node->bounds = node->left->bounds.Union(node->right->bounds);

  return node;
}
auto Bvh::GetIntersection(Ray const& ray, const std::shared_ptr<BvhNode>& node,
                          Intersection& intersection) -> bool {
  if (node == nullptr) return false;
  if (node->left == nullptr && node->right == nullptr)
    return node->object->Intersect(ray, intersection);

  Intersection inter1;
  Intersection inter2;
  auto const kI1 = GetIntersection(ray, node->left, inter1);
  auto const kI2 = GetIntersection(ray, node->right, inter2);
  intersection = inter1.distance < inter2.distance ? inter1 : inter2;
  return kI1 || kI2;
}
}  // namespace cherry