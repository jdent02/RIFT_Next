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

#include "materials/i_material.h"
#include "objects/camera/i_camera.h"
#include "objects/hitables/i_hitable.h"
#include "textures/i_texture.h"
#include "utilities/system/_dll/dll_symbol.h"

#include <memory>

class RIFT_DLL Scene
{
  public:
    Scene();
    ~Scene();

    void set_world(std::unique_ptr<IHitable> world) const;

    void set_cam(std::unique_ptr<ICamera> camera) const;

    void set_lights(std::unique_ptr<IHitable> lamps) const;

    const std::unique_ptr<ICamera>&  get_cam() const;
    const std::unique_ptr<IHitable>& get_world() const;
    const std::unique_ptr<IHitable>& get_lights() const;

  private:
    struct Impl;
    Impl* m_impl_;
};

class RIFT_DLL SceneFactory
{
  public:
    static std::unique_ptr<Scene> create();
};
