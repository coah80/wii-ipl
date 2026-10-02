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

## w1008/cdb leaf — dead-fn fossil + Encrypt coloring (worker w1008)

SOLVED — link-deadstrip fossil mechanism: orig .data's fossil literals (0x398-0x9be)
come from ~15 dead functions whose code mwldeppc stripped at link. Added all dead
fns (CDBRecordGetFileSize through CDBRecordPrivateChangeOwner) as GLOBAL fns in
fossil-emission order; global (not static) emits standalone code AND auto-inlines
at use sites. .data content byte-identical (orig has 2B reconstruction tail pad).
Verified at DOL level: fossil strings land at exact expected vaddrs.

SOLVED — Encrypt +0x40 code gap: `err = CDBRecordGetFileSize(record, &fileSize)`
calls the dead fn which auto-inlines, reproducing orig's expanded block.
`(s32)ptr == 0` → `cmpwi r0,0` required (== NULL gives cmplw). 284/284 insns
identical, 0 stream diffs.

WALL — CDBRecordEncrypt 57 byte diffs, pure callee-reg coloring on identical
web structure. Orig packs {key+err}→r24, {tempFile+fileOffset}→r31, pool→r25,
args→r26-29; mine packs {tempFile+err}→r24, {key+fileOffset}→r29, pool→r31,
args→r25-28. Equal-cost packings (tie-break). ~18 probes all neutral/regressed:
recordFile/err/tempFile/fileOffset decl order+scope+init forms, per-block vs
shared `result`, single-web fileOffset (-69), fn-scope tempFile, `register`,
err dead-init (emits, +4B/831), u32/s32 types, decl+init forms.
DOL-verified: the entire DOL diff vs orig = exactly these 57 bytes.
