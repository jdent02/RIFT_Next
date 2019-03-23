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

#include <cassert>

// Rift implementation of a smart pointer.  Not too sophisticated but it gets
// the job done.

namespace rift
{
template<typename R>
class RiftPointer
{
  public:
    // Take ownership of pointer passed to constructor
    explicit RiftPointer(R* in_ptr = nullptr)
      : m_ptr_(in_ptr)
    {}

    ~RiftPointer()
    {
        if (m_ptr_)
        {
            delete m_ptr_;
        }
    }

    // Delete copy operator
    RiftPointer(const RiftPointer& rhs) = delete;

    // Transfer ownership of data and zero out pointer
    R* transfer_owner()
    {
        R* temp_ptr = m_ptr_;
        m_ptr_ = nullptr;
        return temp_ptr;
    }

    // Assume ownership of passed pointer data and zero out originator
    RiftPointer& operator=(R* rhs)
    {
        if (m_ptr_ != rhs)
        {
            m_ptr_ = rhs;
            rhs = nullptr;
        }
        return *this;
    }

    // Assume ownership of another RiftPointer's data
    RiftPointer& operator=(RiftPointer& rhs)
    {
        if (m_ptr_ != rhs.get())
        {
            m_ptr_ = rhs.transfer_owner();
        }
        return *this;
    }

    // Getter
    R* get() { return m_ptr_; }

    // Dereferencing
    R& operator*() const
    {
        assert(m_ptr_);
        return *m_ptr_;
    }

    R* operator->() const
    {
        assert(m_ptr_);
        return m_ptr_;
    }

  private:
    R* m_ptr_;
};
} // namespace rift
