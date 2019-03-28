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

#include "test_render_controller.h"

#include <cstdio>
#include "core/image_writers/oiio_writer.h"

struct TestRenderController::Impl
{
    RenderSettings                        settings;
    std::unique_ptr<IBuffer>              m_buffer;
    std::unique_ptr<renderer::IOutWriter> m_output_writer;
};

TestRenderController::TestRenderController()
  : m_impl_(new Impl)
{}

TestRenderController::~TestRenderController()
{
    delete m_impl_;
}

void TestRenderController::render()
{
    set_buffer();
}

void TestRenderController::cleanup()
{
    printf("Render cleanup\n");
}

void TestRenderController::add_settings(RenderSettings settings) {}

RenderSettings& TestRenderController::get_settings()
{
    return m_impl_->settings;
}

void TestRenderController::set_buffer() {}

IBuffer* TestRenderController::get_buffer()
{
    return m_impl_->m_buffer.get();
}

void TestRenderController::set_output_writer()
{
    m_impl_->m_output_writer = std::make_unique<renderer::OIIOWriter>();
}

void TestRenderController::write_output() {}

std::unique_ptr<IRenderController> TestRenderControllerFactory::create()
{
    return std::make_unique<TestRenderController>();
}


