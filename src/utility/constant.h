// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
// 
// This file is part of Project Cherry.
// File Name   : constant.h
// Author      : QRWells
// Created at  : 2021/08/24 5:53
// Description :

#ifndef CHERRY_UTILITY_CONSTANT
#define CHERRY_UTILITY_CONSTANT

#include <limits>

namespace cherry {
constexpr double kPi = 3.14159265358979323846;
constexpr double k2Pi = kPi * 2.0;
constexpr double k4Pi = kPi * 4.0;
constexpr double kPiInv = 1 / kPi;
constexpr double k2PiInv = 0.5 / kPi;
constexpr double kSqrtPi = 1.77245385090551602729816748334;
constexpr double kSqrtInvPi = 0.564189583547756286948079451561;
constexpr double kSqrt2InvPi = 0.797884560802865355879892119869;
constexpr double kInfinity = std::numeric_limits<double>::max();
constexpr double kEpsilon = 1e-5;
}  // namespace cherry

#endif  // !CHERRY_UTILITY_CONSTANT
