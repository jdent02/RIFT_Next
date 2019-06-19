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

#include "core/raytracing/aabb.h"
#include "objects/hitables/i_hitable.h"
#include "utilities/containers/records/hit_record.h"

#include <vector>

class HitableList : public IHitable
{
  public:
    HitableList() = default;
    ~HitableList() = default;

    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

    bool bounding_box(float t0, float t1, AABB& box) const override;

    std::vector<std::unique_ptr<IHitable>> m_list;
};

inline bool HitableList::hit(const Ray& r, const float t_min, const float t_max, HitRecord& rec) const
{
    HitRecord temp_rec;
    bool      hit_anything = false;
    float     closest_so_far = t_max;
    for (const auto& hitable : m_list)
    {
        if (hitable->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.m_t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

inline bool HitableList::bounding_box(const float t0, const float t1, AABB& box) const
{
    if (m_list.empty())
    {
        return false;
    }
    AABB       temp_box;
    const bool first_true = m_list.at(0)->bounding_box(t0, t1, temp_box);
    if (!first_true)
    {
        return false;
    }

    box = temp_box;

    for (auto& hitable : m_list)
    {
        if (hitable->bounding_box(t0, t1, temp_box))
        {
            box = surrounding_box(box, temp_box);
        }
        else
        {
            return false;
        }
    }
    return true;
}
