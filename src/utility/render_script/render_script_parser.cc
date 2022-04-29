#include "utility/render_script/render_script_parser.h"

#include "core/integrator.h"
#include "core/rasterizer.h"
#include "core/ray_tracer.h"
#include "integrator/normal_integrator.h"
#include "integrator/path_integrator.h"
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
    -> std::unique_ptr<Renderer> {
  auto data = json::parse(script);
  auto renderer_data = data.get<RenderData>();
  return CreateRenderer(renderer_data);
}

auto CreateMaterial(MaterialData const& data) -> std::shared_ptr<Material> {
  // TODO(qrwells): implement
}

auto CreateObject(ObjectData const& data) -> std::shared_ptr<Object> {
  // TODO(qrwells): implement
}

auto CreateLight(LightData const& data) -> std::shared_ptr<Light> {
  // TODO(qrwells): implement
}

auto CreateScene(SceneData const& data) -> std::shared_ptr<Scene> {
  auto camera = CreateCamera(data.camera);
  auto scene = std::make_shared<Scene>(camera);
  for (auto const& object_data : data.objects) {
    auto object = CreateObject(object_data);
    scene->Add(object);
  }
  for (auto const& light_data : data.lights) {
    auto light = CreateLight(light_data);
    scene->Add(light);
  }
  return scene;
}

auto CreateCamera(CameraData const& data) -> std::shared_ptr<Camera> {
  if (data.type == CameraType::Perspective) {
    return std::make_shared<PerspectiveCamera>(
        data.look_from, data.look_at, data.up_direction, data.fov,
        data.aspect_ratio, data.aperture, data.focal_distance);
  }
  return std::make_shared<OrthographicCamera>(
      data.look_from, data.look_at, data.up_direction, data.fov,
      data.aspect_ratio, data.aperture, data.focal_distance);
}

auto CreateRenderer(RenderData const& data) -> std::unique_ptr<Renderer> {
  auto scene = CreateScene(data.scene_data);

  if (data.renderer == RenderType::RayTracing) {
    shared_ptr<Integrator> integrator;
    switch (data.integrator) {
      case IntegratorType::Normal:
        integrator = make_shared<NormalIntegrator>();
      case IntegratorType::MonteCarlo:
        integrator = make_shared<PathIntegrator>();
    }
    return std::make_unique<RayTracer>(scene, data.width, data.height,
                                       integrator);
  }

  return std::make_unique<Rasterizer>(scene, data.width, data.height);
}
}  // namespace cherry
