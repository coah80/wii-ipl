# fz3 attempts

Start HEAD 5543b7b720e18b9e093f2f3a9e8f9d4cb3a2eabb; origin/main 422a344b282c65104a9157a99239d0950b337472

libs/RVL_SDK/src/fa/pf_fat12 pool: POOL IDENTICAL up to 0 (mine=0 base=0)

src/keyboard/tiSignWindow pool: POOL IDENTICAL up to 30 (mine=30 base=30)

libs/RVL_SDK/src/fa/msc/puh_msc_blk pool: POOL IDENTICAL up to 0 (mine=0 base=0)

libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32 pool: POOL IDENTICAL up to 0 (mine=0 base=0)

## PFFAT12_ReadFATEntryWithBuf
Remote source unchanged. Pool empty. Target/source both 0x30 frame, 155 instructions, identical branches and operand forms; remaining registers cycle error/current FAT/sector/offset.
PFFAT12_ReadFATEntryWithBuf | callback result scoped to callback block | 155/155 instructions; structural/exact differences (0, 34)
PFFAT12_ReadFATEntryWithBuf | pointer-index byte read form | 155/155 instructions; structural/exact differences (0, 34)
PFFAT12_ReadFATEntryWithBuf | inverted terminal success branch | 155/155 instructions; structural/exact differences (9, 46)
restored structural trials; 155/155 instructions; structural/exact differences (0, 34)
PFFAT12_ReadFATEntryWithBuf exhaustive declarations ('    pf_u32 sector;', '    pf_u32 current_fat;', '    pf_s32 err;', '    pf_u32 offset;', '    pf_s32 result;') (0, 23)
exhaustive retained 155/155 instructions; structural/exact differences (0, 23)

## create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator
Remote source unchanged. Pool 30 strings identical; data already 3468/3468. Target/source frame 0x50, 221 instructions, branch/operand structure identical, hoisted vtable and count registers differ.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | for outer loop instead of do/while | 221/221 instructions; structural/exact differences (0, 34)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | animation count scoped after append | BUILD FAIL clude/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c++ -O4,p -MMD -c src/keyboard/tiSignWindow.cpp -o build/43U/src/src/keyboard && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/keyboard/tiSignWindow.d build/43U/src/src/keyboard/tiSignWindow.d
### mwcceppc.exe Compiler:
#    File: src\keyboard\tiSignWindow.cpp
# --------------------------------------
#      77:     {0, "N_SGNkeytop_all", 3, 0, {&csAninationFileForSign[0], &csAninationFileForSign[1], &csAninationFileForSign[2]}}, 
#   Error:                             ^
#   (10209) illegal implicit conversion from 'int' to
#   'const char *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | shared allocation buffer across switch arms | 221/221 instructions; structural/exact differences (0, 34)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | animation table reference declared before pane pointer | 221/221 instructions; structural/exact differences (0, 34)
restored 221/221 instructions; structural/exact differences (0, 34)
PFFAT12_ReadFATEntryWithBuf | offset computation temporary separate from in-sector offset | 155/155 instructions; structural/exact differences (0, 23)
PFFAT12_ReadFATEntryWithBuf | distinct FAT flush index and read error | 155/155 instructions; structural/exact differences (0, 34)
PFFAT12_ReadFATEntryWithBuf | sector narrowing as cast and offset as additive expression | 155/155 instructions; structural/exact differences (0, 26)
fat retained 155/155 instructions; structural/exact differences (0, 23)

## uhf_msc_blk_pread
Remote source unchanged. Pool empty; all 424 data bytes already paired. Target/source frames and 129 instructions identical. Transfer block variable scoped in loop shifts callee-saved coloring; control flow and operands identical.
uhf_msc_blk_pread | transfer block count declared at function scope | 129/129 instructions; structural/exact differences (0, 17)
uhf_msc_blk_pread | cache flag positive comparison | 129/129 instructions; structural/exact differences (0, 33)
uhf_msc_blk_pread | transfer byte length named in copy block | 129/129 instructions; structural/exact differences (0, 33)
hoisted transfer declaration 129/129 instructions; structural/exact differences (0, 17)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | retry animation count scoped only inside create | 221/221 instructions; structural/exact differences (0, 59)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | force name and count both scoped after append | 221/221 instructions; structural/exact differences (0, 61)
sign declaration search:
declaration block:
      const char* forceName;
      u32 animationCount;
      u32 paneIndex = 0;
start (0, 34)
best (0, 34) after 6 builds; source restored; best order was:
    const char* forceName;
    u32 animationCount;
    u32 paneIndex = 0;

sign retained 221/221 instructions; structural/exact differences (0, 34)
PFFAT12_ReadFATEntryWithBuf | initialize error before offset | 155/155 instructions; structural/exact differences (3, 26)
PFFAT12_ReadFATEntryWithBuf | initialize error at declaration | 155/155 instructions; structural/exact differences (3, 26)
PFFAT12_ReadFATEntryWithBuf | load current FAT before sector calculation | 155/155 instructions; structural/exact differences (15, 38)
PFFAT12_ReadFATEntryWithBuf | inline callback result direct local | 155/155 instructions; structural/exact differences (0, 23)
retained fat 155/155 instructions; structural/exact differences (0, 23)

## uhf_msc_blk_pwrite
Remote source unchanged. Empty pool and 424/424 data. Both frames 0x40 and 129 instructions, branch forms and operands identical; device and transfer-block registers exchanged.
uhf_msc_blk_pwrite | transfer count scoped to transfer loop | 129/129 instructions; structural/exact differences (0, 30)
uhf_msc_blk_pwrite | cache flag explicit zero and positive comparisons | 129/129 instructions; structural/exact differences (0, 16)
uhf_msc_blk_pwrite | find device loop in caller scope | 129/129 instructions; structural/exact differences (0, 7)
pwrite restored 129/129 instructions; structural/exact differences (0, 16)

## TMCJPEGDEC_decode_iquant
Remote source unchanged. No data section or strings. Both 0x50 frames and 276 instructions. Structural diagnosis: AC aggregate stack slot 0x18 instead of 8; DC/AC helper copy slots reversed; long-code addition operands reversed; helper parameter/temporary colors differ.
TMCJPEGDEC_decode_iquant | AC entry scoped to AC decode block | 276/276 instructions; structural/exact differences (12, 59)
TMCJPEGDEC_decode_iquant | shared long Huffman inline helper for DC and AC | 277/276 instructions; structural/exact differences (19, 177)
TMCJPEGDEC_decode_iquant | Huffman symbol offset as named difference plus symbol | BUILD FAIL  include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -use_lmw_stmw on -lang=c -MMD -c libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32.c -o build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/b65 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32.d build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32.d
### mwcceppc.exe Compiler:
#    File: libs\RVLMiddleware\TMC_JPEG\src\b65\iqdec_b65_frv32.c
# --------------------------------------------------------------
#      58:             u32 symbolIndex = code - entry->bitLength; 
#   Error:             ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

jpeg restored 276/276 instructions; structural/exact differences (12, 59)
uhf_msc_blk_pread retained caller-scope lookup 129/129 instructions; structural/exact differences (0, 35)
uhf_msc_blk_pwrite retained caller-scope lookup 129/129 instructions; structural/exact differences (0, 7)
pread declaration search:
declaration block:
      u16 transfer_blocks;
      s32 error;
      UHF_MSC_DEVICE* device;
      u32 block_size;
      u8* transfer_buffer;
      u32 transfer_limit;
      s32 cacheable;
      u8 sense[3] = {0};
start (0, 17)
best (0, 17) after 71 builds; source restored; best order was:
    u16 transfer_blocks;
    s32 error;
    UHF_MSC_DEVICE* device;
    u32 block_size;
    u8* transfer_buffer;
    u32 transfer_limit;
    s32 cacheable;
    u8 sense[3] = {0};

pwrite declaration search:
declaration block:
      u16 transfer_blocks;
      UHF_MSC_DEVICE* device;
      u32 block_size;
      s32 error;
      u8* transfer_buffer;
      u32 transfer_limit;
      s32 cacheable;
      u8 sense[3] = {0};
start (0, 16)
best (0, 16) after 71 builds; source restored; best order was:
    u16 transfer_blocks;
    UHF_MSC_DEVICE* device;
    u32 block_size;
    s32 error;
    u8* transfer_buffer;
    u32 transfer_limit;
    s32 cacheable;
    u8 sense[3] = {0};

TMCJPEGDEC_decode_iquant | unsigned Huffman symbol offset temporary | 276/276 instructions; structural/exact differences (12, 58)
TMCJPEGDEC_decode_iquant | AC aggregate declared after DC helper calls | 276/276 instructions; structural/exact differences (12, 59)
TMCJPEGDEC_decode_iquant | long helper code and table entry declaration order reversed | 276/276 instructions; structural/exact differences (12, 63)
TMCJPEGDEC_decode_iquant | Huffman table advance as byte-scaled index | 276/276 instructions; structural/exact differences (12, 59)
TMCJPEGDEC_decode_iquant | fast DC consumption assigned directly to work field | 276/276 instructions; structural/exact differences (12, 57)
jpeg retained 276/276 instructions; structural/exact differences (12, 59)
uhf_msc_blk_pread | find index at function scope | 129/129 instructions; structural/exact differences (0, 17)
uhf_msc_blk_pread | find index declared first | 129/129 instructions; structural/exact differences (0, 17)
uhf_msc_blk_pread | find index narrower signed int | 129/129 instructions; structural/exact differences (0, 17)
uhf_msc_blk_pread | explicit cursor for device lookup | 129/129 instructions; structural/exact differences (2, 17)
uhf_msc_blk_pwrite | find index at function scope | 129/129 instructions; structural/exact differences (0, 7)
uhf_msc_blk_pwrite | find index declared first | 129/129 instructions; structural/exact differences (0, 35)
uhf_msc_blk_pwrite | find index narrower signed int | 129/129 instructions; structural/exact differences (0, 7)
uhf_msc_blk_pwrite | explicit cursor for device lookup | 129/129 instructions; structural/exact differences (2, 7)
msc retained pread 129/129 instructions; structural/exact differences (0, 17)
msc retained pwrite 129/129 instructions; structural/exact differences (0, 7)
uhf_msc_blk_pwrite | cursor increment before index | 129/129 instructions; structural/exact differences (0, 7)
uhf_msc_blk_pwrite | find index before null assignment | 129/129 instructions; structural/exact differences (0, 8)
uhf_msc_blk_pwrite | return device through inline output helper | 129/129 instructions; structural/exact differences (0, 35)
retained pwrite 129/129 instructions; structural/exact differences (0, 7)
uhf_msc_blk_pwrite | inline device lookup using output parameter | 129/129 instructions; structural/exact differences (0, 28)
uhf_msc_blk_pwrite | inline output lookup parameter order swapped | 129/129 instructions; structural/exact differences (0, 28)
restored 129/129 instructions; structural/exact differences (0, 7)
uhf_msc_blk_pwrite | index declared before explicit cursor | 129/129 instructions; structural/exact differences (0, 0)
uhf_msc_blk_pwrite | cursor initialized before device | 129/129 instructions; structural/exact differences (0, 0)
uhf_msc_blk_pwrite | cursor object at function scope | 129/129 instructions; structural/exact differences (0, 7)
uhf_msc_blk_pwrite | loop count explicitly starts before cursor | 129/129 instructions; structural/exact differences (0, 0)
restored pwrite 129/129 instructions; structural/exact differences (0, 7)
retained index before cursor uhf_msc_blk_pread 129/129 instructions; structural/exact differences (0, 10)
retained index before cursor uhf_msc_blk_pwrite 129/129 instructions; structural/exact differences (0, 0)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | pane table pointer instead of reference | 221/221 instructions; structural/exact differences (0, 34)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | animation index function scope | 221/221 instructions; structural/exact differences (0, 63)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | pane pointer function scope | 221/221 instructions; structural/exact differences (0, 34)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | animation record pointer named in inner loop | 219/221 instructions; structural/exact differences (9, 91)
restored sign 221/221 instructions; structural/exact differences (0, 34)
uhf_msc_blk_pread | transfer bytes function scope | 129/129 instructions; structural/exact differences (0, 15)
uhf_msc_blk_pread | transfer bytes before block count declaration | 129/129 instructions; structural/exact differences (0, 17)
uhf_msc_blk_pread | count at loop scope with explicit device cursor | 129/129 instructions; structural/exact differences (0, 27)
uhf_msc_blk_pread | byte copy in inline helper | 129/129 instructions; structural/exact differences (0, 10)
restored pread 129/129 instructions; structural/exact differences (0, 10)

