#include "utility/render_script/render_script_parser.h"
#include "utility/render_script/render_data.h"

#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <magic_enum.hpp>
#include <nlohmann/json.hpp>

using namespace nlohmann;
using namespace std;
namespace cherry {
// TODO(qrwells): factories

auto RenderScriptParser::Parse(string_view script)
    -> std::shared_ptr<Renderer> const& {
  auto data = json::parse(script);
  auto renderer_data = data.get<RenderData>();
  return CreateRenderer(renderer_data);
}
}  // namespace cherry
