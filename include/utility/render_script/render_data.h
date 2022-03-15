/**
 * @file render_data.h
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief
 * @version 0.1
 * @date 2022-02-12
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#pragma once
#ifndef CHERRY_UTILITY_RENDER_DATA
#define CHERRY_UTILITY_RENDER_DATA

#include <array>
#include <string>
#include <vector>

#include "nlohmann/detail/macro_scope.hpp"

using uint32 = unsigned int;

namespace cherry {
enum class RenderType { RayTracing, Rasterization };
enum class IntegratorType { Normal, MonteCarlo };
enum class MaterialType { Reflect, Microfacet, Dielectric, Diffuse };
enum class CameraType { Perspective, Orthographic };
enum class Primitive { Cuboid, Plane, Sphere, Triangle };
enum class LightType { Area };

struct MaterialData {
  std::string name;
  MaterialType type;
};

struct CameraData {
  CameraType type;
  std::array<double, 3> look_from;
  std::array<double, 3> look_at;
  std::array<double, 3> up_direction;
  double fov;
  double aperture;
  double focal_distance;
};

struct ObjectData {
  Primitive primitive;
  std::array<double, 3> position;
  // TODO(qrwells): transform
};

struct LightData {
  LightType type;
  std::array<double, 3> position;
  // TODO(qrwells): direction
};

struct SceneData {
  CameraData camera;
  std::vector<ObjectData> objects;
  std::vector<LightData> lights;
};

struct RenderData {
  std::string name;
  uint32 width;
  uint32 height;
  RenderType renderer;
  IntegratorType integrator;
  std::vector<MaterialData> materials;
  SceneData scene_data;
};
}  // namespace cherry

#endif