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

#include "image_tile.h"

#include <unordered_map>

struct ImageTile::Impl
{
    std::unordered_map<std::string, std::unique_ptr<IBuffer>> m_layers;
};

ImageTile::ImageTile()
  : m_impl_(new Impl)
{}

ImageTile::ImageTile(
    const int x_min,
    const int y_min,
    const int x_max,
    const int y_max)
  : m_x_min_(x_min)
  , m_x_max_(x_max)
  , m_y_min_(y_min)
  , m_y_max_(y_max)
  , m_impl_(new Impl)
{}

ImageTile::~ImageTile()
{
    delete m_impl_;
}

void ImageTile::add_layer(
    const char*              layer_name,
    std::unique_ptr<IBuffer> buffer) const
{
    m_impl_->m_layers[layer_name] = std::move(buffer);
}
