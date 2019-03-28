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

#include "core/rendering/i_render_controller.h"
#include "utility/containers/render_settings.h"
#include "utility/system/_dll/dll_symbol.h"

class Scene;

class RIFT_DLL FinalRenderController : public IRenderController
{
  public:
    FinalRenderController();
    ~FinalRenderController();

    void add_settings(RenderSettings settings) override;

    void add_scene(Scene* render_scene) override;

    void render() override;

    void cleanup() override;

    RenderSettings& get_settings() override;

    void set_output_writer() override;

    void write_output() override;

    void set_buffer() override;

    IBuffer* get_buffer() override;

  private:
    struct Impl;
    Impl* m_impl_;
};

class RIFT_DLL FinalRenderControllerFactory : IControllerFactory
{
  public:
    static std::unique_ptr<IRenderController> create();
};
