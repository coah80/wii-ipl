# CDBRecord attempts

Baseline: 0/29 exact, 0/7076 code bytes.

Reconstructed descriptor, instance, cryptographic, and file operations using the target instructions and existing declarations. Named mutex, used flag, database and open flags replace opaque offsets; the header layout is gated by CDB_RECORD_IMPLEMENTATION.

The pool first diverges at string 8: the original contains diagnostics for file-size, reduction, setters, duplication and owner-change functions absent from this extracted object. No unused string objects or artificial padding were retained. BSS buffers and zero AES key match (144 bytes); the 2496-byte data section remains partial.

CDBCryptBuffer | for loop offset progression | (99.97479, -3) | src 0x1dc base 0x1dc insns 119/119
CDBCryptBuffer | remaining-length comparison | (92.411766, -9999) | src 0x1d8 base 0x1dc insns 118/119
CDBCryptBuffer | named input chunk pointer | (96.40336, -9999) | src 0x1e0 base 0x1dc insns 120/119
CDBRecordEncrypt | integer null tests | (96.20422, -68) | src 0x470 base 0x470 insns 284/284
CDBRecordEncrypt | signature and hmac declaration order | (90.60564, -9999) | src 0x494 base 0x470 insns 293/284
CDBRecordEncrypt | single file temporary for setters | (90.60564, -9999) | src 0x494 base 0x470 insns 293/284
CDBRecordDecrypt | 64-byte hash key alignment | (86.073395, -9999) | src 0x384 base 0x368 insns 225/218
CDBRecordDecrypt | integer null tests | (90.348625, -9999) | src 0x370 base 0x368 insns 220/218
CDBRecordDecrypt | signature before digest declaration | (86.0367, -9999) | src 0x384 base 0x368 insns 225/218
CDBRecordDecrypt | signature and hmac alignment | (99.89449, -23) | src 0x368 base 0x368 insns 218/218
CDBRecordDecrypt | 64-byte key alignment with signature | (99.89449, -23) | src 0x368 base 0x368 insns 218/218
CDBRecordDecrypt | reverse file and status declaration lifetime | (99.68807, -32) | src 0x368 base 0x368 insns 218/218
CDBRecordDecrypt | swap digest and key-string lifetimes | (99.944954, -12) | src 0x368 base 0x368 insns 218/218
CDBRecordDecrypt | 16-byte key string alignment | (99.94954, -11) | src 0x368 base 0x368 insns 218/218
CDBRecordDecrypt | unaligned key string | (99.94954, -11) | src 0x368 base 0x368 insns 218/218
CDBRecordDecrypt | complete record key | (99.96789, -7) | src 0x368 base 0x368 insns 218/218

Additional Encrypt attempt: moved error status to the outer scope, 97.19014%, 283/284 instructions.
Additional Decrypt correction: restored 0x3E800 size limit, actual seek/read error returns, level-3 owner warning, output-size local; 218/218 instructions. Natural buffer alignment and declaration order reach 99.96789%, seven stack-address differences.

Remaining: CDBCryptBuffer 99.97479%, 119/119 instructions, three pool offsets; CDBRecordEncrypt 97.19014%, register allocation and one instruction; CDBRecordDecrypt 99.96789%, stack placement.

The four forced field accessors end with CDBUnlock and do not produce a CDBErr result. Their void declarations are gated by CDB_RECORD_IMPLEMENTATION, preserving all other translation units and avoiding fall-through non-void definitions.

## Wave: dead-helper emission decode (scene2 leaf)

Decoded MWCC literal-emission model via /tmp/tlit*.c experiments:
- Non-static fns emit literals + standalone .text bodies at DEF position, even uncalled.
- Static fns fully inlined at all call sites emit literals at FIRST-CALL parse position, no body.
- A call inside ANY runtime check materializes code at the inlined site — MWCC never
  constant-folds `&local != NULL` (tlit10: `if(src==NULL)` w/ `&loc` arg emits addic+bne).
- A static called only from a body that never materializes emits literals but no .text.

Final structure (all helpers NON-STATIC dead impl fns at orig def positions):
- CDBRecordGetFileSize_ (def after Seek, before GetDataSize) -> emits @0x1b0
- ReduceFileSize_/ReduceDataSize_ before Remove -> 0x228-0x38c
- SetFileType_..GetCalenderTime_ before GetTypeForce -> 0x428-0x7d4
- CDBRecordDuplicate_ (pure key+field copies, called by BackupToSD_) -> inlines clean
- CDBRecordDuplicatePanic_ (dead, OSPanic __FILE__ pair) -> 0x8d8/0x8e4
- CDBRecordPrivateChangeOwner_ ({CDBReport_(3);OSReport(sjis)}, called by Decrypt) -> inlines
- CDBRecordPrivateChangeOwnerDebug_ (dead 5-OSReport debug block) -> 0x958-0x9b4
- Extra .text bodies of dead extern fns are score-neutral (objdiff counts orig fns only).
- Decrypt's first locked report = "can't get data size" (0x1ec, NOT modified-time; orig
  Decrypt refs 0x1ec + SJIS 0x940 only). GetId refs 0x814 (CDBId) + 0x5b0 (maker code).
- Orig Encrypt refs base+0x1b0/0x1ec/0x178 (file-size/data-size/read reports, 3 refs ->
  homes .data base in r25). Record struct field `file` is void* -> needs (CDBRecordFile*) cast.

Result: .data byte-identical (mod extraction tail pad), 28/29 fns at 100%.
Residual: CDBRecordEncrypt pure register-home permutation (153 diff lines, all REGNAME,
instruction-count-equal). Orig: base=r25, record=r26, buffer=r27, key/err=r24, size=r28,
encSize=r29, recordFile=r30, file=r31. Mine: base=r31, params shifted -1, key=r29.
Tried: recordFile decl order (worse, 159), recordFile load after memset (key->r24 fixed
but CR-field regressions, 155). Documented tie-break.
