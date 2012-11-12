Tetris project readme
=====================

This project is primarily educational, with the following objectives:
 - Increased knowledge with C++
 - Basic knowledge with DirectX and DXUT
 - Basic game programming techniques
 - Basic knowledge of using Git and GitHub
 - Basic graphics programming techniques
 - Familiarity with Doxygen documentation
 - A game to play

Boost
=====
This project is dependent on the boost libraries (version 1.51) which is expected to be located in
the Boost folder at the root of the repository. The actual files have not been committed, to avoid
excessive repository size, and massive commits when updating boost version.

You can copy the entire Boost folder (containing headers) into here, or use something like the BCP
tool to extract only the required files. As of 12/11/2012 the required boost packages are:
 - foreach.hpp
 - lambda/bind.hpp
 - lambda/lambda.hpp
 - noncopyable.hpp
 - optional.hpp

DirectX
=======
This project is, obviously, dependent on the DirectX SDK (Jun 2010). I have configured my visual
studio installation to be able to locate the SDK on my system, such that no changes exist within
the project.

To do the same see: http://takinginitiative.net/2010/07/02/setting-up-the-directx-sdk-with-visual-studio-2010/

Doxygen
=======
I've included a settings file for compiling documentation for the project (.doxygen) which creates
HTML documentation within a Documentation folder. I am not committing the generated documentation,
and will instead update the settings file as required. If you wish to reap the benefits of this
documentation generator, simply get a version of Doxygen and run using the settings file. (At this
point I have not tested the paths all work correctly from another location).

Doxygen can be found here: http://www.stack.nl/~dimitri/doxygen/index.html