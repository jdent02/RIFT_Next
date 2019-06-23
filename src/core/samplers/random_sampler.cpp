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

#include "random_sampler.h"

#include <memory>

SampleOffset RandomSampler::generate_sample_offset()
{
    return SampleOffset{m_rng_generator.get_1_d(), m_rng_generator.get_1_d()};
}

RandomSampler::RandomSampler(const uint64_t& seed)
{
    m_rng_generator.seed_gen(seed);
}

void RandomSampler::seed_rng(const uint64_t& seed)
{
    m_rng_generator.seed_gen(seed);
}

CameraSampleOffset RandomSampler::generate_camera_offset()
{
    return CameraSampleOffset{m_rng_generator.get_1_d(), m_rng_generator.get_1_d(), m_rng_generator.get_1_d()};
}

std::unique_ptr<IRenderSampler> RandomSamplerFactory::create(const uint64_t& seed)
{
    return std::make_unique<RandomSampler>(seed);
}