## First accepted improvement
Pwrite 129/129 instructions and ctxdiff diffs 0. Fresh objdiff 100%. Caller-scope lookup with index declared before cursor restores target scratch registers. Pread remains open; declsearch restores its closest order. FAT/JPEG declaration searches improve fuzzy scores without changing instruction count or matched neighbors. Data already 100% in every owned unit, so no symbol rename or extent edit needed.
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/pf_fat12] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_fat12] objdiff: code 1544/2164 data None/None functions 3/4 fuzzy 99.7597 linked code 0
[libs/RVL_SDK/src/fa/pf_fat12] instruction-exact functions: 3/4
[libs/RVL_SDK/src/fa/pf_fat12]   section .text size 2164 match 99.759705
[libs/RVL_SDK/src/fa/pf_fat12]   below 100: PFFAT12_ReadFATEntryWithBuf 99.16129
[libs/RVL_SDK/src/fa/pf_fat12] baseline: code 1544/2164 data None functions 3 fuzzy 99.6396
[src/keyboard/tiSignWindow] pool: IDENTICAL
[src/keyboard/tiSignWindow] objdiff: code 6300/7184 data 3468/3468 functions 55/56 fuzzy 99.8914 linked code 0
[src/keyboard/tiSignWindow] instruction-exact functions: 55/56
[src/keyboard/tiSignWindow]   section .ctors size 4 match 100.0
[src/keyboard/tiSignWindow]   section .data size 2672 match 100.0
[src/keyboard/tiSignWindow]   section .rodata size 784 match 100.0
[src/keyboard/tiSignWindow]   section .sdata size 8 match 100.0
[src/keyboard/tiSignWindow]   section .text size 7184 match 99.891426
[src/keyboard/tiSignWindow]   below 100: create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.117645
[src/keyboard/tiSignWindow] baseline: code 6300/7184 data 3468 functions 55 fuzzy 99.8914
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] pool: IDENTICAL
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] objdiff: code 1556/2072 data 424/424 functions 10/11 fuzzy 99.8938 linked code 0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] instruction-exact functions: 10/11
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .bss size 384 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .data size 32 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .text size 2072 match 99.89382
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   below 100: uhf_msc_blk_pread 99.57365
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] baseline: code 1040/2072 data 424 functions 9 fuzzy 99.4498
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 98.9058 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 98.9058
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 98.9058
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 98.8333
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.59130
global fuzzy_match_percent: 99.45531 -> 99.45574
global complete_code_percent: 63.16065 -> 63.16065
global matched_data_percent: 98.20744 -> 98.20744
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
uhf_msc_blk_pread copy-block helper parameters ('destination', 'source', 'blocks', 'block_size') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('destination', 'source', 'block_size', 'blocks') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('destination', 'blocks', 'source', 'block_size') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('destination', 'blocks', 'block_size', 'source') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('destination', 'block_size', 'source', 'blocks') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('destination', 'block_size', 'blocks', 'source') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('source', 'destination', 'blocks', 'block_size') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('source', 'destination', 'block_size', 'blocks') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('source', 'blocks', 'destination', 'block_size') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('source', 'blocks', 'block_size', 'destination') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('source', 'block_size', 'destination', 'blocks') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('source', 'block_size', 'blocks', 'destination') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('blocks', 'destination', 'source', 'block_size') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('blocks', 'destination', 'block_size', 'source') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('blocks', 'source', 'destination', 'block_size') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('blocks', 'source', 'block_size', 'destination') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('blocks', 'block_size', 'destination', 'source') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('blocks', 'block_size', 'source', 'destination') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('block_size', 'destination', 'source', 'blocks') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('block_size', 'destination', 'blocks', 'source') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('block_size', 'source', 'destination', 'blocks') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('block_size', 'source', 'blocks', 'destination') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('block_size', 'blocks', 'destination', 'source') 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread copy-block helper parameters ('block_size', 'blocks', 'source', 'destination') 129/129 instructions; structural/exact differences (0, 10)
helper permutations restored 129/129 instructions; structural/exact differences (0, 10)
TMCJPEGDEC_decode_iquant AC coefficient loop isolated in real inline helper 276/276 instructions; structural/exact differences (5, 128)
restored JPEG 276/276 instructions; structural/exact differences (12, 55)
uhf_msc_blk_pread | copy byte count at transfer-loop scope | 129/129 instructions; structural/exact differences (0, 33)
uhf_msc_blk_pread | transfer count unsigned int with call-bound narrowing | 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread | copy byte count declared before device | 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread | transfer loop copies with named signed byte count | 129/129 instructions; structural/exact differences (0, 33)
retained pread 129/129 instructions; structural/exact differences (0, 10)
TMCJPEGDEC_decode_iquant | long decode aggregate caller-scope declarations | 276/276 instructions; structural/exact differences (5, 128)
TMCJPEGDEC_decode_iquant | long symbol offset compound assignment | 276/276 instructions; structural/exact differences (5, 129)
TMCJPEGDEC_decode_iquant | AC helper with outer scalar declarations preserved | 276/276 instructions; structural/exact differences (5, 128)
TMCJPEGDEC_decode_iquant | long decoded declarations plus operand compounds | 276/276 instructions; structural/exact differences (5, 129)
restored JPEG 276/276 instructions; structural/exact differences (12, 55)
PFFAT12_ReadFATEntryWithBuf | sixteen-bit byte offset | 156/155 instructions; structural/exact differences (8, 90)
PFFAT12_ReadFATEntryWithBuf | signed byte offset with unsigned boundary compare | 155/155 instructions; structural/exact differences (2, 24)
PFFAT12_ReadFATEntryWithBuf | signed sector with unsigned page comparison | 155/155 instructions; structural/exact differences (0, 23)
PFFAT12_ReadFATEntryWithBuf | callback flag branch as conditional expression | 155/155 instructions; structural/exact differences (0, 23)
FAT restored 155/155 instructions; structural/exact differences (0, 23)
PFFAT12_ReadFATEntryWithBuf | FAT flush loops isolated in genuine inline helper | 155/155 instructions; structural/exact differences (0, 34)
fat restored 155/155 instructions; structural/exact differences (0, 23)
uhf_msc_blk_pread completed randomized leading declarations 900 builds; 129/129 instructions; structural/exact differences (0, 10)
TMCJPEGDEC_decode_iquant | DC and AC limit helpers defined in reverse order | 276/276 instructions; structural/exact differences (5, 128)
TMCJPEGDEC_decode_iquant | Huffman return copied through explicit output pointer | 276/276 instructions; structural/exact differences (5, 128)
TMCJPEGDEC_decode_iquant | Huffman return copied via named initializer | 276/276 instructions; structural/exact differences (5, 128)
restored jpeg 276/276 instructions; structural/exact differences (12, 55)
PFFAT12_ReadFATEntryWithBuf | readable full FAT local names | BUILD FAIL TION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/fa/pf_fat12.c -o build/43U/src/libs/RVL_SDK/src/fa && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/fa/pf_fat12.d build/43U/src/libs/RVL_SDK/src/fa/pf_fat12.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\fa\pf_fat12.c
# ---------------------------------------
#     218:              if (p_page->fat_sector != fat_sector + (0)) { if (p_page->option == 1) { for (error = 0; ; 
#   Error:                                     ^^
#   (10393) 'fat_sector' is not a member of class 'struct PF_CACHE_PAGE'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

PFFAT12_ReadFATEntryWithBuf | error local status name | 155/155 instructions; structural/exact differences (0, 23)
PFFAT12_ReadFATEntryWithBuf | byte offset local FAT offset name | 155/155 instructions; structural/exact differences (0, 23)
fat retained 155/155 instructions; structural/exact differences (0, 23)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (0, 0, 0, 0) 221/221 instructions; structural/exact differences (0, 34)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (0, 0, 0, 1) 221/221 instructions; structural/exact differences (0, 34)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (0, 0, 1, 0) 221/221 instructions; structural/exact differences (0, 63)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (0, 0, 1, 1) 221/221 instructions; structural/exact differences (0, 63)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (0, 1, 0, 0) 221/221 instructions; structural/exact differences (0, 59)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (0, 1, 0, 1) 221/221 instructions; structural/exact differences (0, 59)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (0, 1, 1, 0) 221/221 instructions; structural/exact differences (0, 38)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (0, 1, 1, 1) 221/221 instructions; structural/exact differences (0, 38)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (1, 0, 0, 0) 221/221 instructions; structural/exact differences (0, 61)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (1, 0, 0, 1) 221/221 instructions; structural/exact differences (0, 61)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (1, 0, 1, 0) 221/221 instructions; structural/exact differences (0, 41)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (1, 0, 1, 1) 221/221 instructions; structural/exact differences (0, 41)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (1, 1, 0, 0) 221/221 instructions; structural/exact differences (0, 61)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (1, 1, 0, 1) 221/221 instructions; structural/exact differences (0, 61)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (1, 1, 1, 0) 221/221 instructions; structural/exact differences (0, 65)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator force/count inner and index/pane outer scopes (1, 1, 1, 1) 221/221 instructions; structural/exact differences (0, 65)
sign retained 221/221 instructions; structural/exact differences (0, 34)
AC helper declaration search restored: structural (5,128) unchanged after118 builds; restores better objdiff committed source.
declaration block:
      TMCHuffmanEntry dcEntry;
      u8* huff_sym;
      u32* huff_tbl;
      s32 bit_pos;
      u32 bit_data;
      const TMCHuffmanEntry* dc_fast;
      s32 r;
      s32 blk0;
      s32 extra;
      u32 tmp;
start (5, 128)
best (5, 128) after 118 builds; source restored; best order was:
    TMCHuffmanEntry dcEntry;
    u8* huff_sym;
    u32* huff_tbl;
    s32 bit_pos;
    u32 bit_data;
    const TMCHuffmanEntry* dc_fast;
    s32 r;
    s32 blk0;
    s32 extra;
    u32 tmp;

TMCJPEGDEC_decode_iquant DC fast lookup single bit-index expression 276/276 instructions; structural/exact differences (12, 50)
TMCJPEGDEC_decode_iquant DC fast lookup from work bit buffer 276/276 instructions; structural/exact differences (12, 55)
TMCJPEGDEC_decode_iquant DC fast lookup uses signed bit index 276/276 instructions; structural/exact differences (12, 50)
TMCJPEGDEC_decode_iquant DC consume direct work bit count 276/276 instructions; structural/exact differences (12, 53)
retained JPEG fast lookup 276/276 instructions; structural/exact differences (12, 50)
uhf_msc_blk_pread | inline transfer count selection | 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread | inline count selection reversed parameters | 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread | inline count selection loop-scope destination | BUILD FAIL ath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/fa/msc/puh_msc_blk.c -o build/43U/src/libs/RVL_SDK/src/fa/msc && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/fa/msc/puh_msc_blk.d build/43U/src/libs/RVL_SDK/src/fa/msc/puh_msc_blk.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\fa\msc\puh_msc_blk.c
# ----------------------------------------------
#     237:         transfer_blocks = transfer_limit; 
#   Error:         ^^^^^^^^^^^^^^^
#   (10140) undefined identifier 'transfer_blocks'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

pread restored 129/129 instructions; structural/exact differences (0, 10)
TMCJPEGDEC_decode_iquant explicit Huffman-limit scalar declarations ('    TMCHuffmanEntry limit;', '    u16 bitLength;', '    u16 symbol;') 276/276 instructions; structural/exact differences (12, 50)
TMCJPEGDEC_decode_iquant explicit Huffman-limit scalar declarations ('    TMCHuffmanEntry limit;', '    u16 symbol;', '    u16 bitLength;') 276/276 instructions; structural/exact differences (12, 50)
TMCJPEGDEC_decode_iquant explicit Huffman-limit scalar declarations ('    u16 bitLength;', '    TMCHuffmanEntry limit;', '    u16 symbol;') 276/276 instructions; structural/exact differences (12, 50)
TMCJPEGDEC_decode_iquant explicit Huffman-limit scalar declarations ('    u16 bitLength;', '    u16 symbol;', '    TMCHuffmanEntry limit;') 276/276 instructions; structural/exact differences (12, 50)
TMCJPEGDEC_decode_iquant explicit Huffman-limit scalar declarations ('    u16 symbol;', '    TMCHuffmanEntry limit;', '    u16 bitLength;') 276/276 instructions; structural/exact differences (12, 50)
TMCJPEGDEC_decode_iquant explicit Huffman-limit scalar declarations ('    u16 symbol;', '    u16 bitLength;', '    TMCHuffmanEntry limit;') 276/276 instructions; structural/exact differences (12, 50)
JPEG retained limit 276/276 instructions; structural/exact differences (12, 50)

## Open-function audit before final full gate
PFFAT12_ReadFATEntryWithBuf distinct measured source trials 17; 155/155 instructions; structural/exact differences (0, 23)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator distinct measured source trials 9; 221/221 instructions; structural/exact differences (0, 34)
uhf_msc_blk_pread distinct measured source trials 17; 129/129 instructions; structural/exact differences (0, 10)
TMCJPEGDEC_decode_iquant distinct measured source trials 14; 276/276 instructions; structural/exact differences (12, 50)
Data ownership audit: FAT/JPEG contain no target data; SignWindow .ctors/.data/.rodata/.sdata are fully matched at 3468/3468, MSC .bss/.data/.sbss fully matched at 424/424. No config renames, extents, addresses, or section totals changed.
JPEG structural work retained only direct fast DC lookup simplification; AC helper extraction fixed some stack slots but worsened exact differences and was restored. Every remaining function has more than three built, distinct source attempts. No remaining untried function.

## Final clean full gate
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/pf_fat12] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_fat12] objdiff: code 1544/2164 data None/None functions 3/4 fuzzy 99.7597 linked code 0
[libs/RVL_SDK/src/fa/pf_fat12] instruction-exact functions: 3/4
[libs/RVL_SDK/src/fa/pf_fat12]   section .text size 2164 match 99.759705
[libs/RVL_SDK/src/fa/pf_fat12]   below 100: PFFAT12_ReadFATEntryWithBuf 99.16129
[libs/RVL_SDK/src/fa/pf_fat12] baseline: code 1544/2164 data None functions 3 fuzzy 99.6396
[src/keyboard/tiSignWindow] pool: IDENTICAL
[src/keyboard/tiSignWindow] objdiff: code 6300/7184 data 3468/3468 functions 55/56 fuzzy 99.8914 linked code 0
[src/keyboard/tiSignWindow] instruction-exact functions: 55/56
[src/keyboard/tiSignWindow]   section .ctors size 4 match 100.0
[src/keyboard/tiSignWindow]   section .data size 2672 match 100.0
[src/keyboard/tiSignWindow]   section .rodata size 784 match 100.0
[src/keyboard/tiSignWindow]   section .sdata size 8 match 100.0
[src/keyboard/tiSignWindow]   section .text size 7184 match 99.891426
[src/keyboard/tiSignWindow]   below 100: create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.117645
[src/keyboard/tiSignWindow] baseline: code 6300/7184 data 3468 functions 55 fuzzy 99.8914
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] pool: IDENTICAL
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] objdiff: code 1556/2072 data 424/424 functions 10/11 fuzzy 99.8938 linked code 0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] instruction-exact functions: 10/11
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .bss size 384 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .data size 32 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .text size 2072 match 99.89382
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   below 100: uhf_msc_blk_pread 99.57365
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] baseline: code 1040/2072 data 424 functions 9 fuzzy 99.4498
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 99.0326 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 99.03261
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 99.03261
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 98.8333
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.59130
global fuzzy_match_percent: 99.45531 -> 99.45580
global complete_code_percent: 63.16065 -> 63.16065
global matched_data_percent: 98.20744 -> 98.20744
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
libs/RVL_SDK/src/fa/pf_fat12 POOL IDENTICAL up to 0 (mine=0 base=0)
src/keyboard/tiSignWindow POOL IDENTICAL up to 30 (mine=30 base=30)
libs/RVL_SDK/src/fa/msc/puh_msc_blk POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32 POOL IDENTICAL up to 0 (mine=0 base=0)
Fresh clean-build pwrite ctxdiff: 129/129 instructions, diffs 0. DOL SHA1 correct; regressions 0; forbidden patterns 0; readability warnings 0. Matched data remains 100% for all owned sections.
Second accepted improvement: direct DC fast Huffman index expression raises JPEG fuzzy 98.9058 -> 99.03261; code count stays 0/1. Final clean full gate is PASS over all four units. Original inline-helper boundaries remain uncertain; rejected helper variants were restored.

# Round 2
Start a3b27c9ed0395c408f5c94ff657914456cc7d3f0; current origin/main a3b27c9ed0395c408f5c94ff657914456cc7d3f0
libs/RVL_SDK/src/fa/pf_fat12 POOL IDENTICAL up to 0 (mine=0 base=0)
src/keyboard/tiSignWindow POOL IDENTICAL up to 30 (mine=30 base=30)
libs/RVL_SDK/src/fa/msc/puh_msc_blk POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32 POOL IDENTICAL up to 0 (mine=0 base=0)

