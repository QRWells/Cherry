// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : ray_tracer.cc
// Author      : QRWells
// Created at  : 2021/08/23 18:47
// Description :

#include <cstdint>
#include <thread>

#include "fmt/core.h"
#include "omp.h"

#include "core/ray_tracer.h"
#include "utility/random.h"

namespace cherry {
void RayTracer::Render() {
  auto const& k_camera = scene->camera;
  auto const& k_width = width;
  auto const& k_height = height;
  auto const kSppInv = 1.0 / static_cast<double>(spp);
  fmt::print("trace with spp: {}\n", spp);

#pragma omp parallel
  {
    auto const kThreadCount = omp_get_num_threads();
    auto const kThreadId = omp_get_thread_num();
    auto const kStart = kThreadId * k_height / kThreadCount;
    auto const kEnd = (kThreadId + 1) * k_height / kThreadCount;
    for (uint32_t j = kStart; j < kEnd; ++j) {
      auto m = j * k_width;
      for (uint32_t i = 0; i < k_width; ++i) {
        for (int k = 0; k < spp; k++) {
          auto x = static_cast<double>(i) / static_cast<double>(width - 1);
          auto y = static_cast<double>(j) / static_cast<double>(height - 1);
          frame_buffer[m] +=
              integrator_->Li(k_camera->GenerateRay(x, y), scene) * kSppInv;
        }
        ++m;
      }
    }
  }
}

}  // namespace cherry
