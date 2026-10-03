# H2b helper and guard round

Worktree data-d2; branch agent/w1003/lever11-h2b; base 34858f3f. Read AGENTS.md, h2.attempts.md, common.md and levers.md. Initial full 43U Ninja build passes. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Origin main fetched under /tmp/wii-git.lock; no owned source changes. Existing untracked a9h/a9m/a9x/u3 attempts logs remain untouched.

Objdiff baseline: AOSS 17/21, code 7720/16192, data 3928/3928; ATERM 19/26, code 11584/19204, data 18584/18864; AOSSLink 12/14, code 668/2196, data 2432/2432. The ATERM 280-byte switch table belongs to ATERMRunConfigProtocol. No configure or hand-placed data changes are in scope. Scratch trials and measurements stay under .h2b during this run.
- 1. AOSSi_WLANGetBSSList | helper copies descriptor list with const source | 98.37004%; insns 227/227, raw diffs 30; exact 12; code 668; data 2432; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 0e44152e67e1.
- 2. AOSSi_WLANGetBSSList | retry declarations follow startup scan cleanup unlock order | 98.30396%; insns 227/227, raw diffs 32; exact 12; code 668; data 2432; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 160b6f7103f4.
- 3. AOSSi_WLANGetBSSList | const descriptor and index declared in traversal order | 98.30396%; insns 227/227, raw diffs 32; exact 12; code 668; data 2432; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 13c8d160b183.
- 4. AOSSi_WLANGetBSSList | block scoped channel mask with ordered retries | 98.30396%; insns 227/227, raw diffs 32; exact 12; code 668; data 2432; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source e7c5e33d2c56.
- 5. AOSSi_WLANConnect | wireless setup helper with const connection | 94.509674%; insns 160/155, raw diffs 102; exact 12; code 668; data 2432; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source c99f179b3f17.
- 6. AOSSi_WLANConnect | use memset returned IP configuration pointer | 95.29032%; insns 155/155, raw diffs 14; exact 12; code 668; data 2432; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 0eb391d18936.
  [(62, ('lis', 'r3, 0'), ('lis', 'r27, 0')), (64, ('addi', 'r3, r3, 0'), ('addi', 'r27, r27, 0')), (67, ('bl', 0), ('mr', 'r3, r27')), (68, ('li', 'r0, 0x514'), ('bl', 0)), (69, ('li', 'r4, 0x64'), ('li', 'r0, 0')), (70, ('stw', 'r0, 0x1c(r3)'), ('li', 'r3, 0x514')), (71, ('li', 'r6, 4'), ('li', 'r7, 0x64')), (72, ('li', 'r0, 0'), ('li', 'r6, 4')), (73, ('mr', 'r27, r3'), ('stw', 'r3, 0x1c(r27)')), (74, ('stw', 'r4, 0x20(r3)'), ('addi', 'r3, r27, 8')), (77, ('stw', 'r6, 0x24(r3)'), ('stw', 'r7, 0x20(r27)')), (78, ('stw', 'r0, 0(r3)'), ('stw', 'r6, 0x24(r27)')), (79, ('stw', 'r0, 4(r3)'), ('stw', 'r0, 0(r27)')), (80, ('addi', 'r3, r3, 8'), ('stw', 'r0, 4(r27)'))]
- 7. AOSSi_WLANConnect | scope IP configuration pointer to IP setup | 98.70968%; insns 155/155, raw diffs 2; exact 12; code 668; data 2432; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 63649db09aba.
  [(66, ('mr', 'r3, r27'), ('li', 'r5, 0x7c4')), (67, ('li', 'r5, 0x7c4'), ('mr', 'r3, r27'))]
- 8. AOSSi_WLANConnect | initialize IP pointer after clearing global configuration | 96.20645%; insns 155/155, raw diffs 26; exact 12; code 668; data 2432; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 84adc9afe03a.

## AOSS guard evidence

Target AOSS_Init_old starts at 813FE4A8. The first mention of r14 in its target assembly is cmpwi r14, 0 at 813FEC9C, reached after successful SOSocket at 813FEC4C and bge at 813FEC58. No earlier instruction assigns r14. The first write is li r14, 0x11 at 813FEDA8 on a later error path. The entry _savegpr_14 call saves its incoming value but does not define it. Therefore the guard must not inherit the earlier AOSSi_SetNCDIPAddr return. Lever 10 permits this demonstrated uninitialized local. Later protocolResult writes also occupy r14 in the target.

