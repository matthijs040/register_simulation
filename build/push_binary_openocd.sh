openocd \
-f interface/ftdi/ft232h-module-swd.cfg \
-f target/rp2040.cfg \
-c "adapter speed 64" \
-c "program src/main.elf verify reset exit" \