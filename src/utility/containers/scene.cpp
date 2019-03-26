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

#include "scene.h"

#include "objects/camera/i_camera.h"
#include "objects/camera/thin_lens_camera.h"
#include "objects/hitables/i_hitable.h"
#include "texture_store.h"

#include <memory>
#include <unordered_map>

struct Scene::Impl
{
    std::unique_ptr<ICamera>  m_cam;
    std::unique_ptr<IHitable> m_world;
    std::unique_ptr<IHitable> m_lights{nullptr};
    TextureStore              m_textures;
};

Scene::Scene()
  : m_impl_(new Impl)
{}

Scene::~Scene()
{
    delete m_impl_;
}

ICamera* Scene::create_cam(
    const char* model,
    const Vec3  lookfrom,
    const Vec3  lookat,
    const Vec3  vup,
    const float vfov,
    const float aspect,
    const float t0,
    const float t1,
    const float aperture,
    const float focus_dist) const
{
    if (strcmp(model, "thin_lens") != 0)
    {
        m_impl_->m_cam = std::make_unique<ThinLensCamera>(
            lookfrom, lookat, vup, vfov, aspect, aperture, focus_dist, t0, t1);
    }

    return m_impl_->m_cam.get();
}

ICamera* Scene::get_cam() const
{
    return m_impl_->m_cam.get();
}

void Scene::set_world() const {}

IHitable* Scene::get_world() const
{
    return m_impl_->m_world.get();
}

TextureStore& Scene::get_texture_store() const
{
    return m_impl_->m_textures;
}

// Scene factory
std::unique_ptr<Scene> SceneFactory::create_scene()
{
    return std::make_unique<Scene>();
}