- 9. AOSS_Init_old | request record initializer helper | 95.833336%; insns 1572/1584, raw diffs 1452; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source 94d1d52778ba.
- 10. AOSS_Init_old | lever10 target uninitialized protocol result guard | 96.37942%; insns 1580/1584, raw diffs 1341; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source 366c9cb8f0c1.
- 11. AOSS_Init_old | guard with target stack address declaration order | 96.385735%; insns 1580/1584, raw diffs 1341; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source 07e76523d01a.
- 12. AOSS_Init_old | guard with saved g10 initialization and record scopes | 96.77273%; insns 1578/1584, raw diffs 1265; exact 17; code 7720; data 3920; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source 6e6fb5192b26.
- 13. AOSSApplyAuthOptions | network option validator and copy helper on saved a4x cursor | 88.333336%; insns 102/114, raw diffs 57; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source 485c7646e12f.
- 14. AOSSApplyAuthOptions | traverse response parameter directly and reuse it for options | 97.2807%; insns 114/114, raw diffs 18; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source 618fc82fcaf3.
- 15. AOSSApplyAuthOptions | initialize option flags after response search | 96.75439%; insns 114/114, raw diffs 21; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source a3fca9a5f1e4.
- 16. AOSSApplyAuthOptions | defer flags with saved response cursor local | 97.67544%; insns 114/114, raw diffs 23; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source 9bf8b031a034.
- 17. AOSSSendHelloRequest | complete hello encryption loop helper with const input | 69.337%; insns 207/273, raw diffs 254; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source 7956c5782af5.
- 18. AOSSSendHelloRequest | saved g10 stream byte before stream index declaration | 92.190475%; insns 271/273, raw diffs 254; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source cd5d7a9b4e01.
- 19. AOSSSendHelloRequest | stream byte scoped to output XOR | 92.48351%; insns 271/273, raw diffs 254; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source ced8365cff1e.
- 20. AOSSSendHelloRequest | single counted CRC byte loop | 87.31502%; insns 270/273, raw diffs 266; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source afeb2b0e36df.
- 21. AOSSXorBufferWithKey | XOR buffer loop helper with const mask | 48.32653%; insns 81/147, raw diffs 134; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source 2b0b0a937090.
- 22. AOSSXorBufferWithKey | direct compound XOR assignment | 98.23129%; insns 147/147, raw diffs 46; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source b6998b6514a2.
- 23. AOSSXorBufferWithKey | mask byte local as XOR destination | 98.57143%; insns 147/147, raw diffs 31; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source 935bfce2d95d.
- 24. AOSSXorBufferWithKey | mask first XOR expression | 97.993195%; insns 147/147, raw diffs 46; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source 7b168da48f58.
- 25. ATERMStartNetworkStack | shared message queue sleep helper | 97.88961%; insns 154/154, raw diffs 55; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 9459b8c162af.
- 26. ATERMStartNetworkStack | single typed network settings view for both configurations | 97.91558%; insns 154/154, raw diffs 51; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source d1c6d4bbcbb9.
- 27. ATERMStartNetworkStack | assign IP view after clearing global storage | 97.91558%; insns 154/154, raw diffs 51; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 5606a2c07ab1.
- 28. ATERMStartNetworkStack | file local network configuration and SSID globals | 97.91558%; insns 154/154, raw diffs 51; exact 19; code 11584; data 10424; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 82ddaee059c1.
- 29. ATERMDiscoverAccessPoints | nested MAC and hex nibble loop helpers | 97.20532%; insns 263/263, raw diffs 194; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source c41e113f938d.
- 30. ATERMDiscoverAccessPoints | hex cursor declared before nibble array in helper | 97.20532%; insns 263/263, raw diffs 194; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 49f5638de290.
- 31. ATERMDiscoverAccessPoints | pointer bounded MAC helper with nested nibble helper | 95.79088%; insns 264/263, raw diffs 222; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 87f5bc3fcf21.
- 32. ATERMDiscoverAccessPoints | unsigned nibble values inside nested encoder helper | 96.76806%; insns 263/263, raw diffs 194; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 85192697e142.
- 33. ATERMBuildAssociationRequest | nested MAC and hex nibble loop helpers | 97.55639%; insns 133/133, raw diffs 50; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source a1be2a212513.
- 34. ATERMBuildAssociationRequest | hex cursor declared before nibble array in helper | 97.55639%; insns 133/133, raw diffs 50; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source bd4b4f3350cb.
- 35. ATERMBuildAssociationRequest | pointer bounded MAC helper with nested nibble helper | 91.887215%; insns 133/133, raw diffs 77; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 9f01e375e4f6.
- 36. ATERMBuildAssociationRequest | unsigned nibble values inside nested encoder helper | 95.86466%; insns 133/133, raw diffs 51; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 20820b85ead9.
- 37. ATERMBuildEncryptedMessage | trailing checksum helper returns message end | BUILD FAILED: FAILED: [code=2] build/43U/src/src/scene/setting/ATERM.o  build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -O4,p -inline on -MMD -c src/scene/setting/ATERM.c -o build/43U/src/src/scene/setting && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/scene/setting/ATERM.d build/43U/src/src/scene/setting/ATERM.d ### mwcceppc.exe Compiler: #    File: src\scene\setting\ATERM.c # ---------------------------------- #    1043:     u8* cursor = (u8*)messageBuffer;  #   Error:     ^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- 38. ATERMBuildEncryptedMessage | separate encryption key local at entry | 99.791664%; insns 96/96, raw diffs 4; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 3a883a9f1307.
  [(9, ('mr', 'r29, r7'), ('mr', 'r3, r27')), (10, ('mr', 'r3, r27'), ('mr', 'r29, r7')), (47, ('bge', -3371), ('bge', -3379)), (52, ('bgt', -3391), ('bgt', -3399))]
- 39. ATERMBuildEncryptedMessage | readonly encryption key argument | 99.791664%; insns 96/96, raw diffs 4; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 1189a466a1b9.
  [(9, ('mr', 'r29, r7'), ('mr', 'r3, r27')), (10, ('mr', 'r3, r27'), ('mr', 'r29, r7')), (47, ('bge', -3371), ('bge', -3379)), (52, ('bgt', -3391), ('bgt', -3399))]
- 40. ATERMBuildEncryptedMessage | separate payload header local for clearing and length | 99.791664%; insns 96/96, raw diffs 4; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 26084e4023c5.
  [(9, ('mr', 'r29, r7'), ('mr', 'r3, r27')), (10, ('mr', 'r3, r27'), ('mr', 'r29, r7')), (47, ('bge', -3371), ('bge', -3379)), (52, ('bgt', -3391), ('bgt', -3399))]
- 41. ATERMBuildEncryptedMessage | checksum lifetime begins after payload clear | 96.34375%; insns 96/96, raw diffs 9; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source a2f0869227be.
  [(9, ('mr', 'r29, r7'), ('mr', 'r3, r27')), (10, ('mr', 'r3, r27'), ('mr', 'r29, r7')), (11, ('li', 'r4, 0'), ('li', 'r31, 0')), (12, ('li', 'r5, 8'), ('li', 'r4, 0')), (13, ('bl', 0), ('li', 'r5, 8')), (14, ('addi', 'r0, r28, -8'), ('bl', 0)), (15, ('li', 'r31, 0'), ('addi', 'r0, r28, -8')), (47, ('bge', -3371), ('bge', -3379)), (52, ('bgt', -3391), ('bgt', -3399))]
