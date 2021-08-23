// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : mesh.cc
// Author      : QRWells
// Created at  : 2021/08/31 23:52
// Description :

#include "mesh.h"

namespace cherry {

void Mesh::LoadObj(std::string const&) {}
Box Mesh::GetBounds() { return bounding_box_; }
bool Mesh::Intersect(Ray const&, Intersection&) const { return false; }
void Mesh::Sample(Intersection&, double&) {}
bool Mesh::HasEmission() const { return false; }
double Mesh::GetSurfaceArea() const { return 0.0; }
}  // namespace cherry
