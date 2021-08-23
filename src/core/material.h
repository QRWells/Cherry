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

#include "../common/intersection.h"
#include "../common/ray.h"
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
      : attribute_(attribute), emission_(emit), kd_(kd), ks_(ks), ior_(ior) {}
  virtual ~Material() = default;

  virtual bool HasEmission() { return emission_.Norm2() > kEpsilon; }
  virtual math::Color GetEmission() { return emission_; }

  virtual math::Color Evaluate(const math::Vector3d&, const math::Vector3d&,
                               const math::Vector3d&) = 0;
  virtual math::Vector3d Sample(const math::Vector3d&,
                                const math::Vector3d&) = 0;
  virtual double Pdf(const math::Vector3d&, const math::Vector3d&,
                     const math::Vector3d&) = 0;

  static math::Vector3d ToWorld(const math::Vector3d&, const math::Vector3d&);

  Attribute attribute_;
 protected:
  std::shared_ptr<Texture> texture_ = nullptr;
  math::Color emission_;
  math::Color kd_;
  math::Color ks_;
  double ior_;
};
}  // namespace cherry

#endif  // !CHERRY_CORE_MATERIAL