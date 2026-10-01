
## singles leaf session
- .bss 100% via OSThreadQueue queue member in UpdateThreadData (Thread size 0x1320 -> UH0 at 0x2320). Keep separate globals, NOT an enclosing struct: a struct forces a single base symbol and perturbs all member-address codegen; orig has separate globals and MWCC reuses Flags0's homed base reg for +0x800/+0x2320 offsets.
- .sdata 100% via "." (not "-") region suffix strcats.
- E/D region check: `!(x != 'E' && x != 'D')` defeats MWCC adjacent-value range fusion (subi+cmplwi 1) and reproduces orig's shared li r0,1 arm exactly.
- UpdateWork-struct + w-> pointer locals: REGRESSION (-11 fuzzy); reverted.
- Remaining .text gaps = const-home/remat policy: orig homes lis 0x8048 (disc base) + zero/one consts in callee regs and remats `add base,byteoff` per access site (~+50 insns); MWCC folds to subis + CSE'd entry ptrs. Same RA-pinning wall as fa-file/scene2 units.

## singles2 wave (w0929)
- `u32* flags = Flags0;` local + `memset(&flags[512],0,sizeof(Flags1))` gives base's single-home form (`lis r30,Flags0; addi r3,r30,0x800`; `&Thread.thread`/`stack` fold to `r30+0x1000/+0x1318`, no relocs — same-section delta folding). Init now 72/72 insns.
- Residual: base commits 3 callee regs (`_savegpr_29`: r29=arg, r30=flags, r31=strbase) and materializes flags EARLY (insn6) so ranges overlap; MWCC reuses r31 (arg→flags) here → manual stw pair. No source lever found for the early home (decl/`register`/derived-ptr all tested).
- UpdateThread 908/913 — base pins a const-zero callee reg (r15) for stack-local stores; extra stw/lwz spill pairs = store-forward wall.
- Separate globals (Flags0/Flags1/Thread) is the correct model — base symtab proves it; a union/struct also folds but perturbs other fns less predictably.