- 42. ATERMBuildEncryptedMessage | reuse memset return as cleared payload view | 97.5%; insns 96/96, raw diffs 12; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 2abba34644b9.
  [(5, ('mr', 'r30, r3'), ('mr', 'r27, r5')), (6, ('mr', 'r26, r4'), ('mr', 'r30, r3')), (7, ('mr', 'r3, r5'), ('mr', 'r26, r4')), (9, ('mr', 'r29, r7'), ('mr', 'r3, r27')), (10, ('li', 'r31, 0'), ('mr', 'r29, r7')), (11, ('li', 'r4, 0'), ('li', 'r31, 0')), (12, ('li', 'r5, 8'), ('li', 'r4, 0')), (13, ('bl', 0), ('li', 'r5, 8')), (14, ('addi', 'r0, r28, -8'), ('bl', 0)), (15, ('mr', 'r27, r3'), ('addi', 'r0, r28, -8')), (47, ('bge', -3371), ('bge', -3379)), (52, ('bgt', -3391), ('bgt', -3399))]

## ATERM guard evidence

At 8140408C the target compares the first TLV pointer against the option end. The empty path at 81404094 sets only r16 to zero and branches to 814040B8. The store to stack offset 0x120 at 814040AC occurs only on the nonempty path, after SONtoHs(option->type). At 814040B8 the target unconditionally loads that slot and compares it with 0x101 at 814040BC. There is no r16 null check. No earlier store to 0x120 occurs in this function. Thus optionType is uninitialized on the empty path. Lever 10 permits dropping the extra optionValue null guard to match this exact target path.

- 43. ATERMRunConfigProtocol | MD5 initialization helper | 89.77287%; insns 958/951, raw diffs 929; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 6a7b8fc41f14.
- 44. ATERMRunConfigProtocol | lever10 remove TLV null guard absent from target | 89.40589%; insns 956/951, raw diffs 925; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 1584ce57b26a.
- 45. ATERMRunConfigProtocol | guard plus MD5 finalization helper | 89.388016%; insns 956/951, raw diffs 925; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 8d54630ec8cb.
- 46. ATERMRunConfigProtocol | guard plus MD5 init and final helpers | 89.388016%; insns 956/951, raw diffs 925; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 4976bcacd226.
- 47. ATERMRunConfigProtocol | guard with MD5 word encoder nested in finalization | 88.89064%; insns 969/951, raw diffs 946; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source e53a18041a3e.
- 48. ATERMi_AutoConfigThread | completion report helper with natural result conditional | 94.75%; insns 40/40, raw diffs 3; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 7ea0ac27ad1b.
  [(20, ('nor', 'r0, r3, r0'), ('nor', 'r3, r3, r0')), (22, ('srawi', 'r3, r0, 0x1f'), ('lwz', 'r0, 0(0)')), (23, ('lwz', 'r0, 0(0)'), ('srawi', 'r3, r3, 0x1f'))]
- 49. ATERMi_AutoConfigThread | natural success state conditional | 94.0%; insns 40/40, raw diffs 9; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 2a72ea69c60c.
  [(20, ('nor', 'r0, r3, r0'), ('nor', 'r3, r3, r0')), (21, ('li', 'r5, -1'), ('li', 'r4, -1')), (22, ('srawi', 'r3, r0, 0x1f'), ('lwz', 'r0, 0(0)')), (23, ('lwz', 'r0, 0(0)'), ('srawi', 'r3, r3, 0x1f')), (24, ('addi', 'r4, r3, 7'), ('addi', 'r5, r3, 7')), (26, ('stw', 'r5, 0(0)'), ('stw', 'r4, 0(0)')), (28, ('stw', 'r4, 0(0)'), ('stw', 'r5, 0(0)')), (29, ('stw', 'r4, 8(r1)'), ('stw', 'r5, 8(r1)')), (30, ('stw', 'r5, 0xc(r1)'), ('stw', 'r4, 0xc(r1)'))]
- 50. ATERMi_AutoConfigThread | signed equality mask and differences | 94.75%; insns 40/40, raw diffs 3; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source d2eaf3bd417e.
  [(20, ('nor', 'r0, r3, r0'), ('nor', 'r3, r3, r0')), (22, ('srawi', 'r3, r0, 0x1f'), ('lwz', 'r0, 0(0)')), (23, ('lwz', 'r0, 0(0)'), ('srawi', 'r3, r3, 0x1f'))]
- 51. ATERMi_AutoConfigThread | reuse completed protocol result for equality conversion | 94.75%; insns 40/40, raw diffs 3; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 95359512eff0.
  [(20, ('nor', 'r0, r3, r0'), ('nor', 'r3, r3, r0')), (22, ('srawi', 'r3, r0, 0x1f'), ('lwz', 'r0, 0(0)')), (23, ('lwz', 'r0, 0(0)'), ('srawi', 'r3, r3, 0x1f'))]
- 52. ATERMi_AutoConfigThread | compute completed state before clearing deadline | 94.75%; insns 40/40, raw diffs 3; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source f54a2c488169.
  [(20, ('nor', 'r0, r3, r0'), ('nor', 'r3, r3, r0')), (22, ('srawi', 'r3, r0, 0x1f'), ('lwz', 'r0, 0(0)')), (23, ('lwz', 'r0, 0(0)'), ('srawi', 'r3, r3, 0x1f'))]
