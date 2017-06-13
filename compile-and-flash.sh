#!/bin/sh

docker run -t -i --privileged -v /dev/bus/usb:/dev/bus/usb -v $(pwd)/src:/build/jerryscript/targets/particle/source -v $(pwd)/Makefile.particle:/build/jerryscript/targets/particle/Makefile.particle -v $(pwd)/dist:/tmp/dist --rm sebadoom/jerryphoton /bin/bash -c 'cd /build/jerryscript && make -f ./targets/particle/Makefile.particle && cp ./build/particle/jerry_main.bin /tmp/dist/firmware.bin && dfu-util -d 2b04:d006 -a 0 -i 0 -s 0x80A0000:leave -D ./build/particle/jerry_main.bin'

