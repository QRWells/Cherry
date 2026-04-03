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

#include <nlohmann/json.hpp>

using namespace nlohmann;
using namespace std;
namespace cherry {
namespace {
auto ToVector3d(std::vector<double> const& values) -> math::Vector3d {
  if (values.size() < 3) return {};
  return {values[0], values[1], values[2]};
}
}  // namespace

// TODO(qrwells): factories

auto RenderScriptParser::Parse(string_view script)
    -> std::unique_ptr<Renderer> {
  auto data = json::parse(script);
  auto renderer_data = data.get<RenderData>();
  return CreateRenderer(renderer_data);
}

auto CreateMaterial(MaterialData const& data) -> std::shared_ptr<Material> {
  // TODO(qrwells): implement
  return {};
}

auto CreateObject(ObjectData const& data) -> std::shared_ptr<Object> {
  // TODO(qrwells): implement
  return {};
}

auto CreateLight(LightData const& data) -> std::shared_ptr<Light> {
  // TODO(qrwells): implement
  return {};
}

auto CreateScene(SceneData const& data) -> std::shared_ptr<Scene> {
  auto camera = CreateCamera(data.camera);
  auto scene = std::make_shared<Scene>(camera);
  for (auto const& object_data : data.objects) {
    auto object = CreateObject(object_data);
    if (object) scene->Add(object);
  }
  for (auto const& light_data : data.lights) {
    auto light = CreateLight(light_data);
    if (light) scene->Add(light);
  }
  return scene;
}

auto CreateCamera(CameraData const& data) -> std::shared_ptr<Camera> {
  auto const kLookFrom = ToVector3d(data.look_from);
  auto const kLookAt = ToVector3d(data.look_at);
  auto const kUpDirection = ToVector3d(data.up_direction);

  if (data.type == CameraType::Perspective) {
    return std::make_shared<PerspectiveCamera>(
        kLookFrom, kLookAt, kUpDirection, data.fov,
        data.aspect_ratio, data.aperture, data.focal_distance);
  }
  return std::make_shared<OrthographicCamera>(
      kLookFrom, kLookAt, kUpDirection, data.fov,
      data.aspect_ratio, data.aperture, data.focal_distance);
}

auto CreateRenderer(RenderData const& data) -> std::unique_ptr<Renderer> {
  auto scene = CreateScene(data.scene_data);

  if (data.renderer == RenderType::RayTracing) {
    shared_ptr<Integrator> integrator;
    switch (data.integrator) {
      case IntegratorType::Normal:
        integrator = make_shared<NormalIntegrator>();
        break;
      case IntegratorType::MonteCarlo:
        integrator = make_shared<PathIntegrator>();
        break;
    }
    return std::make_unique<RayTracer>(scene, data.width, data.height,
                                       integrator);
  }

  return std::make_unique<Rasterizer>(scene, data.width, data.height);
}
}  // namespace cherry