- 53. ATERMAesExpandEncryptKey | AES128 complete round helper with key and table pointers | 98.94403%; insns 268/268, raw diffs 49; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source a32b33356575.
- 54. ATERMAesExpandEncryptKey | key word scoped to each expansion loop | 98.94403%; insns 268/268, raw diffs 49; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 98a10255e639.
- 55. ATERMAesExpandEncryptKey | initial key word helper returns typed prefix | 95.07462%; insns 276/268, raw diffs 238; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source c7433d61db68.
- 56. ATERMAesExpandEncryptKey | initial key words declared in source key order | 98.75746%; insns 268/268, raw diffs 53; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source c2fde2849166.
- 57. ATERMBuildAssociationRequest | MAC helper takes source before destination | 98.353386%; insns 133/133, raw diffs 36; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 01a77b707532.
- 58. ATERMBuildAssociationRequest | hex helper takes byte before destination | 97.55639%; insns 133/133, raw diffs 50; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source ad1e81c2104b.
- 59. ATERMBuildAssociationRequest | generic MAC formatter takes byte length | 97.55639%; insns 133/133, raw diffs 50; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 6a8b98d981a8.
- 60. ATERMBuildAssociationRequest | MAC formatter returns end for caller terminator | 97.55639%; insns 133/133, raw diffs 50; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source d8d2fe341273.
- 61. ATERMBuildAssociationRequest | formatter uses separate input and output cursor locals | 98.7594%; insns 133/133, raw diffs 28; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 6fa4cc5bdf9e.
- 62. ATERMBuildAssociationRequest | hex helper uses named high and low nibble pair | 95.86466%; insns 135/133, raw diffs 82; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source c2e1b8b6900d.
- 63. ATERMBuildAssociationRequest | nested encoder walks high then low bit shifts | 90.112785%; insns 141/133, raw diffs 88; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 7f72664a7718.
- 64. ATERMBuildAssociationRequest | shift iterator declared before encoded cursor | 90.112785%; insns 141/133, raw diffs 88; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 656ddbec82f4.
- 65. ATERMBuildAssociationRequest | counted two nibble encoder computes shift from index | 84.77444%; insns 149/133, raw diffs 98; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source fe0f85e80c95.
- 66. ATERMBuildAssociationRequest | MAC iteration counter declared before cursors | 97.55639%; insns 133/133, raw diffs 50; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source df1d3cc250e8.
- 67. ATERMBuildAssociationRequest | MAC output cursor declared before source cursor | 97.90225%; insns 133/133, raw diffs 44; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 215be2dbfafc.
- 68. ATERMBuildAssociationRequest | MAC source parameter and separate output local | 97.55639%; insns 133/133, raw diffs 50; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 552cd8557386.
- 69. ATERMBuildAssociationRequest | MAC destination parameter and separate source local | 97.52631%; insns 133/133, raw diffs 50; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source ffdab3e296e7.
- 70. ATERMBuildAssociationRequest | generic source length destination formatter with local cursors | 98.7594%; insns 133/133, raw diffs 28; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 2887994aeb05.
- 71. ATERMBuildAssociationRequest | byte encoder reads const source pointer | 98.7594%; insns 133/133, raw diffs 28; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 696c66c93789.
- 72. ATERMBuildAssociationRequest | byte encoder advances source through pointer reference | 98.7594%; insns 133/133, raw diffs 28; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source be9942193ab4.
- 73. ATERMBuildAssociationRequest | byte encoder accepts promoted unsigned source | 98.7594%; insns 133/133, raw diffs 28; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 969d0759ee91.
- 74. ATERMBuildAssociationRequest | low nibble initialized before high nibble | 98.233086%; insns 133/133, raw diffs 40; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 426a42485d7b.
- 75. ATERMBuildAssociationRequest | named low and high nibble locals feed encoder array | 98.7594%; insns 133/133, raw diffs 28; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 53ee44be5f3f.
- 76. ATERMBuildAssociationRequest | caller prepares nibble pair for generic encoder | 98.7594%; insns 133/133, raw diffs 28; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 851008378cc6.
- 77. ATERMBuildAssociationRequest | nibble encoder takes source pair before output | 98.7594%; insns 133/133, raw diffs 28; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source eadb1112bc18.
- 78. ATERMBuildAssociationRequest | MAC caller terminates each encoded byte | 95.52631%; insns 131/133, raw diffs 63; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source afe8ffc70e9f.
- 79. ATERMBuildAssociationRequest | nibble array uses aggregate initializer | BUILD FAILED: FAILED: [code=2] build/43U/src/src/scene/setting/ATERM.o  build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c -O4,p -inline on -MMD -c src/scene/setting/ATERM.c -o build/43U/src/src/scene/setting && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/scene/setting/ATERM.d build/43U/src/src/scene/setting/ATERM.d ### mwcceppc.exe Compiler: #    File: src\scene\setting\ATERM.c # ---------------------------------- #    1147:     s32 nibbles[2] = { (byte & 0xF0) >> 4, byte & 0xF };  #   Error:                                                        ^ #   (10124) illegal constant expression #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- 80. ATERMDiscoverAccessPoints | separate MAC cursors from improved association helper | 97.50951%; insns 263/263, raw diffs 194; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source fc6f890167ce.
- 81. ATERMDiscoverAccessPoints | nested encoders and saved g3 timeout exit structure | 98.28897%; insns 261/263, raw diffs 221; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 9f59e4faaf4b.
- 82. AOSSXorBufferWithKey | word sized XOR input temporary | 98.605446%; insns 147/147, raw diffs 36; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source e475166a02d9.
- 83. AOSSXorBufferWithKey | separate input and mask byte temporaries | 98.5034%; insns 147/147, raw diffs 39; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source c2477032e383.
- 84. AOSSXorBufferWithKey | word sized input and mask temporaries | 98.5034%; insns 147/147, raw diffs 39; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source e5e0c9245d6e.
- 85. AOSSXorBufferWithKey | plain packet first XOR expression | 98.5034%; insns 147/147, raw diffs 39; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source 0ce5c64bd095.
- 86. AOSSXorBufferWithKey | const mask view scoped to XOR loop | 98.605446%; insns 147/147, raw diffs 36; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source 8e6622364ecc.
- 87. AOSSXorBufferWithKey | separate advancing mask and output cursors | 92.58504%; insns 147/147, raw diffs 33; exact 17; code 7720; data 3928; regressions []; POOL IDENTICAL up to 1 (mine=1 base=1); source e0b32c732285.
- 88. ATERMi_AutoConfigThread | completion state uses boolean offset from success | 83.35%; insns 40/40, raw diffs 6; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 2b613479ad71.
  [(18, ('subfic', 'r3, r31, 1'), ('addi', 'r3, r31, -1')), (19, ('addi', 'r0, r31, -1'), ('subfic', 'r0, r31, 1')), (20, ('or', 'r0, r3, r0'), ('nor', 'r3, r3, r0')), (22, ('srwi', 'r3, r0, 0x1f'), ('lwz', 'r0, 0(0)')), (23, ('lwz', 'r0, 0(0)'), ('srawi', 'r3, r3, 0x1f')), (24, ('addi', 'r5, r3, 6'), ('addi', 'r5, r3, 7'))]
