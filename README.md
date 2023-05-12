# so2023-gvccandido
Code for the toy OS developed at the operating systems lecture for graduate
school at ICMC/USP.

## hw
Folder `hw` has the implementation of the first exercise, which comprised 3
tasks:
  - binary, hexadecimal implementation of hello world (`hw.hex`)
  - assembly implementation of hello world (`hw.S`)
  - C implementation of hello world, with custom runtime0 and stdio
    (`*.c`,`*.h`,`*.ld`,`rt0.S`)

### Running the tasks
  - `make hw.hex.bin/run` will build `hw.hex.bin` and run it on QEMU
  - `make hw.S.bin/run` will build `hw.S.bin` and run it on QEMU
  - `make hw.c.bin/run` will build `hw.c.bin` and run it on QEMU

Besides the above commands to run each of the specifics tasks, `make` will build
the 3 binaries from each task, but will not run any of them.

`make clean` and `make purge` removes the objects and also the binaries/images,
respectively.

### Caveats
The BIOS from my DELL laptop (from ~2014) only booted correctly when using a ISO
image.
