#include "render_script_parser.h"

namespace cherry {
auto RenderScriptLexer::Lex() -> std::vector<uint64_t> { return {}; }
auto RenderScriptParser::Parse() -> std::shared_ptr<Renderer> const& {
  return nullptr;
}
}  // namespace cherry