- 89. ATERMi_AutoConfigThread | snapshot result before converting completion state | 91.325%; insns 40/40, raw diffs 8; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source b26c2f4cb063.
  [(20, ('nor', 'r0, r3, r0'), ('nor', 'r3, r3, r0')), (22, ('srawi', 'r3, r0, 0x1f'), ('lwz', 'r0, 0(0)')), (23, ('lwz', 'r0, 0(0)'), ('srawi', 'r3, r3, 0x1f')), (26, ('stw', 'r0, 0x10(r1)'), ('stw', 'r4, 0(0)')), (28, ('stw', 'r4, 0(0)'), ('stw', 'r5, 0(0)')), (29, ('stw', 'r5, 0(0)'), ('stw', 'r5, 8(r1)')), (30, ('stw', 'r5, 8(r1)'), ('stw', 'r4, 0xc(r1)')), (31, ('stw', 'r4, 0xc(r1)'), ('stw', 'r0, 0x10(r1)'))]
- 90. ATERMi_AutoConfigThread | separate result snapshot after equality mask | 94.75%; insns 40/40, raw diffs 3; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 9b402c8bbf87.
  [(20, ('nor', 'r0, r3, r0'), ('nor', 'r3, r3, r0')), (22, ('srawi', 'r3, r0, 0x1f'), ('lwz', 'r0, 0(0)')), (23, ('lwz', 'r0, 0(0)'), ('srawi', 'r3, r3, 0x1f'))]
- 91. ATERMi_AutoConfigThread | store conditional completed state directly then copy to progress | 94.0%; insns 40/40, raw diffs 9; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source fdef1741a1e8.
  [(20, ('nor', 'r0, r3, r0'), ('nor', 'r3, r3, r0')), (21, ('li', 'r5, -1'), ('li', 'r4, -1')), (22, ('srawi', 'r3, r0, 0x1f'), ('lwz', 'r0, 0(0)')), (23, ('lwz', 'r0, 0(0)'), ('srawi', 'r3, r3, 0x1f')), (24, ('addi', 'r4, r3, 7'), ('addi', 'r5, r3, 7')), (26, ('stw', 'r5, 0(0)'), ('stw', 'r4, 0(0)')), (28, ('stw', 'r4, 0(0)'), ('stw', 'r5, 0(0)')), (29, ('stw', 'r4, 8(r1)'), ('stw', 'r5, 8(r1)')), (30, ('stw', 'r5, 0xc(r1)'), ('stw', 'r4, 0xc(r1)'))]
- 92. ATERMi_AutoConfigThread | natural completion conditional with deadline beside remaining time | 91.625%; insns 40/40, raw diffs 6; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 174fbca34236.
  [(20, ('nor', 'r0, r3, r0'), ('nor', 'r3, r3, r0')), (22, ('srawi', 'r3, r0, 0x1f'), ('lwz', 'r0, 0(0)')), (23, ('lwz', 'r0, 0(0)'), ('srawi', 'r3, r3, 0x1f')), (26, ('stw', 'r5, 0(0)'), ('stw', 'r4, 0(0)')), (28, ('stw', 'r5, 8(r1)'), ('stw', 'r5, 0(0)')), (29, ('stw', 'r4, 0(0)'), ('stw', 'r5, 8(r1)'))]

Storage hypothesis for ATERMStartNetworkStack: the target separately prepares IP and interface pointers from one BSS anchor, then obtains the SSID from that anchor. The source groups the IP and interface values into a single struct. Search confirmed gNetworkSettings has no references outside ATERM.c. Test separate real NCD configuration objects, preserving types and declaration order, without padding or symbol/config edits. Reject any data or exact-function regression.

- 93. ATERMStartNetworkStack | separate real IP and interface configuration globals | 100.0%; insns 154/154, raw diffs 0; exact 20; code 12200; data 10424; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 9787c322851d.
  []
- 94. ATERMStartNetworkStack | explicit zero initialization of separate configuration objects | 100.0%; insns 154/154, raw diffs 0; exact 20; code 12200; data 10424; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source 34b8e0ca9c4f.
  []
- 95. ATERMBuildEncryptedMessage | trailing checksum helper with C89 declarations corrected | 93.739586%; insns 96/96, raw diffs 74; exact 19; code 11584; data 18584; regressions []; POOL IDENTICAL up to 0 (mine=0 base=0); source ee427e4a5bac.

## Exact ATERMStartNetworkStack candidate and data ownership proof

Trial 93 matches ATERMStartNetworkStack at 100.0%, 154/154 instructions, ctxdiff diffs 0. It separates actual NCDIpConfig and NCDIfConfig globals. No other baseline exact function regresses. The target clears 0x7c4 IP bytes at 814021E0..814021E8, passes that same base to NCDSetIpConfig at 81402264..81402268, then clears 0x15e bytes at base+0x7c4 at 8140226C..81402278 and passes that second address to NCDSetIfConfig at 814022B0..814022B4. The SSID begins at base+0x924 at 81402288 and 814022A4.

