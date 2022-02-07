// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : renderer.cpp
// Author      : QRWells
// Created at  : 2021/09/23 16:45
// Description :

#include "renderer.h"

namespace cherry {

Renderer::Renderer(std::shared_ptr<Scene> scene, const uint64_t& width,
                   const uint64_t& height)
    : frame_buffer(height * width),
      width(width),
      height(height),
      scene(std::move(scene)) {}

void Renderer::SavePpm(const std::string& file_name) const {
  FILE* fp = fopen((file_name + ".ppm").c_str(), "wb");
  if (fp != nullptr) {
    (void)fprintf(fp, "P6\n%lu %lu\n255\n", width, height);
    for (const auto& k_i : frame_buffer) {
      static unsigned char color[3] = {0};
      color[0] = static_cast<unsigned char>(
          255 * std::pow(std::clamp(k_i.x, 0.0, 1.0), 0.7));
      color[1] = static_cast<unsigned char>(
          255 * std::pow(std::clamp(k_i.y, 0.0, 1.0), 0.7));
      color[2] = static_cast<unsigned char>(
          255 * std::pow(std::clamp(k_i.z, 0.0, 1.0), 0.7));
      fwrite(color, 1, 3, fp);
    }
    fclose(fp);
  }
}
}  // namespace cherry
