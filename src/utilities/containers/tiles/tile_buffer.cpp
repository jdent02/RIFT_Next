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

#include "tile_buffer.h"

#include "image_tile.h"

#include <mutex>

struct TileBuffer::Impl
{
    std::mutex                              m_write_guard;
    std::vector<std::unique_ptr<ImageTile>> m_tiles;
};

TileBuffer::TileBuffer()
  : m_impl_(new Impl)
{}

TileBuffer::~TileBuffer()
{
    delete m_impl_;
}

void TileBuffer::add_tile(std::unique_ptr<ImageTile> tile) const
{
    std::lock_guard<std::mutex> lock(m_impl_->m_write_guard);

    m_impl_->m_tiles.emplace_back(std::move(tile));
}

void TileBuffer::set_number_of_tiles(const int num_tiles) const
{
    m_impl_->m_tiles.reserve(num_tiles);
}

std::vector<std::unique_ptr<ImageTile>>& TileBuffer::get_tiles() const
{
    return m_impl_->m_tiles;
}

std::unique_ptr<TileBuffer> TileBufferFactory::create()
{
    return std::make_unique<TileBuffer>();
}
