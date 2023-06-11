# about:

This project is trying to mimic the style of register modeling presented by Ben Saks at CppCon 2022. With some additions:
* The "operator new"-based mechanism for peripheral creation is privatized in the class describing the register. 
Instead of "allocating" this resource in the HAL-handles. It is acquired like a singleton through a get() function. Returning it by reference.
* The bitfield class is used to apply harsh type-safety to register accesses. This class ensures that e.g. no reserved bits can be written to (as it reads the existing state before applying the masked and shifted value) and no out-of-range assignments can be made to it (by specifying the number of bits and offset range as template variables that determine its mask)

The major value-add from the Saks presentation is also implemented: Register mocking. When running the code on a PC. The "allocation" of an MCU-subsystems mapped-registers is redirected to an instance of "simulated_peripheral". This creates a static array of the same size. Ensuring that there is memory for the HAL-code to interact with.
Then, the initializer-list of the HAL-peripheral's constructor runs over it. This ensures that the bitfields are in the same initial state as the hardware. (with maybe better defaults picked where applicable.) After that, the simulated_device_register class allows test-writers to assign effect_handlers to a static map. Which fires an on_read handler when the corresponding bitfield is converted to its underlying class, or write_handler when that bitfield is assigned to.

# build instructions:
This repo uses cmake to build its components.
First, navigate to the root of the repo, there, create dedicated directories to place CMake's outputs: One for building the release code, to deploy on a Microcontroller, one for test code. To be runnable on the desktop.

Then, configure the build. This is the point where enabling debug symbols can be specified:
"cmake -B <output_directory> -DCMAKE_BUILD_TYPE=<Debug|Release> -S <src|test>"
Once you have configured the type of artifacts you want CMake to produce, they can be built using:
"cmake --build <output_directory> --config <Debug|Release>"
