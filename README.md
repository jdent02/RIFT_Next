# RIFT Renderer
This is a personal toolbox for rendering experiments.  Originally it started as an implementation of Peter Shirley's "Raytracing in One Weekend", because why not?

Eventually decided I wanted a challenge so this is a re-write and re engineering of the original RIFT renderer, this time as a DLL library.

Name is an acronym for a “Reduction in Free Time".

Currently compiles on Windows with Visual Studio 2017 or 2019. Other compilers and operating systems haven’t been tested.

Includes headers from the STB image library: https://github.com/nothings/stb

The default ‘no frills’ build has PNG and JPEG export.  There’s also an optional OpenImageIO exporter, and it requires the following dependency versions:

* Boost - 1.69
* OpenImageIO - 2.0.6
* OpenEXR - 2.2.0
* ILMBase - 2.2.0
* LibPNG - 1.6.12
* LibJPEG-Turbo - 1.3.1
* LibTIFF - 4.0.3
* ZLib - 1.2.8
