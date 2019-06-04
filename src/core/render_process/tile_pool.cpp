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

#include "tile_pool.h"

#include "utilities/rng/drand48.h"

#include <chrono>
#include <iostream>

TilePool::TilePool() = default;

void TilePool::create_pool(
    const int x_res,
    const int y_res,
    const int tile_size)
{
    const int x_tiles = x_res / tile_size;
    const int y_tiles = y_res / tile_size;
    const bool do_extra_x = x_res - x_tiles * tile_size != 0;
    const bool do_extra_y = y_res - y_tiles * tile_size != 0;

    // Full sized tiles.
    for (int y = 1; y <= y_tiles; ++y)
    {
        const int y_start = y_res - y * tile_size;
        const int y_end = y_start + tile_size;
        for (int x = 0; x < x_tiles; ++x)
        {
            const int x_start = x * tile_size;
            const int x_end = x_start + tile_size;
            m_tile_pool_.push(TileOutline{x_start, x_end, y_start, y_end});
        }
    }

    if (do_extra_y)
    {
        const int y_start = 0;
        const int y_end = y_res - tile_size * y_tiles;
        for (int x = 0; x < x_tiles; ++x)
        {
            const int x_start = x * tile_size;
            const int x_end = x_start + tile_size;
            m_tile_pool_.push(TileOutline{x_start, x_end, y_start, y_end});
        }
    }

    if (do_extra_x)
    {
        const int x_start = tile_size * x_tiles;
        for (int y = 1; y <= y_tiles; ++y)
        {
            const int y_start = y_res - y * tile_size;
            const int y_end = y_start + tile_size;
            m_tile_pool_.push(TileOutline{x_start, x_res, y_start, y_end});
        }
    }

    // Final corner tile.
    const int x_start = x_tiles * tile_size;
    const int y_end = y_res - y_tiles * tile_size;
    m_tile_pool_.push(TileOutline{x_start, x_res, 0, y_end});
}

int TilePool::get_pool_size() const
{
    return static_cast<int>(m_tile_pool_.size());
}

TileOutline TilePool::get_next_tile()
{
    const TileOutline tile{m_tile_pool_.front()};

    m_tile_pool_.pop();

    return tile;
}
