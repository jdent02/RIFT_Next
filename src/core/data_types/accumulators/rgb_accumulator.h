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

#include "core/data_types/accumulators/i_accumulator.h"
#include "utilities/color_utilities.h"
#include <vector>
#include "core/data_types/buffers/view.h"
#include "utilities/system/_dll/dll_symbol.h"
#include "core/data_types/rgb_color.h"

class RgbAccumulator : public IAccumulator
{
  public:
    RgbAccumulator() = default;

    void add_sample(
        HitRecord&     hrec,
        ScatterRecord& srec,
        Ray&           r,
        Ray&           scattered) override;

    std::unique_ptr<View> export_to_view() override;

  private:
    std::vector<std::vector<RGBColor>> m_samples_;
};
