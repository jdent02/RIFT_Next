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

#include "utility/system/_dll/dll_symbol.h"
#include "utility/containers/render_settings.h"
#include "utility/buffers/i_buffer.h"


class Scene;

class RIFT_DLL IRenderController
{
  public:
    virtual ~IRenderController() = default;

    virtual void render() = 0;
    virtual void cleanup() = 0;

    virtual void add_scene(Scene* render_scene) = 0;

    virtual void add_settings(RenderSettings settings) = 0;
    virtual RenderSettings& get_settings() = 0;

    virtual void set_buffer() = 0;
    virtual IBuffer* get_buffer() = 0;

    virtual void set_output_writer() = 0;
    virtual void write_output() = 0;
};

class RIFT_DLL IControllerFactory
{
public:
    virtual ~IControllerFactory() = default;

    virtual std::unique_ptr<IRenderController> create() = 0;
};
