#include "directional_light.h"

#include "../utility/random.h"
namespace cherry {
void DirectionalLight::Sample(Intersection& intersection, double& p) {
  auto const kX = 1 - GetRandomDouble() * 2;
  auto const kY = 1 - GetRandomDouble() * 2;
  auto const kDir = direction + kX * tangent_x + kY * tangent_y;
  intersection.coordinate = shoot_from;
  intersection.shading_point =
      ShadingPoint(kDir.Normalized(), tangent_x, tangent_y);
  intersection.normal = kDir.Normalized();
  p = this->pdf;
}
}  // namespace cherry
