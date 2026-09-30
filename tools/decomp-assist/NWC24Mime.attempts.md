# NWC24Mime matching attempts

Baseline: no source, 0/16 functions, 0/6124 code bytes, 0/88 data bytes.
All functions are implemented in object order, with ordinary literals.
The encoding alphabet, pointer and small marker strings match all 88 data bytes.
The initial implementation was adapted from readable C references available
in /tmp, then checked against the target object and object-exported Ghidra C.
Oversized Ghidra stack arrays were replaced with actual octet/scalar storage.

## Source-level experiments

Base64Encode | canonical three-byte loop from SDK | (96.233765, -37) | src 0x134 base 0x134 insns 77/77
Base64Encode | mask initial sextet | (80.19481, -9999) | src 0x144 base 0x134 insns 81/77
Base64Encode | pointer-relative second byte | (80.38961, -9999) | src 0x144 base 0x134 insns 81/77
NWC24InitBase64Table | unsigned scan index | (97.41304, -51) | src 0x2e0 base 0x2e0 insns 184/184
NWC24InitBase64Table | one character scan with explicit bounds | (100.0, 0) | src 0x2e0 base 0x2e0 insns 184/184
QEncode | signed copy count | (73.83251, -9999) | src 0x324 base 0x32c insns 201/203
QEncode | credit output before optional line break | (72.28571, -9999) | src 0x2fc base 0x32c insns 191/203
QEncode | initialize encoded byte before classification | (69.3202, -9999) | src 0x2f4 base 0x32c insns 189/203
QDecode | signed cursors | (74.9315, -9999) | src 0x234 base 0x248 insns 141/146
QDecode | predicate return order | (74.863014, -9999) | src 0x234 base 0x248 insns 141/146
QDecode | remaining input while loop | (74.9315, -9999) | src 0x234 base 0x248 insns 141/146
QEncode | SDK signed copy scan and octet operations | (100.0, 0) | src 0x32c base 0x32c insns 203/203
EncodeWord | unsigned intermediate string length | (69.91919, -9999) | src 0x2c0 base 0x318 insns 176/198
EncodeWord | capacity condition reversed | (69.86869, -9999) | src 0x2c0 base 0x318 insns 176/198
EncodeWord | defer overflow flag initialization | (69.91919, -9999) | src 0x2c0 base 0x318 insns 176/198
CopyWithoutLinearWhiteSpaces | switch classification | (8.835616, -55) | src 0x124 base 0x124 insns 73/73
CopyWithoutLinearWhiteSpaces | signed output offset | (14.315068, -9999) | src 0x114 base 0x124 insns 69/73
CopyWithoutLinearWhiteSpaces | cache input value across capacity check | (10.068493, -9999) | src 0x110 base 0x124 insns 68/73
DecodeWord | repeat consumed initialization before capacity return | (77.37222, -161) | src 0x2d0 base 0x2d0 insns 180/180
DecodeWord | independent whitespace scan pointer | (74.02778, -9999) | src 0x2c0 base 0x2d0 insns 176/180
DecodeWord | unconditional decoded size on copy overflow | (74.094444, -9999) | src 0x2b8 base 0x2d0 insns 174/180
NWC24DecodeMIMEHeaderFieldBody | check decode status before consumed count | (74.13043, -9999) | src 0x158 base 0x170 insns 86/92
NWC24DecodeMIMEHeaderFieldBody | signed remaining input | (81.195656, -9999) | src 0x158 base 0x170 insns 86/92
NWC24DecodeMIMEHeaderFieldBody | direct input size parameter scan | (81.195656, -9999) | src 0x158 base 0x170 insns 86/92
ConcatEncodedText | signed prefix length | (93.22222, -43) | src 0xfc base 0xfc insns 63/63
ConcatEncodedText | single remaining capacity expression | (93.492065, -41) | src 0xfc base 0xfc insns 63/63
ConcatEncodedText | positive capacity branch | (90.84127, -9999) | src 0x100 base 0xfc insns 64/63
ExtractCharset | signed scan indices | (74.04762, -9999) | src 0x148 base 0x150 insns 82/84
ExtractCharset | signed extracted length | (75.34524, -9999) | src 0x144 base 0x150 insns 81/84
ExtractCharset | reuse marker length for span | (75.34524, -9999) | src 0x144 base 0x150 insns 81/84
ExtractEncodedText | signed scan index | (85.4, -9999) | src 0x208 base 0x21c insns 130/135
ExtractEncodedText | unsigned extracted length | (87.437035, -9999) | src 0x204 base 0x21c insns 129/135
ExtractEncodedText | merge invalid pointer predicates | (87.36296, -9999) | src 0x204 base 0x21c insns 129/135
CopyWithoutLinearWhiteSpaces | switch with loop continuation predicate | (98.287674, -20) | src 0x124 base 0x124 insns 73/73
CopyWithoutLinearWhiteSpaces | unsigned cached capacity | (98.42466, -18) | src 0x124 base 0x124 insns 73/73
CopyWithoutLinearWhiteSpaces | capacity before output counter | (98.287674, -20) | src 0x124 base 0x124 insns 73/73
Base64Encode | combine shifted initial octet | (100.0, 0) | src 0x134 base 0x134 insns 77/77
CopyWithoutLinearWhiteSpaces | declare character before flags | (98.42466, -18) | src 0x124 base 0x124 insns 73/73
CopyWithoutLinearWhiteSpaces | separate default pointer advancement | (98.561646, -17) | src 0x124 base 0x124 insns 73/73
CopyWithoutLinearWhiteSpaces | cache capacity minus terminator | (96.9863, -10) | src 0x124 base 0x124 insns 73/73
NWC24DecodeMIMEHeaderFieldBody | bounded signed input and output cursors | (85.92391, -9999) | src 0x16c base 0x170 insns 91/92
NWC24DecodeMIMEHeaderFieldBody | avoid initial consumed-count clear | (82.065216, -9999) | src 0x154 base 0x170 insns 85/92
NWC24DecodeMIMEHeaderFieldBody | fold status into loop condition | (83.36957, -9999) | src 0x16c base 0x170 insns 91/92
QDecode | moving input/output cursors | (81.99315, -9999) | src 0x230 base 0x248 insns 140/146
QDecode | late moving cursor initialization | (81.03425, -9999) | src 0x230 base 0x248 insns 140/146
QDecode | decode high nibble before low conversion | (86.20548, -9999) | src 0x230 base 0x248 insns 140/146
QDecode | independent pointer validation | (81.10274, -9999) | src 0x238 base 0x248 insns 142/146
NWC24DecodeMIMEHeaderFieldBody | independent encoded-pointer validation | (88.20652, -9999) | src 0x174 base 0x170 insns 93/92
NWC24DecodeMIMEHeaderFieldBody | consumed count written by decoder | (86.95652, -9999) | src 0x168 base 0x170 insns 90/92
NWC24DecodeMIMEHeaderFieldBody | defer remaining input initialization | (88.097824, -9999) | src 0x16c base 0x170 insns 91/92

