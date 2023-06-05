openocd -f interface/ftdi/ft232h-module-swd.cfg \
-f target/rp2040.cfg \
-s tcl \
-c "adapter speed 256"