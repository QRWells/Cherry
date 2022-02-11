// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : path_integrator.h
// Author      : QRWells
// Created at  : 2021/09/11 3:44
// Description :

#ifndef CHERRY_INTEGRATOR_PATH
#define CHERRY_INTEGRATOR_PATH

#include "core/integrator.h"

namespace cherry {
class PathIntegrator final : public Integrator {
 public:
  PathIntegrator() = default;
  auto Li(Ray const& ray, std::shared_ptr<Scene> const& scene)
      -> math::Point3 override;
};
}  // namespace cherry

#endif  // !CHERRY_INTEGRATOR_PATH