## Retained result

8/16 instruction-exact and objdiff-exact functions; 2240/6124 code bytes;
88/88 data bytes. Base64 encoding uses the canonical three-byte scan and
one initial shifted-octet expression. Alphabet initialization scans actual
character bounds. Quoted-printable encoding uses a signed byte-copy scan.
All remaining functions have at least three logged distinct experiments.
Remaining differences: QDecode cursor/error control flow; EncodeWord append
status propagation; CopyWithoutLinearWhiteSpaces register allocation;
DecodeWord search/status allocation; MIME header validation and cursor
allocation; ConcatEncodedText allocation; charset/text search loop scheduling.
Combination of moving QDecode cursor initialization and sequential nibble
conversion gives 86.54794%. Combining bounded MIME-header scanning, independent
input validation and decoder-owned consumed count gives 86.03261%.
No other unit or shared header was changed.

## Continuation 2026-09-30

Baseline: 8/16 exact functions; 2240/6124 code bytes; 88/88 data bytes.

CopyWithoutLinearWhiteSpaces | signed output count with unsigned bound comparison | (98.561646, -17) | src 0x124 base 0x124 insns 73/73
CopyWithoutLinearWhiteSpaces | declare capacity before newline state | (98.561646, -17) | src 0x124 base 0x124 insns 73/73
CopyWithoutLinearWhiteSpaces | for scan with advancing input in iteration expression | (98.561646, -17) | src 0x124 base 0x124 insns 73/73
CopyWithoutLinearWhiteSpaces | signed output-size count with character declared early | (98.561646, -17) | src 0x124 base 0x124 insns 73/73
ConcatEncodedText | defer result before remaining-byte count | (93.492065, -41) | src 0xfc base 0xfc insns 63/63
ConcatEncodedText | unsigned available-byte count with signed exhaustion check | (93.492065, -41) | src 0xfc base 0xfc insns 63/63
ConcatEncodedText | increment encoded size before terminator store | (91.42857, -41) | src 0xfc base 0xfc insns 63/63
ConcatEncodedText | positive capacity body before overflow case | (100.0, 0) | src 0xfc base 0xfc insns 63/63
ExtractEncodedText | inline marker search with pointer-valued results | (91.25926, -9999) | src 0x208 base 0x21c insns 130/135
ExtractEncodedText | independent invalid pointer checks | (86.85185, -9999) | src 0x20c base 0x21c insns 131/135
ExtractEncodedText | cache encoded-word span before decoding | (84.36296, -9999) | src 0x204 base 0x21c insns 129/135
QDecode | separate null input and output checks | (87.60959, -9999) | src 0x238 base 0x248 insns 142/146
QDecode | unsigned nibble values | (86.54794, -9999) | src 0x230 base 0x248 insns 140/146
QDecode | reverse valid-nibble conjunction | (86.58219, -9999) | src 0x230 base 0x248 insns 140/146
NWC24DecodeMIMEHeaderFieldBody | late input count initialization | (88.36957, -9999) | src 0x17c base 0x170 insns 95/92
NWC24DecodeMIMEHeaderFieldBody | use signed remaining count and final test | (86.08696, -9999) | src 0x17c base 0x170 insns 95/92
NWC24DecodeMIMEHeaderFieldBody | fold error status into loop continuation | (83.58696, -9999) | src 0x17c base 0x170 insns 95/92
DecodeWord | pointer scan for inter-word whitespace | (77.26111, -161) | src 0x2d0 base 0x2d0 insns 180/180
DecodeWord | permissive output size updated unconditionally on copy failure | (78.833336, -9999) | src 0x2c8 base 0x2d0 insns 178/180
DecodeWord | signed marker-match position length | (0, -9999) | [1/1] MWCC build/43U/src/libs/RevoEX/src/nwc24/NWC24Mime.o
ExtractCharset | inline marker search with pointer-valued results | (83.75, -9999) | src 0x148 base 0x150 insns 82/84
ExtractCharset | comparison expressed as positive capacity test | (75.34524, -9999) | src 0x144 base 0x150 insns 81/84
ExtractCharset | delay initial delimiter variables | (76.72619, -9999) | src 0x144 base 0x150 insns 81/84
EncodeWord | store encoding character before validation | (71.681816, -9999) | src 0x2c0 base 0x318 insns 176/198
EncodeWord | defer encoded overflow flag until concat result | (69.91919, -9999) | src 0x2c0 base 0x318 insns 176/198
EncodeWord | positive charset pointer branch first | (69.81313, -9999) | src 0x2c4 base 0x318 insns 177/198
ExtractCharset | moving marker cursor with base-plus-index return | (84.64286, -9999) | src 0x154 base 0x150 insns 85/84
ExtractEncodedText | moving marker cursor with base-plus-index return | (89.85185, -9999) | src 0x214 base 0x21c insns 133/135

DecodeWord | consumed count declared before decoded count | (78.88333, -9999) | src 0x2c8 base 0x2d0 insns 178/180

Retained continuation: positive-capacity ConcatEncodedText is instruction-exact.
FindMarker provides shared bounded scans with real pointer results.
Header decoding initializes its remaining input after argument validation;
QDecode validates each pointer separately. DecodeWord copies its size output
unconditionally on the copy-overflow path, as in the target.
All existing exact functions and all data bytes are preserved.

## Remaining functions

CopyWithoutLinearWhiteSpaces, 98.561646%: 73/73 instructions; saved-register allocation and scheduling differ.
ExtractEncodedText, 91.25926%: bounded-marker scans and decoder dispatch still have different control flow.
NWC24DecodeMIMEHeaderFieldBody, 88.36957%: error handling and loop termination emit different branches.
QDecode, 87.60959%: hex-digit classification and input-loop branches differ.
ExtractCharset, 83.75%: 82/84 instructions; second delimiter scan and register lifetimes differ.
DecodeWord, 78.88333%: 178/180 instructions; delimiter search, whitespace handling, and error exits differ.
EncodeWord, 71.681816%: 176/198 instructions; append-capacity checks and overflow exits differ.
