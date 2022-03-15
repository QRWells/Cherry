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

#include <nlohmann/json.hpp>

#include "core/renderer.h"

using json = nlohmann::json;

namespace cherry {
class RenderScriptParser {
 public:
  explicit RenderScriptParser(const json& lexer) {}
  explicit RenderScriptParser(const std::vector<uint64_t>& codes) {}
  auto Parse() -> std::shared_ptr<Renderer> const&;
};
}  // namespace cherry

#endif  // !CHERRY_UTILITY_RENDER_SCRIPT_PARSER
