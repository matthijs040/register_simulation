openocd \
-f interface/ftdi/ft232h-module-swd.cfg \
-f target/rp2040.cfg \
-c "adapter speed 64" \
-c "program build_application/main.elf verify reset exit" \