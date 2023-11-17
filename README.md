# C-VM

My try to implement a virtual CPU in C

More details on [my blog article](https://0xninja.fr/posts/c-vm/).

This VM implements the following features:

* [ ] Registers
    * [x] Basic registers
    * [ ] Flags
        * [x] Zero flag 
* [ ] Stack
    * [x] LIFO
    * [ ] Max size 
    * [ ] Stackframes
* [ ] Heap
    * [ ] Max size
* [ ] Instructions
    * [x] `add reg, val`
    * [x] `add reg, reg`
    * [x] `sub reg, val`
    * [x] `sub reg, reg`
    * [x] `cmp reg, val`
    * [x] `cmp reg, reg`
    * [x] `mov reg, val`
    * [x] `mov reg, reg`
    * [ ] `push val`
    * [ ] `push reg`
    * [ ] `pop reg`
    * [ ] `jmp addr`
    * [ ] `jmp label`
    * [ ] `call func`
    * [x] `exit`
