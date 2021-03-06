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

#include "image_tile.h"
#include "utilities/system/_dll/dll_symbol.h"

#include <memory>
#include <vector>

class RIFT_DLL TileBuffer
{
  public:
    TileBuffer();
    ~TileBuffer();

    void add_tile(std::unique_ptr<ImageTile> tile) const;

    void set_number_of_tiles(int num_tiles) const;

    std::vector<std::unique_ptr<ImageTile>>& get_tiles() const;

  private:
    struct Impl;
    Impl* m_impl_;
};

class RIFT_DLL TileBufferFactory
{
  public:
    static std::unique_ptr<TileBuffer> create();
};