## Round 2 PFFAT12_ReadFATEntryWithBuf
Origin/main source unchanged before starting. Pool empty. Frame 0x30 and 155 instructions identical. Structural comparison shows only error/offset registers exchanged; previous leading-declaration search exhausted all120 orders without exact match. New attempts vary real helper and state boundaries before register search.
PFFAT12_ReadFATEntryWithBuf | R2 typed buffered-read state aggregate | 155/155 instructions; structural/exact differences (0, 0)
PFFAT12_ReadFATEntryWithBuf | R2 FAT offset calculation inline helper | 155/155 instructions; structural/exact differences (0, 23)
PFFAT12_ReadFATEntryWithBuf | R2 buffered-read inline boundary ('p_vol', 'p_page', 'cluster', 'p_value') | 155/155 instructions; structural/exact differences (3, 26)
PFFAT12_ReadFATEntryWithBuf | R2 buffered-read inline boundary ('p_page', 'p_vol', 'p_value', 'cluster') | 155/155 instructions; structural/exact differences (3, 26)
PFFAT12_ReadFATEntryWithBuf | R2 buffered-read inline boundary ('cluster', 'p_value', 'p_page', 'p_vol') | 155/155 instructions; structural/exact differences (3, 26)
R2 FAT structural restore 155/155 instructions; structural/exact differences (0, 23)
R2 retained real buffered-read state aggregate 155/155 instructions; structural/exact differences (0, 0)

## R2 accepted FAT result
Real buffered-read state aggregate scalar-replaces without changing frame or instructions. Exact-name objdiff100%, instruction-exact4/4, ctxdiff155/155 diffs0. No extra data or alignment object.
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/pf_fat12] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_fat12] objdiff: code 2164/2164 data None/None functions 4/4 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/pf_fat12] instruction-exact functions: 4/4
[libs/RVL_SDK/src/fa/pf_fat12]   section .text size 2164 match 100.0
[libs/RVL_SDK/src/fa/pf_fat12] baseline: code 1544/2164 data None functions 3 fuzzy 99.7597
regressions vs baseline: 0
global matched_code_percent: 88.64712 -> 88.66782
global fuzzy_match_percent: 99.47315 -> 99.47333
global complete_code_percent: 63.16065 -> 63.16065
global matched_data_percent: 98.51344 -> 98.51344
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS

## Round 2 create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator
Origin/main unchanged before starting. Pool 30strings and3468data bytes identical. Same0x50frame and221instructions. Differences involve hoisted constructor vtables, animation record pointer/count. Previous scopes/loop/declsearch tried; new typed creation-state and constructor-helper boundaries.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R2 outer creation state | 221/221 instructions; structural/exact differences (0, 38)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R2 creation state including inner index | 221/221 instructions; structural/exact differences (0, 63)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R2 creation state including pane pointer | 221/221 instructions; structural/exact differences (0, 38)
R2 Sign restore 221/221 instructions; structural/exact differences (0, 34)

## Round 2 uhf_msc_blk_pread
Origin/main source unchanged before starting. Pool empty and424/424data. Same0x40frame,129instructions, control flow and operands. Only transfer-block count and memcpy byte-count registers exchanged. Try genuine transfer-state aggregate and typed length temporary, then declaration search.
uhf_msc_blk_pread | R2 full block transfer state | 129/129 instructions; structural/exact differences (0, 33)
uhf_msc_blk_pread | R2 transfer count and limit state | 129/129 instructions; structural/exact differences (0, 28)
uhf_msc_blk_pread | R2 copy length and transfer count state | 129/129 instructions; structural/exact differences (0, 10)
R2 MSC restored 129/129 instructions; structural/exact differences (0, 10)

## Round 2 TMCJPEGDEC_decode_iquant
Origin/main source unchanged. No pool/data. Same0x50frame and276instructions. Structure differs in temporary aggregate-copy slots, AC fast-entry stack slot, helper subtraction/add operand order. New typed bit-reader/coefficient state and long-decoder helper state experiments; register search last.
TMCJPEGDEC_decode_iquant | R2 bit-reader scalar state | 276/276 instructions; structural/exact differences (12, 54)
TMCJPEGDEC_decode_iquant | R2 coefficient and Huffman scalar state | 276/276 instructions; structural/exact differences (12, 129)
TMCJPEGDEC_decode_iquant | R2 typed long-Huffman decoder state | 276/276 instructions; structural/exact differences (12, 64)
R2 JPEG structural restore 276/276 instructions; structural/exact differences (12, 50)
R2 state member declsearch restored src/keyboard/tiSignWindow 221/221 instructions; structural/exact differences (0, 34)
R2 state member declsearch restored libs/RVL_SDK/src/fa/msc/puh_msc_blk 129/129 instructions; structural/exact differences (0, 10)
declaration block:
          const char* forceName;
          u32 animationCount;
          u32 paneIndex;
start (0, 38)
best (0, 38) after 6 builds; source restored; best order was:
        const char* forceName;
        u32 animationCount;
        u32 paneIndex;

declaration block:
          UHF_MSC_DEVICE* device;
          u16 transfer_blocks;
          s32 error;
          u32 block_size;
          u8* transfer_buffer;
          u32 transfer_limit;
          s32 cacheable;
start (0, 33)
best (0, 33) after 52 builds; source restored; best order was:
        UHF_MSC_DEVICE* device;
        u16 transfer_blocks;
        s32 error;
        u32 block_size;
        u8* transfer_buffer;
        u32 transfer_limit;
        s32 cacheable;

create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R2 per-pane animation state | 221/221 instructions; structural/exact differences (0, 65)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R2 per-pane state with pane object | 221/221 instructions; structural/exact differences (0, 65)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R2 typed sign-pane factory inline boundary | 221/221 instructions; structural/exact differences (0, 61)
R2 Sign restored 221/221 instructions; structural/exact differences (0, 34)
R2 transfer-state subset search 120 builds; retained 129/129 instructions; structural/exact differences (0, 10)
TMCJPEGDEC_decode_iquant | R2 DC count subtraction directly into work | 276/276 instructions; structural/exact differences (12, 48)
TMCJPEGDEC_decode_iquant | R2 long-helper consumed bit count explicit subtraction | 276/276 instructions; structural/exact differences (12, 50)
TMCJPEGDEC_decode_iquant | R2 long symbol subtraction separate from addition | 276/276 instructions; structural/exact differences (12, 51)
R2 JPEG retained 276/276 instructions; structural/exact differences (12, 48)

## R2 open-function audit before final full gate
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator built, distinct R2 structural attempts 6; 221/221 instructions; structural/exact differences (0, 34)
uhf_msc_blk_pread built, distinct R2 structural attempts 3; 129/129 instructions; structural/exact differences (0, 10)
TMCJPEGDEC_decode_iquant built, distinct R2 structural attempts 6; 276/276 instructions; structural/exact differences (12, 46)
FAT open-function audit: none remains; ReadFATEntryWithBuf155/155 instructions, diffs0 and unit4/4exact.
declaration block:
      TMCHuffmanEntry dcEntry;
      u8* huff_sym;
      const TMCHuffmanEntry* ac_fast;
      s32 idx;
      u32* huff_tbl;
      s32 bit_pos;
      u32 bit_data;
      const TMCHuffmanEntry* dc_fast;
      s32 r;
      s32 blk0;
      TMCHuffmanEntry acEntry;
      s32 extra;
      s32 t;
      s32 zz;
      s32 q;
      u32 tmp;
      const u8* zztbl;
start (12, 48)
improved (12, 46)
best (12, 46) after 320 builds; kept in source:
    TMCHuffmanEntry dcEntry;
    u8* huff_sym;
    const TMCHuffmanEntry* ac_fast;
    s32 idx;
    u32* huff_tbl;
    s32 bit_pos;
    u32 bit_data;
    u32 tmp;
    s32 r;
    s32 blk0;
    TMCHuffmanEntry acEntry;
    s32 extra;
    s32 t;
    s32 zz;
    s32 q;
    const TMCHuffmanEntry* dc_fast;
    const u8* zztbl;

R2 MSC all120 nontrivial transfer-state field subsets built without improvement; restored original source. Sign outer/member/per-pane/factory boundaries all preserve221instructions but worsen colors; restored. JPEG only direct bit-count subtraction and improved declaration order retained; 46instruction differences remain, including12 structural stack/copy differences.

## R2 final clean full gate
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/pf_fat12] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_fat12] objdiff: code 2164/2164 data None/None functions 4/4 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/pf_fat12] instruction-exact functions: 4/4
[libs/RVL_SDK/src/fa/pf_fat12]   section .text size 2164 match 100.0
[libs/RVL_SDK/src/fa/pf_fat12] baseline: code 1544/2164 data None functions 3 fuzzy 99.7597
[src/keyboard/tiSignWindow] pool: IDENTICAL
[src/keyboard/tiSignWindow] objdiff: code 6300/7184 data 3468/3468 functions 55/56 fuzzy 99.8914 linked code 0
[src/keyboard/tiSignWindow] instruction-exact functions: 55/56
[src/keyboard/tiSignWindow]   section .ctors size 4 match 100.0
[src/keyboard/tiSignWindow]   section .data size 2672 match 100.0
[src/keyboard/tiSignWindow]   section .rodata size 784 match 100.0
[src/keyboard/tiSignWindow]   section .sdata size 8 match 100.0
[src/keyboard/tiSignWindow]   section .text size 7184 match 99.891426
[src/keyboard/tiSignWindow]   below 100: create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.117645
[src/keyboard/tiSignWindow] baseline: code 6300/7184 data 3468 functions 55 fuzzy 99.8914
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] pool: IDENTICAL
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] objdiff: code 1556/2072 data 424/424 functions 10/11 fuzzy 99.8938 linked code 0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] instruction-exact functions: 10/11
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .bss size 384 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .data size 32 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .text size 2072 match 99.89382
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   below 100: uhf_msc_blk_pread 99.57365
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] baseline: code 1556/2072 data 424 functions 10 fuzzy 99.8938
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 99.1051 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 99.10507
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 99.10507
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 99.0326
regressions vs baseline: 0
global matched_code_percent: 88.64712 -> 88.66782
global fuzzy_match_percent: 99.47315 -> 99.47335
global complete_code_percent: 63.16065 -> 63.16065
global matched_data_percent: 98.51344 -> 98.51344
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
libs/RVL_SDK/src/fa/pf_fat12 POOL IDENTICAL up to 0 (mine=0 base=0)
src/keyboard/tiSignWindow POOL IDENTICAL up to 30 (mine=30 base=30)
libs/RVL_SDK/src/fa/msc/puh_msc_blk POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32 POOL IDENTICAL up to 0 (mine=0 base=0)
Fresh clean FAT ctxdiff155/155 diffs0. Code bytes1544->2164, exactfunctions3->4. Other exact counts unchanged. JPEG fuzzy99.03261->99.10507; declaration/direct-expression improvement remains partial. All owned data100%; no configuration/linking edits. Final full gate PASS, DOL correct, regressions0, forbidden0, readability0. Original JPEG inline-helper/copy layout remains uncertain.

# Round 3
HEAD c6c0b145f823573a643925eacc094af8547ff502 origin/main 5fe0a61af71d078b7b2da949b49a9cf30e81d66f
src/keyboard/tiSignWindow POOL IDENTICAL up to 30 (mine=30 base=30)
libs/RVL_SDK/src/fa/msc/puh_msc_blk POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32 POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RVL_SDK/src/fa/pf_entry_iterator POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RevoEX/src/so/SOOption POOL IDENTICAL up to 0 (mine=0 base=0)
src/keyboard/tiString POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RVL_SDK/src/fa/pf_volume POOL IDENTICAL up to 1 (mine=1 base=1)
Round 3 create diagnosis: frame 0x50 and 221 instructions equal; branch forms/helper inlining equal; all 34 differences register allocation, including hoisted vtables and loop state. origin source unchanged.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | r3 animation pointer temporary | BUILD FAIL i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c++ -O4,p -MMD -c src/keyboard/tiSignWindow.cpp -o build/43U/src/src/keyboard && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/keyboard/tiSignWindow.d build/43U/src/src/keyboard/tiSignWindow.d
### mwcceppc.exe Compiler:
#    File: src\keyboard\tiSignWindow.cpp
# --------------------------------------
#     252:             const Animation* animation = paneInfo.animations[animationIndex]; 
# Warning:                   ^^^^^^^^^
#   (10349) implicit 'int' is no longer supported in C++
### mwcceppc.exe Compiler:
#     252:             const Animation* animation = paneInfo.animations[animationIndex]; 
#   Error:                            ^
#   (10224) 'const' or '&' variable needs initializer
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | r3 move force/count into loop scope | 221/221 instructions; structural/exact differences (0, 61)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | r3 outer for loop | 221/221 instructions; structural/exact differences (0, 34)
221/221 instructions; structural/exact differences (0, 34)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | r3 corrected animation temporary | 219/221 instructions; structural/exact differences (9, 91)
Round 3 pread diagnosis: 129/129 instructions, frame 0x40 identical; 10 register differences transfer_blocks and byte product. No structural/operand-order differences; origin source unchanged.
uhf_msc_blk_pread | r3 conditional transfer selection | 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread | r3 byte product scoped to success | 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread | r3 count signed temporary | 129/129 instructions; structural/exact differences (0, 10)
Round 3 JPEG diagnosis: frame/instruction counts equal (276), 12 structural differences in returned Huffman aggregate stack slots; remaining coloring differences. origin source unchanged.
TMCJPEGDEC_decode_iquant | r3 shared entry aggregate | 276/276 instructions; structural/exact differences (10, 41)
TMCJPEGDEC_decode_iquant | r3 AC aggregate declared in AC scope | 276/276 instructions; structural/exact differences (12, 46)
TMCJPEGDEC_decode_iquant | r3 reverse returned entry declaration fields loads | 276/276 instructions; structural/exact differences (18, 47)
FindCluster diagnosis: same 0xb0 frame/237 instructions, all 8 differences constant-one vs shifted entries register allocation; no branch or helper boundary differences. origin source unchanged.
PFENT_ITER_FindCluster | initialize shifted entries before iterator fields | 238/237 instructions; structural/exact differences (13, 208)
PFENT_ITER_FindCluster | use iterator start cluster as shift operand | 237/237 instructions; structural/exact differences (0, 8)
PFENT_ITER_FindCluster | sector scalar state | 237/237 instructions; structural/exact differences (0, 11)
Last-register searches: create 6 permutations no change (0,34); pread40 no change (0,10); JPEG35 no change (12,46); FindCluster35 no change (0,8).
GetLFNEntryName diagnosis: 73/73, target loop uses i*13 index strengthened to byte offset; source carries an advancing pointer and independent character index. Target terminator uses reloaded num_entry_LFNs*13. Branch/helper forms equal.
PFENT_ITER_GetLFNEntryName | indexed 13 character fragments and reloaded terminator | 76/73 instructions; structural/exact differences (26, 75)
PFENT_ITER_GetLFNEntryName | typed LFN fragment array indexed by entry | 76/73 instructions; structural/exact differences (26, 75)
PFENT_ITER_GetLFNEntryName | fragment array typedef, loop-local base initialization | 76/73 instructions; structural/exact differences (26, 75)
PFENT_ITER_GetLFNEntryName | explicit byte offset for packed LFN copies; byte-size terminator | 76/73 instructions; structural/exact differences (24, 75)
PFENT_ITER_GetLFNEntryName | packed fragment inline helper boundary | 76/73 instructions; structural/exact differences (24, 75)
SOGetInterfaceOpt diagnosis: 119/119, frame equal, target computes command/reply/length from nested payload bases; source uses direct request bases. Also register assignment/scheduling. origin source unchanged.
SOGetInterfaceOpt | construct all buffer pointers before command assignments | 119/119 instructions; structural/exact differences (5, 16)
SOGetInterfaceOpt | command fields in opposite statement order | 119/119 instructions; structural/exact differences (10, 14)
SOGetInterfaceOpt | returned length after reply assignment | 119/119 instructions; structural/exact differences (5, 16)
SOSetInterfaceOpt diagnosis: 74/74 frame/calls/branches equal; payload pointer derived from command base target, direct request source. Source stores option after reply pointer, target before. origin source unchanged.
SOSetInterfaceOpt | reply pointer before stores | 74/74 instructions; structural/exact differences (4, 14)
SOSetInterfaceOpt | reverse command assignments | 74/74 instructions; structural/exact differences (6, 19)
SOSetInterfaceOpt | request and allocation size scalar state | 74/74 instructions; structural/exact differences (4, 15)
inputChar diagnosis: target136/source125 frame0x30 same; target translate mode3 uses indexed character append with count++ and trailing NUL, source direct scalar stores. Target dead newline comparison suggests converter helper boundary. origin source unchanged.
inputChar__Q39textinput8tistring9DecolatedFw | mode3 indexed append | 125/136 instructions; structural/exact differences (18, 73)
inputChar__Q39textinput8tistring9DecolatedFw | mode3 scan append index | 137/136 instructions; structural/exact differences (17, 74)
inputChar__Q39textinput8tistring9DecolatedFw | mode3 count as conversion state | 125/136 instructions; structural/exact differences (18, 73)
p_rmvvol diagnosis: 64/64 frame0x500 equal; constant target lbz SDA21 vs source folded li0xe5. Target indicates aggregate initialization from small constant template, investigate genuine local byte array.
PFVOL_p_rmvvol | one byte local deleted marker array initializer | 64/64 instructions; structural/exact differences (0, 0)
PFVOL_p_rmvvol | array initialized from existing constant object | BUILD FAIL  -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/fa/pf_volume.c -o build/43U/src/libs/RVL_SDK/src/fa && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/fa/pf_volume.d build/43U/src/libs/RVL_SDK/src/fa/pf_volume.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\fa\pf_volume.c
# ----------------------------------------
#     588:     u8 deleted[1] = {deleted_entry_mark[0]}; 
#   Error:                                            ^
#   (10124) illegal constant expression
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

