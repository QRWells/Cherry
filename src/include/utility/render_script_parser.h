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

#include "../core/renderer.h"

namespace cherry {
class RenderScriptLexer {
 public:
  explicit RenderScriptLexer(std::string_view const& str) : source_(str) {}
  auto Lex() -> std::vector<uint64_t>;

 private:
  std::string source_;
  std::vector<uint64_t> codes_;
};

class RenderScriptParser {
 public:
  explicit RenderScriptParser(const RenderScriptLexer& lexer) {}
  explicit RenderScriptParser(const std::vector<uint64_t>& codes) {}
  auto Parse() -> std::shared_ptr<Renderer> const&;
};
}  // namespace cherry

#endif  // !CHERRY_UTILITY_RENDER_SCRIPT_PARSER
