
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

  Integrator& operator=(const Integrator&) = delete;
  Integrator& operator=(Integrator&&) = delete;

  virtual ~Integrator() = default;
  virtual math::Point3 Li(const Ray& ray,
                          const std::shared_ptr<Scene>& scene) = 0;
};
}  // namespace cherry

#endif  // !CHERRY_CORE_INTEGRATOR
