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

#include "textures/i_texture.h"
#include "utilities/data_structures/rgb_color.h"

#include <memory>
#include <utility>

// Forward declaration

class CheckerTexture : public ITexture
{
  public:
    CheckerTexture() = default;

    CheckerTexture(std::shared_ptr<ITexture> t0, std::shared_ptr<ITexture> t1)
      : m_odd_(std::move(t1))
      , m_even_(std::move(t0)){};

    ~CheckerTexture() override = default;

    RGBColor value(float u, float v, const Vec3& p) const override;

  private:
    const std::shared_ptr<ITexture> m_odd_{};
    const std::shared_ptr<ITexture> m_even_{};
};
