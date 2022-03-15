#pragma once
#ifndef CHERRY_COMMON_BOX
#define CHERRY_COMMON_BOX

#include "math/vector.h"

namespace cherry {
struct BsdfInfo {
  math::Vector3d wi;
  math::Vector3d wo;
  math::Vector3d n;
  double eta{};
};
}  // namespace cherry
#endif