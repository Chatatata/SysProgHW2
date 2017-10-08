# SysProgHW2

A kernel modification allowing controlled supervision by applying one-for-all strategy for `fork(2)`-style created child processes.

## Installation

- Merge the repository with `linux-kernel-3.13.0` release.
- Run `kernel_comp.sh` shell script to build the kernel.
- Reboot and choose custom kernel with GRUB loader.

## Tests

You might run integration tests with `run.sh` script found in `tests` folder.
The tests do adequate amount of fuzzing, pull requests are welcomed if any bugs found.

## Caveats

This modification creates a new system call.
You might need to check [this](https://github.com/Chatatata/SysProgHW2/blob/master/tests/include/kill_child_on_exit.h) out to get the prototype.

This kernel modification is tested with Ubuntu 13.04 (Raring Ringtail) for **x86** architecture.
Please note that I haven't tried **amd64** variation.
No experience with that all.

Tests were performed with kernel compiled with `gcc 4.7.3 (Ubuntu/Linaro 4.7.3-1ubuntu1)`.
That was what you get when you use the package `build-essential` from *aptitude* with `old-releases` repository.

Feel free to ask questions, I'll check when you create issues.

## License

MIT