The old reference metadata described all 0x924 bytes as one inferred ATERM_810BECA0 object. Correct ownership is IP 0x810BECA0 size 0x7c4, interface 0x810BF464 size 0x15e, then the existing two alignment bytes before SSID 0x810BF5C4. The candidate emitted exactly these addresses. All later objects retain offsets 0x924, 0x948, 0xba0, 0x14a0 and 0x1cb8. No data object was inserted, removed, padded, or forced into a section. The unit split and total_data 18864 are unchanged. Only the two real configuration symbols are corrected in symbols.txt, with the inferred aggregate typedef removed from C. This corrects an overbroad inferred object boundary, not function size or code ownership. Preserve the original reference ELF in scratch and verify section bytes plus relocation-resolved targets before accepting.

Reference ELF ownership verification: every allocated section, including .text, .data and .bss, has identical size and bytes before/after the symbol correction; all 594 relocation destinations and addends are unchanged after resolving symbol section+value+addend. Unit data total remains 18864.

## Coverage and disposition

95 trials were attempted. Trials 37 and 79 failed C89 compilation and do not count toward coverage; trial 95 corrects the checksum helper declaration order. No compiler flags, pragmas, assembly, shared headers, forced data objects or linking settings changed. Both guard experiments are restored. AOSS and AOSSLink source equal entry baseline. ATERM retains only the exact network configuration split and corresponding proven data ownership correction.

- AOSS_Init_old: 4 compiled trials; baseline 96.18624%; best 96.77273%, 1578/1584 instructions, raw diffs 1265; OPEN; all trials restored; trials 9, 10, 11, 12.
- AOSSApplyAuthOptions: 4 compiled trials; baseline 98.77193%; best 97.67544%, 114/114 instructions, raw diffs 23; OPEN; all trials restored; trials 13, 14, 15, 16.
- AOSSSendHelloRequest: 4 compiled trials; baseline 92.48351%; best 92.48351%, 271/273 instructions, raw diffs 254; OPEN; all trials restored; trials 17, 18, 19, 20.
- AOSSXorBufferWithKey: 10 compiled trials; baseline 98.605446%; best 98.605446%, 147/147 instructions, raw diffs 36; OPEN; all trials restored; trials 21, 22, 23, 24, 82, 83, 84, 85, 86, 87.
- ATERMStartNetworkStack: 6 compiled trials; baseline 97.91558%; best 100.0%, 154/154 instructions, raw diffs 0; RETAINED EXACT with ownership correction; trials 25, 26, 27, 28, 93, 94.
- ATERMDiscoverAccessPoints: 6 compiled trials; baseline 95.304184%; best 98.28897%, 261/263 instructions, raw diffs 221; OPEN; all trials restored; trials 29, 30, 31, 32, 80, 81.
- ATERMBuildEncryptedMessage: 6 compiled trials; baseline 99.791664%; best 99.791664%, 96/96 instructions, raw diffs 4; OPEN; all trials restored; trials 38, 39, 40, 41, 42, 95.
- ATERMBuildAssociationRequest: 26 compiled trials; baseline 93.44361%; best 98.7594%, 133/133 instructions, raw diffs 28; OPEN; all trials restored; trials 33, 34, 35, 36, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78.
- ATERMRunConfigProtocol: 5 compiled trials; baseline 89.77287%; best 89.77287%, 958/951 instructions, raw diffs 929; OPEN; all trials restored; trials 43, 44, 45, 46, 47.
- ATERMi_AutoConfigThread: 10 compiled trials; baseline 94.75%; best 94.75%, 40/40 instructions, raw diffs 3; OPEN; all trials restored; trials 48, 49, 50, 51, 52, 88, 89, 90, 91, 92.
- ATERMAesExpandEncryptKey: 4 compiled trials; baseline 98.94403%; best 98.94403%, 268/268 instructions, raw diffs 49; OPEN; all trials restored; trials 53, 54, 55, 56.
- AOSSi_WLANGetBSSList: 4 compiled trials; baseline 98.48018%; best 98.37004%, 227/227 instructions, raw diffs 30; OPEN; all trials restored; trials 1, 2, 3, 4.
- AOSSi_WLANConnect: 4 compiled trials; baseline 98.70968%; best 98.70968%, 155/155 instructions, raw diffs 2; OPEN; all trials restored; trials 5, 6, 7, 8.

Best remaining source leads: trial 61/70 takes ATERMBuildAssociationRequest to 98.7594% with two nested MAC/hex helpers and separate const input/output cursors, but leaves 28 register differences. Trial 81 combines those helpers with the saved g3 timeout exits for ATERMDiscoverAccessPoints at 98.28897%, still 261/263 instructions. Neither is an exact match or part of the retained source. Trial 12 raises AOSS_Init_old to 96.77273% but loses eight matched data bytes by omitting the original default-options reads, so it is rejected. All compiling trials ran pool_diff before instruction/objdiff inspection.

## Final open functions

- AOSSi_WLANGetBSSList: 98.48018%; retry counters, descriptor pointer and channel initialization scheduling differ.
- AOSSi_WLANConnect: 98.70968%; two memset argument setup instructions remain swapped.
- AOSS_Init_old: 96.18624%; guard correction does not resolve control flow, stack layout and register allocation.
- AOSSApplyAuthOptions: 98.77193%; response cursor, option counters and parameter copies still use different registers.
- AOSSSendHelloRequest: 92.48351%; CRC and stream scheduling remains 271/273 instructions.
- AOSSXorBufferWithKey: 98.605446%; XOR output and unrolled buffer pointers use different registers.
- ATERMDiscoverAccessPoints: 95.304184%; timeout exits, scan state registers and MAC formatting differ.
- ATERMBuildEncryptedMessage: 99.791664%; two prologue moves remain swapped; raw ctxdiff also has two CR1 branch normalization artifacts.
- ATERMBuildAssociationRequest: 93.44361%; nested helper trial fixes counted loop shape but retains register differences.
- ATERMRunConfigProtocol: 89.77287%; TLV guard, MD5 temporary layout and protocol control flow differ; generated switch table remains nonexact.
- ATERMi_AutoConfigThread: 94.75%; NOR destination and result load versus shift order differ.
- ATERMAesExpandEncryptKey: 98.94403%; initial word assembly and key expansion use different registers.

