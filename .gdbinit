target remote :2338
mon reset
mon halt
load build/debug/target.elf
symbol-file build/debug/target.elf
b main
