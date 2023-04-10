# about:

This project is trying to mimic the style of register modeling presented by Ben Saks at CppCon 2022. With some additions:
* The "operator new"-based mechanism for peripheral creation is wrapped in shared/weak pointers. Allowing for automatic "construction and destruction" of resources. Which in this case could mean disabling peripherals to save power.
* This make_shared-specialization is further customized by first checking if a static weak pointer is valid. Effectively making it a singleton pattern.

# build instructions:

This repo uses cmake to build its components.
First, navigate to the root of the repo, there, create a dedicated "build" directory to place cmake's output.
Then, configure the build set if debug of release is desired using:
"cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Debug"
When that's done, start the build using:
"cmake --build build/"
