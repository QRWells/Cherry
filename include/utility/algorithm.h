/**
 * @file algorithm.h
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief Useful algorithms
 * @version 0.1
 * @date 2022-02-09
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#ifndef CHERRY_UTILITY_ALGORITHM
#define CHERRY_UTILITY_ALGORITHM

#include <algorithm>
#include <cmath>

#include "math/vector.h"
#include "utility/constant.h"

namespace cherry {

/**
 * @brief Convert Degree to radian
 *
 * @param deg degree
 * @return double the radian corresponding to the deg
 */
inline auto DegToRad(double const& deg) -> double { return deg * PI / 180.0; }

inline auto Interp(math::Vector3d const& x, math::Vector3d const& y,
                   double const& level) -> math::Vector3d {
  return x * (1 - level) + y * level;
}

/**
 * @brief Solving quadratic equations by given coefficients
 *
 * @param a quadratic coefficient
 * @param b linear coefficient
 * @param c constant
 * @param x0 smaller real root
 * @param x1 greater real root
 * @return true if there exist real roots
 * @return false if there is no real root
 */
inline auto SolveQuadratic(double const& a, double const& b, double const& c,
                           double& x0, double& x1) -> bool {
  auto const kDiscriminant = b * b - 4 * a * c;
  if (kDiscriminant < 0) return false;
  if (fabs(kDiscriminant) < EPSILON)
    x0 = x1 = -0.5 * b / a;
  else {
    auto const kQ = b > 0 ? -0.5 * (b + sqrt(kDiscriminant))
                          : -0.5 * (b - sqrt(kDiscriminant));
    x0 = kQ / a;
    x1 = c / kQ;
  }
  if (x0 > x1) std::swap(x0, x1);
  return true;
}

/**
 * @brief Compute the GGX distribution
 *
 * @param n normal vector
 * @param h half vector
 * @param a roughness of the material
 * @return double the pdf at the direction
 */
inline auto DistributionGGXTR(math::Vector3d const& n, math::Vector3d const& h,
                              double const& a) -> double {
  auto const&& a2 = a * a;
  auto const kNDotH = std::max(n.Dot(h), 0.0);
  auto const kNDotH2 = kNDotH * kNDotH;

  auto denominator = kNDotH2 * (a2 - 1.0) + 1.0;
  denominator = PI * denominator * denominator;

  return a2 / denominator;
}

/**
 * @brief Compute the reflectance of given material at given direction
 *
 * @param cos_theta equals Dot(v,n)
 * @param f0 base reflectance
 * @return math::Vector3d
 */
inline auto FresnelSchlick(double const& cos_theta, math::Vector3d const& f0)
    -> math::Vector3d {
  return f0 + (math::Vector3d(1.0) - f0) *
                  std::pow(std::clamp(1.0 - cos_theta, 0.0, 1.0), 5.0);
}

/**
 * @brief Geometry function using Schlick-GGX method.
 *
 * @param n_dot_v Dot(n,v)
 * @param k remapping of roughness(alpha)
 * @return double
 */
inline auto GeometrySchlickGGX(double const& n_dot_v, double const& k)
    -> double {
  auto const& nom = n_dot_v;
  auto const kDenominator = n_dot_v * (1.0 - k) + k;

  return nom / kDenominator;
}

/**
 * @brief Compute both geometry obstruction and geometry shadowing
 *        using Smith's method
 * @param n normal vector
 * @param v view vector
 * @param l light vector
 * @param k remapping of roughness(alpha)
 * @return double
 */
inline auto GeometrySmith(math::Vector3d const& n, math::Vector3d const& v,
                          math::Vector3d const& l, double const& k) -> double {
  auto const kNDotV = std::max(n.Dot(v), 0.0);
  auto const kNDotL = std::max(n.Dot(l), 0.0);
  auto const kGgx1 = GeometrySchlickGGX(kNDotV, k);
  auto const kGgx2 = GeometrySchlickGGX(kNDotL, k);

  return kGgx1 * kGgx2;
}

/**
 * @brief Compute reflect vector
 *
 * @param i incidence direction
 * @param n normal vector
 * @return math::Vector3d reflection direction
 */
inline auto Reflect(math::Vector3d const& i, math::Vector3d const& n)
    -> math::Vector3d {
  return i - 2.0 * i.Dot(n) * n;
}

/**
 * @brief Compute refraction direction using Snell's law
 * We need to handle with care the two possible situations:
 *
 *    - When the ray is inside the object
 *
 *    - When the ray is outside.
 *
 * If the ray is outside, you need to make cos(i) positive cos(i) = -n.I
 *
 * If the ray is inside, you need to invert the refractive indices and negate
 * the normal n
 * @param i incidence direction
 * @param n normal vector
 * @param ior_in ior of the material in the direction of incidence
 * @param ior_out ior of the material in the direction of refraction
 * @return math::Vector3d the refraction direction
 */
