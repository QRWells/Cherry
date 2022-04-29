#include "utility/render_script/render_data.h"

#include "magic_enum.hpp"

using namespace std;

namespace cherry {
void from_json(const nlohmann::json& j, CameraData& p) {
  p.type = magic_enum::enum_cast<CameraType>(j["type"].get<string>())
               .value_or(CameraType::Perspective);
  p.look_from = j["look_from"].get<vector<double>>();
  p.look_at = j["look_at"].get<vector<double>>();
  p.up_direction = j["up"].get<vector<double>>();
  p.aspect_ratio = j["aspect_ratio"].get<double>();
  p.fov = j["fov"].get<double>();
  p.aperture = j["aperture"].get<double>();
  p.focal_distance = j["focal_distance"].get<double>();
}

void from_json(const nlohmann::json& j, ObjectData& p) {
  p.primitive = magic_enum::enum_cast<Primitive>(j["primitive"].get<string>())
                    .value_or(Primitive::Cuboid);
  p.position = j["position"].get<vector<double>>();
}

void from_json(const nlohmann::json& j, LightData& p) {
  p.type = magic_enum::enum_cast<LightType>(j["type"].get<string>())
               .value_or(LightType::Area);
  p.position = j["position"].get<vector<double>>();
}

void from_json(const nlohmann::json& j, SceneData& p) {
  p.camera = j["camera"].get<CameraData>();
  p.objects = j["objects"].get<vector<ObjectData>>();
  p.lights = j["lights"].get<vector<LightData>>();
}

void from_json(const nlohmann::json& j, MaterialData& p) {
  p.name = j["name"].get<string>();
  p.type = magic_enum::enum_cast<MaterialType>(j["type"].get<string>())
               .value_or(MaterialType::Reflect);
}

void from_json(const nlohmann::json& j, RenderData& p) {
  p.name = j["name"].get<string>();
  p.width = j["width"].get<uint32>();
  p.height = j["height"].get<uint32>();
  p.renderer = magic_enum::enum_cast<RenderType>(j["renderer"].get<string>())
                   .value_or(RenderType::RayTracing);
  p.integrator =
      magic_enum::enum_cast<IntegratorType>(j["integrator"].get<string>())
          .value_or(IntegratorType::Normal);
  p.materials = j["materials"].get<vector<MaterialData>>();
  p.scene_data = j["scene_data"].get<SceneData>();
}
}  // namespace cherry