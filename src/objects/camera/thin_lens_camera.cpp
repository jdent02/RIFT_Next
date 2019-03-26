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

#include "thin_lens_camera.h"

#include "utility/math_functions/utility_functions.h"

struct ThinLensCamera::Impl
{
    CameraSettings settings;
};

ThinLensCamera::~ThinLensCamera()
{
    delete m_impl_;
}

ThinLensCamera::ThinLensCamera(
    const Vec3  lookfrom,
    const Vec3  lookat,
    const Vec3  vup,
    const float vfov,
    const float aspect,
    const float aperture,
    const float focus_dist,
    const float t0,
    const float t1)
  : m_impl_(new Impl)
{
    m_impl_->settings.m_origin = lookfrom;
    m_impl_->settings.m_lens_radius = aperture / 2.f;
    m_impl_->settings.m_time0 = t0;
    m_impl_->settings.m_time1 = t1;
    const float theta = vfov * FLOAT_M_PI / 180.f;
    const float half_height = std::tan(theta / 2.f);
    const float half_width = aspect * half_height;

    m_impl_->settings.m_w = unit_vector(lookfrom - lookat);
    m_impl_->settings.m_u = unit_vector(cross(vup, m_impl_->settings.m_w));
    m_impl_->settings.m_v = cross(m_impl_->settings.m_w, m_impl_->settings.m_u);
    m_impl_->settings.m_lower_left_corner =
        m_impl_->settings.m_origin -
        half_width * focus_dist * m_impl_->settings.m_u -
        half_height * focus_dist * m_impl_->settings.m_v -
        focus_dist * m_impl_->settings.m_w;
    m_impl_->settings.m_horizontal =
        2 * half_width * focus_dist * m_impl_->settings.m_u;
    m_impl_->settings.m_vertical =
        2 * half_height * focus_dist * m_impl_->settings.m_v;
}

Ray ThinLensCamera::get_ray(const float s, const float t) const
{
    Vec3       rd = m_impl_->settings.m_lens_radius * random_in_unit_disk();
    const Vec3 offset =
        m_impl_->settings.m_u * rd.x() + m_impl_->settings.m_v * rd.y();
    const float time =
        m_impl_->settings.m_time0 +
        rand() * INV_RAND_MAX *
            (m_impl_->settings.m_time1 - m_impl_->settings.m_time0);
    return {m_impl_->settings.m_origin + offset,
            m_impl_->settings.m_lower_left_corner +
                s * m_impl_->settings.m_horizontal +
                t * m_impl_->settings.m_vertical - m_impl_->settings.m_origin -
                offset,
            time};
}

CameraSettings& ThinLensCamera::get_cam_settings() const
{
    return m_impl_->settings;
}
