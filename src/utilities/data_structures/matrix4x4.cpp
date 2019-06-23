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

#include "matrix4x4.h"

#include <ostream>

void operator<<(std::ostream& os, Matrix4x4& matrix)
{
    os << "[ " << matrix.m_vector[0][0] << " " << matrix.m_vector[0][1] << " " << matrix.m_vector[0][2]
       << matrix.m_vector[0][3] << " ]\n"
       << "[ " << matrix.m_vector[1][0] << " " << matrix.m_vector[1][1] << " " << matrix.m_vector[1][2]
       << matrix.m_vector[1][3] << " ]\n"
       << "[ " << matrix.m_vector[2][0] << " " << matrix.m_vector[2][1] << " " << matrix.m_vector[2][2]
       << matrix.m_vector[2][3] << " ]\n"
       << "[ " << matrix.m_vector[3][0] << " " << matrix.m_vector[3][1] << " " << matrix.m_vector[3][2]
       << matrix.m_vector[3][3] << " ]\n";
}

Matrix4x4::Matrix4x4()
{
    m_vector[0][0] = 1.0;
    m_vector[0][1] = 0.0;
    m_vector[0][2] = 0.0;
    m_vector[0][3] = 0.0;

    m_vector[1][0] = 0.0;
    m_vector[1][1] = 1.0;
    m_vector[1][2] = 0.0;
    m_vector[1][3] = 0.0;

    m_vector[2][0] = 0.0;
    m_vector[2][1] = 0.0;
    m_vector[2][2] = 1.0;
    m_vector[2][3] = 0.0;

    m_vector[3][0] = 0.0;
    m_vector[3][1] = 0.0;
    m_vector[3][2] = 0.0;
    m_vector[3][3] = 1.0;
}