## Final clean gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 7720/16192 data 3928/3928 functions 17/21 fuzzy 97.9155 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 15/21
[src/scene/setting/AOSS]   section .bss size 3496 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 100.0
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 97.91551
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 96.18624
[src/scene/setting/AOSS]   below 100: AOSSApplyAuthOptions 98.77193
[src/scene/setting/AOSS]   below 100: AOSSSendHelloRequest 92.48351
[src/scene/setting/AOSS]   below 100: AOSSXorBufferWithKey 98.605446
[src/scene/setting/AOSS] baseline: code 7720/16192 data 3928 functions 17 fuzzy 97.9155
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 12200/19204 data 18584/18864 functions 20/26 fuzzy 97.4284 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 19/26
[src/scene/setting/ATERM]   section .bss size 8160 match 100.0
[src/scene/setting/ATERM]   section .data size 280 match 92.14286
[src/scene/setting/ATERM]   section .rodata size 10280 match 100.0
[src/scene/setting/ATERM]   section .sbss size 80 match 100.0
[src/scene/setting/ATERM]   section .sdata size 56 match 100.0
[src/scene/setting/ATERM]   section .sdata2 size 8 match 100.0
[src/scene/setting/ATERM]   section .text size 19204 match 97.42845
[src/scene/setting/ATERM]   below 100: ATERMDiscoverAccessPoints 95.304184
[src/scene/setting/ATERM]   below 100: ATERMBuildEncryptedMessage 99.791664
[src/scene/setting/ATERM]   below 100: ATERMBuildAssociationRequest 93.44361
[src/scene/setting/ATERM]   below 100: ATERMRunConfigProtocol 89.77287
[src/scene/setting/ATERM]   below 100: ATERMi_AutoConfigThread 94.75
[src/scene/setting/ATERM]   below 100: ATERMAesExpandEncryptKey 98.94403
[src/scene/setting/ATERM] baseline: code 11584/19204 data 18584 functions 19 fuzzy 97.3616
[src/scene/setting/AOSSLink] pool: IDENTICAL
[src/scene/setting/AOSSLink] objdiff: code 668/2196 data 2432/2432 functions 12/14 fuzzy 99.0073 linked code 0
[src/scene/setting/AOSSLink] instruction-exact functions: 12/14
[src/scene/setting/AOSSLink]   section .bss size 2344 match 100.0
[src/scene/setting/AOSSLink]   section .data size 48 match 100.0
[src/scene/setting/AOSSLink]   section .sbss size 40 match 100.0
[src/scene/setting/AOSSLink]   section .text size 2196 match 99.007286
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANGetBSSList 98.48018
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANConnect 98.70968
[src/scene/setting/AOSSLink] baseline: code 668/2196 data 2432 functions 12 fuzzy 99.0073
regressions vs baseline: 0
global matched_code_percent: 92.55309 -> 92.57366
global fuzzy_match_percent: 99.73582 -> 99.73624
global complete_code_percent: 76.20227 -> 76.20227
global matched_data_percent: 99.94696 -> 99.94696
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```

Fresh post-gate ctxdiff: ATERMStartNetworkStack src 0x268/base 0x268, 154/154 instructions, diffs 0. Explicit Ninja build/43U/ok reports no work to do. DOL SHA1 remains 26116613f624061ba99c8d1a299aaa6efa85670d. All pools identical; global regressions, forbidden additions and readability warnings are zero. ATERM objdiff exact functions 19 -> 20; instruction-exact 18 -> 19; matched code 11584 -> 12200; matched data 18584 unchanged. AOSS and AOSSLink counts and bytes unchanged. The whole units remain incomplete. Parent must review the proven symbol-boundary correction and repeat its own acceptance gate.

## Unretained follow-up reproductions

These diffs reproduce the best remaining encoding trials against base 34858f3f. They are not part of the retained source or a claimed exact match.

### 061-ATERMBuildAssociationRequest.c

```diff
--- a/src/scene/setting/ATERM.c
+++ b/src/scene/setting/ATERM.c
@@ -1143,6 +1143,38 @@
     return 0;
 }
 