PFVOL_p_rmvvol | single field aggregate initializer | 64/64 instructions; structural/exact differences (0, 0)
p_rmvvol local byte-array yields exact instructions but .sdata2 is1byte versus target8byte padded extent; gate currently fails matched-data regression8. No commit until resolved.
PFVOL_p_rmvvol | read marker helper | 64/64 instructions; structural/exact differences (2, 4)
PFVOL_p_rmvvol | pointer local | 64/64 instructions; structural/exact differences (2, 4)
PFVOL_p_rmvvol | char aggregate through constant pointer | 64/64 instructions; structural/exact differences (2, 4)
attach diagnosis: 174/176 frame0x20 same. clear_mount return value allocation crosses inline boundary; target moves failure result to r0 and materializes success0 before checking. Shared helper must not regress other matched users.
PFVOL_attach | mount helper return variable declared separately | 174/176 instructions; structural/exact differences (10, 39)
PFVOL_attach | scope mount result into aggregate | 174/176 instructions; structural/exact differences (10, 39)
PFVOL_attach | error branch else form | 174/176 instructions; structural/exact differences (10, 39)
PFVOL_attach | success branch first in mount helper | 174/176 instructions; structural/exact differences (19, 39)
setcode diagnosis: 23/23 instructions; aggregate assignment loads all six pointers then stores, target alternates field load/store. Six real function pointer fields should copy individually.
PFVOL_setcode | explicit code conversion callback copies | 23/23 instructions; structural/exact differences (10, 17)
PFVOL_setcode | mutable callback table pointer with field copies | 23/23 instructions; structural/exact differences (0, 0)
setcode exact: mutable code_set pointer preserves potential alias between callback field reads and global field stores.

SOOption register search: size-before-request declarations improve GetInterface16->10 differences and SetInterface14->4; source retained. setcode23/23 exact, volume33->34; quick gate PASS with regressions0/data unchanged. p_rmvvol exact local-array candidate abandoned because data regression; existing source/data restored.
regctx diagnosis: 75/75, frame0x10 same; 15 differences free_context_index vs masked status r5/r8 allocation in unrolled three-context loop. All branch/operand/helper boundaries identical; origin source unchanged except our setcode match.
PFVOL_regctx | status declared at function scope | 75/75 instructions; structural/exact differences (0, 15)
PFVOL_regctx | free and status typed state | 75/75 instructions; structural/exact differences (0, 25)
PFVOL_regctx | status tested through stored full flags | 75/75 instructions; structural/exact differences (0, 14)
SOOption | genuine nested IPC payload layout | 119/119 instructions; structural/exact differences (5, 10); set 74/74 instructions; structural/exact differences (4, 4)
PFVOL_regctx | search state free_context_index,context_index | 75/75 instructions; structural/exact differences (0, 25)
PFVOL_regctx | search state free_context_index,error | 75/75 instructions; structural/exact differences (0, 15)
PFVOL_regctx | search state free_context_index,stat | 75/75 instructions; structural/exact differences (0, 25)
PFVOL_regctx | search state context_index,error | 75/75 instructions; structural/exact differences (0, 20)
PFVOL_regctx | search state context_index,stat | 75/75 instructions; structural/exact differences (0, 16)
PFVOL_regctx | search state error,stat | 75/75 instructions; structural/exact differences (0, 14)
PFVOL_regctx | search state free_context_index,context_index,error | 75/75 instructions; structural/exact differences (0, 25)
PFVOL_regctx | search state free_context_index,context_index,stat | 75/75 instructions; structural/exact differences (0, 25)
PFVOL_regctx | search state free_context_index,error,stat | 75/75 instructions; structural/exact differences (0, 25)
PFVOL_regctx | search state context_index,error,stat | 75/75 instructions; structural/exact differences (0, 16)
PFVOL_regctx | search state free_context_index,context_index,error,stat | 75/75 instructions; structural/exact differences (0, 25)
SOOption | typed 32-byte IPC blocks with sequential payload addressing | 119/119 instructions; structural/exact differences (0, 5); set 74/74 instructions; structural/exact differences (0, 0)
IPC block proof: target command at request+32, length at command+32, value at length+32 (set value at command+32); existing storage already reserves these 32-byte IPC blocks. Typed pointer traversal preserves allocation/layout; SetInterface 74/74 diffs0, Get119/119 structural0/exact5.
PFENT_ITER_GetLFNEntryName | byte fragment state i,index | 76/73 instructions; structural/exact differences (24, 74)
PFENT_ITER_GetLFNEntryName | byte fragment state index,err | 76/73 instructions; structural/exact differences (24, 75)
PFENT_ITER_GetLFNEntryName | byte fragment state i,index,err | 76/73 instructions; structural/exact differences (24, 74)
SOGetInterfaceOpt | option input state level,option | 119/119 instructions; structural/exact differences (0, 5)
SOGetInterfaceOpt | option input state option,level | 119/119 instructions; structural/exact differences (0, 5)
SOGetInterfaceOpt | option input state level,option,length | 119/119 instructions; structural/exact differences (0, 5)
SOGetInterfaceOpt | option input state level,option,value | 119/119 instructions; structural/exact differences (0, 5)
SOGetInterfaceOpt | random permutations 50 | best remains (0, 5)
SOGetInterfaceOpt | random permutations 100 | best remains (0, 5)
SOGetInterfaceOpt | random permutations 150 | best remains (0, 5)
SOGetInterfaceOpt | random permutations 200 | best remains (0, 5)
SOGetInterfaceOpt | random permutations 250 | best remains (0, 5)
SOGetInterfaceOpt | random permutations 300 | best remains (0, 5)
SOGetInterfaceOpt | random permutations 350 | best remains (0, 5)
SOGetInterfaceOpt | random permutations 400 | best remains (0, 5)
PFVOL_attach | ignored mount status return zero | 174/176 instructions; structural/exact differences (10, 39)
PFVOL_attach | mount helper returns void | 174/176 instructions; structural/exact differences (10, 39)
PFVOL_attach | mount check distinct status result | 174/176 instructions; structural/exact differences (10, 39)
Structural frame correction: FindCluster is0xa0, not0xb0; JPEG0x50; GetLFN/GetInterface/SetInterface0x30. Registers and frame statements verified against fresh target disassembly.

SOOption final quick gate PASS, regressions0, forbidden0/readability0, no data. SetInterface exact count2->3/code520->816; GetInterface remains99.78992 with five pure parameter-register differences after400 additional declaration permutations.

Completeness audit: all10 remaining functions have at least3 distinct successful-build source attempts in Round3; no untried open function. All seven owned data sections100%, no symbol/configuration changes. Exact p_rmvvol local-byte-array candidate reverted because7 target alignment bytes caused data regression; initializer/extent uncertain. GetLFN induction shape, inputChar converter helper, attach return helper, JPEG aggregate stack scope remain uncertain.

## Final full clean gate, Round3
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiSignWindow] pool: IDENTICAL
[src/keyboard/tiSignWindow] objdiff: code 6300/7184 data 3468/3468 functions 55/56 fuzzy 99.8914 linked code 0
[src/keyboard/tiSignWindow] instruction-exact functions: 55/56
[src/keyboard/tiSignWindow]   section .ctors size 4 match 100.0
[src/keyboard/tiSignWindow]   section .data size 2672 match 100.0
[src/keyboard/tiSignWindow]   section .rodata size 784 match 100.0
[src/keyboard/tiSignWindow]   section .sdata size 8 match 100.0
[src/keyboard/tiSignWindow]   section .text size 7184 match 99.891426
[src/keyboard/tiSignWindow]   below 100: create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.117645
[src/keyboard/tiSignWindow] baseline: code 6300/7184 data 3468 functions 55 fuzzy 99.8914
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] pool: IDENTICAL
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] objdiff: code 1556/2072 data 424/424 functions 10/11 fuzzy 99.8938 linked code 0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] instruction-exact functions: 10/11
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .bss size 384 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .data size 32 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .text size 2072 match 99.89382
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   below 100: uhf_msc_blk_pread 99.57365
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] baseline: code 1556/2072 data 424 functions 10 fuzzy 99.8938
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 99.1051 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 99.10507
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 99.10507
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 99.1051
[libs/RVL_SDK/src/fa/pf_entry_iterator] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_entry_iterator] objdiff: code 6640/7880 data 24/24 functions 14/16 fuzzy 99.6264 linked code 0
[libs/RVL_SDK/src/fa/pf_entry_iterator] instruction-exact functions: 14/16
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .sdata size 24 match 100.0
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .text size 7880 match 99.626396
[libs/RVL_SDK/src/fa/pf_entry_iterator]   below 100: PFENT_ITER_FindCluster 99.81013
[libs/RVL_SDK/src/fa/pf_entry_iterator]   below 100: PFENT_ITER_GetLFNEntryName 90.53425
[libs/RVL_SDK/src/fa/pf_entry_iterator] baseline: code 6640/7880 data 24 functions 14 fuzzy 99.6264
[libs/RevoEX/src/so/SOOption] pool: IDENTICAL
[libs/RevoEX/src/so/SOOption] objdiff: code 816/1292 data None/None functions 3/4 fuzzy 99.9226 linked code 0
[libs/RevoEX/src/so/SOOption] instruction-exact functions: 3/4
[libs/RevoEX/src/so/SOOption]   section .text size 1292 match 99.9226
[libs/RevoEX/src/so/SOOption]   below 100: SOGetInterfaceOpt 99.78992
[libs/RevoEX/src/so/SOOption] baseline: code 520/1292 data None functions 2 fuzzy 97.5759
[src/keyboard/tiString] pool: IDENTICAL
[src/keyboard/tiString] objdiff: code 4632/5176 data 288/288 functions 41/42 fuzzy 98.9629 linked code 0
[src/keyboard/tiString] instruction-exact functions: 41/42
[src/keyboard/tiString]   section .data size 288 match 100.0
[src/keyboard/tiString]   section .text size 5176 match 98.962906
[src/keyboard/tiString]   below 100: inputChar__Q39textinput8tistring9DecolatedFw 90.132355
[src/keyboard/tiString] baseline: code 4632/5176 data 288 functions 41 fuzzy 98.9629
[libs/RVL_SDK/src/fa/pf_volume] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_volume] objdiff: code 16732/17992 data 210976/210976 functions 34/37 fuzzy 99.8755 linked code 0
[libs/RVL_SDK/src/fa/pf_volume] instruction-exact functions: 34/37
[libs/RVL_SDK/src/fa/pf_volume]   section .bss size 210944 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .data size 16 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .sdata size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .text size 17992 match 99.8755
[libs/RVL_SDK/src/fa/pf_volume]   below 100: PFVOL_p_rmvvol 95.9375
[libs/RVL_SDK/src/fa/pf_volume]   below 100: PFVOL_attach 98.72159
[libs/RVL_SDK/src/fa/pf_volume]   below 100: PFVOL_regctx 99.0
[libs/RVL_SDK/src/fa/pf_volume] baseline: code 16640/17992 data 210976 functions 33 fuzzy 99.6396
regressions vs baseline: 0
global matched_code_percent: 88.68973 -> 88.70268
global fuzzy_match_percent: 99.47443 -> 99.47685
global complete_code_percent: 63.16065 -> 63.16065
global matched_data_percent: 98.51344 -> 98.51344
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Instruction exact functions; objdiff matched code bytes; matched data bytes, before -> after:
src/keyboard/tiSignWindow: functions 55/56 -> 55/56; code 6300 -> 6300 / 7184; data 3468 -> 3468 / 3468
libs/RVL_SDK/src/fa/msc/puh_msc_blk: functions 10/11 -> 10/11; code 1556 -> 1556 / 2072; data 424 -> 424 / 424
libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32: functions 0/1 -> 0/1; code 0 -> 0 / 1104; data 0 -> 0 / 0
libs/RVL_SDK/src/fa/pf_entry_iterator: functions 14/16 -> 14/16; code 6640 -> 6640 / 7880; data 24 -> 24 / 24
libs/RevoEX/src/so/SOOption: functions 2/4 -> 3/4; code 520 -> 816 / 1292; data 0 -> 0 / 0
src/keyboard/tiString: functions 41/42 -> 41/42; code 4632 -> 4632 / 5176; data 288 -> 288 / 288
libs/RVL_SDK/src/fa/pf_volume: functions 33/37 -> 34/37; code 16640 -> 16732 / 17992; data 210976 -> 210976 / 210976

Remaining unmatched functions, every one has >=3 distinct Round3 source experiments:
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator: 99.117645%; 34 register-only differences; vtable/loop state coloring
uhf_msc_blk_pread: 99.57365%; 10 register-only count/product differences
TMCJPEGDEC_decode_iquant: 99.10507%; 12 structural stack-slot differences in Huffman aggregate returns, plus register coloring
PFENT_ITER_FindCluster: 99.81013%; 8 register-only shifted-entry vs constant-one differences
PFENT_ITER_GetLFNEntryName: 90.53425%; pointer induction vs target byte-index loop; terminator uses count reload
SOGetInterfaceOpt: 99.78992%; 5 parameter-register coloring differences; structure now exact
inputChar__Q39textinput8tistring9DecolatedFw: 90.132355%; 125/136 instructions; mode3 conversion append/helper boundary unresolved
PFVOL_p_rmvvol: 95.9375%; folded constant vs target byte-template load; exact candidate rejected for data regression
PFVOL_attach: 98.72159%; 174/176 instructions; inline clear_mount return boundary
PFVOL_regctx: 99.0%; 15 register-only status/free-index differences

