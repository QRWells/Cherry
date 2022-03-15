/**
 * @file constant.h
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief Constants
 * @version 0.1
 * @date 2022-02-09
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#ifndef CHERRY_UTILITY_CONSTANT
#define CHERRY_UTILITY_CONSTANT

namespace cherry {
constexpr double PI = 3.14159265358979323846;
constexpr double PI_OVER_2 = PI / 2.0;
constexpr double PI_OVER_4 = PI / 4.0;
constexpr double PI_TIMES_2 = PI * 2.0;
constexpr double PI_TIMES_4 = PI * 4.0;
constexpr double PI_INV = 1 / PI;
constexpr double PI_TIMES_2_INV = 0.5 / PI;
constexpr double PI_TIMES_4_INV = 0.25 / PI;
constexpr double SQRT_PI = 1.77245385090551602729816748334;
constexpr double SQRT_INV_PI = 0.564189583547756286948079451561;
constexpr double SQRT2_INV_PI = 0.797884560802865355879892119869;
constexpr double EPSILON = 1e-5;
constexpr double INF = 1.7976931348623157e+308;
}  // namespace cherry

#endif  // !CHERRY_UTILITY_CONSTANT
