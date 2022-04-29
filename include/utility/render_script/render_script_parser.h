// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : render_script_parser.h
// Author      : QRWells
// Created at  : 2021/09/23 16:37
// Description :

#ifndef CHERRY_UTILITY_RENDER_SCRIPT_PARSER
#define CHERRY_UTILITY_RENDER_SCRIPT_PARSER

#include <memory>
#include <string_view>

#include <nlohmann/json.hpp>

#include "core/renderer.h"
#include "utility/render_script/render_data.h"

namespace cherry {
using json = nlohmann::json;
class RenderScriptParser {
 public:
  auto static Parse(std::string_view script) -> std::unique_ptr<Renderer>;
};

auto CreateMaterial(MaterialData const& data) -> std::shared_ptr<Material>;
auto CreateObject(ObjectData const& data) -> std::shared_ptr<Object>;
auto CreateScene(SceneData const& data) -> std::shared_ptr<Scene>;
auto CreateCamera(CameraData const& data) -> std::shared_ptr<Camera>;
auto CreateLight(LightData const& data) -> std::shared_ptr<Light>;
auto CreateRenderer(RenderData const& data) -> std::unique_ptr<Renderer>;

}  // namespace cherry

#endif  // !CHERRY_UTILITY_RENDER_SCRIPT_PARSER
