Tetris project readme
=====================

This project is primarily educational, with the following objectives:
 - Increased knowledge with C++
 - Basic knowledge with DirectX and DXUT
 - Basic game programming techniques
 - Basic knowledge of using Git, and possibly also GitHub
 - Basic graphics programming techniques
 - A game to play

Boost
-----
This project is dependent on the boost libraries (version 1.51) which is expected to be located
in the Boost folder at the root of the repository. The actual files have not been committed, to
avoid excessive repository size, and massive commits when updating boost version.
You can copy the entire Boost folder (containing headers) into here, or use something like the
BCP tool to extract only the required files. As of 12/10/2012 the required boost packages are:
 - foreach.hpp
 - lambda/bind.hpp
 - lambda/lambda.hpp
 - noncopyable.hpp
 - optional.hpp