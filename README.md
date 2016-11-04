# eos library
The name Eos was taken from greek mythology and translates as the dawn of the Sun.

Now library contains one container class Range for special work and helper file for printing STL containers as is in one line of code.

    
**Library hierarchy is adapted for Unix systems**. After compilation You can add content from /include folder into /usr/include/ and from /lib folder into /usr/lib/. After that you do not have to write PATH to library in your project.

    
**Requirements:**
* GoogleTest - for testing library (now it loads directly from github).


**How to build:**
* Go to eos library root folder
* Run build.sh or build.bat (it depends on operation system). You can build library and samples using CMake GUI or from console/terminal/...
* The library will be added into folder ./lib/ or ./lib/${Configuration} 
* Samples will be generated into folder ./built as Makefile, VS solution, QtCreator project or something else (it depends on chosen generator).
* If You want to see/run tests for library you should build it from folder ./Tests with CMake. All tests based on [googletest library](https://github.com/google/googletest) (library will be downloaded from github).
    