Changed source files: libs/RevoEX/src/so/SOOption.c and libs/RVL_SDK/src/fa/pf_volume.c; attempts log tools/decomp-assist/fz3.attempts.md. Commits43b95ca5/d4a8860d. No config/symbol edits. Full clean gate PASS; pool identical across7 units; regressions0, forbidden0, readability0, target DOL SHA1 preserved.

# Round 5 HIGH; fresh HEAD 2039813c, owned seven units only
libs/RevoEX/src/so/SOOption: POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RVL_SDK/src/fa/pf_volume: POOL IDENTICAL up to 1 (mine=1 base=1)
libs/RVL_SDK/src/fa/pf_entry_iterator: POOL IDENTICAL up to 0 (mine=0 base=0)
src/keyboard/tiString: POOL IDENTICAL up to 0 (mine=0 base=0)
src/keyboard/tiSignWindow: POOL IDENTICAL up to 30 (mine=30 base=30)
libs/RVL_SDK/src/fa/msc/puh_msc_blk: POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var: POOL IDENTICAL up to 0 (mine=0 base=0)

SOGetInterfaceOpt current origin/main source identical after fetch; structural diagnosis: frame0x30 119/119 instructions; five parameter-color differences only; target reuses level storage for returnedLength and option storage for reply. Data0/0, no pool.
SOGetInterfaceOpt | R5 scope reply and returnedLength at payload lifetime | 119/119 instructions; structural/exact differences (0, 5)
SOGetInterfaceOpt | R5 snapshot requested option after prepare before validation | 119/119 instructions; structural/exact differences (0, 5)
SOGetInterfaceOpt | R5 isolate result of ioctl from prepare and allocation error | BUILD FAIL uto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/so/SOOption.c -o build/43U/src/libs/RevoEX/src/so && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/so/SOOption.d build/43U/src/libs/RevoEX/src/so/SOOption.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\so\SOOption.c
# --------------------------------------
#     125:                 int ioctlResult; 
#   Error:                 ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

R5 SO restored: 119/119 instructions; structural/exact differences (0, 5)
SOGetInterfaceOpt | R5 ioctl result block with valid C89 declaration | 119/119 instructions; structural/exact differences (0, 5)
R5 declaration search60 builds (0,5), no improvement; 119/119 instructions; structural/exact differences (0, 5)

R5 PFVOL_p_rmvvol fetch rc=1 ; origin/main d34e09d5dcb0dd67dd34a4a3b41c6238fe499689; source identical=True; baseline open per fresh report. 64/64 frame0x500. Folded scalar initializer li versus target lbz template; four prolog scheduling differences. Real deleted byte template currently8byte extent, no rename/extent proof sufficient, data210976/210976.
PFVOL_p_rmvvol | R5 const deleted scalar with explicit initializer | 64/64 instructions; structural/exact differences (2, 4)
PFVOL_p_rmvvol | R5 byte marker in directory byte field struct initializer | 64/64 instructions; structural/exact differences (0, 0)
PFVOL_p_rmvvol | R5 byte marker array copied from template via initializer | BUILD FAIL  -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/fa/pf_volume.c -o build/43U/src/libs/RVL_SDK/src/fa && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/fa/pf_volume.d build/43U/src/libs/RVL_SDK/src/fa/pf_volume.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\fa\pf_volume.c
# ----------------------------------------
#     591:     u8 deleted[1] = {deleted_entry_mark[0]}; 
#   Error:                                            ^
#   (10124) illegal constant expression
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

R5 PFVOL_p_rmvvol restored: 64/64 instructions; structural/exact differences (2, 4)
PFVOL_p_rmvvol | R5 byte marker array aggregate with literal initializer | 64/64 instructions; structural/exact differences (0, 0)
PFVOL_p_rmvvol | R5 deleted-field struct using named mark initializer | BUILD FAIL ontract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/fa/pf_volume.c -o build/43U/src/libs/RVL_SDK/src/fa && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/fa/pf_volume.d build/43U/src/libs/RVL_SDK/src/fa/pf_volume.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\fa\pf_volume.c
# ----------------------------------------
#     591:     struct { u8 first_byte; } deleted = {deleted_entry_mark[0]}; 
#   Error:                                                                ^
#   (10124) illegal constant expression
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

R5 PFVOL_p_rmvvol aggregate exact candidate rejected: extra local template would leave old mark as unused object; removing old mark regresses section data. No padding or extent change justified solely by one byte access. 64/64 instructions; structural/exact differences (2, 4)

R5 PFVOL_attach fetch rc=0 ; origin/main 78d682775730a945bd3c3211dd704cc170f82b4b; source identical=True; baseline open per fresh report. 174/176 frame0x20. Caller ignores mount helper return, target still materializes its success/error into r0; ours collapses inline boundary and tests r3 from final void call. Other clear_mount consumers already exact, use attach-only helper variants.
PFVOL_attach | R5 flatten mount helper with explicit retained mount status | 176/176 instructions; structural/exact differences (10, 22)
PFVOL_attach | R5 mount result as helper state record | 174/176 instructions; structural/exact differences (10, 39)
PFVOL_attach | R5 successful mount branch first in attach helper | 174/176 instructions; structural/exact differences (19, 39)
R5 attach restored 174/176 instructions; structural/exact differences (10, 39)
PFVOL_attach | R5 explicit mount status join through shared completion label | 173/176 instructions; structural/exact differences (11, 39)
PFVOL_attach | R5 attach-only clear helper with status output parameter | 174/176 instructions; structural/exact differences (10, 39)
PFVOL_attach | R5 attach-only aggregate mount return | 174/176 instructions; structural/exact differences (10, 39)
R5 attach final restored 174/176 instructions; structural/exact differences (10, 39)

R5 PFVOL_regctx fetch rc=0 ; origin/main 1ce1b0458a9bb25cdfd7828882f9c2baf4e84ef6; source identical=True; baseline open per fresh report. 75/75 frame0x10 identical unrolled branches, target free index r8 status r5 versus ours r5/r8; declarations last. All owned data exact, no label renames warranted.
PFVOL_regctx | R5 signed iteration index with unchanged context bounds | 75/75 instructions; structural/exact differences (1, 16)
PFVOL_regctx | R5 status declaration alongside error before loop | 75/75 instructions; structural/exact differences (0, 15)
PFVOL_regctx | R5 per-iteration typed context reference before status extraction | 75/75 instructions; structural/exact differences (0, 18)
R5 regctx restored 75/75 instructions; structural/exact differences (0, 15)

R5 PFENT_ITER_FindCluster fetch rc=0 ; origin/main a2abf248541b955965816157d0c0412cdb7f3f62; source identical=True; baseline open per fresh report. 237/237 frame0xa0. Same locals/branches/inline LoadEntry, eight register-only differences between constant1 and entriesPerSector. Data24/24 exact.
PFENT_ITER_FindCluster | R5 shared typed first-cluster value for iterator and hint initialization | 237/237 instructions; structural/exact differences (0, 8)
PFENT_ITER_FindCluster | R5 entriesPerSector lifetime scoped to initialized iterator | 237/237 instructions; structural/exact differences (0, 11)
PFENT_ITER_FindCluster | R5 signed entries-per-sector temporary for positive power-of-two count | 237/237 instructions; structural/exact differences (0, 8)
R5 FindCluster restored 237/237 instructions; structural/exact differences (0, 8)

R5 PFENT_ITER_GetLFNEntryName fetch rc=0 ; origin/main a2abf248541b955965816157d0c0412cdb7f3f62; source identical=True; baseline open per fresh report. 73/73 frame0x30. Target maintains byte offset +=26 in r31 and copy destination r30 computed each iteration. Ours carries pointer; final target reloads numLFNs, multiply26 and clear bit0 before sthx. Inline LoadEntry boundary otherwise same.
PFENT_ITER_GetLFNEntryName | R5 byte-address offset and terminator from live LFN count | 76/73 instructions; structural/exact differences (26, 75)
PFENT_ITER_GetLFNEntryName | R5 byte destinations for all three LFN fragments | 76/73 instructions; structural/exact differences (26, 75)
PFENT_ITER_GetLFNEntryName | R5 byte offset converted through UTF16 index at destination | 74/73 instructions; structural/exact differences (11, 34)
R5 GetLFNEntryName restored 73/73 instructions; structural/exact differences (9, 43)
R5 GetLFN shift-index candidate has extra rlwinm alignment mask and multiply13+slwi versus target multiply26+clearbit; restored 73/73 instructions; structural/exact differences (9, 43)

R5 inputChar__Q39textinput8tistring9DecolatedFw fetch rc=0 ; origin/main a2abf248541b955965816157d0c0412cdb7f3f62; source identical=True; baseline open per fresh report. 125/136 frame0x30. Main Kana and insertion blocks structurally match. Hangul branch target retains dynamic append count, initialNUL and dead newline comparison from inline converter; source folds count1 directstores. Data288/288 exact; no data pairing gaps.
inputChar__Q39textinput8tistring9DecolatedFw | R5 Hangul append with advancing output pointer and count | 125/136 instructions; structural/exact differences (18, 73)
inputChar__Q39textinput8tistring9DecolatedFw | R5 Hangul conversion local32bit length and explicit initial terminator | 126/136 instructions; structural/exact differences (17, 73)
inputChar__Q39textinput8tistring9DecolatedFw | R5 Hangul typed append helper carrying current UTF16 length | 125/136 instructions; structural/exact differences (18, 73)
R5 tiString restored 125/136 instructions; structural/exact differences (18, 73)

R5 create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator fetch rc=0 ; origin/main d0c3d43000a96839d7d74dee39c3998cc4a99aa4; source identical=True; baseline open per fresh report. 221/221 frame0x50, branches and all constructors/calls same; 34 differences are hoisted pane vtable/constants and animation count/table registers. Data3468/3468 and pool30 strings exact.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R5 count and forceName declared at animation-binding phase | 221/221 instructions; structural/exact differences (0, 61)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R5 widened loop state with explicit16bit animation lookup boundary | 221/221 instructions; structural/exact differences (0, 34)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R5 placement-construction helper separates pane lookup from constructor inline scope | 221/221 instructions; structural/exact differences (42, 73)
R5 SignWindow restored 221/221 instructions; structural/exact differences (0, 34)
R5 SignWindow declaration search24 budget completed after structural/source trials; baseline coloring retained.

R5 uhf_msc_blk_pread fetch rc=0 From https://github.com/coah80/wii-ipl
   d0c3d430..65cd387b  main       -> origin/main; origin/main 65cd387bcb48559396b79257ab6069fcda9bf259; source identical=True; baseline open per fresh report. 129/129 frame0x40. Same find-device and read/retry branches, only10 differences swapping transfer_blocks r25/product r27 against target r27/r25. Data424/424 exact.
uhf_msc_blk_pread | R5 transfer count lifetime restricted to each read iteration | 129/129 instructions; structural/exact differences (0, 27)
uhf_msc_blk_pread | R5 byte-count product ordered block-size then transfer count | 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread | R5 byte-count temporary scoped to copied noncacheable transfer | BUILD FAIL  reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/fa/msc/puh_msc_blk.c -o build/43U/src/libs/RVL_SDK/src/fa/msc && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/fa/msc/puh_msc_blk.d build/43U/src/libs/RVL_SDK/src/fa/msc/puh_msc_blk.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\fa\msc\puh_msc_blk.c
# ----------------------------------------------
#     152:                 transfer_buffer += transfer_bytes; 
#   Error:                                    ^^^^^^^^^^^^^^
#   (10140) undefined identifier 'transfer_bytes'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

R5 pread restored 129/129 instructions; structural/exact differences (0, 10)
uhf_msc_blk_pread | R5 corrected byte-count temporary in copy branch only | 129/129 instructions; structural/exact differences (0, 33)
R5 pread declaration search71 builds no improvement; restored 129/129 instructions; structural/exact differences (0, 10)

R5 TMCJPEGDEC_IdctBlock4x4 fetch rc=0 ; origin/main 65cd387bcb48559396b79257ab6069fcda9bf259; source identical=True; baseline open per fresh report. 136/136 frame0x120, row loads, arithmetic scheduling and store order differ19 structural/93 exact. Target first pass reuses row temporaries and stores0,1,2,3; d+b operand order. Column clamp/pitch schedule shape same. No data sections.
TMCJPEGDEC_IdctBlock4x4 | R5 reusable row temporaries with canonical four-store order and d+b operand | 136/136 instructions; structural/exact differences (37, 93)
TMCJPEGDEC_IdctBlock4x4 | R5 delay even coefficient loads until odd rotation expression | 130/136 instructions; structural/exact differences (45, 134)
TMCJPEGDEC_IdctBlock4x4 | R5 odd sum before rotation with same store boundaries | 136/136 instructions; structural/exact differences (37, 93)
R5 luma restored 136/136 instructions; structural/exact differences (19, 93)
TMCJPEGDEC_IdctBlock4x4 | R5 native-int arithmetic locals at coefficient conversion boundaries | 136/136 instructions; structural/exact differences (37, 93)
TMCJPEGDEC_IdctBlock4x4 | R5 named odd difference and multiplication before delayed rotation shift | 136/136 instructions; structural/exact differences (37, 93)
TMCJPEGDEC_IdctBlock4x4 | R5 commuted butterfly addition operands for both row stores | 136/136 instructions; structural/exact differences (37, 93)
R5 luma after extra structural probes restored 136/136 instructions; structural/exact differences (19, 93)
PFVOL_p_rmvvol | R5 named const marker definition after functions, preserving actual object and references | 64/64 instructions; structural/exact differences (2, 4)
R5 const definition-order probe restored 64/64 instructions; structural/exact differences (2, 4)