+static inline s32 atermFormatHexByte(char* output, u8 byte) {
+    s32 nibbles[2];
+    s32 index;
+    char* encoded = output;
+    nibbles[0] = (byte & 0xF0) >> 4;
+    nibbles[1] = byte & 0xF;
+    for (index = 0; index < 2; index++) {
+        s32 nibble = nibbles[index];
+        if (nibble <= 9) {
+            *encoded++ = nibble + '0';
+        } else {
+            *encoded++ = nibble + '7';
+        }
+    }
+    *encoded = 0;
+    return encoded - output;
+}
+
+static inline void atermFormatMacAddress(char* text, const u8* address) {
+    const u8* input = address;
+    char* output = text;
+    s32 index;
+    for (index = 0; index < 6; index++) {
+        u8 byte = *input++;
+        output += atermFormatHexByte(output, byte);
+        if (index < 5) {
+            *output++ = ':';
+        }
+    }
+    *output = 0;
+}
+
 int ATERMBuildAssociationRequest(AtermAssociationRequest* request) {
     u8 scanAddress[8];
     u8 interfaceMacAddress[8];
@@ -1164,66 +1196,8 @@
         memcpy(request->secondAddress, interfaceMacAddress, 6);
     }
     if (gAtermUseSharedAddress != 0) {
-        {
-            const u8* addressCursor = interfaceMacAddress;
-            const u8* addressEnd = interfaceMacAddress + 6;
-            int addressIndex;
-            char* textCursor = interfaceMacText;
-            addressIndex = 0;
-            do {
-                u8 addressByte = *addressCursor++;
-                char* encoded = textCursor;
-                s32 highNibble = (addressByte & 0xF0) >> 4;
-                s32 lowNibble = addressByte & 0xF;
-                if (highNibble <= 9) {
-                    *encoded++ = highNibble + '0';
-                } else {
-                    *encoded++ = highNibble + '7';
-                }
-                if (lowNibble <= 9) {
-                    *encoded++ = lowNibble + '0';
-                } else {
-                    *encoded++ = lowNibble + '7';
-                }
-                *encoded = 0;
-                textCursor += encoded - textCursor;
-                if (addressIndex < 5) {
-                    *textCursor++ = ':';
-                }
-                addressIndex++;
-            } while (addressCursor < addressEnd);
-            *textCursor = '\0';
-        }
-        {
-            const u8* addressCursor = scanAddress;
-            const u8* addressEnd = scanAddress + 6;
-            int addressIndex;
-            char* textCursor = scanAddressText;
-            addressIndex = 0;
-            do {
-                u8 addressByte = *addressCursor++;
-                char* encoded = textCursor;
-                s32 highNibble = (addressByte & 0xF0) >> 4;
-                s32 lowNibble = addressByte & 0xF;
-                if (highNibble <= 9) {
-                    *encoded++ = highNibble + '0';
-                } else {
-                    *encoded++ = highNibble + '7';
-                }
-                if (lowNibble <= 9) {
-                    *encoded++ = lowNibble + '0';
-                } else {
-                    *encoded++ = lowNibble + '7';
-                }
-                *encoded = 0;
-                textCursor += encoded - textCursor;
-                if (addressIndex < 5) {
-                    *textCursor++ = ':';
-                }
-                addressIndex++;
-            } while (addressCursor < addressEnd);
-            *textCursor = '\0';
-        }
+        atermFormatMacAddress(interfaceMacText, interfaceMacAddress);
+        atermFormatMacAddress(scanAddressText, scanAddress);
     }
     return 1;
 }
```

### 081-ATERMDiscoverAccessPoints.c

```diff
--- a/src/scene/setting/ATERM.c
+++ b/src/scene/setting/ATERM.c
@@ -870,6 +870,38 @@
     return result;
 }
 
+static inline s32 atermFormatHexByte(char* output, u8 byte) {
+    s32 nibbles[2];
+    s32 index;
+    char* encoded = output;
+    nibbles[0] = (byte & 0xF0) >> 4;
+    nibbles[1] = byte & 0xF;
+    for (index = 0; index < 2; index++) {
+        s32 nibble = nibbles[index];
+        if (nibble <= 9) {
+            *encoded++ = nibble + '0';
+        } else {
+            *encoded++ = nibble + '7';
+        }
+    }
+    *encoded = 0;
+    return encoded - output;
+}
+
+static inline void atermFormatMacAddress(char* text, const u8* address) {
+    const u8* input = address;
+    char* output = text;
+    s32 index;
+    for (index = 0; index < 6; index++) {
+        u8 byte = *input++;
+        output += atermFormatHexByte(output, byte);
+        if (index < 5) {
+            *output++ = ':';
+        }
+    }
+    *output = 0;
+}
+
 int ATERMDiscoverAccessPoints(void) {
     s32 result = -1;
     u32 scanBufferBytes;
@@ -963,35 +995,7 @@
             memcpy(gAtermSelectedBssid,
                 selectedRecord->bssid,
                 sizeof(selectedRecord->bssid));
-            {
-                u8* addressCursor = gAtermSelectedBssid;
-                s32 addressIndex = 0;
-                char* output = selectedMacText;
-
-                for (addressIndex = 0; ; addressIndex++) {
-                    u8 addressByte = *addressCursor++;
-                    char* encoded = output;
-                    s32 highNibble = (addressByte & 0xF0) >> 4;
-                    s32 lowNibble = addressByte & 0xF;
-                    if (highNibble <= 9) {
-                        *encoded++ = highNibble + '0';
-                    } else {
-                        *encoded++ = highNibble + '7';
-                    }
-                    if (lowNibble <= 9) {
-                        *encoded++ = lowNibble + '0';
-                    } else {
-                        *encoded++ = lowNibble + '7';
-                    }
-                    *encoded = 0;
-                    output += encoded - output;
-                    if (addressIndex == 5) {
-                        break;
-                    }
-                    *output++ = ':';
-                }
-                *output = '\0';
-            }
+            atermFormatMacAddress(selectedMacText, gAtermSelectedBssid);
             break;
         }
 
@@ -1010,18 +1014,18 @@
         iteration++;
     }
 
-    if (iteration < 300) {
-        now = (u32)OSTicksToMilliseconds(OSGetTime());
-        if (now > gAtermDeadline) {
-            result = -3;
-        } else {
-            result = 1;
-            if (gAtermCancelRequested != 0) {
-                result = -8;
-            }
-        }
+    if (iteration >= 300) {
+        goto timed_out;
+    }
+    now = (u32)OSTicksToMilliseconds(OSGetTime());
+    if (now > gAtermDeadline) {
+    timed_out:
+        result = -3;
     } else {
-        result = -3;
+        result = 1;
+        if (gAtermCancelRequested != 0) {
+            result = -8;
+        }
     }
 
 cleanup:
```

All retained code is ordinary C. No uninitialized-local trial survives. Initial chatter followed the higher-priority runtime requirement for commentary; the attempted worker silent-mode contract was therefore not met. Existing untracked a9h/a9m/a9x/u3 logs were left untouched. Scratch trial files are removed after this log records final validation and the useful follow-up reproductions.
