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

#include "i_light_integrator_list.h"

#include "core/lighting_integrators/direct_lighting.h"
#include "core/lighting_integrators/light_sample_path.h"
#include "core/lighting_integrators/path_tracer.h"

ILightIntegratorList::ILightIntegratorList()
{
    m_integrator_list_[DIRECT_LIGHTING] =
        std::make_shared<DirectLightingFactory>();

    m_integrator_list_[PATH_TRACING] = std::make_shared<PathTracerFactory>();

    m_integrator_list_[LIGHT_SAMPLE_PATH_TRACING] =
        std::make_shared<LightSamplePathFactory>();
}

std::shared_ptr<ILightIntegratorFactory> ILightIntegratorList::get_integrator(
    const IntegratorEnum& model)
{
    return m_integrator_list_[model];
}
