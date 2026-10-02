# Run fixed-stack relocation correction

This is a narrow follow-up to #973, not another Run implementation or a new
match. The existing assembly, cache loop, register clearing, labels and handoff
remain intact. No linking flag changes.

## Evidence

The hash-verified original DOL and linked ELF contain Run at 0x8137B3EC,
size 0xAC (43 instructions). Its instructions at 0x8137B468/0x8137B46C establish
SP as 0x81600000. This architectural stack value should not depend on placement
of an unrelated formatted-output routine.

Automatic extraction had attached two relocations to __pformatter + 0x280:
R_PPC_ADDR16_HI at Run+0x7E and R_PPC_ADDR16_LO at Run+0x82. The linked formatter
address happens to make this expression equal 0x81600000 in this target, but
that is a false semantic dependency in the reconstruction.

DTK block_relocations uses instruction addresses, not ELF halfword offsets.
The two exclusions are therefore .text:0x8137B468 and .text:0x8137B46C.
The source removes the unrelated extern and uses the fixed high/low immediate.
No other source instructions or original bytes are replaced.

## Independent validation

- Full 43U all_source, progress, report and DOL check pass.
- Original app and rebuilt DOL SHA1 both remain
  26116613f624061ba99c8d1a299aaa6efa85670d.
- Run remains 100%, 43/43 instructions, ctxdiff zero. No new match attribution.
- Whole report is unchanged: no code, data, function, linking or fuzzy delta.
- Pool: all 91 strings identical.
- All 1027 native source objects compared: only BS2Mach .text changes; size
  16960 is unchanged. Exactly the two false text relocations are removed.
  All other allocated objects and data sections are unchanged.
- All 1027 active extracted objects compared, plus the same obsolete cached
  tiManager.o in both trees. Only BS2Mach .text changes: size 16980 unchanged;
  only Run's high immediate placeholder bytes at +0x7E/+0x7F become 0x81,0x60.
  Exactly the two formatter relocations disappear, with no added relocations.
  Defined target symbols and non-text sections stay unchanged.
- Supplemental integer-PPC contract model checks the compiled source for 1,
  4 and 131072 cache lines, preserved LR entry, SP 0x81600000, cleared GPRs and
  alternating dcbz/dcbf events. The zero-count prefix retains the original CTR
  wrap to 0xFFFFFFFF; the full 2^32-iteration path is not executed. This is an
  abstract contract test, not actual cache/MMIO or console execution.
- Workflow/literal/jump-table/pool tests: 8/36/27/8 passed.
- Diff check passes.

Assembly was already introduced by #973. The original isolated full-Run
experiment is deliberately not included here. This correction adds no new
assembly instructions, forced register uses, retail .s objects or padding.
Please review the metadata/source constant attribution explicitly.
