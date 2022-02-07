#include "directional_light.h"

#include "../utility/random.h"
namespace cherry {
void DirectionalLight::Sample(Intersection& intersection, double& p) {
  auto const kX = 1 - GetRandomDouble() * 2;
  auto const kY = 1 - GetRandomDouble() * 2;
  auto const kDir = direction_ + kX * tangent_x_ + kY * tangent_y_;
  intersection.coordinate = shoot_from_;
  intersection.shading_point =
      ShadingPoint(kDir.Normalized(), tangent_x_, tangent_y_);
  intersection.normal = kDir.Normalized();
  p = this->pdf_;
}
}  // namespace cherry
