# about:

This project is trying to mimic the style of register modeling presented by Ben Saks at CppCon 2022. With some additions:
* The "operator new"-based mechanism for peripheral creation is privatized in the class describing the register. 
Instead of "allocating" this resource in the HAL-handles. It is acquired like a singleton through a get() function. Returning it by reference.
* The bitfield class is used to apply harsh type-safety to register accesses. This class ensures that e.g. no reserved bits can be written to (as it reads the existing state before applying the masked and shifted value) and no out-of-range assignments can be made to it (by specifying the number of bits and offset range as template variables that determine its mask)

The major value-add from the Saks presentation is also implemented: Register mocking. When running the code on a PC. The "allocation" of an MCU-subsystems mapped-registers is redirected to an instance of "simulatable_peripheral". This creates a static array of the same size. Ensuring that there is memory for the HAL-code to interact with.
Then, the initializer-list of the HAL-peripheral's constructor runs over it. This ensures that the bitfields are in the same initial state as the hardware. (with maybe better defaults picked where applicable.) After that, the simulated_device_register class allows test-writers to assign effect_handlers to a static map. Which fires an on_read handler when the corresponding bitfield is converted to its underlying class, or write_handler when that bitfield is assigned to.

# build instructions:
This repo uses cmake to build its components.
First, navigate to the root of the repo, there, create dedicated directories to place CMake's outputs: One for building the release code, to deploy on a Microcontroller, one for test code. To be runnable on the desktop.

Then, configure the build. This is the point where enabling debug symbols can be specified:
"cmake -B <output_directory> -DCMAKE_BUILD_TYPE=<Debug|Release> -S <src|test>"
Once you have configured the type of artifacts you want CMake to produce, they can be built using:
"cmake --build <output_directory> --config <Debug|Release>"

## Examples:
When going to (re)configure an out-of-source build directory, going for a debug configuration. The following command could be used:
``` bash
cmake --fresh tests -B ./<build_directory> -DCMAKE_BUILD_TYPE=DEBUG
```
The "--fresh" clears any existing cmake artifacts and cached data.
The "../tests/" path refers to the root "CMakeLists.txt" file that begins listing targets and their dependencies.
The "-DCMAKE_BUILD_TYPE" flag forwards a three-state parameter to the configuration. Either "DEBUG", "RELEASE", or "RELWITHDEBINFO".

Next it can be built using:
``` bash
cmake --build ./<build_directory> --config Debug
```

Once built, CMake/CTest can run unit tests by calling:
``` bash
ctest --verbose -C Debug --test-dir ./<build_directory>
```

# Code coverage:

After building and running the unit tests CMake will have produced ".gcda" and ".gcno" in the "<build_dir>/CMakeFiles/tests.dir/" 
directory. These are processed using "lcov" with the invocation:
``` bash
lcov --directory . --capture --output-file ./coverage.info --keep-going --demangle-cpp --exclude <build_directory>/ --no-external
```
Note that the . directory refers to the root of the workspace. This path is needed for lcov to know the project's sources.
Next it is converted to an html report using
``` bash
genhtml --demangle-cpp -o coverage_report_dir coverage.info
```