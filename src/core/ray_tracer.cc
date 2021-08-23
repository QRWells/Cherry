// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : ray_tracer.cc
// Author      : QRWells
// Created at  : 2021/08/23 18:47
// Description :

#include "ray_tracer.h"

#include <algorithm>
#include <thread>

#include "../utility/random.h"
#include "omp.h"

namespace cherry {
void RayTracer::Render() {
  auto const& kCamera = scene_->camera_;
  auto const& kWidth = width_;
  auto const& kHeight = height_;
  auto const kSppInv = 1.0 / static_cast<double>(spp_);
  printf("trace with spp: %lld\n", spp_);

#pragma omp parallel
  {
    auto const kThreadCount = omp_get_num_threads();
    auto const kThreadId = omp_get_thread_num();
    auto const kStart = kThreadId * kHeight / kThreadCount;
    auto const kEnd = (kThreadId + 1) * kHeight / kThreadCount;
    for (auto j = kStart; j < kEnd; ++j) {
      auto m = j * kWidth;
      for (uint32_t i = 0; i < kWidth; ++i) {
        for (int k = 0; k < spp_; k++) {
          auto x = (i + GetRandomDouble()) / (width_ - 1);
          auto y = (j + GetRandomDouble()) / (height_ - 1);
          frame_buffer_[m] +=
              integrator_->Li(kCamera->GenerateRay(x, y), scene_) * kSppInv;
        }
        ++m;
      }
      printf(".");
    }
  }
}

void RayTracer::SavePpm(const std::string& file_name) {
  FILE* fp = nullptr;
  if (auto const kErr = fopen_s(&fp, (file_name + ".ppm").c_str(), "wb");
      kErr == 0) {
    (void)fprintf(fp, "P6\n%d %d\n255\n", width_, height_);
    for (const auto& kI : frame_buffer_) {
      static unsigned char color[3] = {0};
      color[0] = static_cast<unsigned char>(
          255 * std::pow(std::clamp(kI.x, 0.0, 1.0), 0.7));
      color[1] = static_cast<unsigned char>(
          255 * std::pow(std::clamp(kI.y, 0.0, 1.0), 0.7));
      color[2] = static_cast<unsigned char>(
          255 * std::pow(std::clamp(kI.z, 0.0, 1.0), 0.7));
      fwrite(color, 1, 3, fp);
    }
    fclose(fp);
  }
}

}  // namespace cherry
