# RIFT Renderer
Welcome to my personal path tracer sandbox.  Originally it started as an implementation of Peter Shirley's "Raytracing in One Weekend", because why not?

Eventually I decided that Shirley's raytracer, while completely useable, wasn't very modular or easily modifiable, so I decided to borrow some of his techniques and incorporate them into a new renderer that was both modular and easily upgradable.

Code style follows C++11 with a few C++14 features (mostly std::make_unique).

The name is an acronym for a “Reduction in Free Time".

Currently compiles on Windows with Visual Studio 2017 or 2019. Other compilers and operating systems haven’t been tested.

Includes headers from the STB image library: https://github.com/nothings/stb

Also includes a VS2019 build of OpenEXR: https://www.openexr.com/

# Here's where I say 'thanks'
Special thanks goes to the teams behind the appleseed renderer: https://github.com/appleseedhq/appleseed and PBRT: https://github.com/mmp/pbrt-v3.  Both renders have provided a lot of inspiration for the ultimate design of RIFT Next.
