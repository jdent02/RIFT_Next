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

#include "utilities/containers/records/hit_record.h"
#include "utilities/containers/records/scatter_record.h"
#include "utilities/data_structures/rgb_color.h"

class IMaterial
{
  public:
    IMaterial() = default;
    virtual ~IMaterial() = default;

    /// Scatter is called for every ray hit point.
    virtual bool scatter(const Ray& r_in, const HitRecord& hrec, ScatterRecord& srec) const { return false; }

    /// Scatter weight is used to determine the contribution of a BSDF sample on a scattering object.
    virtual float scatter_weight(const Ray& r_in, const HitRecord& hrec, const Ray& scattered) const { return false; }

    virtual RGBColor emission(const Ray& r_in, const HitRecord& rec, float u, float v, const Vec3& p) const
    {
        return RGBColor(0.f, 0.f, 0.f);
    }
};
