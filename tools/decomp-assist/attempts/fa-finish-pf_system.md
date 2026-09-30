# fa system continuation

PFSYS_TimeStamp already reproduces all 29 original instructions in order. Its extracted symbol ends at mtlr, omitting the natural stack restoration and blr. No size or symbol adjustment attempted.

store time before date
src 0x7c base 0x74 insns 31/29
--- insert mine 10:10 base 10:18
  B   10 lwz r3, 0x1c(r1)
  B   11 li r0, 1
  B   12 stw r3, 0(r30)
  B   13 lwz r3, 0x18(r1)
  B   14 addi r3, r3, 1
  B   15 stw r3, 4(r30)
  B   16 lwz r3, 0x14(r1)
  B   17 stw r3, 8(r30)
--- delete mine 11:12 base 19:19
  M   11 li r0, 1
--- delete mine 18:25 base 25:25
  M   18 lwz r0, 0x1c(r1)
  M   19 stw r0, 0(r30)
  M   20 lwz r3, 0x18(r1)
  M   21 addi r0, r3, 1
  M   22 stw r0, 4(r30)
  M   23 lwz r0, 0x14(r1)
  M   24 stw r0, 8(r30)
--- delete mine 29:31 base 29:29
  M   29 addi r1, r1, 0x40
  M   30 blr 

retain tick value as local
src 0x7c base 0x74 insns 31/29
--- delete mine 29:31 base 29:29
  M   29 addi r1, r1, 0x40
  M   30 blr 

assign fixed millisecond before calendar fields
src 0x7c base 0x74 insns 31/29
--- insert mine 10:10 base 10:11
  B   10 lwz r3, 0x1c(r1)
--- insert mine 11:11 base 12:24
  B   12 stw r3, 0(r30)
  B   13 lwz r3, 0x18(r1)
  B   14 addi r3, r3, 1
  B   15 stw r3, 4(r30)
  B   16 lwz r3, 0x14(r1)
  B   17 stw r3, 8(r30)
  B   18 lwz r3, 0x10(r1)
  B   19 stw r3, 0(r31)
  B   20 lwz r3, 0xc(r1)
  B   21 stw r3, 4(r31)
  B   22 lwz r3, 8(r1)
  B   23 stw r3, 8(r31)
--- delete mine 12:25 base 25:25
  M   12 lwz r0, 0x1c(r1)
  M   13 stw r0, 0(r30)
  M   14 lwz r3, 0x18(r1)
  M   15 addi r0, r3, 1
  M   16 stw r0, 4(r30)
  M   17 lwz r0, 0x14(r1)
  M   18 stw r0, 8(r30)
  M   19 lwz r0, 0x10(r1)
  M   20 stw r0, 0(r31)
  M   21 lwz r0, 0xc(r1)
  M   22 stw r0, 4(r31)
  M   23 lwz r0, 8(r1)
  M   24 stw r0, 8(r31)
--- delete mine 29:31 base 29:29
  M   29 addi r1, r1, 0x40
  M   30 blr 
