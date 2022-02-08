#include "integrator/normal_integrator.h"

using namespace cherry::math;
namespace cherry {
auto NormalIntegrator::Li(const Ray& ray, const std::shared_ptr<Scene>& scene)
    -> Point3 {
  if (Intersection intersection; scene->Intersect(ray, intersection))
    return intersection.normal.Abs();
  return {};
}
}  // namespace cherry
