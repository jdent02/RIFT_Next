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

#include "scene_generator.h"

#include "utility/containers/scene.h"

void SceneGenerator::make_cornell_box(Scene* scene, RenderSettings& settings)
{
    scene->get_texture_store().add_texture(
        "red_tex",
        "constant_texture",
        ParamArray().add_entry("albedo", "0.78 0.78 0.78"));

    // Camera
    const Vec3  lookfrom(278.f, 278.f, -800.f);
    const Vec3  lookat(278.f, 278.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    scene->create_cam(
        "thin_lens",
        lookfrom,
        lookat,
        Vec3(0.f, 1.f, 0.f),
        40.f,
        float(settings.m_xres) / float(settings.m_yres),
        aperture,
        dist_to_focus,
        0.f,
        0.5f);
}