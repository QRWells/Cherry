#ifndef CHERRY_LIGHT_DIRECTIONAL_LIGHT
#define CHERRY_LIGHT_DIRECTIONAL_LIGHT

#include "../core/light.h"

namespace cherry {
struct DirectionalLight final : public Light {
  explicit DirectionalLight(const math::Vector3d& position,
                            const math::Vector3d& at, const double& r,
                            const double& _intensity)
      : Light(_intensity),
        shoot_from_(position),
        direction_(at - position),
        radius_(r) {
    GenerateOrthonormalBasis(direction_, tangent_x_, tangent_y_);
    tangent_x_ *= radius_;
    tangent_y_ *= radius_;
    auto const kR = std::sqrt(radius_ * radius_ + direction_.Norm2());
    auto const kH = kR - direction_.Norm();
    pdf_ = 1.0 / (kR * kH * PI_TIMES_2_INV);
  }

  void Sample(Intersection&, double&) override;

 private:
  math::Vector3d shoot_from_;
  math::Vector3d direction_;
  math::Vector3d tangent_x_;
  math::Vector3d tangent_y_;
  double radius_;
  double pdf_;
};
}  // namespace cherry

#endif  // !CHERRY_LIGHT_DIRECTIONAL_LIGHT
