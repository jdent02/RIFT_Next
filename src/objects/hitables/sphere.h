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

#include "core/raytracing/utility_functions.h"
#include "objects/hitables/i_hitable.h"

#include <utility>

// Forward declarations
class IMaterial;
class Ray;
struct HitRecord;

inline void get_sphere_uv(const Vec3& p, float& u, float& v)
{
    float phi = std::atan2(p.z(), p.x());
    float theta = std::asin(p.y());
    u = 1.f - (phi + FLOAT_M_PI) / (2 * FLOAT_M_PI);
    v = (theta + FLOAT_M_PI / 2) / FLOAT_M_PI;
}

class Sphere final : public IHitable
{
  public:
    Sphere() = default;

    Sphere(const Vec3 cen, const float r, std::shared_ptr<IMaterial> mat)
      : m_center_(cen)
      , m_radius_(r)
      , m_material_(std::move(mat)){};

    ~Sphere() override = default;

    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

    bool bounding_box(float t0, float t1, AABB& box) const override;

    float pdf_value(const Vec3& o, const Vec3& v) const override;

    Vec3 random(const Vec3& o) const override;

  private:
    Vec3                       m_center_;
    float                      m_radius_;
    std::shared_ptr<IMaterial> m_material_;
};
