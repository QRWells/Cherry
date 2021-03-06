#include "object/primitive/triangle.h"

#include "core/material.h"
#include "utility/constant.h"
#include "utility/random.h"

namespace cherry {
auto Triangle::Intersect(const Ray& ray, Intersection& intersection) const
    -> bool {
  if (normal_.Dot(ray.direction) > 0) return false;
  auto const kPVec = ray.direction.Cross(e2_);
  auto const kDet = e1_.Dot(kPVec);
  if (fabs(kDet) < EPSILON) return false;

  auto const kDetInv = 1.0 / kDet;
  auto const kTVec = ray.origin - v0_;
  double const kU = kTVec.Dot(kPVec) * kDetInv;
  if (kU < 0 || kU > 1) return false;
  auto const kQVec = kTVec.Cross(e1_);
  if (double const kV = ray.direction.Dot(kQVec) * kDetInv;
      kV < 0 || kU + kV > 1)
    return false;
  double const kTTmp = e2_.Dot(kQVec) * kDetInv;

  if (kTTmp < 0) return false;

  intersection.coordinate = ray(kTTmp);
  intersection.distance = kTTmp;
  intersection.material = material_;
  intersection.normal = normal_;

  return true;
}
auto Triangle::GetBounds() -> Box {
  auto const kMin1 = math::Min(v0_, v1_);
  auto min = math::Min(kMin1, v2_);
  auto const kMax1 = math::Max(v0_, v1_);
  auto max = math::Max(kMax1, v2_);
  return {min, max};
}
void Triangle::Sample(Intersection& intersection, double& pdf) {
  auto const kX = std::sqrt(GetRandomDouble());
  auto const kY = GetRandomDouble();
  intersection.coordinate =
      v0_ * (1.0 - kX) + v1_ * (kX * (1.0 - kY)) + v2_ * (kX * kY);
  intersection.normal = this->normal_;
  intersection.material = material_;
  pdf = 1.0 / GetSurfaceArea();
}
auto Triangle::HasEmission() const -> bool {
  return material_->GetEmission().Norm2() > EPSILON;
}
auto Triangle::GetSurfaceArea() const -> double {
  auto const kE1 = v1_ - v0_;
  auto const kE2 = v2_ - v0_;
  return kE1.Cross(kE2).Norm() * 0.5;
}
}  // namespace cherry
