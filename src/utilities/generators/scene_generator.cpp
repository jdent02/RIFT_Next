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
#include "materials/dielectric.h"
#include "materials/diffuse_light.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "objects/camera/thin_lens_camera.h"
#include "objects/hitables/hitable_list.h"
#include "objects/hitables/rect.h"
#include "objects/hitables/sphere.h"
#include "textures/checker_tex.h"
#include "textures/constant_tex.h"
#include "textures/sky_gradient.h"
#include "objects/hitables/instancers.h"
#include "objects/hitables/box.h"

std::unique_ptr<Scene> SceneGenerator::make_cornell_box(const std::unique_ptr<RenderSettings>& settings)
{
    std::unique_ptr<Scene> scene = std::make_unique<Scene>();

    std::unique_ptr<HitableList> world = std::make_unique<HitableList>();

    std::shared_ptr<IMaterial> red_mat =
        std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(RGBColor(0.65f, 0.05f, 0.05f)));

    std::shared_ptr<IMaterial> green_mat =
        std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(RGBColor(0.12f, 0.45f, 0.15f)));

    std::shared_ptr<IMaterial> white_mat =
        std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(RGBColor(0.73f, 0.73f, 0.73f)));

    std::shared_ptr<IMaterial> white_lamp =
        std::make_shared<DiffuseLight>(std::make_shared<ConstantTexture>(RGBColor(15.f, 15.f, 15.f)));

    world->m_list.emplace_back(std::make_unique<FlipNormals>(std::make_unique<YZRect>(0.f, 555.f, 0.f, 555.f, 555.f, green_mat)));

    world->m_list.emplace_back(std::make_unique<YZRect>(0.f, 555.f, 0.f, 555.f, 0.f, red_mat));
    
    world->m_list.emplace_back(
        std::make_unique<FlipNormals>(std::make_unique<XZRect>(213.f, 343.f, 227.f, 332.f, 554.f, white_lamp)));
    
    world->m_list.emplace_back(std::make_unique<FlipNormals>(std::make_unique<XZRect>(0.f, 555.f, 0.f, 555.f, 555.f, white_mat)));
    
    world->m_list.emplace_back(std::make_unique<XZRect>(0.f, 555.f, 0.f, 555.f, 0.f, white_mat));
    
    world->m_list.emplace_back(std::make_unique<FlipNormals>(std::make_unique<XYRect>(0.f, 555.f, 0.f, 555.f, 555.f, white_mat)));

    world->m_list.emplace_back(std::make_unique<Translate>(std::make_unique<RotateY>(
        std::make_unique<Box>(Vec3(0.f, 0.f, 0.f), Vec3(165.f, 165.f, 165.f), white_mat), -18.f), Vec3(130.f, 0.f, 65.f)));

    world->m_list.emplace_back(std::make_unique<Translate>(
        std::make_unique<RotateY>(std::make_unique<Box>(Vec3(0.f, 0.f, 0.f), Vec3(165.f, 330.f, 165.f), white_mat), 15.f),
        Vec3(265.f, 0.f, 295.f)));

    scene->set_lights(std::make_unique<XZRect>(213.f, 343.f, 227.f, 332.f, 554.f, nullptr));

    scene->set_world(std::move(world));

    const Vec3  lookfrom(278.f, 278.f, -800.f);
    const Vec3  lookat(278.f, 278.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    scene->set_cam(std::make_unique<ThinLensCamera>(
        lookfrom,
        lookat,
        Vec3(0.f, 1.f, 0.f),
        40.f,
        float(settings->m_xres) / float(settings->m_yres),
        aperture,
        dist_to_focus,
        0.f,
        0.5f));

    return scene;
}

std::unique_ptr<Scene> SceneGenerator::make_sphere(const std::unique_ptr<RenderSettings>& settings)
{
    std::unique_ptr<Scene> scene = std::make_unique<Scene>();

    std::unique_ptr<HitableList> world = std::make_unique<HitableList>();

    world->m_list.emplace_back(std::make_unique<Sphere>(
        Vec3(0.f, -1000.f, 0.f),
        1000.f,
        std::make_shared<Lambertian>(std::make_shared<CheckerTexture>(
            std::make_shared<ConstantTexture>(RGBColor(0.1f, 0.1f, 0.1f)),
            std::make_shared<ConstantTexture>(RGBColor(0.8f, 0.8f, 0.8f))))));

    world->m_list.emplace_back(std::make_unique<Sphere>(Vec3(0.f, 1.f, 0.f), 1.f, std::make_shared<Dielectric>(1.5f)));

    world->m_list.emplace_back(
        std::make_unique<Sphere>(Vec3(1.f, 1.f, 2.f), 1.f, std::make_shared<Metal>(RGBColor(0.7f, 0.6f, 0.5f), 0.03f)));

    world->m_list.emplace_back(std::make_unique<Sphere>(
        Vec3(-1.f, 1.f, -2.f),
        1.f,
        std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(RGBColor(0.4f, 0.2f, 0.1f)))));

    world->m_list.emplace_back(std::make_unique<FlipNormals>(std::make_unique<Sphere>(
        Vec3(0.f, 0.f, 0.f),
        1000000.f,
        std::make_shared<DiffuseLight>(
            std::make_shared<SkyGradient>(RGBColor(1.f, 1.f, 1.f), RGBColor(0.3f, 0.6f, 1.f))))));

    scene->set_world(std::move(world));

    const Vec3  lookfrom(0.f, 2.f, 8.f);
    const Vec3  lookat(0.f, 1.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    scene->set_cam(std::make_unique<ThinLensCamera>(
        lookfrom,
        lookat,
        Vec3(0.f, 1.f, 0.f),
        40.f,
        float(settings->m_xres) / float(settings->m_yres),
        aperture,
        dist_to_focus,
        0.f,
        0.5f));

    return scene;
}
