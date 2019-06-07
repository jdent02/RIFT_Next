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

#include "core/data_types/containers/scene.h"
#include "core/data_types/vec3.h"
#include "materials/diffuse_light.h"
#include "materials/lambertian.h"
#include "objects/camera/thin_lens_camera.h"
#include "objects/hitables/hitable_list.h"
#include "objects/hitables/rect.h"
#include "objects/hitables/sphere.h"
#include "textures/checker_tex.h"
#include "textures/constant_tex.h"
#include "textures/sky_gradient.h"

std::unique_ptr<Scene> SceneGenerator::make_cornell_box(const std::unique_ptr<RenderSettings>& settings)
{
    std::unique_ptr<Scene> scene;
    // Camera
    // const Vec3  lookfrom(278.f, 278.f, -800.f);
    // const Vec3  lookat(278.f, 278.f, 0.f);
    // const float dist_to_focus = (lookfrom - lookat).length();
    // const float aperture = 0.05f;

    // scene->create_cam(
    //     "thin_lens",
    //     lookfrom,
    //     lookat,
    //     Vec3(0.f, 1.f, 0.f),
    //     40.f,
    //     float(settings.m_xres) / float(settings.m_yres),
    //     aperture,
    //     dist_to_focus,
    //     0.f,
    //     0.5f);

    return scene;
}

std::unique_ptr<Scene> SceneGenerator::make_sphere(const std::unique_ptr<RenderSettings>& settings)
{
    std::unique_ptr<Scene> scene = std::make_unique<Scene>();

    std::unique_ptr<HitableList> world = std::make_unique<HitableList>();

    std::shared_ptr<ITexture> tex_1 = std::make_shared<ConstantTexture>(RGBColor(0.1f, 0.1f, 0.1f));
    std::shared_ptr<ITexture> tex_2 = std::make_shared<ConstantTexture>(RGBColor(0.8f, 0.8f, 0.8f));

    std::shared_ptr<ITexture> sphere_tex = std::make_shared<CheckerTexture>(tex_1, tex_2);

    std::shared_ptr<IMaterial> sphere_mat = std::make_shared<Lambertian>(sphere_tex);

    std::unique_ptr<IHitable> sphere = std::make_unique<Sphere>(Vec3(0.f, -1000.f, 0.f), 1000.f, sphere_mat);

    world->m_list.emplace_back(std::move(sphere));

    std::shared_ptr<ITexture> world_tex =
        std::make_shared<SkyGradient>(RGBColor(1.f, 1.f, 1.f), RGBColor(0.3f, 0.6f, 1.f));

    std::shared_ptr<IMaterial> world_mat = std::make_shared<DiffuseLight>(world_tex);

    std::unique_ptr<IHitable> world_sphere =
        std::make_unique<FlipNormals>(std::make_unique<Sphere>(Vec3(0.f, 0.f, 0.f), 1000000.f, world_mat));

    world->m_list.emplace_back(std::move(world_sphere));

    scene->set_world(std::move(world));

    const Vec3  lookfrom(0.f, 2.f, 8.f);
    const Vec3  lookat(0.f, 1.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    std::unique_ptr<ICamera> cam = std::make_unique<ThinLensCamera>(
        lookfrom,
        lookat,
        Vec3(0.f, 1.f, 0.f),
        40.f,
        float(settings->m_xres) / float(settings->m_yres),
        aperture,
        dist_to_focus,
        0.f,
        0.5f);

    scene->set_cam(std::move(cam));

    return scene;
}
