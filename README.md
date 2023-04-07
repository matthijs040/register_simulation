# about:

This project is trying to mimic the style of register modeling presented by Ben Saks at CppCon 2022. With some additions:
* The "operator new"-based mechanism for peripheral creation is wrapped in shared/weak pointers. Allowing for automatic "construction and destruction" of resources. Which in this case could mean disabling peripherals to save power.
* This make_shared-specialization is further customized by first checking if a static weak pointer is valid. Effectively making it a singleton pattern.