// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : renderer.cpp
// Author      : QRWells
// Created at  : 2021/09/23 16:45
// Description :

#include "core/renderer.h"
#include <fmt/core.h>
#include <fstream>
#include <ios>

namespace cherry {

Renderer::Renderer(std::shared_ptr<Scene> scene, const uint64_t& width,
                   const uint64_t& height)
    : frame_buffer(height * width),
      width(width),
      height(height),
      scene(std::move(scene)) {}

void Renderer::SavePpm(const std::string& file_name) const {
  using namespace std;

  ofstream file(file_name + ".ppm", ios_base::binary | ios_base::out);

  if (!file.is_open())
    fmt::print(stderr, "Unable to write to file: {}\n", file_name + ".ppm");

  auto header = fmt::format("P6\n{} {}\n255\n", width, height);
  file << header;

  for (const auto& k_i : frame_buffer) {
    static array<char, 3> color;
    color[0] =
        static_cast<char>(255 * std::pow(std::clamp(k_i.x, 0.0, 1.0), 0.6));
    color[1] =
        static_cast<char>(255 * std::pow(std::clamp(k_i.y, 0.0, 1.0), 0.6));
    color[2] =
        static_cast<char>(255 * std::pow(std::clamp(k_i.z, 0.0, 1.0), 0.6));
    file.write(color.data(), 3);
  }

  file.close();
}
}  // namespace cherry
