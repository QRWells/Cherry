// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : material.h
// Author      : QRWells
// Created at  : 2021/08/24 5:31
// Description :

#ifndef CHERRY_CORE_MATERIAL
#define CHERRY_CORE_MATERIAL

#include <memory>

#include "../math/vector.h"
#include "../utility/constant.h"
#include "texture.h"


namespace cherry {
class Material {
 public:
  enum class Attribute : size_t {
    kDiffuse = 1 << 0,
    kGlossy = 1 << 1,
    kReflect = 1 << 2,
    kRefract = 1 << 3,
    kTransparent = 1 << 4,
    kMicrofacet = 1 << 5,
    kDielectric = 1 << 6
  };

  explicit Material(const math::Color& kd = {0, 0, 0},
                    const math::Color& ks = {0, 0, 0},
                    const Attribute& attribute = Attribute::kDiffuse,
                    const math::Color& emit = {}, const double& ior = 1.5)
      : attribute(attribute), emission(emit), kd(kd), ks(ks), ior(ior) {}
  virtual ~Material() = default;

  virtual auto HasEmission() -> bool { return emission.Norm2() > EPSILON; }
  virtual auto GetEmission() -> math::Color { return emission; }

  virtual auto Evaluate(const math::Vector3d&, const math::Vector3d&,
                        const math::Vector3d&) -> math::Color = 0;
  virtual auto Sample(const math::Vector3d&, const math::Vector3d&)
      -> math::Vector3d = 0;
  virtual auto Pdf(const math::Vector3d&, const math::Vector3d&,
                   const math::Vector3d&) -> double = 0;

  static auto ToWorld(const math::Vector3d&, const math::Vector3d&)
      -> math::Vector3d;

  Attribute attribute;

 protected:
  std::shared_ptr<Texture> texture = nullptr;
  math::Color emission;
  math::Color kd;
  math::Color ks;
  double ior;
};
}  // namespace cherry

#endif  // !CHERRY_CORE_MATERIAL