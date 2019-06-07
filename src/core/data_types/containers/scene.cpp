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

#include "materials/i_material.h"
#include "objects/camera/i_camera.h"
#include "objects/hitables/i_hitable.h"

#include <memory>
#include <unordered_map>
#include "textures/i_texture.h"

struct Scene::Impl
{
    std::unique_ptr<ICamera>                m_cam;
    std::unique_ptr<IHitable>               m_world;
    std::unique_ptr<IHitable>               m_lights{nullptr};
};

Scene::Scene()
  : m_impl_(new Impl)
{}

Scene::~Scene()
{
    delete m_impl_;
}

void Scene::set_world(std::unique_ptr<IHitable> world) const
{
    m_impl_->m_world = std::move(world);
}

void Scene::set_cam(std::unique_ptr<ICamera> camera) const
{
    m_impl_->m_cam = std::move(camera);
}

const std::unique_ptr<ICamera>& Scene::get_cam() const
{
    return m_impl_->m_cam;
}

const std::unique_ptr<IHitable>& Scene::get_world() const
{
    return m_impl_->m_world;
}

const std::unique_ptr<IHitable>& Scene::get_lights() const
{
    return m_impl_->m_lights;
}

// Scene factory
std::unique_ptr<Scene> SceneFactory::create()
{
    return std::make_unique<Scene>();
}