R5 TMCJPEGDEC_IdctBlock4x4_Col fetch rc=0 ; origin/main 65cd387bcb48559396b79257ab6069fcda9bf259; source identical=True; baseline open per fresh report. 139/137 frame0x120, extra saved r28 and epilog reload plus reassociated odd sums; target reuses row variables and stores0..3; column arithmetic operand order d+b. No data sections.
TMCJPEGDEC_IdctBlock4x4_Col | R5 common odd rotation locals reused in positive and negative butterfly outputs | 137/137 instructions; structural/exact differences (31, 48)
TMCJPEGDEC_IdctBlock4x4_Col | R5 target odd-sum and rotated-sum operand order on shared temporaries | 137/137 instructions; structural/exact differences (31, 48)
TMCJPEGDEC_IdctBlock4x4_Col | R5 reuse row coefficients and butterfly state across both column rows | 135/137 instructions; structural/exact differences (47, 136)
R5 Col restored 139/137 instructions; structural/exact differences (33, 134)
PFVOL_p_rmvvol | R5 external linkage for named readonly marker, same8byte definition | 64/64 instructions; structural/exact differences (2, 4)
R5 restored after linkage probe 64/64 instructions; structural/exact differences (2, 4)
TMCJPEGDEC_IdctBlock4x4 | R5 common row helper with named butterfly intermediates | 136/136 instructions; structural/exact differences (31, 93)
TMCJPEGDEC_IdctBlock4x4 | R5 row helper output parameter before readonly input | 136/136 instructions; structural/exact differences (31, 93)
TMCJPEGDEC_IdctBlock4x4 | R5 row helper coefficient locals before butterfly state | 136/136 instructions; structural/exact differences (31, 93)
TMCJPEGDEC_IdctBlock4x4_Col | R5 common row helper with named butterfly intermediates | 137/137 instructions; structural/exact differences (31, 54)
TMCJPEGDEC_IdctBlock4x4_Col | R5 row helper output parameter before readonly input | 137/137 instructions; structural/exact differences (31, 54)
TMCJPEGDEC_IdctBlock4x4_Col | R5 row helper coefficient locals before butterfly state | 137/137 instructions; structural/exact differences (31, 54)
R5 helper probes restored 139/137 instructions; structural/exact differences (33, 134)
PFENT_ITER_GetLFNEntryName | R5 directory-name address plus byte offset and byte-length terminator conversion | 76/73 instructions; structural/exact differences (24, 75)
R5 integer-address probe restored 73/73 instructions; structural/exact differences (9, 43)
TMCJPEGDEC_IdctBlock4x4 | R5 single rotation expression reused in first-row butterfly | 136/136 instructions; structural/exact differences (13, 93)
TMCJPEGDEC_IdctBlock4x4 | R5 single rotation with fourth-plus-second sum order | 136/136 instructions; structural/exact differences (13, 93)
TMCJPEGDEC_IdctBlock4x4 | R5 single rotation and target first-row output-store order | 136/136 instructions; structural/exact differences (39, 93)
R5 luma narrowed rotation restored 136/136 instructions; structural/exact differences (19, 93)
R5 IDCT luma single objdiff 90.43459 function 85.161766 136/136 instructions; structural/exact differences (13, 93)
R5 IDCT luma single reverse objdiff 90.412415 function 85.088234 136/136 instructions; structural/exact differences (13, 93)
R5 IDCT Col shared oddrot objdiff 90.773834 function 83.89781 137/137 instructions; structural/exact differences (31, 48)
SOGetInterfaceOpt | R5 command-return helper with option and level ordered by validation lifetime | 119/119 instructions; structural/exact differences (0, 14)
R5 SO payload helper restored 119/119 instructions; structural/exact differences (0, 5)
R5 luma full local block declaration search: declaration block:
      s32 bd;
      s32 d;
      s32 c;
      s32 a;
      s32 b;
  
      s32* sp;
      s32* dp;
  
      s32 tmp[64];
      s32 i;
  
      s32 evsum, rot, oddrot, cd;
start (19, 93)
best (19, 93) after 120 builds; source restored; best order was:
    s32 bd;
    s32 d;
    s32 c;
    s32 a;
    s32 b;

    s32* sp;
    s32* dp;

    s32 tmp[64];
    s32 i;

    s32 evsum, rot, oddrot, cd;

R5 Col leading declaration search13 builds no improvement, retained shared oddRotation expressions:137/137 instructions,31 structural48 exact; no new exact function claimed. objdiff83.240875->83.89781.
R5 data ownership audit: all seven units already have100% matched_data, owned sections unchanged; SOOption/IDCT have no data, volume210976,iterator24,tiString288,SignWindow3468,MSC424 exact. No symbol rename or extent change made: no name-pairing gap in these units. Weak emitted vtables ignored. All source experiments confined to owned units and restored except reusable IDCT odd-rotation locals.

R5 completeness audit of every open function, count of distinct successful source attempts this round:
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator: 3 successful distinct source attempts; remains open.
inputChar__Q39textinput8tistring9DecolatedFw: 3 successful distinct source attempts; remains open.
SOGetInterfaceOpt: 4 successful distinct source attempts; remains open.
TMCJPEGDEC_IdctBlock4x4: 12 successful distinct source attempts; remains open.
TMCJPEGDEC_IdctBlock4x4_Col: 6 successful distinct source attempts; remains open.
PFENT_ITER_FindCluster: 3 successful distinct source attempts; remains open.
PFENT_ITER_GetLFNEntryName: 4 successful distinct source attempts; remains open.
PFVOL_p_rmvvol: 5 successful distinct source attempts; remains open.
PFVOL_attach: 6 successful distinct source attempts; remains open.
PFVOL_regctx: 3 successful distinct source attempts; remains open.
uhf_msc_blk_pread: 3 successful distinct source attempts; remains open.

R5 precommit quick gate over all seven owned units: GATE PASS; regressions0, forbidden0, readability0, all pools identical. Retained only column-IDCT shared odd rotations, removes extra saved-register save/restore,139->137 instructions. Exact counts/code bytes/data bytes unchanged.

R5 final full clean gate is running after code commit650cc87e. No source edits while it builds. Live before-run metrics normalized missing data to0:
main/src/keyboard/tiSignWindow: 55/56 exact; code6300/7184; data3468/3468
main/src/keyboard/tiString: 41/42 exact; code4632/5176; data288/288
main/libs/RevoEX/src/so/SOOption: 3/4 exact; code816/1292; data0/0
main/libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var: 4/6 exact; code712/1804; data0/0
main/libs/RVL_SDK/src/fa/pf_entry_iterator: 14/16 exact; code6640/7880; data24/24
main/libs/RVL_SDK/src/fa/pf_volume: 34/37 exact; code16732/17992; data210976/210976
main/libs/RVL_SDK/src/fa/msc/puh_msc_blk: 10/11 exact; code1556/2072; data424/424

## Round5 final full clean gate, copied verbatim
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/so/SOOption] pool: IDENTICAL
[libs/RevoEX/src/so/SOOption] objdiff: code 816/1292 data None/None functions 3/4 fuzzy 99.9226 linked code 0
[libs/RevoEX/src/so/SOOption] instruction-exact functions: 3/4
[libs/RevoEX/src/so/SOOption]   section .text size 1292 match 99.9226
[libs/RevoEX/src/so/SOOption]   below 100: SOGetInterfaceOpt 99.78992
[libs/RevoEX/src/so/SOOption] baseline: code 816/1292 data None functions 3 fuzzy 99.9226
[libs/RVL_SDK/src/fa/pf_volume] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_volume] objdiff: code 16732/17992 data 210976/210976 functions 34/37 fuzzy 99.8755 linked code 0
[libs/RVL_SDK/src/fa/pf_volume] instruction-exact functions: 34/37
[libs/RVL_SDK/src/fa/pf_volume]   section .bss size 210944 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .data size 16 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .sdata size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .text size 17992 match 99.8755
[libs/RVL_SDK/src/fa/pf_volume]   below 100: PFVOL_p_rmvvol 95.9375
[libs/RVL_SDK/src/fa/pf_volume]   below 100: PFVOL_attach 98.72159
[libs/RVL_SDK/src/fa/pf_volume]   below 100: PFVOL_regctx 99.0
[libs/RVL_SDK/src/fa/pf_volume] baseline: code 16732/17992 data 210976 functions 34 fuzzy 99.8755
[libs/RVL_SDK/src/fa/pf_entry_iterator] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_entry_iterator] objdiff: code 6640/7880 data 24/24 functions 14/16 fuzzy 99.6264 linked code 0
[libs/RVL_SDK/src/fa/pf_entry_iterator] instruction-exact functions: 14/16
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .sdata size 24 match 100.0
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .text size 7880 match 99.626396
[libs/RVL_SDK/src/fa/pf_entry_iterator]   below 100: PFENT_ITER_FindCluster 99.81013
[libs/RVL_SDK/src/fa/pf_entry_iterator]   below 100: PFENT_ITER_GetLFNEntryName 90.53425
[libs/RVL_SDK/src/fa/pf_entry_iterator] baseline: code 6640/7880 data 24 functions 14 fuzzy 99.6264
[src/keyboard/tiString] pool: IDENTICAL
[src/keyboard/tiString] objdiff: code 4632/5176 data 288/288 functions 41/42 fuzzy 98.9629 linked code 0
[src/keyboard/tiString] instruction-exact functions: 41/42
[src/keyboard/tiString]   section .data size 288 match 100.0
[src/keyboard/tiString]   section .text size 5176 match 98.962906
[src/keyboard/tiString]   below 100: inputChar__Q39textinput8tistring9DecolatedFw 90.132355
[src/keyboard/tiString] baseline: code 4632/5176 data 288 functions 41 fuzzy 98.9629
[src/keyboard/tiSignWindow] pool: IDENTICAL
[src/keyboard/tiSignWindow] objdiff: code 6300/7184 data 3468/3468 functions 55/56 fuzzy 99.8914 linked code 0
[src/keyboard/tiSignWindow] instruction-exact functions: 55/56
[src/keyboard/tiSignWindow]   section .ctors size 4 match 100.0
[src/keyboard/tiSignWindow]   section .data size 2672 match 100.0
[src/keyboard/tiSignWindow]   section .rodata size 784 match 100.0
[src/keyboard/tiSignWindow]   section .sdata size 8 match 100.0
[src/keyboard/tiSignWindow]   section .text size 7184 match 99.891426
[src/keyboard/tiSignWindow]   below 100: create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.117645
[src/keyboard/tiSignWindow] baseline: code 6300/7184 data 3468 functions 55 fuzzy 99.8914
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] pool: IDENTICAL
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] objdiff: code 1556/2072 data 424/424 functions 10/11 fuzzy 99.8938 linked code 0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] instruction-exact functions: 10/11
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .bss size 384 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .data size 32 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .text size 2072 match 99.89382
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   below 100: uhf_msc_blk_pread 99.57365
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] baseline: code 1556/2072 data 424 functions 10 fuzzy 99.8938
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] objdiff: code 712/1804 data None/None functions 4/6 fuzzy 90.7738 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] instruction-exact functions: 4/6
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var]   section .text size 1804 match 90.773834
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var]   below 100: TMCJPEGDEC_IdctBlock4x4 85.625
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var]   below 100: TMCJPEGDEC_IdctBlock4x4_Col 83.89781
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] baseline: code 712/1804 data None functions 4 fuzzy 90.5743
regressions vs baseline: 0
global matched_code_percent: 88.92459 -> 88.92459
global fuzzy_match_percent: 99.48913 -> 99.48926
global complete_code_percent: 65.19670 -> 65.19670
global matched_data_percent: 99.06781 -> 99.06781
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Round5 exact functions, matched code bytes, matched data bytes before -> after:
libs/RevoEX/src/so/SOOption: functions 3/4 -> 3/4; code 816 -> 816/1292; data 0 -> 0/0
libs/RVL_SDK/src/fa/pf_volume: functions 34/37 -> 34/37; code 16732 -> 16732/17992; data 210976 -> 210976/210976
libs/RVL_SDK/src/fa/pf_entry_iterator: functions 14/16 -> 14/16; code 6640 -> 6640/7880; data 24 -> 24/24
src/keyboard/tiString: functions 41/42 -> 41/42; code 4632 -> 4632/5176; data 288 -> 288/288
src/keyboard/tiSignWindow: functions 55/56 -> 55/56; code 6300 -> 6300/7184; data 3468 -> 3468/3468
libs/RVL_SDK/src/fa/msc/puh_msc_blk: functions 10/11 -> 10/11; code 1556 -> 1556/2072; data 424 -> 424/424
libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var: functions 4/6 -> 4/6; code 712 -> 712/1804; data 0 -> 0/0

Round5 every remaining open function relisted after final clean build:
SOGetInterfaceOpt: 99.78992%; five parameter-register coloring differences; frame/branches/instruction count exact; 4 distinct successful source attempts.
PFVOL_p_rmvvol: 95.9375%; constant scalar folds to li; target loads byte initializer template; aggregate exact-code variants need different data and were rejected; 5 distinct successful source attempts.
PFVOL_attach: 98.72159%; inline clear_mount result boundary removes two target instructions; success status materialization unresolved; 6 distinct successful source attempts.
PFVOL_regctx: 99.0%; 15 free-index/status register-color differences in unrolled loop; 3 distinct successful source attempts.
PFENT_ITER_FindCluster: 99.81013%; eight constant-one/entries-per-sector register-color differences; 3 distinct successful source attempts.
PFENT_ITER_GetLFNEntryName: 90.53425%; target byte-offset loop versus source pointer induction, plus terminator multiply/clear-bit form; 4 distinct successful source attempts.
inputChar__Q39textinput8tistring9DecolatedFw: 90.132355%; Hangul conversion helper boundary folds dynamic append and count;125/136 instructions; 3 distinct successful source attempts.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator: 99.117645%; 34 hoisted vtable/constants and animation-loop register-color differences; 3 distinct successful source attempts.
uhf_msc_blk_pread: 99.57365%; 10 transfer-count/product register-color differences; 3 distinct successful source attempts.
TMCJPEGDEC_IdctBlock4x4: 85.625%; row scheduling/store order and operands;136/136 instructions,19 structural93 exact differences; 12 distinct successful source attempts.
TMCJPEGDEC_IdctBlock4x4_Col: 83.89781%; row scheduling/operand order;137/137 instructions,31 structural48 exact differences; 6 distinct successful source attempts.

Files changed: libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var.c and tools/decomp-assist/fz3.attempts.md; code commit650cc87e. No symbol/config changes, no unowned eZiText changes. Zero new exact functions; retained one honest fuzzy improvement: Col83.240875->83.89781 and139->137 instructions. Full gatePASS, regressions0, forbidden0, readability0; target DOL SHA1 unchanged.
Uncertain: original Hangul converter/helper structure, clear_mount inline result materialization, IDCT source scheduling, and whether pure register differences have another real source lever. No full-completion claim.

