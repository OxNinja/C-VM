![](https://img.shields.io/github/languages/code-size/oxninja/c-vm)

# C-VM

My try to implement a virtual CPU in C

More details on [my blog article](https://0xninja.fr/posts/c-vm/).

This VM implements the following features:

* [ ] Registers
    * [ ] Basic registers
    * [ ] Flags
        * [ ] Zero flag 
* [ ] Stack
    * [ ] LIFO
    * [ ] Max size 
    * [ ] Stackframes
* [ ] Heap
    * [ ] Max size
* [ ] Instructions
    * [ ] `add reg, val`
    * [ ] `add reg, reg`
    * [ ] `sub reg, val`
    * [ ] `sub reg, reg`
    * [ ] `cmp reg, val`
    * [ ] `cmp reg, reg`
    * [ ] `mov reg, val`
    * [ ] `mov reg, reg`
    * [ ] `push val`
    * [ ] `push reg`
    * [ ] `pop reg`
    * [ ] `jmp addr`
    * [ ] `jmp label`
    * [ ] `call func`
    * [ ] `exit`
