// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : mesh.cc
// Author      : QRWells
// Created at  : 2021/08/31 23:52
// Description :

#include "object/mesh.h"

namespace cherry {

void Mesh::LoadObj(std::string const&) {}
auto Mesh::GetBounds() -> Box { return bounding_box; }
auto Mesh::Intersect(Ray const&, Intersection&) const -> bool { return false; }
void Mesh::Sample(Intersection&, double&) {}
auto Mesh::HasEmission() const -> bool { return false; }
auto Mesh::GetSurfaceArea() const -> double { return 0.0; }
}  // namespace cherry
