openocd \
-f interface/ftdi/ft232h-module-swd.cfg \
-f target/rp2040.cfg \
-c "adapter speed 8" \
-c "program src/main verify reset exit" \