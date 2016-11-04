# eos library
The name Eos was taken from greek mythology and translates as the dawn of the Sun.

Now library contains one container class Range for special work and helper file for printing STL containers as is in one line of code.

Library hierarchy adapted for Unix systems, after compilation You can add content from /include folder into /usr/include/ and from /lib folder into /usr/lib/. After that you do not have to write PATH to library in your project.

Requirements:
	GoogleTest - for testing library (now it loads directly from github).

How to build:
	Firstly, you should start CMake in the root folder of project (You can specify a build system generator by key -G). It will built the eos library and samples. If You want to run Tests for library You should go to the folder /Tests and run CMake there. All tests based on googletest library (library will be downloaded from github).