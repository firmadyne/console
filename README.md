Introduction
============

This is a small binary that spawns a console on the `/firmadyne/ttyS1`` special
character device at system startup. In conjunction with a patched filesystem
and instrumented kernel, this allows an analyst to interact with an emulated
firmware image through QEMU, since some firmware images do not spawn a terminal
on the primary serial console.

Usage
=====

First, create the special character device within the firmware image:

`mknod -m 666 /firmadyne/ttyS1 c 4 65`

Next, copy this binary into the firmware image:

`cp console /firmadyne/console`

Then, it will be automatically executed by the instrumented kernel during system
bootup after the 4th `execve()` call if the `firmadyne.execute` kernel parameter
is set to 1 (this is the default).

Notes
====

## ARM Serial Devices
QEMU ARM guests do not currently support multiple serial consoles. You can build qemu with [this patch](https://unix.stackexchange.com/questions/479085/can-qemu-m-virt-on-arm-aarch64-have-multiple-serial-ttys-like-such-as-pl011-t/549798#549798) or try the [PANDA emulator](https://github.com/panda-re/panda) to run ARM guests with multiple serial devices.

## Shell Usability
If you start a serial console with `-serial stdio`, pressing ctrl-C, ctl-Z, or so on will be sent to the emulator itself. If you wish for these commands to be sent to the guest, you can use `-nographic` (if running with a single serial console), or `-serial telnet:localhost:4321,noserver,nowait -serial stdio` to expose a root shell on ttyS1 via telnet and the standard guest output on stdio. Then you can connect to the root console via telnet (with `telnet localhost 4321`) and press ctrl-C, ctrl-Z and have these commands sent directly into the guest.
