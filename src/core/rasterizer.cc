// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : rasterizer.cc
// Author      : QRWells
// Created at  : 2021/09/03 3:49
// Description :

#include "rasterizer.h"

namespace cherry {
void Rasterizer::Render() {}
void Rasterizer::SavePpm(const std::string& file_name) {
  FILE* fp = fopen((file_name + std::string(".ppm")).c_str(), "wb");
  (void)fprintf(fp, "P6\n%d %d\n255\n", width_,
                height_);
  for (const auto& kI : frame_buffer_) {
    static unsigned char color[3] = {0};
    color[0] = static_cast<unsigned char>(
        255 * std::pow(std::clamp(kI.x, 0.0, 1.0), 0.6));
    color[1] = static_cast<unsigned char>(
        255 * std::pow(std::clamp(kI.y, 0.0, 1.0), 0.6));
    color[2] = static_cast<unsigned char>(
        255 * std::pow(std::clamp(kI.z, 0.0, 1.0), 0.6));
    fwrite(color, 1, 3, fp);
  }
  fclose(fp);
}
}  // namespace cherry
