This project is intended to be a _quick_ starting template for
C++ projects which wants to be _self sufficient_--- i.e.,
with _less_ dependency on requirements of the development system.

Based on [CPM](https://github.com/TsinghuaAI/CPM), the project can download
 the 3rd party library sources on first build, and cached them for later build.

The user only has to modify the src/CMakefile for project name,
this template use [nlohmann JSON](https://github.com/nlohmann/json) and [asio](https://think-async.com/Asio/)
as a demonstration.

Of course, more 3rd party packages can be added to create a _self_suffcient_ application.

##Quick Start##:

	Under the root source:
	mkdir build/ && cd build
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
	make
