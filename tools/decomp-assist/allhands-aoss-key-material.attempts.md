# AOSS contiguous key-material representation

Base candidate: 00b02c27 (the separate WLAN argument-contract correction). Original branch base: 9c7d87ab. 43U only.

## Evidence and focused change

The original decryptor copies two raw nonce bytes and eight access-point bytes into consecutive positions of s_packetState, then passes that base and length 10 to AOSSInitKeySchedule. The original hello sender builds the same key. The key-schedule helper actually indexes all ten bytes; its instruction stream and resolved calls match the source exactly.

Previously the caller passed keyNonce[2] with length sizeof(keyNonce)+sizeof(keyAddress), relying on indexing beyond the first array member. AOSSKeyMaterial now represents the complete key as named nonce[2] and address[8] members. s_packetState embeds this key object, followed by its unchanged payload[0x5e]. Each schedule call uses a const u8 byte view of the complete key object with sizeof(key), so the byte span belongs to the object being viewed.

Only the two nonce copies, two address copies, and two key-schedule calls in AOSSDecryptMessage/AOSSSendHelloRequest are updated. No other packet representation, algorithm, checksum, byte order, allocation, validation, state transition, header or protocol change. No added storage, alignment, padding or assembly.

## Layout and gates

- Key size 10, nonce offset 0, address offset 2, packet payload offset 10, packet-state size 104, natural byte alignment unchanged
- Entire compiled AOSS.o is byte-identical to 00b02c27, including all payloads, symbol spellings and relocations
- Full-project objdiff unchanged from branch baseline: unit 97.71665% fuzzy, 16/21 exact, 6436 exact code bytes, 3928/3928 data bytes; no matching gain claimed
- DecryptMessage remains 97.74143%, 321/321 instructions and the same 87 allocation/operand differences
- Pool identical, 1/1; literal-reference audit still checks 12 arguments in 19 functions without candidates/errors, with the same two unequal-size skips (AOSS_Init_old and AOSSSendHelloRequest)
- ASan/UBSan extracted-production harness passes 68,423 cases: all 65,536 nonce byte combinations with varied addresses against an independent schedule model; every valid payload length 0..0x5c0; checksum/allocation/manufacturer/control error paths; 1,024 hello sender encryption round trips. It asserts key layout/content, unchanged trailing payload, output copy/checksum order and allocation cleanup. The production decryptor, sender, key scheduling, CRC table and name check execute; manufacturer scrambling and transport are controlled stubs, with no network activity
- The separate 30,600-case WLAN pointer/host-wait validator is rerun and passes
- LeakSanitizer disabled for ptrace restriction; address and undefined-behavior instrumentation enabled
- Full 43U build and ok gate pass; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d
- git diff --check passes

Private reproducible validators, reports and build logs: /tmp/aoss-key-call-contracts. Original disassembly remains private in /tmp/aoss-decrypt-audit.
