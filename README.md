![](https://img.shields.io/github/languages/code-size/oxninja/c-vm)
![](https://img.shields.io/tokei/lines/github/oxninja/c-vm)
![](https://img.shields.io/maintenance/yes/2022)

# C-VM

My try to implement a virtual CPU in C

More details on [my blog article](https://0xninja.fr/c-vm/).

This VM implements the following features:

- [X] `mov reg, reg/val`
- [X] `add reg, reg/val`
- [X] `sub reg, reg/val`
- [X] `exit`
- [X] `cmp reg, reg/val`
- [ ] `push reg/val`
- [ ] `pop reg`
- [ ] `jmp addr`
- [ ] `call label`
- [X] Registers
  - [X] `a b c d`: common operations
- [X] Flags (one register with flags in it)
  - [X] Zero flag `0x10000000`
- [ ] Virtual stack
- [ ] Virtual heap
