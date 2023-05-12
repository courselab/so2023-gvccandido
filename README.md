# so2023-gvccandido
Code for the toy OS developed at the operating systems lecture for graduate
school at ICMC/USP.

## hw
Folder `hw` has the implementation of the first exercise, which comprised 3
tasks:
  - binary, hexadecimal implementation of hello world
  - assembly implementation of hello world
  - C implementation of hello world, with custom runtime0 and stdio

### Running the tasks
  - `make hw.hex.bin/run` will build `hw.hex.bin` and run it on QEMU
  - `make hw.S.bin/run` will build `hw.S.bin` and run it on QEMU
  - `make hw.c.bin/run` will build `hw.c.bin` and run it on QEMU

Besides the above commands to run each of the specifics tasks, `make` will build
the 3 binaries from each task, but will not run any of them.