# Round6 XHIGH, same branch HEAD98cb7171. Each trial logs first differing instruction and source construct, with original always restored until accepted by gate.
SOGetInterfaceOpt first difference instruction5: parameter level moved to r25, targetr26. Register allocation class;119/119 frame0x30 branches operands/helper calls identical. Change full option-helper formal parameter lifetime ordering before declaration-only searches.
SOGetInterfaceOpt | R6 full helper with option level length value lifetime order | objdiff 98.32773; 119/119 instructions; structural/exact (4, 42); first (5, ('mr', 'r27, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 full helper option before level with unchanged output arguments | objdiff 98.32773; 119/119 instructions; structural/exact (4, 42); first (5, ('mr', 'r27, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 initialize request-state locals before preparation | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 retain option parameter until reply pointer initialization | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 option command store before level at reply setup boundary | objdiff 99.85714; 119/119 instructions; structural/exact (2, 3); first (5, ('mr', 'r28, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 option store precedes level before both reply pointer declarations | objdiff 99.85714; 119/119 instructions; structural/exact (2, 3); first (5, ('mr', 'r28, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 selection state fields initialized option before level but command stores in target order | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 typed command-header aggregate assignment retains8byte command extent | BUILD FAIL /src/so && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/so/SOOption.d build/43U/src/libs/RevoEX/src/so/SOOption.d ### mwcceppc.exe Compiler: #    File: libs\RevoEX\src\so\SOOption.c # -------------------------------------- #     119:                     InterfaceHeader header = {level, option};  #   Error:                                                             ^ #   (10124) illegal constant expression #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
SOGetInterfaceOpt | R6 typed command-header copy with C89 field initialization | objdiff 98.0084; 121/119 instructions; structural/exact (12, 82); first (0, ('stwu', 'r1, -0x40(r1)'), ('stwu', 'r1, -0x30(r1)'))
SOGetInterfaceOpt | R6 command and response phases share typed local length and reply union state | objdiff 98.23529; 119/119 instructions; structural/exact (0, 41); first (5, ('mr', 'r27, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 length validator defined after get implementation using forward declaration | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 distinct preparation status and operation result lifetimes | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 separate ioctl result from public API return result | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 typed response state stores length pointer before data pointer | objdiff 98.94958; 119/119 instructions; structural/exact (0, 24); first (5, ('mr', 'r28, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 typed response state stores data pointer before length pointer | objdiff 98.94958; 119/119 instructions; structural/exact (0, 24); first (5, ('mr', 'r28, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 command and returned-length pointers grouped as IPC input state | objdiff 99.07563; 119/119 instructions; structural/exact (0, 22); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 allocation request and response-buffer pointer in shared state record | objdiff 98.94958; 119/119 instructions; structural/exact (0, 24); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
R6 SOGetInterfaceOpt register-only declaration search after helper/state/lifetime trials: declaration block:
      s32 rm;
      int temporary;
      int size;
      int result;
      InterfaceOption* request;
      InterfaceCommand* command;
      int* returnedLength;
      u8* reply;
start (0, 5)
best (0, 5) after 30 builds; source restored; best order was:
    s32 rm;
    int temporary;
    int size;
    int result;
    InterfaceOption* request;
    InterfaceCommand* command;
    int* returnedLength;
    u8* reply;

R6 PFVOL_p_rmvvol first difference instruction3: source li r0,0xe5 before root pointer setup; target addi r4,r1,0x2b0 then SDA lbz at6. Initialization construct folded scalar versus aggregate byte template;64/64 frame0x500. Source on origin/main identical. Inspect real template type/extents, do not add padding or unused objects.
PFVOL_p_rmvvol | R6 ordinary memcpy of named marker byte allows builtin constant-size copy | objdiff 89.375; 67/64 instructions; structural/exact (7, 63); first (2, ('li', 'r4, 0'), ('stw', 'r0, 0x504(r1)'))
R6 deleted marker data evidence: target .sdata2 aligned8, sole extent8 contains E5 followed7zeros, only code relocation lbz readsbyte0 and PFSEC_WriteData count1. A local one-byte initializer proves compiled template1 but does not independently prove original object1 rather than array8; no extent edits retained without full pairing proof/gate.
PFVOL_p_rmvvol | R6 explicit byte view of named readonly marker before root lookup | objdiff 93.75; 64/64 instructions; structural/exact (2, 3); first (4, ('lbz', 'r0, 0(0)'), ('stw', 'r31, 0x4fc(r1)'))
PFVOL_p_rmvvol | R6 readonly marker byte view in scalar declaration initializer | objdiff 93.75; 64/64 instructions; structural/exact (2, 3); first (4, ('lbz', 'r0, 0(0)'), ('stw', 'r31, 0x4fc(r1)'))
R6 marker byte-view cast generates actual SDA lbz without volatile or new data. Target and ours now both load the same8-byte E5/zero marker through one-byte access; target object lbl_816959A0 vs real source deleted_entry_mark may require permitted name pairing. Investigate relocation names before changing config.
PFVOL_p_rmvvol | R6 typed deleted directory-byte field copied through readonly marker view | objdiff 93.75; 64/64 instructions; structural/exact (2, 3); first (4, ('lbz', 'r0, 0(0)'), ('stw', 'r31, 0x4fc(r1)'))
PFVOL_p_rmvvol | R6 one-byte directory-mark aggregate copy initialized from named readonly data | objdiff 93.75; 64/64 instructions; structural/exact (2, 3); first (4, ('lbz', 'r0, 0(0)'), ('stw', 'r31, 0x4fc(r1)'))
PFVOL_p_rmvvol | R6 natural one-byte local initializer with obsolete8byte constant removed | objdiff 100.0; 64/64 instructions; structural/exact (0, 0); first None
EXACT CANDIDATE /tmp/fz3-r6-candidates/PFVOL_p_rmvvol_natural_one_byte_local_initializer_with_obsolete8byte_constant_removed.txt
R6 natural local deleted[1]={0xE5} proves byte-template initialization and target64/64 instructions exact. Code100%; original8byte global removed, section may have7 alignment bytes. Testing authorized symbol extent correction only, no addresses or split/section totals will change. Proof: PFVOL_p_rmvvol sole SDA21 relocation lbz reads one byte, stores to stack byte8, WriteData pointer stack8 count1; natural type u8[1] and target next unit alignment8 account for trailing7zero bytes.
R6 ACCEPTED data extent proof: PFVOL_p_rmvvol relocation SDA21 at offset0x7a8 reads1 byte of lbl_816959A0; stack byte8 is passed to PFSEC_WriteData count1; local u8[1] initializer compiles identical64 instructions. Correct object extent8->1 at same0x816959A0, leave7 alignment zeros unowned; split .sdata2 remains8 bytes and unit data210976/210976 unchanged. No address or section-total edits.
R6 PFVOL_p_rmvvol exact100%, ctxdiff64/64 diffs0, pool identical; volume34/37->35/37, matched code16732->16988/17992; quick full-build gatePASS, regressions0/forbidden0/readability0, DOL SHA1 correct.
R6 PFVOL_attach first difference35 is exit branch displacement524 vs532, caused by missing inline return-materialization instructions. First semantic difference142 beq8 vs12, then missing mr r0,r3. Frame0x20 correct, data/pool exact; change attach-only status conversion and helper completion boundary; shared clear_mount consumers must stay exact.
PFVOL_attach | R6 native-int attach mount status converts signed-long inline return | objdiff 98.72159; 174/176 instructions; structural/exact (10, 39); first (35, ('b', '524'), ('b', '532'))
PFVOL_attach | R6 unsigned attach-status view of inline mount result | objdiff 98.72159; 174/176 instructions; structural/exact (10, 39); first (35, ('b', '524'), ('b', '532'))
PFVOL_attach | R6 auto-inline attach-only mount helper preserves returned status boundary | objdiff 98.72159; 174/176 instructions; structural/exact (10, 39); first (35, ('b', '524'), ('b', '532'))
PFVOL_attach | R6 auto inline clear_mount boundary | objdiff 98.72159; 174/176 instructions; structural/exact (10, 39); first (35, ('b', '524'), ('b', '532'))
PFVOL_attach | R6 single joined mount status after success branch | objdiff 95.142044; 176/176 instructions; structural/exact (10, 22); first (134, ('li', 'r31, 0'), ('ori', 'r0, r0, 0x10'))
PFVOL_regctx | R6 fresh origin/main unchanged function; first difference16 free_context_index r5 versus targetr8; frame0x10 and75instructions identical, unrolled-loop stat r8 versus targetr5. Structural diagnosis complete; declaration/temporary experiments next.
PFVOL_regctx | R6 context id and free slot state | objdiff 80.36; 83/75 instructions; structural/exact (27, 71); first (12, ('b', '268'), ('b', '236'))
PFVOL_regctx | R6 unsigned free slot and signed status temporary | objdiff 99.0; 75/75 instructions; structural/exact (0, 15); first (16, ('li', 'r5, 0'), ('li', 'r8, 0'))
PFVOL_regctx | R6 explicit continue after selecting free context | objdiff 99.0; 75/75 instructions; structural/exact (0, 15); first (16, ('li', 'r5, 0'), ('li', 'r8, 0'))
PFENT_ITER_FindCluster | R6 origin/main source unchanged; pool identical; first39 li r7,1 vs targetr8,1, with8pure operand diffs/237instructions/frame0xA0; constantone and entries_per_sector interference. Structural initialization boundaries examined before declsearch.
PFENT_ITER_FindCluster | R6 initialize FAT hint before iterator fields | objdiff 95.43882; 237/237 instructions; structural/exact (8, 50); first (2, ('li', 'r8, 0'), ('li', 'r6, 0'))
PFENT_ITER_FindCluster | R6 inline iterator setup with returned entry count | BUILD FAIL s/RVL_SDK/src/fa && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/fa/pf_entry_iterator.d build/43U/src/libs/RVL_SDK/src/fa/pf_entry_iterator.d ### mwcceppc.exe Compiler: #    File: libs\RVL_SDK\src\fa\pf_entry_iterator.c # ------------------------------------------------ #     500:     pf_u32 entries_per_sector = 1 << iter->log2_entries_per_sector;  #   Error:     ^^^^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
PFENT_ITER_FindCluster | R6 C89 inline iterator setup and returned entry count | objdiff 99.81013; 237/237 instructions; structural/exact (0, 8); first (39, ('li', 'r7, 1'), ('li', 'r8, 1'))
PFENT_ITER_FindCluster | R6 entry geometry state shares first cluster constant | BUILD FAIL ld/43U/src/libs/RVL_SDK/src/fa/pf_entry_iterator.d build/43U/src/libs/RVL_SDK/src/fa/pf_entry_iterator.d ### mwcceppc.exe Compiler: #    File: libs\RVL_SDK\src\fa\pf_entry_iterator.c # ------------------------------------------------ #     513:     iter.log2_geometry.entries = p_ent->p_vol->bpb.log2_bytes_per_sector - 5;  #   Error:                       ^ #   (10393) 'log2_geometry' is not a member of class 'struct PFITER_ENT_ITER' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
PFENT_ITER_FindCluster | R6 typed entry geometry shares first cluster constant | objdiff 99.81013; 237/237 instructions; structural/exact (0, 8); first (39, ('li', 'r7, 1'), ('li', 'r8, 1'))
PFENT_ITER_GetLFNEntryName | R6 fresh fetch and source check; first13 pointer induction mr r31,r28 versus target zero fragment counter r29. Both73/frame0x30; target keeps byteoffset, calculates destination atloop44, reloadsLFNcount and terminates count*26 masked even. Need fragment-address/terminator constructs, not register edits.
PFENT_ITER_GetLFNEntryName | R6 byteoffset destination and count-derived terminator | objdiff 79.328766; 76/73 instructions; structural/exact (24, 75); first (0, ('stwu', 'r1, -0x20(r1)'), ('stwu', 'r1, -0x30(r1)'))
PFENT_ITER_GetLFNEntryName | R6 fragment inline helper returns byteoffset | objdiff 99.246574; 73/73 instructions; structural/exact (0, 8); first (14, ('li', 'r30, 0'), ('li', 'r31, 0'))
PFENT_ITER_GetLFNEntryName | R6 fragment helper counter initializes before offset | objdiff 99.178085; 73/73 instructions; structural/exact (0, 9); first (13, ('li', 'r30, 0'), ('li', 'r29, 0'))
PFENT_ITER_GetLFNEntryName | R6 fragment helper progress fields counter then offset | objdiff 99.38356; 73/73 instructions; structural/exact (0, 7); first (13, ('li', 'r30, 0'), ('li', 'r29, 0'))
PFENT_ITER_GetLFNEntryName | R6 fragment progress offset then counter | objdiff 99.38356; 73/73 instructions; structural/exact (0, 7); first (13, ('li', 'r30, 0'), ('li', 'r29, 0'))
PFENT_ITER_GetLFNEntryName | R6 fragment helper offset parameter first | objdiff 99.246574; 73/73 instructions; structural/exact (0, 8); first (14, ('li', 'r30, 0'), ('li', 'r31, 0'))
PFENT_ITER_GetLFNEntryName | R6 fragment helper updates byteoffset by pointer | objdiff 79.328766; 76/73 instructions; structural/exact (24, 75); first (0, ('stwu', 'r1, -0x20(r1)'), ('stwu', 'r1, -0x30(r1)'))
PFENT_ITER_GetLFNEntryName | R6 fragment helper uses UTF16 destination type | objdiff 99.246574; 73/73 instructions; structural/exact (0, 8); first (14, ('li', 'r30, 0'), ('li', 'r31, 0'))
PFENT_ITER_GetLFNEntryName | R6 retained ordinary inline fragment copy returning byteoffset, count-derived terminator; source73 target73, structural0, remaining7 registeroperand differences. declsearch6builds moved declaration index beforecounter, best7; no artificial fields retained.
PFENT_ITER_GetLFNEntryName | R6 quick gate PASS:99.38356 vs90.53425;14/16 exact unchanged, code6640/7880 data24/24, global regressions0 forbidden0 readability0 DOL26116613f624061ba99c8d1a299aaa6efa85670d. Retain structural correction with7 registerdifferences for future escalation.
inputChar__Q39textinput8tistring9DecolatedFw | R6 fresh origin source unchanged poolidentical; first10 branch extent corresponds125vs136/frame0x30; true firstconstruct65 mode3 lacks inlined dynamiccount append, initialNUL, ch==newline comparison. Count truncation also foldedaway; do generic builder helper experiments, no invented newline stub.
inputChar__Q39textinput8tistring9DecolatedFw | R6 two inline builder boundaries return input length | objdiff 90.132355; 125/136 instructions; structural/exact (18, 73); first (10, ('beq', '428'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R6 inline append length by C++ reference | objdiff 90.132355; 125/136 instructions; structural/exact (18, 73); first (10, ('beq', '428'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R6 input builder constructor append finish method boundaries | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R6 out of class auto inline input builder methods | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R6 fresh origin source unchanged pool30identical; first48 vtablelisr26 vstarget25;221instructions/frame0x50 and34operandonly differences. Hoistedconstructor vtables and animationCount/animationentry lifetimes interfere; try animation inline boundary.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R6 animation resource setup in independent inline helper | objdiff 90.22172; 223/221 instructions; structural/exact (45, 158); first (48, ('lis', 'r27, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R6 animation inline helper retains owner field reloads | objdiff 97.714935; 221/221 instructions; structural/exact (0, 73); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R6 pane descriptor pointer instead of reference lifetime | objdiff 99.117645; 221/221 instructions; structural/exact (0, 34); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
uhf_msc_blk_pread | R6 fresh fetch source unchanged poolidentical; first75 clrlwi transfer_blocks r25 vstarget27, productr27 vstarget25;129instructions/frame0x40 and10operand-only differences. Try transfer selection inline boundary and actual read transfer descriptor, then declarations.
uhf_msc_blk_pread | R6 inline transfer limit selection returns u16 | objdiff 99.612404; 129/129 instructions; structural/exact (0, 10); first (26, ('li', 'r25, 0'), ('li', 'r26, 0'))
uhf_msc_blk_pread | R6 inline selection returns full count caller narrows | objdiff 98.21706; 130/129 instructions; structural/exact (9, 59); first (18, ('b', '424'), ('b', '420'))
uhf_msc_blk_pread | R6 read descriptor combines selected device and transfer count | objdiff 100.0; 129/129 instructions; structural/exact (0, 0); first None
EXACT CANDIDATE /tmp/fz3-r6-candidates/uhf_msc_blk_pread_read_descriptor_combines_selected_device_and_transfer_count.txt
uhf_msc_blk_pread | R6 exact candidate: inline u16 selection fixes count operand at75; ordinary read descriptor {device,blocks} fixes device/product live-range ordering.129/129 instructions0 structural0 operands; no dummy objects, pwrite unchanged.
TMCJPEGDEC_IdctBlock4x4 | R6 fresh origin/main function unchanged, poolidentical; first2 addi sp=r3 versus targetr8;136/frame0x120 identical but19instruction-form and93operanddifferences. Reused input/temporary pointers allow parameter coalescing; separate row/column pass scopes before operand tuning.
uhf_msc_blk_pread | R6 quick GATE PASS:11/11 vs10/11, code2072/2072 vs1556/2072 data424/424 unchanged, unitall100. Globalregressions0 forbidden0 readability0, ctxdiff129/129diffs0, DOL26116613f624061ba99c8d1a299aaa6efa85670d.
TMCJPEGDEC_IdctBlock4x4 | R6 distinct row and column pointer scopes | objdiff 85.84559; 136/136 instructions; structural/exact (19, 89); first (2, ('addi', 'r3, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R6 IDCT pass descriptor pairs source and temporary pointers | objdiff 85.77206; 136/136 instructions; structural/exact (19, 93); first (2, ('addi', 'r7, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R6 pass descriptor includes transform loop index | objdiff 85.77206; 136/136 instructions; structural/exact (19, 93); first (2, ('addi', 'r7, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R6 target order row stores and reusable even differences | objdiff 81.81618; 136/136 instructions; structural/exact (20, 93); first (2, ('addi', 'r3, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4_Col | R6 fresh origin source differs onlyaccepted oddrot commontemps fromHIGH; poolidentical; actual first8 lwz b r5 vstarget10, pointers7/8alreadymatch,137/frame0x120;31formdiffs/48operands, arithmeticload/store scheduling plus b/c/rot registerswap. Separate pass and row coefficients next.
TMCJPEGDEC_IdctBlock4x4_Col | R6 independent row and column source pointer scopes | objdiff 83.38686; 137/137 instructions; structural/exact (31, 54); first (8, ('lwz', 'r5, 4(r7)'), ('lwz', 'r10, 4(r7)'))
TMCJPEGDEC_IdctBlock4x4_Col | R6 shared coefficient temporaries row store sequence operand d+b | objdiff 78.948906; 135/137 instructions; structural/exact (47, 136); first (0, ('stwu', 'r1, -0x110(r1)'), ('stwu', 'r1, -0x120(r1)'))
TMCJPEGDEC_IdctBlock4x4_Col | R6 inline four-point helper returns arithmetic terms struct | objdiff 74.07299; 155/137 instructions; structural/exact (58, 154); first (0, ('stwu', 'r1, -0x160(r1)'), ('stwu', 'r1, -0x120(r1)'))
PFENT_ITER_GetLFNEntryName | R6 fragment helper computes next offset before copies | objdiff 99.38356; 73/73 instructions; structural/exact (0, 7); first (13, ('li', 'r30, 0'), ('li', 'r29, 0'))
PFENT_ITER_GetLFNEntryName | R6 fragment position and read status state | objdiff 99.38356; 73/73 instructions; structural/exact (0, 7); first (13, ('li', 'r30, 0'), ('li', 'r29, 0'))
PFENT_ITER_GetLFNEntryName | R6 reordered counter initialization after declaration search | objdiff 99.45206; 73/73 instructions; structural/exact (0, 6); first (14, ('li', 'r30, 0'), ('li', 'r31, 0'))
PFENT_ITER_GetLFNEntryName | R6 fragment helper accepts caller computed destination | objdiff 99.45206; 73/73 instructions; structural/exact (0, 6); first (14, ('li', 'r30, 0'), ('li', 'r31, 0'))
PFENT_ITER_GetLFNEntryName | R6 copy helper fragment destination and byte offset state | objdiff 99.45206; 73/73 instructions; structural/exact (0, 6); first (14, ('li', 'r30, 0'), ('li', 'r31, 0'))
PFENT_ITER_GetLFNEntryName | R6 caller scoped fragment destination temporary | objdiff 99.45206; 73/73 instructions; structural/exact (0, 6); first (14, ('li', 'r30, 0'), ('li', 'r31, 0'))
PFENT_ITER_GetLFNEntryName | R6 caller destination lifetime plus searched declaration order | objdiff 100.0; 73/73 instructions; structural/exact (0, 0); first None
EXACT CANDIDATE /tmp/fz3-r6-candidates/PFENT_ITER_GetLFNEntryName_caller_destination_lifetime_plus_searched_declaration_order.txt
PFENT_ITER_GetLFNEntryName | R6 exact: fragment helper accepts computed destination; caller owns destination lifetime; initialization counter before byteoffset; declaration index,destination,counter,error foundby2-builddeclsearch.73/73diffs0 objdiff100. Natural13UTF16/26byte fragment copies and count-derived terminator.
R6 declaration followups: SOGetInterfaceOpt30builds remained5, PFVOL_regctx13builds remained15, FindCluster30builds remained8, signcreate6builds remained34. They followed logged structural/source trials; originals restored.
PFENT_ITER_GetLFNEntryName | R6 quick GATE PASS:15/16 vs14/16, code6932/7880 vs6640/7880 data24/24,0 regressions forbidden readability, DOL26116613f624061ba99c8d1a299aaa6efa85670d.
PFENT_ITER_FindCluster | R6 explicit active FAT hint pointer lifetime | objdiff 98.50211; 237/237 instructions; structural/exact (2, 27); first (2, ('stw', 'r0, 0xa4(r1)'), ('li', 'r6, 0'))
PFENT_ITER_FindCluster | R6 iterator file descriptor named pointer temporary | objdiff 99.81013; 237/237 instructions; structural/exact (0, 8); first (39, ('li', 'r7, 1'), ('li', 'r8, 1'))
SOGetInterfaceOpt | R6 response header couples level and returned length pointer | objdiff 99.07563; 119/119 instructions; structural/exact (0, 22); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 option payload state holds selector and returned byte pointer | objdiff 98.94958; 119/119 instructions; structural/exact (0, 24); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 request descriptor combines header selectors and allocation | objdiff 99.32773; 119/119 instructions; structural/exact (0, 16); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R6 inline header stores with selector parameter before level | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
R6 completeness checkpoint: three new exact functions PFVOL_p_rmvvol, uhf_msc_blk_pread, PFENT_ITER_GetLFNEntryName are committed after quick gate PASS. All remaining functions have >=3 distinct successfully compiled R6 source trials; SO19, attach5, regctx3, FindCluster5+, input4, sign3, IDCT4/3. SO/pfvol/string/sign/IDCT rejected candidates restored; no eZiText edits. Data audit ownedunits: all target datascores100, only proven1byte deletion marker extent correction retained; weak duplicated symbols ignored.

## R6 final full clean gate and completeness audit
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/so/SOOption] pool: IDENTICAL
[libs/RevoEX/src/so/SOOption] objdiff: code 816/1292 data None/None functions 3/4 fuzzy 99.9226 linked code 0
[libs/RevoEX/src/so/SOOption] instruction-exact functions: 3/4
[libs/RevoEX/src/so/SOOption]   section .text size 1292 match 99.9226
[libs/RevoEX/src/so/SOOption]   below 100: SOGetInterfaceOpt 99.78992
[libs/RevoEX/src/so/SOOption] baseline: code 816/1292 data None functions 3 fuzzy 99.9226
[libs/RVL_SDK/src/fa/pf_volume] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_volume] objdiff: code 16988/17992 data 210976/210976 functions 35/37 fuzzy 99.9333 linked code 0
[libs/RVL_SDK/src/fa/pf_volume] instruction-exact functions: 35/37
[libs/RVL_SDK/src/fa/pf_volume]   section .bss size 210944 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .data size 16 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .sdata size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .text size 17992 match 99.933304
[libs/RVL_SDK/src/fa/pf_volume]   below 100: PFVOL_attach 98.72159
[libs/RVL_SDK/src/fa/pf_volume]   below 100: PFVOL_regctx 99.0
[libs/RVL_SDK/src/fa/pf_volume] baseline: code 16732/17992 data 210976 functions 34 fuzzy 99.8755
[libs/RVL_SDK/src/fa/pf_entry_iterator] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_entry_iterator] objdiff: code 6932/7880 data 24/24 functions 15/16 fuzzy 99.9772 linked code 0
[libs/RVL_SDK/src/fa/pf_entry_iterator] instruction-exact functions: 15/16
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .sdata size 24 match 100.0
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .text size 7880 match 99.97716
[libs/RVL_SDK/src/fa/pf_entry_iterator]   below 100: PFENT_ITER_FindCluster 99.81013
[libs/RVL_SDK/src/fa/pf_entry_iterator] baseline: code 6640/7880 data 24 functions 14 fuzzy 99.6264
[src/keyboard/tiString] pool: IDENTICAL
[src/keyboard/tiString] objdiff: code 4632/5176 data 288/288 functions 41/42 fuzzy 98.9629 linked code 0
[src/keyboard/tiString] instruction-exact functions: 41/42
[src/keyboard/tiString]   section .data size 288 match 100.0
[src/keyboard/tiString]   section .text size 5176 match 98.962906
[src/keyboard/tiString]   below 100: inputChar__Q39textinput8tistring9DecolatedFw 90.132355
[src/keyboard/tiString] baseline: code 4632/5176 data 288 functions 41 fuzzy 98.9629
[src/keyboard/tiSignWindow] pool: IDENTICAL
[src/keyboard/tiSignWindow] objdiff: code 6300/7184 data 3468/3468 functions 55/56 fuzzy 99.8914 linked code 0
[src/keyboard/tiSignWindow] instruction-exact functions: 55/56
[src/keyboard/tiSignWindow]   section .ctors size 4 match 100.0
[src/keyboard/tiSignWindow]   section .data size 2672 match 100.0
[src/keyboard/tiSignWindow]   section .rodata size 784 match 100.0
[src/keyboard/tiSignWindow]   section .sdata size 8 match 100.0
[src/keyboard/tiSignWindow]   section .text size 7184 match 99.891426
[src/keyboard/tiSignWindow]   below 100: create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.117645
[src/keyboard/tiSignWindow] baseline: code 6300/7184 data 3468 functions 55 fuzzy 99.8914
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] pool: IDENTICAL
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] objdiff: code 2072/2072 data 424/424 functions 11/11 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] instruction-exact functions: 11/11
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .bss size 384 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .data size 32 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   section .text size 2072 match 100.0
[libs/RVL_SDK/src/fa/msc/puh_msc_blk] baseline: code 1556/2072 data 424 functions 10 fuzzy 99.8938
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] objdiff: code 712/1804 data None/None functions 4/6 fuzzy 90.7738 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] instruction-exact functions: 4/6
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var]   section .text size 1804 match 90.773834
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var]   below 100: TMCJPEGDEC_IdctBlock4x4 85.625
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var]   below 100: TMCJPEGDEC_IdctBlock4x4_Col 83.89781
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] baseline: code 712/1804 data None functions 4 fuzzy 90.5743
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
libs/RevoEX/src/so/SOOption | R6 before -> after exact 3/4 -> 3/4; objdiff codebytes 816 -> 816/1292; databytes 0 -> 0/0
OPEN SOGetInterfaceOpt 99.78992% | 20 distinct compiledR6trials | 119/119 frame0x30;5parameter register differences level/option; all latercode identical.
libs/RVL_SDK/src/fa/pf_volume | R6 before -> after exact 34/37 -> 35/37; objdiff codebytes 16732 -> 16988/17992; databytes 210976 -> 210976/210976
OPEN PFVOL_attach 98.72159% | 5 distinct compiledR6trials | 174/176 frame0x20; missingerror join materialization mr0,r3 and li0,0 afterinline clear_mount.
OPEN PFVOL_regctx 99.0% | 3 distinct compiledR6trials | 75/75 frame0x10;15register differences free slotr5/8 versus statusr8/5 in unrolled contextscan.
libs/RVL_SDK/src/fa/pf_entry_iterator | R6 before -> after exact 14/16 -> 15/16; objdiff codebytes 6640 -> 6932/7880; databytes 24 -> 24/24
OPEN PFENT_ITER_FindCluster 99.81013% | 5 distinct compiledR6trials | 237/237 frame0xA0;8register differences sharedconstantoner7/8 versus entries-per-sectorr8/7.
src/keyboard/tiString | R6 before -> after exact 41/42 -> 41/42; objdiff codebytes 4632 -> 4632/5176; databytes 288 -> 288/288
OPEN inputChar__Q39textinput8tistring9DecolatedFw 90.132355% | 4 distinct compiledR6trials | 125/136 frame0x30; mode3input helper dynamicappend missing11instructions; original converter boundary unresolved.
src/keyboard/tiSignWindow | R6 before -> after exact 55/56 -> 55/56; objdiff codebytes 6300 -> 6300/7184; databytes 3468 -> 3468/3468
OPEN create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.117645% | 3 distinct compiledR6trials | 221/221 frame0x50;34register differences constructor-vtable hoisting, animationCount and animationentry lifetimes.
libs/RVL_SDK/src/fa/msc/puh_msc_blk | R6 before -> after exact 10/11 -> 11/11; objdiff codebytes 1556 -> 2072/2072; databytes 424 -> 424/424
libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var | R6 before -> after exact 4/6 -> 4/6; objdiff codebytes 712 -> 712/1804; databytes 0 -> 0/0
OPEN TMCJPEGDEC_IdctBlock4x4 85.625% | 4 distinct compiledR6trials | 136/136 frame0x120;19instruction-form and93operand differences source pointer coalescing, arithmetic/store scheduling.
OPEN TMCJPEGDEC_IdctBlock4x4_Col 83.89781% | 3 distinct compiledR6trials | 137/137 frame0x120;31instruction-form and48operand differences first-pass oddsum/rotation scheduling, b/c/rotation registerallocation.
Finalclean ctxdiff:PFVOL_p_rmvvol64/64diffs0;PFENT_ITER_GetLFNEntryName73/73diffs0;uhf_msc_blk_pread129/129diffs0. No code/data/regression failures. No untried remaining function.
R6 files: config/43U/symbols.txt;libs/RVL_SDK/src/fa/pf_volume.c;libs/RVL_SDK/src/fa/pf_entry_iterator.c;libs/RVL_SDK/src/fa/msc/puh_msc_blk.c;tools/decomp-assist/fz3.attempts.md. Commits:2f84a3fe exactvolume+markerextent;5ce59884 iteratorstructuralimprovement;78c76f31 exactMSC;673020e0 exactiterator. HIGH650cc87e/98cb7171 predateR6 retained.
Uncertainty: original mode3 Hangul converter source/inline boundary is unavailable; dynamiccounter and dead newline comparison are proven targetinstructions, generic helper/class attempts constant-fold. Marker1-byteextent proof recorded above; no otherdataownership changes.