inline auto Refract(math::Vector3d const& i, math::Vector3d const& n,
                    double const& ior_in, double const& ior_out)
    -> math::Vector3d {
  auto cos_i = std::clamp(i.Dot(n), -1.0, 1.0);
  auto eta_i = ior_in;
  auto eta_t = ior_out;
  math::Vector3d norm = n;
  if (cos_i < 0)
    cos_i = -cos_i;
  else {
    std::swap(eta_i, eta_t);
    norm = -norm;
  }
  auto const kEta = eta_i / eta_t;
  auto const k_ = 1 - kEta * kEta * (1 - cos_i * cos_i);
  if (k_ < 0) return {};
  return kEta * i + (kEta * cos_i - sqrt(k_)) * norm;
}

/**
 * @brief Compute Fresnel equation.
 * As a consequence of the conservation of energy, transmittance is given by:
 * kt = 1 - kr;
 * @param i the incident view direction
 * @param n the normal at the intersection point
 * @param in_ior the refractive index of the material the ray refract from.
 * @param out_ior the refractive index of the material the ray refract into.
 * @return kr the Fresnel component
 */
inline auto Fresnel(math::Vector3d const& i, math::Vector3d const& n,
                    double const& in_ior, double const& out_ior) -> double {
  auto cos_i = std::clamp(i.Dot(n), -1.0, 1.0);
  auto eta_i(in_ior);
  auto eta_t(out_ior);
  if (cos_i > 0) std::swap(eta_i, eta_t);
  // Total internal reflection
  auto const kSinT =
      eta_i / eta_t * std::sqrt(std::max(0.0, 1 - cos_i * cos_i));
  if (kSinT >= 1) [[unlikely]]
    return 1;

  double const kCosT = sqrt(std::max(0.0, 1 - kSinT * kSinT));
  cos_i = std::fabs(cos_i);
  double const kRs =
      (eta_t * cos_i - eta_i * kCosT) / (eta_t * cos_i + eta_i * kCosT);
  double const kRp =
      (eta_i * cos_i - eta_t * kCosT) / (eta_i * cos_i + eta_t * kCosT);
  return (kRs * kRs + kRp * kRp) / 2;
}

inline auto CookTorrance(math::Vector3d const& wi, math::Vector3d const& wo,
                         math::Vector3d const& n, double const& roughness,
                         math::Vector3d const& f0) -> math::Vector3d {
  auto const kV = -wi;
  auto const kL = wo;
  auto const kH = (kV + kL).Normalized();

  auto const kDotNl = n.Dot(kL);
  auto const kDotNv = n.Dot(kV);
  auto const kDotHv = kH.Dot(kV);

  // Fresnel term
  auto const kF = FresnelSchlick(kDotHv, f0);

  // Geometry(shadowing-masking term) GGX
  auto const k_ = std::pow(roughness + 1.0, 2.0) * 0.125;
  auto const kG = GeometrySmith(n, kV, kL, k_);

  // Distribution of normals GGX
  auto const kAlpha = std::pow(roughness, 2.0);
  auto const kD = DistributionGGXTR(n, kH, kAlpha);

  auto const&& result = kF * kG * kD / (kDotNl * kDotNv * 4.0);
  return result;
}

inline auto CookTorrance(math::Vector3d const& wi, math::Vector3d const& wo,
                         math::Vector3d const& n, double const& roughness,
                         double const& in_ior, double const& out_ior)
    -> double {
  auto const kV = -wi.Normalized();
  auto const kL = wo;
  auto const kH = (kV + kL).Normalized();

  auto const kDotNl = n.Dot(kL);
  auto const kDotNv = n.Dot(kV);

  // Fresnel term
  auto const kF = Fresnel(wi, n, in_ior, out_ior);

  // Geometry(shadowing-masking term) GGX
  auto const k_ = std::pow(roughness + 1.0, 2.0) * 0.125;
  auto const kG = GeometrySmith(n, kV, kL, k_);

  // Distribution of normals GGX
  auto const kAlpha = std::pow(roughness, 2.0);
  auto const kD = DistributionGGXTR(n, kH, kAlpha);

  auto const&& result = kF * kG * kD / (kDotNl * kDotNv * 4.0);
  return result;
}

inline void GenerateOrthonormalBasis(math::Vector3d const& n,
                                     math::Vector3d& t_x, math::Vector3d& t_y) {
  if (std::abs(n.x) > std::abs(n.y)) {
    auto const kInvNorm = 1.0 / std::sqrt(n.x * n.x + n.z * n.z);
    t_y = math::Vector3d(n.z * kInvNorm, 0, -n.x * kInvNorm);
  } else {
    auto const kInvNorm = 1.0 / std::sqrt(n.y * n.y + n.z * n.z);
    t_y = math::Vector3d(0, n.z * kInvNorm, -n.y * kInvNorm);
  }
  t_x = t_y.Cross(n).Normalized();
}
}  // namespace cherry

#endif  // !CHERRY_UTILITY_ALGORITHM
