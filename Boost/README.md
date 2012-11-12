Boost
=====
This project is dependent on the boost libraries (version 1.51) which is expected to be located in
this folder. The actual files have not been committed, to avoid excessive repository size, and
massive commits when updating boost version.

You can copy the entire Boost folder (containing headers) into here, or use something like the BCP
tool to extract only the required files. As of 12/11/2012 the required boost packages are:
 - foreach.hpp
 - lambda/bind.hpp
 - lambda/lambda.hpp
 - noncopyable.hpp
 - optional.hpp