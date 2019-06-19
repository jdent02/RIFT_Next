// Released under MIT License

// Copyright (c) 2018 Jonathan Dent.

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "utilities/data_structures/rgb_color.h"

#include <memory>

class IHitable;
class Ray;
class Vec3;

enum IntegratorEnum
{
    PATH_TRACING,
    LIGHT_SAMPLE_PATH_TRACING,
    DIRECT_LIGHTING
};

class ILightIntegrator
{
  public:
    virtual ~ILightIntegrator() = default;

    virtual RGBColor trace(
        const Ray&                       r,
        const std::unique_ptr<IHitable>& world,
        const std::unique_ptr<IHitable>& light_shape,
        int                              depth) const = 0;
};

class ILightIntegratorFactory
{
  public:
    ILightIntegratorFactory() = default;

    virtual ~ILightIntegratorFactory() = default;

    virtual std::unique_ptr<ILightIntegrator> create() = 0;
};
