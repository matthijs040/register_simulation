openocd \
-f interface/ftdi/ft232h-module-swd.cfg \
-f target/rp2040.cfg \
-c "adapter speed 500" \
-c "program build_app/main.elf verify reset exit" \