/**
 * @file normal_integrator.h
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief
 * @version 0.1
 * @date 2022-02-06
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#ifndef CHERRY_INTEGRATOR_NORMAL_INTEGRATOR
#define CHERRY_INTEGRATOR_NORMAL_INTEGRATOR

#include "../core/integrator.h"

namespace cherry {
class NormalIntegrator final : public Integrator {
 public:
  auto Li(const Ray& ray, const std::shared_ptr<Scene>& scene)
      -> math::Point3 override;
};
}  // namespace cherry
#endif  //! CHERRY_INTEGRATOR_NORMAL_INTEGRATOR
