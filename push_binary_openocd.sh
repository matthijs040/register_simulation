openocd \
-f interface/ftdi/ft232h-module-swd.cfg \
-f target/rp2040.cfg \
-c "adapter speed 256" \
-c "program build_app/SPI_snippet.elf verify reset exit" \
# -c "program ${HOME}/Downloads/picoprobe.elf verify reset exit" \