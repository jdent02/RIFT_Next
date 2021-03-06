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

#include "utilities/rng/i_rand_generator.h"

#include <deque>
#include <mutex>
#include <queue>

struct TileOutline
{
    const int x_min, x_max, y_min, y_max;
};

struct TileOutlinePackage
{
    const TileOutline m_tile_outline;
    const uint64_t    m_rng_seed;
};

class TilePool
{
  public:
    TilePool() = default;
    ~TilePool() = default;

    void create_pool(int x_res, int y_res, int tile_size);

    int get_pool_size();

    TileOutline get_next_tile();

  private:
    std::mutex                                       m_write_lock_;
    std::mutex                                       m_read_lock_;
    std::queue<TileOutline, std::deque<TileOutline>> m_tile_pool_;
};
