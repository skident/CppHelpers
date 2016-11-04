# eos library
The name Eos was taken from greek mythology and translates as the dawn of the Sun.

**Purpose**

Library eos provides own types and functions which are give oportunity to coding on C++ a bit easier and abstract. 
Do you want to construct std::string from int with standatd constructor? I know that You want it! Do it with eos::wire!

*Code*

```
eos::wire constrFromInt(123456);
std::cout << constrFromInt << std::endl;

auto padded = constrFromInt.padding("c", 2);
std::cout << padded << std::endl;

auto reversed = constrFromInt.reverse();
std::cout << reversed << std::endl;

std::vector<eos::wire> chunks = constrFromInt.split(3);
std::cout << chunks << std::endl;
````

*Output:*

> 123456

> cc123456cc

> 654321

> [12, 456]

***
    
**Library hierarchy is adapted for Unix systems**. After compilation You can add content from /include folder into /usr/include/ and from /lib folder into /usr/lib/. After that you do not have to write PATH to library in your project.

***
    
**Requirements:**
* GoogleTest - for testing library (now it loads directly from github).

***

**How to build:**
* Go to eos library root folder
* Run build.sh or build.bat (it depends on operation system). You can build library and samples using CMake GUI or from console/terminal/...
* The library will be added into folder ./lib/ or ./lib/${Configuration} 
* Samples will be generated into folder ./built as Makefile, VS solution, QtCreator project or something else (it depends on chosen generator).
* If You want to see/run tests for library you should build it from folder ./Tests with CMake. All tests based on [googletest library](https://github.com/google/googletest) (library will be downloaded from github).
    