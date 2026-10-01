
## singles leaf session
- .bss 100% via OSThreadQueue queue member in UpdateThreadData (Thread size 0x1320 -> UH0 at 0x2320). Keep separate globals, NOT an enclosing struct: a struct forces a single base symbol and perturbs all member-address codegen; orig has separate globals and MWCC reuses Flags0's homed base reg for +0x800/+0x2320 offsets.
- .sdata 100% via "." (not "-") region suffix strcats.
- E/D region check: `!(x != 'E' && x != 'D')` defeats MWCC adjacent-value range fusion (subi+cmplwi 1) and reproduces orig's shared li r0,1 arm exactly.
- UpdateWork-struct + w-> pointer locals: REGRESSION (-11 fuzzy); reverted.
- Remaining .text gaps = const-home/remat policy: orig homes lis 0x8048 (disc base) + zero/one consts in callee regs and remats `add base,byteoff` per access site (~+50 insns); MWCC folds to subis + CSE'd entry ptrs. Same RA-pinning wall as fa-file/scene2 units.
