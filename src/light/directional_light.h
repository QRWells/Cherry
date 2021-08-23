#ifndef CHERRY_LIGHT_DIRECTIONAL_LIGHT
#define CHERRY_LIGHT_DIRECTIONAL_LIGHT

#include "../core/light.h"

namespace cherry {
struct DirectionalLight final : public Light {
  explicit DirectionalLight(const math::Vector3d& position,
                            const math::Vector3d& at, const double& r,
                            const double& _intensity)
      : Light(_intensity),
        shoot_from(position),
        direction(at - position),
        radius(r) {
    GenerateOrthonormalBasis(direction, tangent_x, tangent_y);
    tangent_x *= radius;
    tangent_y *= radius;
    auto const kR = std::sqrt(radius * radius + direction.Norm2());
    auto const kH = kR - direction.Norm();
    pdf = 1.0 / (kR * kH * k2Pi);
  }

  void Sample(Intersection&, double&) override;

 private:
  math::Vector3d shoot_from;
  math::Vector3d direction;
  math::Vector3d tangent_x;
  math::Vector3d tangent_y;
  double radius;
  double pdf;
};
}  // namespace cherry

#endif  // !CHERRY_LIGHT_DIRECTIONAL_LIGHT
