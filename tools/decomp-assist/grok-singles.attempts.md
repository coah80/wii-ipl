# grok-singles force-retention

## cnt.c
File-scope `const char* __CNTVersion` lands in .sdata and the linker keeps it at 0x81698330 even when CNTInit is stripped (weak and static-used-by-CNTInit both kept). That shifts later sdata: DOL 677 bytes off, sha 01822ae8. Unused static pointer is deleted by the compiler and takes the banner string with it.
Banner stays a local in stripped CNTInit, which calls OSRegisterVersion. CNTInitHandle sprintf's `/content%d` and prints the missing-directory warning. Pool bytes match (version, /content%d, warning, then the three ES strings). 16/16 linked functions differing 0. DOL 26116613f624061ba99c8d1a299aaa6efa85670d.

## CDBConv.c
CDBConvDateValueToDateStr sprintf's "%04d%02d%02d" where the force sat, before CDBConvKeyToFullPath. .data 176/176 identical, .sdata 56/56 identical, 39/39 linked functions differing 0. Helper stripped. DOL matches.

## WUD.c
WUDCancelSyncDevice prints its name and returns StopSync(). StopSync stays inlined in WUDStopSyncSimple (38/38 differing 0). 107 strings equal, data bytes identical, 66/66 linked functions differing 0. Cancel function stripped. DOL matches.

## OSReset.c
DECL_WEAK OSReturnToMenu calls __OSReturnToMenu(MENU) then OSPanic with the original "Falied" string. BS2's strong OSReturnToMenu stays at 0x813808a0. 15/15 strings equal, 8/8 linked functions differing 0. DOL matches.
