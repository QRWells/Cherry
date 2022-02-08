
#ifndef CHERRY_CORE_INTEGRATOR
#define CHERRY_CORE_INTEGRATOR

#include "../common/ray.h"
#include "../math/vector.h"
#include "scene.h"

namespace cherry {
class Integrator {
 public:
  Integrator() = default;
  Integrator(const Integrator&) = delete;
  Integrator(Integrator&&) = delete;

  auto operator=(const Integrator&) -> Integrator& = delete;
  auto operator=(Integrator&&) -> Integrator& = delete;

  virtual ~Integrator() = default;
  virtual auto Li(const Ray& ray, const std::shared_ptr<Scene>& scene)
      -> math::Point3 = 0;
};
}  // namespace cherry

#endif  // !CHERRY_CORE_INTEGRATOR
