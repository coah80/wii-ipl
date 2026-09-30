# RevoEX net attempts

md5/NETMD5GetDigest: current expression and loop forms: src 0x128 base 0x128 insns 74/74; diffs 6: [38, 40, 41, 42, 44, 45]
md5/ProcessBlock: current expression and loop forms: src 0x498 base 0x4c8 insns 294/306; --- replace mine 2:4 base 2:4
md5/NETMD5GetDigest: integer locals and alternate loop declarations: src 0x128 base 0x128 insns 74/74; diffs 6: [38, 40, 41, 42, 44, 45]
md5/ProcessBlock: integer locals and alternate loop declarations: src 0x498 base 0x4c8 insns 294/306; --- replace mine 2:4 base 2:4
md5/NETMD5GetDigest: expression grouping and assignment order: src 0x128 base 0x128 insns 74/74; diffs 6: [38, 40, 41, 42, 44, 45]
md5/ProcessBlock: expression grouping and assignment order: src 0x498 base 0x4c8 insns 294/306; --- replace mine 2:4 base 2:4
md5/NETMD5GetDigest: retained readable candidate: src 0x128 base 0x128 insns 74/74; diffs 6: [38, 40, 41, 42, 44, 45]
md5/ProcessBlock: retained readable candidate: src 0x498 base 0x4c8 insns 294/306; --- replace mine 2:4 base 2:4
hmac/NETHMACInit: current expression and loop forms: src 0x23c base 0x23c insns 143/143; diffs 79: [8, 12, 14, 16, 18, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34]
hmac/NETHMACGetDigest: current expression and loop forms: src 0x198 base 0x1a4 insns 102/105; --- delete mine 4:5 base 4:4
hmac/NETHMACInit: integer locals and alternate loop declarations: src 0x23c base 0x23c insns 143/143; diffs 79: [8, 12, 14, 16, 18, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34]
hmac/NETHMACGetDigest: integer locals and alternate loop declarations: src 0x198 base 0x1a4 insns 102/105; --- delete mine 4:5 base 4:4
hmac/NETHMACInit: expression grouping and assignment order: src 0x23c base 0x23c insns 143/143; diffs 79: [8, 12, 14, 16, 18, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34]
hmac/NETHMACGetDigest: expression grouping and assignment order: src 0x198 base 0x1a4 insns 102/105; --- delete mine 4:5 base 4:4
hmac/NETHMACInit: retained readable candidate: src 0x23c base 0x23c insns 143/143; diffs 79: [8, 12, 14, 16, 18, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34]
hmac/NETHMACGetDigest: retained readable candidate: src 0x198 base 0x1a4 insns 102/105; --- delete mine 4:5 base 4:4
aes/AESiEncryptBlock: current expression and loop forms: src 0x278 base 0x278 insns 158/158; diffs 137: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 21, 23, 24, 25, 26]
aes/AESiDecryptBlock: current expression and loop forms: src 0x3c4 base 0x3ec insns 241/251; --- insert mine 6:6 base 6:7
aes/NETAESCreateEx: current expression and loop forms: src 0x19c base 0x1b0 insns 103/108; --- replace mine 19:21 base 19:21
aes/AESiEncryptBlock: integer locals and alternate loop declarations: src 0x27c base 0x278 insns 159/158; --- replace mine 0:1 base 0:1
aes/AESiDecryptBlock: integer locals and alternate loop declarations: src 0x3c8 base 0x3ec insns 242/251; --- insert mine 6:6 base 6:7
aes/NETAESCreateEx: integer locals and alternate loop declarations: src 0x19c base 0x1b0 insns 103/108; --- replace mine 19:21 base 19:21
aes/AESiEncryptBlock: expression grouping and assignment order: src 0x278 base 0x278 insns 158/158; diffs 139: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 21, 23, 24, 25, 26]
aes/AESiDecryptBlock: expression grouping and assignment order: src 0x3c4 base 0x3ec insns 241/251; --- insert mine 6:6 base 6:7
aes/NETAESCreateEx: expression grouping and assignment order: src 0x19c base 0x1b0 insns 103/108; --- replace mine 19:21 base 19:21
aes/AESiEncryptBlock: retained readable candidate: src 0x278 base 0x278 insns 158/158; diffs 137: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 21, 23, 24, 25, 26]
aes/AESiDecryptBlock: retained readable candidate: src 0x3c4 base 0x3ec insns 241/251; --- insert mine 6:6 base 6:7
aes/NETAESCreateEx: retained readable candidate: src 0x19c base 0x1b0 insns 103/108; --- replace mine 19:21 base 19:21

md5 NETMD5Update: deferred available calculation and declared available before data; 60/60 instructions, diffs 0.
sha1: reordered remaining-length locals and replaced memcpy with a 16-word copy loop; all exact. SHA1 round XOR order b ^ c ^ d gives diffs 0.
neterrorcode: initialized index before mask and disabled inlining inside startup caller; all exact.
