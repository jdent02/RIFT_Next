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

#include "texture_store.h"

#include "textures/i_texture.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

struct TextureStore::Impl
{
    std::unordered_map<const char*, std::unique_ptr<ITexture>> m_textures;
};

TextureStore::TextureStore()
  : m_impl_(new Impl)
{}

TextureStore::~TextureStore()
{
    delete m_impl_;
}

void TextureStore::add_texture(
    const char* key,
    const char* model,
    ParamArray& params) const 
{
    // TODO
}

void TextureStore::add_texture(
    const char* key,
    std::unique_ptr<ITexture> texture) const {
    m_impl_->m_textures[key] = std::move(texture);
}
