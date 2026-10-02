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

# Round7 XHIGH, fresh branch HEAD72cf3991. Each trial logs first differing instruction and source construct, with original always restored until accepted by gate.
libs/RevoEX/src/so/SOOption | R7 pool run before tuning; current source alreadyorigin/main; data ownership audit starts with target extents and relocation names.
libs/RVL_SDK/src/fa/pf_volume | R7 pool run before tuning; current source alreadyorigin/main; data ownership audit starts with target extents and relocation names.
libs/RVL_SDK/src/fa/pf_entry_iterator | R7 pool run before tuning; current source alreadyorigin/main; data ownership audit starts with target extents and relocation names.
src/keyboard/tiString | R7 pool run before tuning; current source alreadyorigin/main; data ownership audit starts with target extents and relocation names.
src/keyboard/tiSignWindow | R7 pool run before tuning; current source alreadyorigin/main; data ownership audit starts with target extents and relocation names.
libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var | R7 pool run before tuning; current source alreadyorigin/main; data ownership audit starts with target extents and relocation names.
libs/RevoEX/src/so/SOOption | R7 data 0/0; no unpaired owned data indicated.
SOGetInterfaceOpt | R7 extent 0x814b476c+0x1dc=0x814b4948; next SOSetInterfaceOpt 0x814b4948; overlap False
SOGetInterfaceOpt | R7 immediate stack store/reload evidence []; no unsupported volatile changes authorized.
libs/RVL_SDK/src/fa/pf_volume | R7 data 210976/210976; no unpaired owned data indicated.
PFVOL_attach | R7 extent 0x815e2364+0x2c0=0x815e2624; next PFVOL_detach 0x815e2624; overlap False
PFVOL_attach | R7 immediate stack store/reload evidence []; no unsupported volatile changes authorized.
PFVOL_regctx | R7 extent 0x815e4220+0x12c=0x815e434c; next PFVOL_unregctx 0x815e434c; overlap False
PFVOL_regctx | R7 immediate stack store/reload evidence []; no unsupported volatile changes authorized.
libs/RVL_SDK/src/fa/pf_entry_iterator | R7 data 24/24; no unpaired owned data indicated.
PFENT_ITER_FindCluster | R7 extent 0x815d3414+0x3b4=0x815d37c8; next PFENT_ITER_Retreat 0x815d37c8; overlap False
PFENT_ITER_FindCluster | R7 immediate stack store/reload evidence [(144, ('stw', 'r0, 0x20(r1)'), ('lwz', 'r0, 0x20(r1)'))]; no unsupported volatile changes authorized.
src/keyboard/tiString | R7 data 288/288; no unpaired owned data indicated.
inputChar__Q39textinput8tistring9DecolatedFw | R7 extent 0x81432ce4+0x220=0x81432f04; next confirmKana__Q39textinput8tistring9DecolatedFv 0x81432f04; overlap False
inputChar__Q39textinput8tistring9DecolatedFw | R7 immediate stack store/reload evidence []; no unsupported volatile changes authorized.
src/keyboard/tiSignWindow | R7 data 3468/3468; no unpaired owned data indicated.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R7 extent 0x81430e50+0x374=0x814311c4; next __dt__Q49textinput8keyboard10signwindow7AnmPaneFv 0x814311c4; overlap False
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R7 immediate stack store/reload evidence []; no unsupported volatile changes authorized.
libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var | R7 data 0/0; no unpaired owned data indicated.
TMCJPEGDEC_IdctBlock4x4 | R7 extent 0x814ef490+0x220=0x814ef6b0; next TMCJPEGDEC_IdctBlock2x2 0x814ef6b0; overlap False
TMCJPEGDEC_IdctBlock4x4 | R7 immediate stack store/reload evidence []; no unsupported volatile changes authorized.
TMCJPEGDEC_IdctBlock4x4_Col | R7 extent 0x814ef810+0x224=0x814efa34; next TMCJPEGDEC_IdctBlock2x2_Col 0x814efa34; overlap False
TMCJPEGDEC_IdctBlock4x4_Col | R7 immediate stack store/reload evidence []; no unsupported volatile changes authorized.
SOGetInterfaceOpt | R7 fresh fetch origin source identical; first5 level parameter r25 vstarget26 and optionr28 vstarget25;119instructions/frame0x30/branchforms andstoresotherwiseidentical. No overlappingextent or adjacentstackstore/reload. Const input helper and response views before declaration search.
SOGetInterfaceOpt | R7 const length input in OptionLength inline boundary | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R7 read-only view of typed selection object | objdiff 89.31933; 122/119 instructions; structural/exact (21, 116); first (0, ('stwu', 'r1, -0x40(r1)'), ('stwu', 'r1, -0x30(r1)'))
SOGetInterfaceOpt | R7 const selectors and returned response read view | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
PFVOL_attach | R7 fresh fetch origin unchanged; true first142 beq distance differs because target143 mr0,r3 gives mountstatus distinct from public return0r3.174/176 frame0x20. Successful source li3,0 afterClearMount vs targetli0,0. Inline helper/public early return boundary first, novolatileproof or extentoverlap.
PFVOL_attach | R7 public zero-return on mount error instead of discarded helper result | objdiff 100.0; 176/176 instructions; structural/exact (0, 0); first None
EXACT CANDIDATE /tmp/fz3-r7-candidates/PFVOL_attach_public_zero_return_on_mount_error_instead_of_discarded_helper_result.txt
PFVOL_attach | R7 exact candidate preserves s32 mount error separately from public zero return; no artificial data or volatile; attach inline helper not called bythispath.176/176differences0.
PFVOL_attach | R7 quick GATE PASS,0regressions forbidden readability,36/37vs35/37 exact code17692/17992vs16988 data210976/210976, ctxdiff176/176diffs0. DOL26116613f624061ba99c8d1a299aaa6efa85670d.
PFVOL_regctx | R7 fresh origin unchanged; first16 free slotr5 vsr8, statusr8 vsr5,75/75/frame0x10, nobranchformdifferences/noadjacentstackreloadproof. Const context table view and inline slot boundary next.
PFVOL_regctx | R7 const context array view for registration scan | objdiff 99.0; 75/75 instructions; structural/exact (0, 15); first (16, ('li', 'r5, 0'), ('li', 'r8, 0'))
PFVOL_regctx | R7 const single context input helper for active status | objdiff 99.066666; 75/75 instructions; structural/exact (0, 14); first (16, ('li', 'r7, 0'), ('li', 'r8, 0'))
PFVOL_regctx | R7 const context helper plus declaration order index free id error | objdiff 100.0; 75/75 instructions; structural/exact (0, 0); first None
EXACT CANDIDATE /tmp/fz3-r7-candidates/PFVOL_regctx_const_context_helper_plus_declaration_order_index_free_id_error.txt
PFVOL_regctx | R7 exact from real const input helper boundary ContextStatus, then declaration order context_index/free_context_index/context_id/error. Targetfree_slotr8 statusr5;75/75diffs0. const pointer selected load/temporary allocation; no volatile.
PFVOL_regctx | R7 quick GATE PASS volume37/37vs35/37, allcode17992/17992 alldata210976/210976,0regressions forbidden readability; targetDOLhash. ctxdiff75/75diffs0.
PFENT_ITER_FindCluster | R7 first39 sharedconstantone r7 vstarget8, shifted entriesr8 vstarget7,237/237/frame0xA0. Definitionvolatile evidence is iter.index, not current_cluster: iterator beginsstack0x20; target144 stw r0,0x20(r1) immediately145 lwz r0,0x20(r1), thencmp. Test private struct fieldqualifier with laterunitregressionaudit.
PFENT_ITER_FindCluster | R7 volatile iterator index field proven by immediate stack reload | objdiff 96.8903; 240/237 instructions; structural/exact (16, 202); first (18, ('b', '856'), ('b', '844'))
PFENT_ITER_FindCluster | R7 const iterator input helper returns sector entry count | objdiff 99.81013; 237/237 instructions; structural/exact (0, 8); first (39, ('li', 'r7, 1'), ('li', 'r8, 1'))
PFENT_ITER_FindCluster | R7 const directory entry input parameter | objdiff 85.27426; 227/237 instructions; structural/exact (47, 233); first (2, ('li', 'r9, 0'), ('li', 'r6, 0'))
PFENT_ITER_FindCluster | R7 const entry view only for initial iterator setup | objdiff 99.81013; 237/237 instructions; structural/exact (0, 8); first (39, ('li', 'r7, 1'), ('li', 'r8, 1'))
PFENT_ITER_FindCluster | R7 const cluster input in hint initialization boundary | objdiff 99.81013; 237/237 instructions; structural/exact (0, 8); first (39, ('li', 'r7, 1'), ('li', 'r8, 1'))
PFENT_ITER_FindCluster | R7 reuse initial cluster field for hint sentinel assignments | objdiff 99.81013; 237/237 instructions; structural/exact (0, 8); first (39, ('li', 'r7, 1'), ('li', 'r8, 1'))
inputChar__Q39textinput8tistring9DecolatedFw | R7 fresh origin unchanged; first65mode3branch size125/136frame0x30. Missing dynamicappend, initialNUL, deadnewlinecmp and countmask; no localvolatile evidence or symboloverlap. Constinput character and builder views test missing helper boundary honestly.
inputChar__Q39textinput8tistring9DecolatedFw | R7 const character pointer in mode3 inline append boundary | objdiff 90.132355; 125/136 instructions; structural/exact (18, 73); first (10, ('beq', '428'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R7 const stream view for mode3 termination and length | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R7 const stream reference preserves builder termination boundary | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R7 fresh origin unchanged221/frame0x50, first48 vtableconstantr26 vstarget25,34operand-only diffs constructor/table/counter registers. Const pane metadata helper before declaration permutations; no adjacentstack reload or extent overlap.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R7 const pane metadata in complete construction helper | objdiff 98.07692; 221/221 instructions; structural/exact (0, 61); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R7 const pane metadata reference in construction boundary | objdiff 98.07692; 221/221 instructions; structural/exact (0, 61); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R7 animation bound read directly through const pane metadata | objdiff 96.47059; 221/221 instructions; structural/exact (3, 128); first (5, ('li', 'r19, 0'), ('li', 'r14, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R7 readonly pane table base as named loop input | objdiff 99.162895; 221/221 instructions; structural/exact (0, 32); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
TMCJPEGDEC_IdctBlock4x4 | R7 fresh origin unchanged136/frame0x120. First2 sourceptrr3 vsr8;19form/93operanddiffs, rowstores1,2,3,0 vtarget0,1,2,3 andload/mathoperand ordering. disasm_fn fails no.rela.text; ctxdiff/Capstone andtarget.s authoritative. Noextentoverlap orstackreloadproof. Const coefficient view first.
TMCJPEGDEC_IdctBlock4x4 | R7 const source pointer for both IDCT passes | objdiff 85.44118; 136/136 instructions; structural/exact (19, 93); first (2, ('addi', 'r3, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 const transform input behind full inline boundary | objdiff 78.338234; 130/136 instructions; structural/exact (47, 133); first (2, ('addi', 'r10, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 const public coefficient input with unit-guarded prototype | objdiff 85.44118; 136/136 instructions; structural/exact (19, 93); first (2, ('addi', 'r3, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 readonly source with first-row stores0 1 2 3 and shared rotation | objdiff 78.492645; 136/136 instructions; structural/exact (39, 93); first (2, ('addi', 'r3, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 read-only transform descriptor includes output pointer and stride | objdiff 85.588234; 136/136 instructions; structural/exact (19, 93); first (2, ('addi', 'r7, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 fresh origin unchanged137/frame0x120; first8 coefficientb r5 vsr10,31form/48operand differences, math operand d+b/rot+sum and load/store scheduling firstpass. Pointers7/8alreadytarget. Const source view then inline row boundary; no volatile/extentproof.
TMCJPEGDEC_IdctBlock4x4_Col | R7 const coefficient source pointer for signed IDCT passes | objdiff 83.89781; 137/137 instructions; structural/exact (31, 48); first (8, ('lwz', 'r5, 4(r7)'), ('lwz', 'r10, 4(r7)'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 const signed transform input behind full inline boundary | objdiff 79.9927; 139/137 instructions; structural/exact (35, 135); first (1, ('addi', 'r5, r3, 0x60'), ('li', 'r0, 2'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 readonly source and target d+b rotation+sum operand order | objdiff 83.86131; 137/137 instructions; structural/exact (31, 48); first (8, ('lwz', 'r5, 4(r7)'), ('lwz', 'r10, 4(r7)'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 odd coefficient recombination inside inline arithmetic boundary | objdiff 79.55474; 137/137 instructions; structural/exact (33, 81); first (2, ('addi', 'r8, r3, 0x60'), ('addi', 'r7, r3, 0x60'))
signcreate | R7 retain candidate readonly named pane table input reduces34to32operand differences221/221structural0,99.117645->99.162895. declsearch13builds nofurtherchange. Actual table remainsmutabledata withsameaddress andextent; view only const, dataowned100.
signcreate | R7 quick GATE PASS,99.162895vs99.117645,55/56 unchanged code6300/7184 data3468/3468;0regressions forbidden readability andtargetDOL. ctxdiff32operands. Constructor-vtable/table relocation load ordering also remains; lis/addi placeholders hide symbol ordering, so not all32differences are onlyregister choices.
SOGetInterfaceOpt | R7 success-scoped immutable command and response pointer bases | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R7 response immutable pointers scoped after selector stores | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R7 unsigned local selector with public API preserved | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R7 unsigned selector check in inline boundary | objdiff 94.94118; 124/119 instructions; structural/exact (9, 112); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
TMCJPEGDEC_IdctBlock4x4 | R7 readonly eight-coefficient row view for first pass | objdiff 85.661766; 136/136 instructions; structural/exact (19, 89); first (2, ('addi', 'r3, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 descending paired-row index derives both pass pointers | objdiff 74.94853; 131/136 instructions; structural/exact (42, 134); first (2, ('li', 'r7, 0x60'), ('addi', 'r8, r3, 0x60'))
IDCT R7 new structural hypothesis: target firstpass paired rows may be automatic unrolling of four single-row iterations, ratherthan hand-written pairedsource. Next test restores natural4-rowloop withsource/destination stride8; no pragmas.
TMCJPEGDEC_IdctBlock4x4 | R7 natural four-row loop lets compiler unroll paired rows | objdiff 78.213234; 130/136 instructions; structural/exact (36, 134); first (2, ('addi', 'r12, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
IDCT R7 natural4rowloop IS auto-unrolled2 as target, but savesr27..31 withstmw/lmw ratherthan4individualsave/restore, explaining exactly130vs136. Firstpass body40instructions matches targetcount. Scope evdiff separately from columnphase before moretuning.
TMCJPEGDEC_IdctBlock4x4 | R7 auto unrolled loop with row-local even difference | objdiff 78.213234; 130/136 instructions; structural/exact (36, 134); first (2, ('addi', 'r12, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 auto unrolled rows with all arithmetic temporaries scoped to row | objdiff 78.58088; 130/136 instructions; structural/exact (36, 131); first (3, ('stmw', 'r27, 0x10c(r1)'), ('stw', 'r31, 0x11c(r1)'))
TMCJPEGDEC_IdctBlock4x4 | R7 auto unrolled rows with const coefficient source | objdiff 78.213234; 130/136 instructions; structural/exact (36, 134); first (2, ('addi', 'r12, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 auto unrolled rows preserve b plus d subtree | objdiff 78.26471; 130/136 instructions; structural/exact (33, 134); first (2, ('addi', 'r12, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 auto unrolled rows recombine odd sum before rotation | objdiff 78.26471; 130/136 instructions; structural/exact (33, 134); first (2, ('addi', 'r12, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 auto unrolled rows compute even difference inside output expressions | objdiff 76.85294; 130/136 instructions; structural/exact (37, 134); first (2, ('stmw', 'r27, 0x10c(r1)'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 auto unrolled rows rotate before adding odd coefficient pair | objdiff 78.213234; 130/136 instructions; structural/exact (36, 134); first (2, ('addi', 'r12, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 natural four-row signed IDCT loop with shared temporaries | objdiff 99.48905; 137/137 instructions; structural/exact (0, 12); first (53, ('lwz', 'r9, 0x20(r6)'), ('lwz', 'r10, 0x20(r6)'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 natural signed rows with scoped coefficient and butterfly locals | objdiff 99.48905; 137/137 instructions; structural/exact (0, 12); first (53, ('lwz', 'r9, 0x20(r6)'), ('lwz', 'r10, 0x20(r6)'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 natural signed rows retain sum plus rotation expression | objdiff 99.34306; 137/137 instructions; structural/exact (0, 14); first (12, ('add', 'r3, r10, r12'), ('add', 'r3, r12, r10'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 natural signed rows declare immutable coefficient values in body | objdiff 97.44526; 137/137 instructions; structural/exact (0, 41); first (8, ('lwz', 'r30, 4(r7)'), ('lwz', 'r10, 4(r7)'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 natural signed IDCT with second-pass d plus b operand tree | objdiff 99.52555; 137/137 instructions; structural/exact (0, 12); first (53, ('lwz', 'r9, 0x20(r6)'), ('lwz', 'r10, 0x20(r6)'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 natural signed IDCT second-pass b c declaration lifetimes | objdiff 98.868614; 137/137 instructions; structural/exact (0, 28); first (8, ('lwz', 'r11, 4(r7)'), ('lwz', 'r10, 4(r7)'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 scoped column coefficients | objdiff 99.30657; 137/137 instructions; structural/exact (0, 13); first (53, ('lwz', 'r8, 0x20(r6)'), ('lwz', 'r10, 0x20(r6)'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 scoped column coefficients c before b | objdiff 99.30657; 137/137 instructions; structural/exact (0, 13); first (53, ('lwz', 'r8, 0x20(r6)'), ('lwz', 'r10, 0x20(r6)'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 scoped column butterfly terms | objdiff 99.52555; 137/137 instructions; structural/exact (0, 12); first (53, ('lwz', 'r9, 0x20(r6)'), ('lwz', 'r10, 0x20(r6)'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 scoped column butterfly terms reversed sums | objdiff 99.52555; 137/137 instructions; structural/exact (0, 12); first (53, ('lwz', 'r9, 0x20(r6)'), ('lwz', 'r10, 0x20(r6)'))
TMCJPEGDEC_IdctBlock4x4_Col | R7 EXACT: natural four-row loop auto-unrolls two rows with target load/store scheduling, first53 instructions exact; second-pass scoped coefficient/butterfly locals and d+b operand order reduce remaining12registerdiffs. declsearch28builds gives137/137 anddiffs0, objdiff100. Quick GATE PASS5/6code1260/1804 versus4/6code712; poolidentical, global0regressions forbidden readability, correctDOL. No data symbols or extents changed.
TMCJPEGDEC_IdctBlock4x4 | R7 fresh fetch origin still unchanged136/85.625; transfer proven natural signed-row odddiff/oddsum/even difference before rotation order, then tune unsigned column phase independently.
TMCJPEGDEC_IdctBlock4x4 | R7 natural unsigned rows with odd and even differences before rotation | objdiff 94.30147; 136/136 instructions; structural/exact (2, 86); first (2, ('addi', 'r12, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 natural unsigned rows with target d plus b addition subtree | objdiff 94.22794; 136/136 instructions; structural/exact (2, 86); first (2, ('addi', 'r12, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 natural unsigned rows use expression for odd difference | objdiff 94.30147; 136/136 instructions; structural/exact (2, 86); first (2, ('addi', 'r12, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 natural unsigned rows share scoped butterfly locals | objdiff 97.09559; 136/136 instructions; structural/exact (0, 51); first (50, ('rlwinm', 'r6, r5, 2, 0xe, 0x1d'), ('rlwinm', 'r3, r5, 2, 0xe, 0x1d'))
TMCJPEGDEC_IdctBlock4x4 | R7 scoped natural row arithmetic reproduces first50instructions exactly136/frame0x120. Remaining unsigned-column operands51; leading5scalar declsearch32builds reduces to49; no structural differences, now separate column lifetimes and pointer declarations.
TMCJPEGDEC_IdctBlock4x4 | R7 natural unsigned columns scoped butterfly coefficients | objdiff 96.13971; 136/136 instructions; structural/exact (0, 71); first (10, ('lwz', 'r31, 0xc(r8)'), ('lwz', 'r28, 0xc(r8)'))
TMCJPEGDEC_IdctBlock4x4 | R7 natural unsigned columns have distinct input pointer lifetime | objdiff 97.64706; 136/136 instructions; structural/exact (0, 45); first (53, ('addi', 'r6, r1, 0x14'), ('addi', 'r11, r1, 0x14'))
TMCJPEGDEC_IdctBlock4x4 | R7 natural unsigned columns distinct pointer and scoped math | objdiff 96.36029; 136/136 instructions; structural/exact (0, 67); first (10, ('lwz', 'r31, 0xc(r8)'), ('lwz', 'r28, 0xc(r8)'))
TMCJPEGDEC_IdctBlock4x4 | R7 natural unsigned columns reorder source and index declarations | objdiff 97.42647; 136/136 instructions; structural/exact (0, 49); first (50, ('rlwinm', 'r6, r5, 2, 0xe, 0x1d'), ('rlwinm', 'r3, r5, 2, 0xe, 0x1d'))
TMCJPEGDEC_IdctBlock4x4 | R7 all9column scalar declaration search146builds reduces45to42operand differences,136/136forms0. Firstpass remains exact; source,clamp temp,coefficients and index register choices in columnpass remain. Scoped column pointer distinguishes pass lifetimes.
TMCJPEGDEC_IdctBlock4x4 | R7 natural unsigned columns readonly temporary-buffer pointer | objdiff 98.01471; 136/136 instructions; structural/exact (0, 42); first (53, ('addi', 'r6, r1, 0x14'), ('addi', 'r11, r1, 0x14'))
TMCJPEGDEC_IdctBlock4x4 | R7 natural unsigned columns use target descending loop index | objdiff 98.01471; 136/136 instructions; structural/exact (0, 42); first (53, ('addi', 'r6, r1, 0x14'), ('addi', 'r11, r1, 0x14'))
TMCJPEGDEC_IdctBlock4x4 | R7 natural unsigned columns signed index preserves four iteration counter | objdiff 98.01471; 136/136 instructions; structural/exact (0, 42); first (53, ('addi', 'r6, r1, 0x14'), ('addi', 'r11, r1, 0x14'))
TMCJPEGDEC_IdctBlock4x4 | R7 natural unsigned columns output pointer declared outside row body | objdiff 96.39706; 136/136 instructions; structural/exact (2, 46); first (52, ('addi', 'r7, r1, 0x14'), ('subf', 'r31, r5, r3'))
TMCJPEGDEC_IdctBlock4x4 | R7 source pointer before coefficient declarations | objdiff 97.79412; 136/136 instructions; structural/exact (0, 46); first (50, ('rlwinm', 'r6, r5, 2, 0xe, 0x1d'), ('rlwinm', 'r3, r5, 2, 0xe, 0x1d'))
TMCJPEGDEC_IdctBlock4x4 | R7 source pointer after coefficient declarations | objdiff 97.79412; 136/136 instructions; structural/exact (0, 46); first (50, ('rlwinm', 'r6, r5, 2, 0xe, 0x1d'), ('rlwinm', 'r3, r5, 2, 0xe, 0x1d'))
TMCJPEGDEC_IdctBlock4x4 | R7 source pointer after buffer and loop variables | objdiff 97.79412; 136/136 instructions; structural/exact (0, 46); first (50, ('rlwinm', 'r6, r5, 2, 0xe, 0x1d'), ('rlwinm', 'r3, r5, 2, 0xe, 0x1d'))
TMCJPEGDEC_IdctBlock4x4 | R7 unsigned column transform isolated in readonly inline phase | objdiff 90.07353; 130/136 instructions; structural/exact (10, 132); first (3, ('stmw', 'r27, 0x10c(r1)'), ('stw', 'r31, 0x11c(r1)'))
TMCJPEGDEC_IdctBlock4x4 | R7 column phase block owns coefficient and math locals | objdiff 96.47059; 136/136 instructions; structural/exact (0, 67); first (10, ('lwz', 'r31, 0xc(r8)'), ('lwz', 'r28, 0xc(r8)'))
TMCJPEGDEC_IdctBlock4x4 | R7 column phase block owns only output address and coefficients | objdiff 97.79412; 136/136 instructions; structural/exact (0, 44); first (53, ('addi', 'r6, r1, 0x14'), ('addi', 'r11, r1, 0x14'))
TMCJPEGDEC_IdctBlock4x4 | R7 column phase block owns only rotation and sums | objdiff 97.42647; 136/136 instructions; structural/exact (0, 47); first (53, ('addi', 'r6, r1, 0x14'), ('addi', 'r11, r1, 0x14'))
TMCJPEGDEC_IdctBlock4x4 | R7 column phase declares index and pointer before assignment | objdiff 98.01471; 136/136 instructions; structural/exact (0, 42); first (53, ('addi', 'r6, r1, 0x14'), ('addi', 'r11, r1, 0x14'))
TMCJPEGDEC_IdctBlock4x4 | R7 column phase initializes index before source after separate declarations | objdiff 98.01471; 136/136 instructions; structural/exact (0, 42); first (53, ('addi', 'r6, r1, 0x14'), ('addi', 'r11, r1, 0x14'))
TMCJPEGDEC_IdctBlock4x4 | R7 reuse sp for temporary-buffer column input | objdiff 97.79412; 136/136 instructions; structural/exact (0, 46); first (50, ('rlwinm', 'r6, r5, 2, 0xe, 0x1d'), ('rlwinm', 'r3, r5, 2, 0xe, 0x1d'))
TMCJPEGDEC_IdctBlock4x4 | R7 reuse dp for temporary-buffer column input | objdiff 97.79412; 136/136 instructions; structural/exact (0, 46); first (50, ('rlwinm', 'r6, r5, 2, 0xe, 0x1d'), ('rlwinm', 'r3, r5, 2, 0xe, 0x1d'))
TMCJPEGDEC_IdctBlock4x4 | R7 column index shares u16 output coordinate type | objdiff 96.83088; 137/136 instructions; structural/exact (6, 51); first (53, ('addi', 'r6, r1, 0x14'), ('addi', 'r11, r1, 0x14'))
TMCJPEGDEC_IdctBlock4x4 | R7 column traversal expressed by source end pointer | objdiff 71.92647; 131/136 instructions; structural/exact (51, 134); first (2, ('addi', 'r7, r3, 0x60'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 readonly column butterfly helper with named result references | objdiff 87.94118; 130/136 instructions; structural/exact (12, 132); first (3, ('stmw', 'r27, 0x10c(r1)'), ('stw', 'r31, 0x11c(r1)'))
TMCJPEGDEC_IdctBlock4x4 | R7 mutable column butterfly helper input for retail alias assumptions | objdiff 87.94118; 130/136 instructions; structural/exact (12, 132); first (3, ('stmw', 'r27, 0x10c(r1)'), ('stw', 'r31, 0x11c(r1)'))
TMCJPEGDEC_IdctBlock4x4 | R7 readonly column butterfly helper with rotation output first | objdiff 87.94118; 130/136 instructions; structural/exact (12, 132); first (3, ('stmw', 'r27, 0x10c(r1)'), ('stw', 'r31, 0x11c(r1)'))
TMCJPEGDEC_IdctBlock4x4 | R7 full natural unsigned transform with readonly inline input boundary | objdiff 87.463234; 130/136 instructions; structural/exact (11, 134); first (2, ('stmw', 'r27, 0x10c(r1)'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 full natural unsigned transform with mutable inline input boundary | objdiff 87.463234; 130/136 instructions; structural/exact (11, 134); first (2, ('stmw', 'r27, 0x10c(r1)'), ('addi', 'r8, r3, 0x60'))
TMCJPEGDEC_IdctBlock4x4 | R7 retain natural four-row unsigned pass:85.625->98.01471,136/136 identical instruction forms, first50instructions exact. Remaining42operands are cyclic r6-r11 allocation in column input/output/clamp temporaries; saved coefficients, pitch/index and arithmetic order now exact. Tested const input, scoped phase/math helpers, natural descending loop, source lifetime/assignment/decl permutations; helpers add fifth saved register and130vs136, rejected. Quick GATE PASS with signed4x4still100,0regressions forbidden/readability andcorrectDOL. Both target.extents exact, novolatile proof ordatachanges.
signcreate | R7 fresh fetch origin remains99.117645, our acceptedreadonlytable99.162895. Inspect constructor constant-hoist relocation order explicitly; next isolate metadata lookup and immutable localpointer forms.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R7 immutable pane metadata pointer instead of readonly reference | objdiff 99.162895; 221/221 instructions; structural/exact (0, 32); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R7 readonly pane metadata lookup inline boundary | objdiff 98.77828; 221/221 instructions; structural/exact (0, 44); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R7 immutable allocated pane buffer inputs to constructors | objdiff 98.30317; 221/221 instructions; structural/exact (0, 54); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R7 immutable readonly pane table base declaration | objdiff 99.162895; 221/221 instructions; structural/exact (0, 32); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
R7 pre-final completeness audit | SOGetInterfaceOpt | 7 successfully compiled distinct source-attempt log entries; remaining function re-listed for full gate.
R7 pre-final completeness audit | PFENT_ITER_FindCluster | 6 successfully compiled distinct source-attempt log entries; remaining function re-listed for full gate.
R7 pre-final completeness audit | inputChar__Q39textinput8tistring9DecolatedFw | 3 successfully compiled distinct source-attempt log entries; remaining function re-listed for full gate.
R7 pre-final completeness audit | create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | 8 successfully compiled distinct source-attempt log entries; remaining function re-listed for full gate.
R7 pre-final completeness audit | TMCJPEGDEC_IdctBlock4x4 | 45 successfully compiled distinct source-attempt log entries; remaining function re-listed for full gate.
R7 data audit | all six owned target data objects paired at100 percent; SOOption/IDCT own no data, pf_volume210976, entry_iterator24, tiString288, tiSignWindow3468. No rename, extent, address or section-total changes required this round. Weak deduplicated extras untouched. Prior extent audit proves no overlapping open function sizes.

# R7 final clean full gate over all six owned units (non --quick)
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
[libs/RVL_SDK/src/fa/pf_volume] objdiff: code 17992/17992 data 210976/210976 functions 37/37 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/pf_volume] instruction-exact functions: 37/37
[libs/RVL_SDK/src/fa/pf_volume]   section .bss size 210944 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .data size 16 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .sdata size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .sdata2 size 8 match 100.0
[libs/RVL_SDK/src/fa/pf_volume]   section .text size 17992 match 100.0
[libs/RVL_SDK/src/fa/pf_volume] baseline: code 16988/17992 data 210976 functions 35 fuzzy 99.9333
[libs/RVL_SDK/src/fa/pf_entry_iterator] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_entry_iterator] objdiff: code 6932/7880 data 24/24 functions 15/16 fuzzy 99.9772 linked code 0
[libs/RVL_SDK/src/fa/pf_entry_iterator] instruction-exact functions: 15/16
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .sdata size 24 match 100.0
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .text size 7880 match 99.97716
[libs/RVL_SDK/src/fa/pf_entry_iterator]   below 100: PFENT_ITER_FindCluster 99.81013
[libs/RVL_SDK/src/fa/pf_entry_iterator] baseline: code 6932/7880 data 24 functions 15 fuzzy 99.9772
[src/keyboard/tiString] pool: IDENTICAL
[src/keyboard/tiString] objdiff: code 4632/5176 data 288/288 functions 41/42 fuzzy 98.9629 linked code 0
[src/keyboard/tiString] instruction-exact functions: 41/42
[src/keyboard/tiString]   section .data size 288 match 100.0
[src/keyboard/tiString]   section .text size 5176 match 98.962906
[src/keyboard/tiString]   below 100: inputChar__Q39textinput8tistring9DecolatedFw 90.132355
[src/keyboard/tiString] baseline: code 4632/5176 data 288 functions 41 fuzzy 98.9629
[src/keyboard/tiSignWindow] pool: IDENTICAL
[src/keyboard/tiSignWindow] objdiff: code 6300/7184 data 3468/3468 functions 55/56 fuzzy 99.8970 linked code 0
[src/keyboard/tiSignWindow] instruction-exact functions: 55/56
[src/keyboard/tiSignWindow]   section .ctors size 4 match 100.0
[src/keyboard/tiSignWindow]   section .data size 2672 match 100.0
[src/keyboard/tiSignWindow]   section .rodata size 784 match 100.0
[src/keyboard/tiSignWindow]   section .sdata size 8 match 100.0
[src/keyboard/tiSignWindow]   section .text size 7184 match 99.896996
[src/keyboard/tiSignWindow]   below 100: create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.162895
[src/keyboard/tiSignWindow] baseline: code 6300/7184 data 3468 functions 55 fuzzy 99.8914
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] objdiff: code 1260/1804 data None/None functions 5/6 fuzzy 99.4013 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] instruction-exact functions: 5/6
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var]   section .text size 1804 match 99.40133
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var]   below 100: TMCJPEGDEC_IdctBlock4x4 98.01471
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] baseline: code 712/1804 data None functions 4 fuzzy 90.7738
regressions vs baseline: 0
global matched_code_percent: 89.19062 -> 89.24243
global fuzzy_match_percent: 99.52355 -> 99.52917
global complete_code_percent: 66.23504 -> 66.23504
global matched_data_percent: 99.36508 -> 99.36508
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
libs/RevoEX/src/so/SOOption | exact 3/4 -> 3/4 | code bytes 816 -> 816/1292 | data bytes 0 -> 0/0
R7 remaining | SOGetInterfaceOpt | 99.78992% | 119/119 identical instruction forms; five callee-saved selector/level register operands differ, first instruction5 mr r25,r4 vsr26. | 7 distinct successful source trials this round; no untried functions.
libs/RVL_SDK/src/fa/pf_volume | exact 35/37 -> 37/37 | code bytes 16988 -> 17992/17992 | data bytes 210976 -> 210976/210976
libs/RVL_SDK/src/fa/pf_entry_iterator | exact 15/16 -> 15/16 | code bytes 6932 -> 6932/7880 | data bytes 24 -> 24/24
R7 remaining | PFENT_ITER_FindCluster | 99.81013% | 237/237 identical forms; eight sector-mask and entries-per-sector register operands differ, first shared1 value r7 vsr8. Volatile iterator-index trial adds three reloads, rejected. | 6 distinct successful source trials this round; no untried functions.
src/keyboard/tiString | exact 41/42 -> 41/42 | code bytes 4632 -> 4632/5176 | data bytes 288 -> 288/288
R7 remaining | inputChar__Q39textinput8tistring9DecolatedFw | 90.132355% | 125/136; Hangul-mode append path optimized to constant index/count; target dynamic append, newline comparison and final count mask remain. No adjacent-stack reload or extent proof supports volatility or resizing. | 3 distinct successful source trials this round; no untried functions.
src/keyboard/tiSignWindow | exact 55/56 -> 55/56 | code bytes 6300 -> 6300/7184 | data bytes 3468 -> 3468/3468
R7 remaining | create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | 99.162895% | 221/221 identical forms;32 operands remain, including constructor/table relocation hoist order and loop/register allocation. First lis AnmPane r26 vsr25. | 8 distinct successful source trials this round; no untried functions.
libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var | exact 4/6 -> 5/6 | code bytes 712 -> 1260/1804 | data bytes 0 -> 0/0
R7 remaining | TMCJPEGDEC_IdctBlock4x4 | 98.01471% | 136/136 identical forms;42 operands, first column pointer r6 vsr11 at instruction53. First50 instructions exact; remaining unsigned column/clamp registers cycle r6-r11. | 45 distinct successful source trials this round; no untried functions.
R7 final files: libs/RVL_SDK/src/fa/pf_volume.c; src/keyboard/tiSignWindow.cpp; libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var.c; tools/decomp-assist/fz3.attempts.md. Source commits451eaff8,becfba47,5058e494,4cd94ca2,8a89a5ba. Three new exact functions,1552 newly matched code bytes; all data unchanged100%, all six poolsidentical, correctDOL,0globalregressions/forbidden/readability. No remaining proof uncertainty for accepted changes; original Hangul helper boundary and remaining compiler allocation are unresolved as logged. No source/header/config changes after clean full gate; final commit is log only.
R8 initial pool libs/RevoEX/src/so/SOOption | POOL IDENTICAL up to 0 (mine=0 base=0)
R8 initial pool libs/RVL_SDK/src/fa/pf_entry_iterator | POOL IDENTICAL up to 0 (mine=0 base=0)
R8 initial pool src/keyboard/tiString | POOL IDENTICAL up to 0 (mine=0 base=0)
R8 initial pool src/keyboard/tiSignWindow | POOL IDENTICAL up to 30 (mine=30 base=30)
R8 initial pool libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var | POOL IDENTICAL up to 0 (mine=0 base=0)

# Round8 XHIGH, fresh branch HEADa61a7cf1. Each trial logs first differing instruction and source construct, with original always restored until accepted by gate.
SOGetInterfaceOpt | R8 origin fetched; source equal origin except README;119/119,frame0x30. First5 mr r25,r4 vtarget26; only five level/option operands. rm/temp slots0xc/8, branchforms, calls,pointersetup andload/store scheduling identical. No symbol overlap (0x814B476c+0x1dc=SOSetInterfaceOpt0x814B4948), no adjacent-stack reload proof; const OptionLength/global qualifiers already ineffective last round. Test selector inline boundary and real response block types before declaration search.
SOGetInterfaceOpt | R8 selector pair initialized inside command inline helper | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R8 selector helper receives operation before protocol level | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R8 aligned length reply remains a typed interface response block | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R8 allocated interface request pointer scoped immutable after allocation | BUILD FAIL OOption.c -o build/43U/src/libs/RevoEX/src/so && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/so/SOOption.d build/43U/src/libs/RevoEX/src/so/SOOption.d ### mwcceppc.exe Compiler: #    File: libs\RevoEX\src\so\SOOption.c # -------------------------------------- #     110:             InterfaceOption* const request=SOiAlloc(12,size);  #   Error:             ^^^^^^^^^^^^^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
SOGetInterfaceOpt | R8 immutable interface allocation pointer in its own successful scope | objdiff 98.61345; 119/119 instructions; structural/exact (0, 33); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R8 readonly interface reply byte view for memcpy input | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R8 five distinct compiled structural/type/helper trials; selectors/read-only byte view preserve5operanddiffs, scopedconstallocation worsens33. Leadingdeclsearch65builds no improvement. Baseline restored119/119,99.78992, no data.
PFENT_ITER_FindCluster | R8 fetch source equalorigin,237/237frame0xa0; first39li1r7 vsr8,8registeronlydiffs constant/entry-count swap. Noextentoverlap0x815d3414+0x3b4=Retreat0x815d37c8. Targetadjacentstore/reloaditer.index0x20 alreadypreserved baseline, last roundfieldvolatileadded3loads, rejected. Loop/helper/call/scheduling otherwiseidentical; test entrycount derived from real initialized firstclusterfield.
PFENT_ITER_FindCluster | R8 entry count derives from initialized iterator first cluster | objdiff 99.81013; 237/237 instructions; structural/exact (0, 8); first (39, ('li', 'r7, 1'), ('li', 'r8, 1'))
PFENT_ITER_FindCluster | R8 entry count computes byte geometry using preceding power of two | objdiff 97.95358; 239/237 instructions; structural/exact (5, 206); first (18, ('b', '852'), ('b', '844'))
PFENT_ITER_FindCluster | R8 readonly initialized iterator supplies first sector entry count | objdiff 99.81013; 237/237 instructions; structural/exact (0, 8); first (39, ('li', 'r7, 1'), ('li', 'r8, 1'))
PFENT_ITER_FindCluster | R8 FAT hint first-cluster sentinel initialized in inline boundary | objdiff 99.81013; 237/237 instructions; structural/exact (0, 8); first (39, ('li', 'r7, 1'), ('li', 'r8, 1'))
PFENT_ITER_FindCluster | R8 four compiled source attempts, initialized-field and hint-inline boundaries preserve8diffs; alternate geometryshift adds2instructions and rejected. Leadingdeclsearch36builds leaves8, baseline restored99.81013. Data24bytes remains100; no header/data edits.
inputChar__Q39textinput8tistring9DecolatedFw | R8 fresh fetch sourceequalorigin,125/136frame0x30. Firstrealconstruct65Hangulmode lacksinlinedstream index/count lifetime, initialNUL andunusednewlinecompare;targetcharregister4, counter6 starts0 andcount29mask. Noadjacentstackreloadproof orsizeoverlap0x81432ce4+0x220=confirmKana0x81432f04. Test shared translatorcounter/output-reference boundaries; no empty newline stubs orunsupportedvolatile.
inputChar__Q39textinput8tistring9DecolatedFw | R8 shared translation count initialized before mode dispatch and appended in Hangul | objdiff 90.132355; 125/136 instructions; structural/exact (18, 73); first (10, ('beq', '428'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R8 wide translation count shared across mode dispatch | objdiff 90.132355; 125/136 instructions; structural/exact (18, 73); first (10, ('beq', '428'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R8 bounded input array reference and readonly character reference | objdiff 90.132355; 125/136 instructions; structural/exact (18, 73); first (10, ('beq', '428'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R8 append character through advancing pointer and derive UTF16 count | objdiff 89.92647; 130/136 instructions; structural/exact (18, 87); first (10, ('beq', '448'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R8 converter handles newline literal then ordinary character append | objdiff 93.22794; 138/136 instructions; structural/exact (17, 75); first (10, ('beq', '480'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R8 converter newline append through bounded buffer and const character | objdiff 93.22794; 138/136 instructions; structural/exact (17, 75); first (10, ('beq', '480'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R8 direct newline normalization expresses target retained comparison | objdiff 89.91912; 130/136 instructions; structural/exact (16, 73); first (10, ('beq', '448'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R8 generic conversion append resets buffer length on newline | objdiff 91.06618; 135/136 instructions; structural/exact (17, 62); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R8 conversion append carries mutable stream length through newline reset | objdiff 93.60294; 135/136 instructions; structural/exact (15, 61); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R8 conversion newline clears previous text and resets stream length | objdiff 91.72794; 136/136 instructions; structural/exact (15, 60); first (63, ('b', '88'), ('b', '80'))
inputChar__Q39textinput8tistring9DecolatedFw | R8 conversion buffer owns newline reset append and readonly length | objdiff 92.52941; 135/136 instructions; structural/exact (16, 61); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R8 conversion buffer keeps UTF16 sized length field | objdiff 91.64706; 135/136 instructions; structural/exact (17, 62); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R8 conversion buffer newline clear is a real reusable stream method | objdiff 93.05147; 136/136 instructions; structural/exact (17, 60); first (63, ('b', '88'), ('b', '80'))
inputChar__Q39textinput8tistring9DecolatedFw | R8 thirteen distinct compiled trials, including natural pointer/count references and functional newline append/reset stream boundaries. Best93.60294/135vs136 stilladds live newline branch absenttarget and lacks targetpointer/zero ordering. No candidate retained: original converter semantics/boundary unresolved; no unused newline arg, empty stub, arbitrary volatile orsymbolresize introduced. Baseline125/136,90.132355 restored.
signcreate | R8 originfetched equalcurrent99.162895,221/frame0x50. First48AnmPanevtablelisr26vs25; relocationorder targetAnmPane,Button,Scroll,table,All versusoursAnmPane,table,Button,Scroll,All. Remaining32operands includeanimationCount22vs31 andanimatedentry25vs22. Metadata,constructorallocation/calls andbranchforms exact; noextentoverlap oradjacentstackvolatileproof. Test real iterator/animation entry lifetimes before register permutations.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 immutable animation bound and force name scoped to pane setup | objdiff 98.12217; 221/221 instructions; structural/exact (0, 60); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 animation traversal explicit wide induction and UTF16 index view | objdiff 99.162895; 221/221 instructions; structural/exact (0, 32); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 pane metadata index uses proven bounded unsigned loop counter | objdiff 95.701355; 220/221 instructions; structural/exact (5, 184); first (5, ('li', 'r19, 0'), ('li', 'r14, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 readonly animation entry reference lives across resource creation | objdiff 99.61539; 221/221 instructions; structural/exact (0, 13); first (49, ('lis', 'r24, 0'), ('lis', 'r27, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 animation bound and index declared together in natural for loop | objdiff 98.19005; 221/221 instructions; structural/exact (0, 58); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 readonly animation reference with direct pane table lookup | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 readonly animation reference with count declared after pane creation | objdiff 98.64253; 221/221 instructions; structural/exact (0, 53); first (49, ('lis', 'r24, 0'), ('lis', 'r27, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 readonly animation slot pointer declared before pane loop and late bound | objdiff 98.64253; 221/221 instructions; structural/exact (0, 53); first (49, ('lis', 'r24, 0'), ('lis', 'r27, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 direct pane lookup with early declared readonly animation slot pointer | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 readonly pane name array view across constructor branches | objdiff 96.8914; 222/221 instructions; structural/exact (5, 160); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 readonly pane table view local to each logical pane iteration | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
signcreate | R8 retain readonly animation-slot reference instead of repeated table indexing, anddirect pane table lookup. Constreference is to pointer object, so actual animation pointer reloads across calls are preserved.99.162895->99.72851,221/221 instructionforms0,32->10 operands. Remaining4All/table constant-load relocation order and6animation-count22/entry31 swap. Leading3declsearch6builds nofurthergain. QuickGATE PASS55/56,data3468/3468,poolidentical,0globalregressions/forbidden/readability andtargetDOL.
TMCJPEGDEC_IdctBlock4x4 | R8 fresh fetch originequalscurrent98.01471,136/136frame0x120. First53columnpointerr6vs11 with42cyclicr6-r11operands, all instructionforms andfirst50exact. Firstpass provenautomaticunroll4rows. Newhypothesis secondpass pointerr11 is compiler-generated strength reduction from indexed tmp[idx], so its virtual lifetime begins after output/clamp locals instead of explicit column pointerdecl. Noextentoverlap0x814ef490+0x220=2x2start814ef6b0; noimmediate stackreloadproof,data0.
TMCJPEGDEC_IdctBlock4x4 | R8 indexed temporary buffer lets compiler reduce column input pointer | objdiff 100.0; 136/136 instructions; structural/exact (0, 0); first None
EXACT CANDIDATE /tmp/fz3-r8-candidates/TMCJPEGDEC_IdctBlock4x4_indexed_temporary_buffer_lets_compiler_reduce_column_input_pointer.txt
TMCJPEGDEC_IdctBlock4x4 | R8 natural descending signed column index and buffer offsets | objdiff 100.0; 136/136 instructions; structural/exact (0, 0); first None
EXACT CANDIDATE /tmp/fz3-r8-candidates/TMCJPEGDEC_IdctBlock4x4_natural_descending_signed_column_index_and_buffer_offsets.txt
TMCJPEGDEC_IdctBlock4x4 | R8 ascending iteration derives descending temporary and output index | objdiff 90.117645; 138/136 instructions; structural/exact (14, 107); first (10, ('lwz', 'r29, 0xc(r8)'), ('lwz', 'r28, 0xc(r8)'))
TMCJPEGDEC_IdctBlock4x4 | R8 EXACT on firstindexed-column attempt:98.01471->100.0,136/136diffs0; replace explicit columnpointer withtmp[idx],tmp[idx+8/16/24]. Compiler generates pointerlater atvirtualregisterorderneeded forr11, resolving all42operanddiffs. Naturaldescendingi variant also100, ascending3-i changes138 and rejected. QuickGATE PASSunit6/6code1804/1804vs5/6code1260/1804,data0,poolidentical,0globalregressions forbidden readability,correctDOL. This is automatic strength reduction, no volatile, helper, symbol orconfigchange.
signcreate | R8 freshfetch remote stillwithoutnewanimationreference; target221first51All/tableloadorder, six animation bound/slot operands remain; try index declaration before bound and natural readonly animation array view, following proven IDCT auto-generated address allocation.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 animation counter declared before immutable loop bound | objdiff 98.64253; 221/221 instructions; structural/exact (0, 54); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 pane animation force metadata and bound scoped after index declaration | objdiff 98.57466; 221/221 instructions; structural/exact (0, 56); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 readonly animation array input view uses compiler generated element address | objdiff 96.49321; 221/221 instructions; structural/exact (10, 62); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 direct pane field indexing lets compiler form shared row address | objdiff 94.81901; 224/221 instructions; structural/exact (15, 174); first (48, ('lis', 'r24, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 direct pane fields and immutable late animation count | objdiff 94.253395; 224/221 instructions; structural/exact (15, 172); first (48, ('lis', 'r24, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 readonly pane row lookup owns masked index alias boundary | objdiff 99.38914; 221/221 instructions; structural/exact (0, 21); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 readonly animation slot reference begins after resource name lookup | objdiff 96.42534; 222/221 instructions; structural/exact (4, 135); first (7, ('mr', 'r23, r3'), ('mr', 'r15, r3'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 readonly animation slot reference begins after transform creation | objdiff 98.61991; 222/221 instructions; structural/exact (4, 69); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R8 resource and transform declarations precede readonly animation slot view | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
signcreate | R8 extra natural-index, animation array alias, declaration/lifetime and direct-field tests have no further gain beyondaccepted99.72851. Direct-field rewrite adds3instructions, late-bound reference adds1 orextra saved-register uses; readonly row helper worsens21operands. All rejected variants restored. Remaining exact-shape10operand diffs are4All/table relocation-load ordering and6bound/animation-slot22/31 register swap; no unsupporteddata fixes.
R8 pre-final remaining-attempt audit | SOGetInterfaceOpt | 5 distinct compiled scored attempts this round; no untried functions.
R8 pre-final remaining-attempt audit | PFENT_ITER_FindCluster | 4 distinct compiled scored attempts this round; no untried functions.
R8 pre-final remaining-attempt audit | inputChar__Q39textinput8tistring9DecolatedFw | 13 distinct compiled scored attempts this round; no untried functions.
R8 pre-final remaining-attempt audit | create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | 20 distinct compiled scored attempts this round; no untried functions.
R8 data ownership audit | owned .data/.rodata/.sdata/.ctors target symbols all100: entry_iterator24 bytes,tiString288,tiSignWindow3468;SOOption/IDCT noowned data. All5poolsidentical frominitial pool_diff; no symbolrename,extent,address,section-total orsharedheaderchange. Relocation gaps fromremainingfunctions remain codework. Clean full all-unit gate follows.

# R8 final clean full gate over all five owned units (non --quick)
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/so/SOOption] pool: IDENTICAL
[libs/RevoEX/src/so/SOOption] objdiff: code 816/1292 data None/None functions 3/4 fuzzy 99.9226 linked code 0
[libs/RevoEX/src/so/SOOption] instruction-exact functions: 3/4
[libs/RevoEX/src/so/SOOption]   section .text size 1292 match 99.9226
[libs/RevoEX/src/so/SOOption]   below 100: SOGetInterfaceOpt 99.78992
[libs/RevoEX/src/so/SOOption] baseline: code 816/1292 data None functions 3 fuzzy 99.9226
[libs/RVL_SDK/src/fa/pf_entry_iterator] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_entry_iterator] objdiff: code 6932/7880 data 24/24 functions 15/16 fuzzy 99.9772 linked code 0
[libs/RVL_SDK/src/fa/pf_entry_iterator] instruction-exact functions: 15/16
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .sdata size 24 match 100.0
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .text size 7880 match 99.97716
[libs/RVL_SDK/src/fa/pf_entry_iterator]   below 100: PFENT_ITER_FindCluster 99.81013
[libs/RVL_SDK/src/fa/pf_entry_iterator] baseline: code 6932/7880 data 24 functions 15 fuzzy 99.9772
[src/keyboard/tiString] pool: IDENTICAL
[src/keyboard/tiString] objdiff: code 4632/5176 data 288/288 functions 41/42 fuzzy 98.9629 linked code 0
[src/keyboard/tiString] instruction-exact functions: 41/42
[src/keyboard/tiString]   section .data size 288 match 100.0
[src/keyboard/tiString]   section .text size 5176 match 98.962906
[src/keyboard/tiString]   below 100: inputChar__Q39textinput8tistring9DecolatedFw 90.132355
[src/keyboard/tiString] baseline: code 4632/5176 data 288 functions 41 fuzzy 98.9629
[src/keyboard/tiSignWindow] pool: IDENTICAL
[src/keyboard/tiSignWindow] objdiff: code 6300/7184 data 3468/3468 functions 55/56 fuzzy 99.9666 linked code 0
[src/keyboard/tiSignWindow] instruction-exact functions: 55/56
[src/keyboard/tiSignWindow]   section .ctors size 4 match 100.0
[src/keyboard/tiSignWindow]   section .data size 2672 match 100.0
[src/keyboard/tiSignWindow]   section .rodata size 784 match 100.0
[src/keyboard/tiSignWindow]   section .sdata size 8 match 100.0
[src/keyboard/tiSignWindow]   section .text size 7184 match 99.96659
[src/keyboard/tiSignWindow]   below 100: create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.72851
[src/keyboard/tiSignWindow] baseline: code 6300/7184 data 3468 functions 55 fuzzy 99.8970
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] objdiff: code 1804/1804 data None/None functions 6/6 fuzzy 100.0000 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] instruction-exact functions: 6/6
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var]   section .text size 1804 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var] baseline: code 1260/1804 data None functions 5 fuzzy 99.4013
regressions vs baseline: 0
global matched_code_percent: 89.86156 -> 89.87973
global fuzzy_match_percent: 99.53919 -> 99.53971
global complete_code_percent: 67.39544 -> 67.39544
global matched_data_percent: 99.36508 -> 99.36508
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
libs/RevoEX/src/so/SOOption | exact 3/4 -> 3/4 | code bytes 816 -> 816/1292 | data bytes 0 -> 0/0
R8 remaining | SOGetInterfaceOpt | 99.78992% | 119/119, frame0x30, five register operands remain: level25vs26 andoption28vs25; first5mr r25,r4 vsr26. rm/temp slots, branches, helper/load order exact. | 5 distinct compiled source attempts this round.
libs/RVL_SDK/src/fa/pf_entry_iterator | exact 15/16 -> 15/16 | code bytes 6932 -> 6932/7880 | data bytes 24 -> 24/24
R8 remaining | PFENT_ITER_FindCluster | 99.81013% | 237/237, frame0xa0, eight sharedconstant1 andentries-per-sector register operands remain; first39li r7,1 vsr8. Definitionvolatile wouldadd3loads andwasrejected, no extentoverlap. | 4 distinct compiled source attempts this round.
src/keyboard/tiString | exact 41/42 -> 41/42 | code bytes 4632 -> 4632/5176 | data bytes 288 -> 288/288
R8 remaining | inputChar__Q39textinput8tistring9DecolatedFw | 90.132355% | 125/136, frame0x30, missing original Hangul converter/index/count boundary andretainedunusednewlinecmp; allnewfunctionalbuilder candidates introduce extra livebranch ortemporaloperation ordering, rejected. | 13 distinct compiled source attempts this round.
src/keyboard/tiSignWindow | exact 55/56 -> 55/56 | code bytes 6300 -> 6300/7184 | data bytes 3468 -> 3468/3468
R8 remaining | create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | 99.72851% | 221/221, frame0x50,10operand differences: All-vtable/table address-load relocation order4 andanimation-count22vs31/slot31vs22 registerswap6. First51LISAll30vstable24; allotherconstructors, pointerread/call/order exact. | 20 distinct compiled source attempts this round.
libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var | exact 5/6 -> 6/6 | code bytes 1260 -> 1804/1804 | data bytes 0 -> 0/0
R8 final files: src/keyboard/tiSignWindow.cpp; libs/RVLMiddleware/TMC_JPEG/src/reschange/idct_resolution_change_var.c; tools/decomp-assist/fz3.attempts.md. Source commits8fbf59f0,1988244e. One new exact function and544matchedcodebytes, IDCTunit6/6code1804/1804data0. Signcreate99.162895->99.72851genuinefuzzyimprovement, exactcountunchanged. 45distinctcompiledsource trials and107declaration evaluations followingstructuraldiagnostics. Allfivepoolsidentical,data100, correctDOL,0globalregressions/forbidden/readability. No sourcechangesafterfullclean gate; finalcommit logonly. Uncertain: original Hangul helper/newline-processing structure andremaining SO/iterator/register constant-hoist choices; allacceptedbytes/state provedbygate. No untried openfunctions, no symbol/data/header/config changes, no Matching status switches orlinking claims.

# R9 XHIGH continued, fresh origin/main branch
Initial HEAD 76d72f06ce72601ba50236376319984c3e70f2af; origin adcd8ca586dc4ad15c62df304e560a7c974f1c12. Four owned units only; IDCT/pf_volume/eZiText excluded.
libs/RevoEX/src/so/SOOption | initial pool | POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RevoEX/src/so/SOOption | initial pool | POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RVL_SDK/src/fa/pf_entry_iterator | initial pool | POOL IDENTICAL up to 0 (mine=0 base=0)
src/keyboard/tiString | initial pool | POOL IDENTICAL up to 0 (mine=0 base=0)
src/keyboard/tiSignWindow | initial pool | POOL IDENTICAL up to 30 (mine=30 base=30)
SOGetInterfaceOpt | R9 fetch origin/main adcd8ca5 source equal. First5 level25 vs26, then option28 vs25;119/119 frame0x30, stackslots0xc/8, branch shape and pointer arithmetic/inline OptionLength boundary all exact. No stack-store/reload volatility proof or extent overlap; all owned data empty. New scalar-reference/response-helper and local lifetime experiments before register-only search.
SOGetInterfaceOpt | R9 unsigned allocation size and response length as byte extents | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 level and option scalar parameters immutable at definition | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 scoped selector copies taken after preparation and before validation | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 readonly scalar input references in selector helper | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 readonly option selector reference alone in command helper | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 readonly protocol level reference alone in command helper | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 typed reply buffer inline accessor boundary | objdiff 98.94958; 119/119 instructions; structural/exact (0, 24); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 typed returned length inline accessor boundary | objdiff 99.07563; 119/119 instructions; structural/exact (0, 22); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 returned length and reply locals scoped to successful allocation | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 command and reply descriptors scoped to successful allocation | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 command helper gets input selectors through aggregate const view | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 vector base and byte lengths assigned through typed descriptor helper | objdiff 96.193275; 119/119 instructions; structural/exact (6, 25); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 successful request payload pointers accessed by actual struct fields | objdiff 97.5042; 119/119 instructions; structural/exact (5, 10); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
PFENT_ITER_FindCluster | R9 fresh fetch 68c4c9ae, sourceequal. First39 li r7,1 vstargetr8;237/237/frame0xa0, eight constant1/entries-per-sector operands. All branches/local offsets/load/store/inline LoadEntry identical. Immediate iter.index reload alreadypresent, prior volatile adds3 loads; no new volatile. Extent endsatRetreat, data24/24. Test natural left-shift entry index and typed count initialization before declsearch.
PFENT_ITER_FindCluster | R9 file entry index computed with shift rather than sector multiplication | objdiff 98.945145; 237/237 instructions; structural/exact (2, 9); first (39, ('li', 'r7, 1'), ('li', 'r8, 1'))
PFENT_ITER_FindCluster | R9 entry mask helper derives count and mask from readonly geometry | objdiff 98.48101; 237/237 instructions; structural/exact (2, 26); first (2, ('stw', 'r0, 0xa4(r1)'), ('li', 'r6, 0'))
PFENT_ITER_FindCluster | R9 entry count helper keeps shift operand unsigned | objdiff 99.81013; 237/237 instructions; structural/exact (0, 8); first (39, ('li', 'r7, 1'), ('li', 'r8, 1'))
PFENT_ITER_FindCluster | R9 local count and first-cluster sentinel grouped as geometry values | BUILD FAIL -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/fa/pf_entry_iterator.c -o build/43U/src/libs/RVL_SDK/src/fa && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/fa/pf_entry_iterator.d build/43U/src/libs/RVL_SDK/src/fa/pf_entry_iterator.d ### mwcceppc.exe Compiler: # File: libs\RVL_SDK\src\fa\pf_entry_iterator.c # ------------------------------------------------ # 513: iter.log2_geometry.entries_per_sector = p_ent->p_vol->bpb.log2_bytes_per_sector - 5; # Error: ^ # (10393) 'log2_geometry' is not a member of class 'struct PFITER_ENT_ITER' # Too many errors printed, aborting program User break, cancelled... ninja: build stopped: subcommand failed.
PFENT_ITER_FindCluster | R9 shift count temporary uses natural byte geometry before iterator storage | objdiff 98.48101; 237/237 instructions; structural/exact (2, 26); first (2, ('stw', 'r0, 0xa4(r1)'), ('li', 'r6, 0'))
PFENT_ITER_FindCluster | R9 offset mask initialized before persistent entries-per-sector value | objdiff 100.0; 237/237 instructions; structural/exact (0, 0); first None
create | R9 fresh origin c7896c38 sourceequal.221/221/frame0x50. First51 LIS Allvtable30vstable24; four relocation-address load-order diffs, six animation count22vs31 and slot31vs22 register operands. All calls/constructors/pane switch/loop forms otherwiseexact; readonly animation-slotreference gain preserved. No adjacentstackreload/extentoverlap, owneddata3468/3468. Test early type input, const table fields and helper/scopes before declsearch.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 pane type read before metadata row address | objdiff 99.38914; 221/221 instructions; structural/exact (0, 21); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 switch type input directly indexes table | objdiff 99.38914; 221/221 instructions; structural/exact (0, 21); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 metadata row constructed before empty pane result | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 constructor switch source order 2,0,1 | objdiff 99.63801; 221/221 instructions; structural/exact (2, 14); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
PFENT_ITER_FindCluster | R9 breakthrough: initialize offset_mask directly from shifted geometry before declaring the persistent entries_per_sector value. Compiler CSE retains identical 237-instruction scheduling but chooses shared1=r8 and shiftedentrycount=r7, resolving all eight operands. Natural dependency/statement order lever, no header/type/volatile or data change. New source saved for gate.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 constructor switch source order 1,2,0 | objdiff 99.24435; 222/221 instructions; structural/exact (8, 158); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
SOGetInterfaceOpt | R9 thirteen compiled new source constructs; leading declsearch: declaration block: |       s32 rm; |       int temporary; |       int size; |       int result; |       InterfaceOption* request; |       InterfaceCommand* command; |       int* returnedLength; |       u8* reply; | start (0, 5) | best (0, 5) after 70 builds; source restored; best order was: |     s32 rm; |     int temporary; |     int size; |     int result; |     InterfaceOption* request; |     InterfaceCommand* command; |     int* returnedLength; |     u8* reply; | . No improvement; baseline source restored.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 constructor switch source order 1,0,2 | objdiff 99.17647; 222/221 instructions; structural/exact (8, 158); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 constructor switch source order 0,2,1 | objdiff 99.049774; 222/221 instructions; structural/exact (6, 159); first (50, ('lis', 'r28, 0'), ('lis', 'r29, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 constructor switch source order 0,1,2 | objdiff 99.06335; 222/221 instructions; structural/exact (8, 160); first (50, ('lis', 'r28, 0'), ('lis', 'r29, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 immutable type field on pane table metadata | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
inputChar | R9 fresh fetch c7896c38, sourceequal125/136/frame0x30. First branch10offset differs only due shorter Hangulblock; first real instruction65 initializer/count/newline compare/indexed append absent. Target carries countzero r6 through shift,indexed store,increment, mask u16return; initialNUL before cmplwi ch10 retaineddead compare. Kana/cursor methods exactshape; no volatile proof, extent0x220 endsatconfirmKana. Data288/288. Test const input/buffer/helper stream ownership and natural newline conversion variants; keep semantic operations, no empty helpers/stubs/dummy state.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 immutable animation count field in pane table | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 immutable force animation target pointer in pane table | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 immutable animation pointer slots at metadata definition | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 metadata selector and count immutable fields together | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation count initialized before force target from same metadata | objdiff 99.69683; 221/221 instructions; structural/exact (4, 11); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 loop count unsigned temporary derived through const field reference | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation index wide with explicit UTF16 lookup and comparison | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation count shares binding state with force target | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 count declared at outer pane iteration but assigned after pane construction | objdiff 99.61539; 221/221 instructions; structural/exact (0, 14); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 force target declared at outer pane iteration with retained count lifetime | objdiff 99.54751; 221/221 instructions; structural/exact (0, 17); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 allocation buffer declared once for all constructor cases | objdiff 98.86878; 221/221 instructions; structural/exact (0, 46); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 pane row type query in readonly inline boundary | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))

R9 exact entry iterator candidate quick full-build authority gate:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/so/SOOption] pool: IDENTICAL
[libs/RevoEX/src/so/SOOption] objdiff: code 816/1292 data None/None functions 3/4 fuzzy 99.9226 linked code 0
[libs/RevoEX/src/so/SOOption] instruction-exact functions: 3/4
[libs/RevoEX/src/so/SOOption]   section .text size 1292 match 99.9226
[libs/RevoEX/src/so/SOOption]   below 100: SOGetInterfaceOpt 99.78992
[libs/RevoEX/src/so/SOOption] baseline: code 816/1292 data None functions 3 fuzzy 99.9226
[libs/RVL_SDK/src/fa/pf_entry_iterator] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_entry_iterator] objdiff: code 7880/7880 data 24/24 functions 16/16 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/pf_entry_iterator] instruction-exact functions: 16/16
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .sdata size 24 match 100.0
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .text size 7880 match 100.0
[libs/RVL_SDK/src/fa/pf_entry_iterator] baseline: code 6932/7880 data 24 functions 15 fuzzy 99.9772
[src/keyboard/tiString] pool: IDENTICAL
[src/keyboard/tiString] objdiff: code 4632/5176 data 288/288 functions 41/42 fuzzy 98.9629 linked code 0
[src/keyboard/tiString] instruction-exact functions: 41/42
[src/keyboard/tiString]   section .data size 288 match 100.0
[src/keyboard/tiString]   section .text size 5176 match 98.962906
[src/keyboard/tiString]   below 100: inputChar__Q39textinput8tistring9DecolatedFw 90.132355
[src/keyboard/tiString] baseline: code 4632/5176 data 288 functions 41 fuzzy 98.9629
[src/keyboard/tiSignWindow] pool: IDENTICAL
[src/keyboard/tiSignWindow] objdiff: code 6300/7184 data 3468/3468 functions 55/56 fuzzy 99.9666 linked code 0
[src/keyboard/tiSignWindow] instruction-exact functions: 55/56
[src/keyboard/tiSignWindow]   section .ctors size 4 match 100.0
[src/keyboard/tiSignWindow]   section .data size 2672 match 100.0
[src/keyboard/tiSignWindow]   section .rodata size 784 match 100.0
[src/keyboard/tiSignWindow]   section .sdata size 8 match 100.0
[src/keyboard/tiSignWindow]   section .text size 7184 match 99.96659
[src/keyboard/tiSignWindow]   below 100: create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.72851
[src/keyboard/tiSignWindow] baseline: code 6300/7184 data 3468 functions 55 fuzzy 99.9666
regressions vs baseline: 0
global matched_code_percent: 90.02490 -> 90.05654
global fuzzy_match_percent: 99.54210 -> 99.54217
global complete_code_percent: 69.30851 -> 69.30851
global matched_data_percent: 99.36508 -> 99.36508
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
R9 accepted PFENT_ITER_FindCluster 100.0%, ctxdiff0/237instructions, wholeunit16/16/code7880/7880/data24/24; all four pools identical,0globalregressions/forbidden/readability, correctDOL. Only two source initialization lines changed; no configure/header/config/data changes.
SOGetInterfaceOpt | R9 command and response statements by actual lifetime level,length,option,reply | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 command and response statements by actual lifetime level,length,reply,option | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 command and response statements by actual lifetime option,level,length,reply | objdiff 99.85714; 119/119 instructions; structural/exact (2, 3); first (5, ('mr', 'r28, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 command and response statements by actual lifetime option,length,level,reply | objdiff 99.85714; 119/119 instructions; structural/exact (2, 3); first (5, ('mr', 'r28, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 command and response statements by actual lifetime option,length,reply,level | objdiff 99.85714; 119/119 instructions; structural/exact (2, 3); first (5, ('mr', 'r28, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 command and response statements by actual lifetime length,level,option,reply | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 command and response statements by actual lifetime length,level,reply,option | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 command and response statements by actual lifetime length,option,level,reply | objdiff 99.85714; 119/119 instructions; structural/exact (2, 3); first (5, ('mr', 'r28, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 command and response statements by actual lifetime length,option,reply,level | objdiff 99.85714; 119/119 instructions; structural/exact (2, 3); first (5, ('mr', 'r28, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 command and response statements by actual lifetime length,reply,level,option | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 command and response statements by actual lifetime length,reply,option,level | objdiff 99.85714; 119/119 instructions; structural/exact (2, 3); first (5, ('mr', 'r28, r4'), ('mr', 'r26, r4'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 UTF16 character passed as const reference into indexed append helper | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 UTF16 output bounded array reference and immutable pointer helper | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 literal conversion buffer uses output array member and meaningful current length | objdiff 87.80147; 128/136 instructions; structural/exact (30, 76); first (0, ('stwu', 'r1, -0x50(r1)'), ('stwu', 'r1, -0x30(r1)'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 stream appender carries pointer and UTF16 count through readonly character input | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 newline resets UTF16 count before common append in readonly character helper | objdiff 93.60294; 135/136 instructions; structural/exact (15, 61); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 newline empties buffered literal stream through Clear helper before append | objdiff 92.52941; 135/136 instructions; structural/exact (16, 61); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 newline byteview reset helper returns zero cursor before common append | objdiff 91.72794; 136/136 instructions; structural/exact (17, 61); first (63, ('b', '88'), ('b', '80'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 generic literal newline flush resets output length using unsigned short state | objdiff 95.036766; 136/136 instructions; structural/exact (8, 23); first (39, ('clrlwi', 'r28, r3, 0x18'), ('clrlwi', 'r29, r3, 0x18'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 stream constructor initializes count through const buffer input reference | objdiff 93.05147; 136/136 instructions; structural/exact (17, 60); first (63, ('b', '88'), ('b', '80'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 generic single character stream uses common append method for newline | objdiff 91.01471; 137/136 instructions; structural/exact (17, 74); first (10, ('beq', '476'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 Hangul conversion derives one character length from bounded output pointer | objdiff 89.92647; 130/136 instructions; structural/exact (18, 87); first (10, ('beq', '448'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 single character buffer append loops over existing buffer terminator | objdiff 89.117645; 139/136 instructions; structural/exact (18, 74); first (10, ('beq', '484'), ('beq', '472'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 mutable pane row reference with readonly animation slot view | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 immutable pane row pointer with readonly animation slot view | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 mutable pane row pointer with readonly animation slot view | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 table input bound through immutable array reference | objdiff 99.502266; 221/221 instructions; structural/exact (0, 18); first (49, ('lis', 'r22, 0'), ('lis', 'r27, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 table row lookup uses scoped const pointer after owner setup | objdiff 99.502266; 221/221 instructions; structural/exact (0, 18); first (49, ('lis', 'r22, 0'), ('lis', 'r27, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation count local signed extent with unsigned compare | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation slot view pointer accessed by typed inline reference getter | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation pointer value read inside readonly slot wrapper struct | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 pane name virtual lookup extracted before allocation in each branch | objdiff 78.746605; 224/221 instructions; structural/exact (74, 158); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation count copied after explicit zero index initialization | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation count and index declaration order shared across pane loop | objdiff 98.64253; 221/221 instructions; structural/exact (0, 54); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation index outside count lifetime and declared before force target | objdiff 98.57466; 221/221 instructions; structural/exact (0, 56); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 generic literal newline flush resets output length using unsigned short state detailed candidate disassembly | objdiff 95.036766; 136/136 instructions; structural/exact (8, 23); first (39, ('clrlwi', 'r28, r3, 0x18'), ('clrlwi', 'r29, r3, 0x18'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 newline reset skips alreadyempty stream u32 | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 newline clear removes existing buffered characters u32 | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 newline reset guards stream clear using immutable length view u32 | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar | R9 candidate u16 streamcount reference reaches95.036766/136instructions,firstrealHangulblock66stillhaslive newline branch and redundant countzero, maskedscaledindexinsteadtargetu32slwi. Registercount28vs29 propagates intoKana. Not retained; next trials implement functional Clear that skips alreadyempty stream or removes existing chars, to test deadbranch elimination at actual helper boundary.
inputChar__Q39textinput8tistring9DecolatedFw | R9 newline reset assigns only when positive old count u32 | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 newline reset skips alreadyempty stream u16 | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 newline clear removes existing buffered characters u16 | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 newline reset guards stream clear using immutable length view u16 | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 newline reset assigns only when positive old count u16 | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 newline stream clears existing buffered chars u32 | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R9 newline stream clears existing buffered chars u16 | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer pane traversal written as natural unsigned for loop | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer pane index initialized by traversal header rather than declaration | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer pane loop while form with increment at tail | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer pane loop do with preincrement in comparison | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer pane loop signed counter with unsigned bounds and UTF16 element lookup | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation traversal uses explicit for loop with existing local counter | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation index initialization inside for header after force metadata | objdiff 99.72851; 221/221 instructions; structural/exact (0, 10); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation loop exit inverted inside unconditional loop | objdiff 59.95475; 221/221 instructions; structural/exact (6, 52); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation count direct copy into index-and-count state | objdiff 98.57466; 221/221 instructions; structural/exact (0, 56); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 pane loop index initialized before force and animation metadata declarations | objdiff 99.54751; 221/221 instructions; structural/exact (0, 17); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 animation bound held by early unsigned immutable scalar copy per pane iteration | objdiff 98.75565; 221/221 instructions; structural/exact (0, 50); first (51, ('lis', 'r30, 0'), ('lis', 'r24, 0'))
signcreate | R9 leadingdeclsearch6builds unchanged10; new structural outer pane do->for loop immediatelyfixesAll/table addresshoistorder,221/221 and6registeronly bound/slot operands remain,99.86425%. Proven natural controlflow lever; candidate pending gate after remaining loop trials.
SOGetInterfaceOpt | R9 preparation failure returns early before request scope | objdiff 98.52941; 120/119 instructions; structural/exact (2, 108); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 preparation failure branches to shared return label | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 preparation status separate with early return and operation result scope | objdiff 98.86555; 120/119 instructions; structural/exact (2, 108); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 valid option block first with invalid branch in trailing else | objdiff 93.31092; 120/119 instructions; structural/exact (9, 108); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 allocated request success block before allocation error branch | objdiff 96.344536; 119/119 instructions; structural/exact (5, 73); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 selector pair store expressions followed by response construction inline block | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 input parameter names reflect protocol level and option request | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R9 input values named for response buffer and byte length | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer pane traversal written as natural unsigned for loop retained best outer loop | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))

R9 accepted natural pane for loop quick gate:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/so/SOOption] pool: IDENTICAL
[libs/RevoEX/src/so/SOOption] objdiff: code 816/1292 data None/None functions 3/4 fuzzy 99.9226 linked code 0
[libs/RevoEX/src/so/SOOption] instruction-exact functions: 3/4
[libs/RevoEX/src/so/SOOption]   section .text size 1292 match 99.9226
[libs/RevoEX/src/so/SOOption]   below 100: SOGetInterfaceOpt 99.78992
[libs/RevoEX/src/so/SOOption] baseline: code 816/1292 data None functions 3 fuzzy 99.9226
[libs/RVL_SDK/src/fa/pf_entry_iterator] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_entry_iterator] objdiff: code 7880/7880 data 24/24 functions 16/16 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/pf_entry_iterator] instruction-exact functions: 16/16
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .sdata size 24 match 100.0
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .text size 7880 match 100.0
[libs/RVL_SDK/src/fa/pf_entry_iterator] baseline: code 6932/7880 data 24 functions 15 fuzzy 99.9772
[src/keyboard/tiString] pool: IDENTICAL
[src/keyboard/tiString] objdiff: code 4632/5176 data 288/288 functions 41/42 fuzzy 98.9629 linked code 0
[src/keyboard/tiString] instruction-exact functions: 41/42
[src/keyboard/tiString]   section .data size 288 match 100.0
[src/keyboard/tiString]   section .text size 5176 match 98.962906
[src/keyboard/tiString]   below 100: inputChar__Q39textinput8tistring9DecolatedFw 90.132355
[src/keyboard/tiString] baseline: code 4632/5176 data 288 functions 41 fuzzy 98.9629
[src/keyboard/tiSignWindow] pool: IDENTICAL
[src/keyboard/tiSignWindow] objdiff: code 6300/7184 data 3468/3468 functions 55/56 fuzzy 99.9833 linked code 0
[src/keyboard/tiSignWindow] instruction-exact functions: 55/56
[src/keyboard/tiSignWindow]   section .ctors size 4 match 100.0
[src/keyboard/tiSignWindow]   section .data size 2672 match 100.0
[src/keyboard/tiSignWindow]   section .rodata size 784 match 100.0
[src/keyboard/tiSignWindow]   section .sdata size 8 match 100.0
[src/keyboard/tiSignWindow]   section .text size 7184 match 99.9833
[src/keyboard/tiSignWindow]   below 100: create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.86425
[src/keyboard/tiSignWindow] baseline: code 6300/7184 data 3468 functions 55 fuzzy 99.9666
regressions vs baseline: 0
global matched_code_percent: 90.02490 -> 90.05654
global fuzzy_match_percent: 99.54210 -> 99.54221
global complete_code_percent: 69.30851 -> 69.30851
global matched_data_percent: 99.36508 -> 99.36508
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
R9 signcreate improvement99.72851->99.86425; hoisted global/table address-load order nowexact,6register operands count22/slot31 swapped versuscount31/slot22.221/221frame0x50; all pools/dataexact,0globalregression/forbidden/readability/correctDOL. Leadingdeclsearch onforcandidate6buildsleaves6diffs. Minimal loop-form change retained andcommitted; no type/header/data changes.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer for loop initializes animation extent before traversal | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer for loop initializes force target before traversal | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer for loop animation bound initialized after index declaration | objdiff 99.75113; 221/221 instructions; structural/exact (0, 10); first (58, ('li', 'r22, 0'), ('li', 'r21, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer for loop animation counter declared before scoped bound | objdiff 98.77828; 221/221 instructions; structural/exact (0, 50); first (58, ('li', 'r22, 0'), ('li', 'r21, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer for loop animation bound shares readonly metadata input scope | objdiff 98.8914; 221/221 instructions; structural/exact (0, 46); first (58, ('li', 'r22, 0'), ('li', 'r21, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer for loop uses actual readonly pointer-to-slot input view | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer for loop declares resource and transform before slot pointer view | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer for loop readonly pane binding helper carries count before pointer reference | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer for loop mutable animation pointer slot reference | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R9 outer for loop caches animation file readonly reference as object | objdiff 97.004524; 219/221 instructions; structural/exact (9, 91); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
R9 data ownership audit: owned target data already100 by exact names: entry_iterator.sdata24, tiString.data288, tiSignWindow.data/rodata/sdata/ctors3468; SOOption noowneddata. Weak extras ignored. No relocation/type proof requiresrename/extentcorrection; no symbol/config/header/section changes.
R9 extent audit SOGetInterfaceOpt = .text:0x814B476C; // type:function size:0x1DC | next SOSetInterfaceOpt = .text:0x814B4948; // type:function size:0x128 | no overlap.
R9 extent audit PFENT_ITER_FindCluster = .text:0x815D3414; // type:function size:0x3B4 | next PFENT_ITER_Retreat = .text:0x815D37C8; // type:function size:0x25C | no overlap.
R9 extent audit inputChar__Q39textinput8tistring9DecolatedFw = .text:0x81432CE4; // type:function size:0x220 | next confirmKana__Q39textinput8tistring9DecolatedFv = .text:0x81432F04; // type:function size:0x14 | no overlap.
R9 extent audit create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator = .text:0x81430E50; // type:function size:0x374 | next __dt__Q49textinput8keyboard10signwindow7AnmPaneFv = .text:0x814311C4; // type:function size:0x58 | no overlap.
SOGetInterfaceOpt | R9 all source variants rejected:5pureoperand differences unchanged by selector const/reference/scopes/types. Eleven dependency-valid command/response operation orders either preserve5diffs orreverse actual header stores, giving99.85714/3diffs but2structural forms; latter rejected because introduces non-target scheduling. Earlyreturn/branchinversion adds1instruction orotherbranchforms, aliases unchanged. Leadingdeclsearch70builds noimprovement. Baseline source intact,3/4.
inputChar | R9 22 distinct compiled new converter trials. Best95.036766/136 stillhaslive newline reset branch absenttarget andwrongindexwidth/countregs; guarded actualclear removesbranch butfoldsindex/count,126/136. No candidate retained because original converter boundary unresolved; baseline125/136,90.132355 restored. Functional helper trials only, no empty stubs, unsupportedvolatile ordata changes.
R9 pre-final remaining audit | SOGetInterfaceOpt | 32 distinct compiled scored source attempts this round; >=3 proved.
R9 pre-final remaining audit | inputChar__Q39textinput8tistring9DecolatedFw | 22 distinct compiled source trials plus one repeated detailed disassembly run; >=3 proved.
R9 pre-final remaining audit | create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | 54 distinct compiled source trials plus one repeated retained-candidate rebuild; >=3 proved.
R9 retained source: entry iterator two initialization-line change exactly237/237 and16/16; sign outerdo->for loop exactly221/221shape and6pure operands,99.86425. SO andtiString source restored. All other units/exactfunctions/data preserved, no header/config changes. Final clean gate follows.
R9 trial totals: 113 distinct compiled source variations across four functions, plus82 declaration-order evaluations,195 builds; failed geometry-struct trial excluded. Three remaining open functions all exceed3 distinct attempts. One new exact function,948newmatchedcodebytes, signloadorderfour operands resolved; no original helper source inferred beyond evidence.

# R9 final clean full gate over all four owned units (non --quick)
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/so/SOOption] pool: IDENTICAL
[libs/RevoEX/src/so/SOOption] objdiff: code 816/1292 data None/None functions 3/4 fuzzy 99.9226 linked code 0
[libs/RevoEX/src/so/SOOption] instruction-exact functions: 3/4
[libs/RevoEX/src/so/SOOption]   section .text size 1292 match 99.9226
[libs/RevoEX/src/so/SOOption]   below 100: SOGetInterfaceOpt 99.78992
[libs/RevoEX/src/so/SOOption] baseline: code 816/1292 data None functions 3 fuzzy 99.9226
[libs/RVL_SDK/src/fa/pf_entry_iterator] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_entry_iterator] objdiff: code 7880/7880 data 24/24 functions 16/16 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/pf_entry_iterator] instruction-exact functions: 16/16
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .sdata size 24 match 100.0
[libs/RVL_SDK/src/fa/pf_entry_iterator]   section .text size 7880 match 100.0
[libs/RVL_SDK/src/fa/pf_entry_iterator] baseline: code 6932/7880 data 24 functions 15 fuzzy 99.9772
[src/keyboard/tiString] pool: IDENTICAL
[src/keyboard/tiString] objdiff: code 4632/5176 data 288/288 functions 41/42 fuzzy 98.9629 linked code 0
[src/keyboard/tiString] instruction-exact functions: 41/42
[src/keyboard/tiString]   section .data size 288 match 100.0
[src/keyboard/tiString]   section .text size 5176 match 98.962906
[src/keyboard/tiString]   below 100: inputChar__Q39textinput8tistring9DecolatedFw 90.132355
[src/keyboard/tiString] baseline: code 4632/5176 data 288 functions 41 fuzzy 98.9629
[src/keyboard/tiSignWindow] pool: IDENTICAL
[src/keyboard/tiSignWindow] objdiff: code 6300/7184 data 3468/3468 functions 55/56 fuzzy 99.9833 linked code 0
[src/keyboard/tiSignWindow] instruction-exact functions: 55/56
[src/keyboard/tiSignWindow]   section .ctors size 4 match 100.0
[src/keyboard/tiSignWindow]   section .data size 2672 match 100.0
[src/keyboard/tiSignWindow]   section .rodata size 784 match 100.0
[src/keyboard/tiSignWindow]   section .sdata size 8 match 100.0
[src/keyboard/tiSignWindow]   section .text size 7184 match 99.9833
[src/keyboard/tiSignWindow]   below 100: create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.86425
[src/keyboard/tiSignWindow] baseline: code 6300/7184 data 3468 functions 55 fuzzy 99.9666
regressions vs baseline: 0
global matched_code_percent: 90.02490 -> 90.05654
global fuzzy_match_percent: 99.54210 -> 99.54221
global complete_code_percent: 69.30851 -> 69.30851
global matched_data_percent: 99.36508 -> 99.36508
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
libs/RevoEX/src/so/SOOption | exact 3/4 -> 3/4 | code bytes 816 -> 816/1292 | data bytes 0 -> 0/0
R9 remaining | SOGetInterfaceOpt | 99.78992% | 119/119 frame0x30; five argument selector/level register operands, first5mr25vs26; rm/temp stack offsets, branch/helper/load/store/pointer order all exact. 32 distinct compiled source trials,70declsearchevaluations.
libs/RVL_SDK/src/fa/pf_entry_iterator | exact 15/16 -> 16/16 | code bytes 6932 -> 7880/7880 | data bytes 24 -> 24/24
src/keyboard/tiString | exact 41/42 -> 41/42 | code bytes 4632 -> 4632/5176 | data bytes 288 -> 288/288
R9 remaining | inputChar__Q39textinput8tistring9DecolatedFw | 90.132355% | 125/136 frame0x30; Hangul converter original inline boundary, indexed append counter and dead newline compare unresolved.22distinct converter trials plus repeated135/136 detailed disassembly; best95.036766rejected because addslive newline branch.
src/keyboard/tiSignWindow | exact 55/56 -> 55/56 | code bytes 6300 -> 6300/7184 | data bytes 3468 -> 3468/3468
R9 remaining | create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | 99.86425% | 221/221 frame0x50; all relocation-address/load orders nowexact, only6count22/slot31 operand differences vstargetcount31/slot22; first159lwz22vs31.54distinct source trials,12declaration evals.
R9 final files: libs/RVL_SDK/src/fa/pf_entry_iterator.c; src/keyboard/tiSignWindow.cpp; tools/decomp-assist/fz3.attempts.md. Source commits83182c27,2ee7e995. Exactcount+1,948matchedcodebytes. Allpoolsidentical/data100/correctDOL/0globalregression/forbidden/readability. No sourcechangesafterfullcleangate. Remaining original Hangul helper structure and SO/count/slot register choices uncertain, logged without fake completion. No symbolrenames/extentchanges/sharedheaders/configure switches, no out-of-scope sourcefiles. Finalcommit logonly.

# R10 XHIGH fresh branch, six owned units
HEAD 3cde45682d70991f4986a389b8cab1ae42a87468; origin 3cde45682d70991f4986a389b8cab1ae42a87468
libs/RevoEX/src/so/SOOption | R10 initial pool | POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RevoEX/src/so/SOOption | R10 baseline open | {'name': 'SOGetInterfaceOpt', 'size': '476', 'fuzzy_match_percent': 99.78992, 'metadata': {}, 'address': '520'}
src/keyboard/tiString | R10 initial pool | POOL IDENTICAL up to 0 (mine=0 base=0)
src/keyboard/tiString | R10 baseline open | {'name': 'inputChar__Q39textinput8tistring9DecolatedFw', 'size': '544', 'fuzzy_match_percent': 90.132355, 'metadata': {'demangled_name': 'textinput::tistring::Decolated::inputChar(wchar_t)'}, 'address': '1740'}
src/keyboard/tiSignWindow | R10 initial pool | POOL IDENTICAL up to 30 (mine=30 base=30)
src/keyboard/tiSignWindow | R10 baseline open | {'name': 'create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator', 'size': '884', 'fuzzy_match_percent': 99.86425, 'metadata': {'demangled_name': 'textinput::keyboard::signwindow::LayoutByNW4R::create(MEMAllocator*)'}, 'address': '1096'}
libs/RevoEX/src/cdb/CDBRecord | R10 initial pool | FIRST DIVERGENCE at index 10
    8 mine=0x1b0    base=0x1b0
      M "can't get file size of the record ; the record is closed\n"
      B "can't get file size of the record ; the record is closed\n"
    9 mine=0x1ec    base=0x1ec
      M "can't get data size of the record ; the record is closed\n"
      B "can't get data size of the record ; the record is closed\n"
*  10 mine=0x228    base=0x228
      M "can't remove the record ; the record is opened\n"
      B "can't reduce file size of the record ; the record is closed\n"
*  11 mine=0x258    base=0x268
      M "can't remove the record ; permission denied\n"
      B "can't reduce file size of the record ; the record is opened as READONL"
*  12 mine=0x288    base=0x2b8
      M "can't get CDBId of the record ; the record is closed\n"
      B "can't reduce file size of the record ; file size must be over %d bytes"
*  13 mine=0x2c0    base=0x300
      M "can't get maker code of the record ; the record is closed\n"
      B "can't reduce data size of the record ; the record is closed\n"
*  14 mine=0x2fc    base=0x340
      M "can't set modified time of the record; the database is opened as READO"
      B "can't reduce data size of the record ; the record is opened as READONL"

mine has 19 strings, base has 47
libs/RevoEX/src/cdb/CDBRecord | R10 initial pool | FIRST DIVERGENCE at index 10 |     8 mine=0x1b0    base=0x1b0    |       M "can't get file size of the record ; the record is closed\n" |       B "can't get file size of the record ; the record is closed\n" |     9 mine=0x1ec    base=0x1ec    |       M "can't get data size of the record ; the record is closed\n" |       B "can't get data size of the record ; the record is closed\n" | *  10 mine=0x228    base=0x228    |       M "can't remove the record ; the record is opened\n" |       B "can't reduce file size of the record ; the record is closed\n" | *  11 mine=0x258    base=0x268    |       M "can't remove the record ; permission denied\n" |       B "can't reduce file size of the record ; the record is opened as READONL" | *  12 mine=0x288    base=0x2b8    |       M "can't get CDBId of the record ; the record is closed\n" |       B "can't reduce file size of the record ; file size must be over %d bytes" | *  13 mine=0x2c0    base=0x300    |       M "can't get maker code of the record ; the record is closed\n" |       B "can't reduce data size of the record ; the record is closed\n" | *  14 mine=0x2fc    base=0x340    |       M "can't set modified time of the record; the database is opened as READO" |       B "can't reduce data size of the record ; the record is opened as READONL" |  | mine has 19 strings, base has 47
libs/RevoEX/src/cdb/CDBRecord | R10 baseline open | {'name': 'CDBCryptBuffer', 'size': '476', 'fuzzy_match_percent': 99.97479, 'metadata': {}, 'address': '4592'}
libs/RevoEX/src/cdb/CDBRecord | R10 baseline open | {'name': 'CDBRecordEncrypt', 'size': '1136', 'fuzzy_match_percent': 99.19014, 'metadata': {}, 'address': '5068'}
libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32 | R10 initial pool | POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32 | R10 baseline open | {'name': 'TMCJPEGDEC_decode_iquant', 'size': '1104', 'fuzzy_match_percent': 99.10507, 'metadata': {}, 'address': '0'}
libs/RevoEX/src/so/SOBasic | R10 initial pool | POOL IDENTICAL up to 1 (mine=1 base=1)
libs/RevoEX/src/so/SOBasic | R10 baseline open | {'name': 'SOGetSockName', 'size': '252', 'fuzzy_match_percent': 95.95238, 'metadata': {}, 'address': '868'}
R10 CDB pool audit | firstmissingtargetstrings at0x228reducefile/data size;19source vs47target, gap not merely a name mismatch. Targetretail extraction keeps stringblocks for code/functions absenttarget29functions andabsentheaders (ReduceFileSize etc). No fakepadding/string blobs or deadfunction stubs will beintroduced. Inference of linkerdedup/gc explains mismatch, original dead API bodies unknown. Needretainpoolbaselinewhileownedcode attempts proceed; code-only cryptoffset gaps remain data work andunresolved.
SOGetInterfaceOpt | R10 fetched origin dea64a8c; source equal original=True; baseline open per fresh report, no duplicate remote match.
SOGetInterfaceOpt | R10 first5mr25vs26,119/119/frame0x30; five argumentlevel/selector registers only; rm/tempstackoffsets, branches, memcpy/pointer/load order exact. No adjacentstackreload proof orsymboloverlap. Try typed selector array view and response-side immutable limits before finaldeclsearch.
SOGetInterfaceOpt | R10 command selectors addressed through real union array fields | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R10 returned length count read through readonly local alias after ioctl | objdiff 98.44538; 120/119 instructions; structural/exact (8, 27); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R10 IPC allocation starts from typed command block as input selector pointer | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R10 returned length and caller capacity compared by named signed locals | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R10 requested output size read as typed length block before vector registration | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
inputChar__Q39textinput8tistring9DecolatedFw | R10 fetched origin dea64a8c; source equal original=True; baseline open per fresh report, no duplicate remote match.
inputChar | R10 source125/136/frame0x30; firstbranch10 displacement reflectsmissing11Hangul instructions; targetcounter6indexedappend, duplicateinitialNUL anddeadch10compare; precedingKana andfollowingcursorblocksotherwiseexact. No targetadjacentstackreload proof, extentendsatconfirmKana. Previousnewline builders leaveextra livebranch; new actualOutput cursor type/helper/constructor trials follow.
inputChar__Q39textinput8tistring9DecolatedFw | R10 Output cursor initializes terminator then appends using mutable u32 index | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R10 Output cursor stores real buffer index as UTF16 count | objdiff 90.757355; 126/136 instructions; structural/exact (17, 73); first (10, ('beq', '432'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R10 Literal converter initializes destination via helper and returns indexed append count | objdiff 90.132355; 125/136 instructions; structural/exact (18, 73); first (10, ('beq', '428'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R10 Literal conversion output count returned through real stream length pointer | objdiff 90.132355; 125/136 instructions; structural/exact (18, 73); first (10, ('beq', '428'), ('beq', '472'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 fetched origin dea64a8c; source equal original=True; baseline open per fresh report, no duplicate remote match.
signcreate | R10 pool30identical/sourceequal;221/221frame0x50; first159bound lwz22vs31 and slot31vs22,6pure operands. Alladdresses/branches/constructors/stack/local ordering nowexact fromforloop gain. No adjacentstackreload orsymboloverlap. New traversal metadata aggregate and field-alias lifetimes beforedeclsearch.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 animation metadata count returned as readonly field reference before scalar copy | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 animation count shared by typed unsigned traversal bound object | objdiff 99.79638; 221/221 instructions; structural/exact (0, 9); first (157, ('lwz', 'r22, 0x1c(r20)'), ('lwz', 'r23, 0x1c(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 animation count cached through pointer to own unsigned loop bound | objdiff 99.095024; 221/221 instructions; structural/exact (0, 35); first (48, ('lis', 'r24, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 animation resources declared before loop with readonly slot reference kept local | objdiff 99.70588; 221/221 instructions; structural/exact (0, 12); first (158, ('li', 'r17, 0'), ('li', 'r18, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 animation count common scope ends together with readonly animation table reference | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 outer traversal const owner view for pane metadata indexed row | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
SOGetSockName | R10 fetched origin dea64a8c; source equal original=True; baseline open per fresh report, no duplicate remote match.
SOGetSockName | R10 63/63frame0x30; first6address29vstarget27 andrequest27vstarget29; call memcpyinputmove/load precedes outputmove targetvsoursdstfirst,3instructionorderdiffs plus8operands. Targetheaderrequestsocket0/address0x20; actualtypes NameRequest andSOSockAddr. New constinputview calleroutputdistinct logical pointer beforedeclsearch.
SOGetSockName | R10 readonly socket address input view with original mutable output argument | objdiff 95.71429; 63/63 instructions; structural/exact (2, 13); first (5, ('mr', 'r27, r4'), ('mr', 'r28, r3'))
SOGetSockName | R10 readonly socket address input immutable local pointer | objdiff 95.71429; 63/63 instructions; structural/exact (2, 13); first (5, ('mr', 'r27, r4'), ('mr', 'r28, r3'))
SOGetSockName | R10 copy helper reads const socket address length before output buffer input | objdiff 95.95238; 63/63 instructions; structural/exact (2, 11); first (6, ('mr', 'r29, r4'), ('mr', 'r27, r4'))
SOGetSockName | R10 immutable typed reply pointer in successful allocation scope | objdiff 95.55556; 63/63 instructions; structural/exact (2, 17); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
SOGetSockName | R10 request descriptor assigned after successful allocation check | objdiff 95.95238; 63/63 instructions; structural/exact (2, 11); first (6, ('mr', 'r29, r4'), ('mr', 'r27, r4'))
SOGetSockName | R10 input address length consumed through unsigned byte temporary | objdiff 95.95238; 63/63 instructions; structural/exact (2, 11); first (6, ('mr', 'r29, r4'), ('mr', 'r27, r4'))
SOGetSockName | R10 reply field pointer derived before socket request initialization | objdiff 95.95238; 63/63 instructions; structural/exact (2, 11); first (6, ('mr', 'r29, r4'), ('mr', 'r27, r4'))
SOGetSockName | R10 request and incoming address pointer grouped as named request state | objdiff 95.0; 63/63 instructions; structural/exact (2, 24); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBCryptBuffer | R10 fetched origin dea64a8c; source equal original=True; baseline open per fresh report, no duplicate remote match.
CDBCryptBuffer | R10 119/119/frame aligned0x180? raw prologue targetexact; onlythree OSReport base+offset operands source388/398/3a8 versus90c/91c/92c. Structuralcode andglobals/key/bufferrelocationsotherwiseexact; confirmedpool19vs47missingearlierdeadAPIstrings. No fakepoolbytes. Three sourcegeometry/helper attempts leavepoolbaseline tocheckmustlogallopens.
CDBCryptBuffer | R10 typed const input buffer view for each AES chunk | objdiff 99.97479; 119/119 instructions; structural/exact (3, 3); first (32, ('addi', 'r3, r29, 0x388'), ('addi', 'r3, r29, 0x90c'))
CDBCryptBuffer | R10 chunk length helper separates boundary arithmetic | objdiff 96.90756; 122/119 instructions; structural/exact (11, 76); first (32, ('addi', 'r3, r29, 0x388'), ('addi', 'r3, r29, 0x90c'))
CDBCryptBuffer | R10 AES block cursor declared before aligned AES context | objdiff 99.97479; 119/119 instructions; structural/exact (3, 3); first (32, ('addi', 'r3, r29, 0x388'), ('addi', 'r3, r29, 0x90c'))
CDBRecordEncrypt | R10 fetched origin dea64a8c; source equal original=True; baseline open per fresh report, no duplicate remote match.
CDBRecordEncrypt | R10 284/284/frame0x400aligned64 andalllocalarrayaddressesexact;44pureoperanddifferences, first8poolbase31vstarget25, argsrecord25vs26,buff26vs27,key29vs24,size27vs28,out28vs29, tempFile24vstarget31. No branch/frame/inlineattribute boundary diffs, noadjacentstackreload forvolatility. FirstnewtempFiledeclarationlifetime beforedeclsearch; pooloffsetsusedwithinfunctionallbeforegapsoexactcodepossible butunitgatewillstillfailbaselinepool.
CDBRecordEncrypt | R10 temporary record file pointer declared at shared function scope | objdiff 99.19014; 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 temporary record file pointer declared before cached file and arguments use | objdiff 99.19014; 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 temporary file pointer input view immutable within Wii ID helper scope | objdiff 99.19014; 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 file tell result and saved offset share one meaningful function variable | objdiff 98.503525; 284/284 instructions; structural/exact (3, 47); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 cached attribute pointer scoped to readonly record file ownership | objdiff 97.193665; 285/284 instructions; structural/exact (6, 276); first (8, ('lwz', 'r24, 0x38(r3)'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 encryption authenticated extent created after cipher calculation | objdiff 99.19014; 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 declsearch #1: const char* forceName; / u32 animationCount; / u32 paneIndex = 0; | 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
CDBRecordEncrypt | R10 declsearch #1: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 declsearch #2: CDBErr err; / CDBRecordFile* recordFile; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 declsearch #3: u32 dataSize; / CDBErr err; / CDBRecordFile* recordFile; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 declsearch #4: u32 fileSize; / CDBErr err; / u32 dataSize; / CDBRecordFile* recordFile; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (6, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #1: int size; / int result; / s32 rm; / SOSockAddr* addr; / SOSockAddr* reply; / NameRequest* request; | 63/63 instructions; structural/exact (2, 11); first (6, ('mr', 'r29, r4'), ('mr', 'r27, r4'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 declsearch #2: u32 animationCount; / const char* forceName; / u32 paneIndex = 0; | 221/221 instructions; structural/exact (0, 9); first (157, ('lwz', 'r22, 0x1c(r20)'), ('lwz', 'r23, 0x1c(r20)'))
CDBRecordEncrypt | R10 declsearch #5: u32 cryptSize; / CDBErr err; / u32 dataSize; / u32 fileSize; / CDBRecordFile* recordFile; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #2: int result; / int size; / s32 rm; / SOSockAddr* addr; / SOSockAddr* reply; / NameRequest* request; | 63/63 instructions; structural/exact (2, 18); first (6, ('mr', 'r29, r4'), ('mr', 'r27, r4'))
CDBRecordEncrypt | R10 declsearch #6: u32 authenticatedSize; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / CDBRecordFile* recordFile; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #3: s32 rm; / int result; / int size; / SOSockAddr* addr; / SOSockAddr* reply; / NameRequest* request; | 63/63 instructions; structural/exact (2, 18); first (6, ('mr', 'r29, r4'), ('mr', 'r27, r4'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 declsearch #3: u32 paneIndex = 0; / u32 animationCount; / const char* forceName; | 221/221 instructions; structural/exact (0, 13); first (58, ('li', 'r23, 0'), ('li', 'r21, 0'))
SOGetSockName | R10 declsearch #4: SOSockAddr* addr; / int result; / s32 rm; / int size; / SOSockAddr* reply; / NameRequest* request; | 63/63 instructions; structural/exact (2, 14); first (6, ('mr', 'r31, r4'), ('mr', 'r27, r4'))
CDBRecordEncrypt | R10 declsearch #7: int fileOffset; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / CDBRecordFile* recordFile; | 284/284 instructions; structural/exact (0, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #5: SOSockAddr* reply; / int result; / s32 rm; / SOSockAddr* addr; / int size; / NameRequest* request; | 63/63 instructions; structural/exact (2, 20); first (5, ('mr', 'r30, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #8: CDBRecordFile* recordFile; / u32 dataSize; / CDBErr err; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #6: NameRequest* request; / int result; / s32 rm; / SOSockAddr* addr; / SOSockAddr* reply; / int size; | 63/63 instructions; structural/exact (2, 14); first (6, ('mr', 'r29, r4'), ('mr', 'r27, r4'))
CDBRecordEncrypt | R10 declsearch #9: CDBRecordFile* recordFile; / u32 fileSize; / u32 dataSize; / CDBErr err; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (6, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 declsearch #4: const char* forceName; / u32 paneIndex = 0; / u32 animationCount; | 221/221 instructions; structural/exact (0, 10); first (58, ('li', 'r22, 0'), ('li', 'r21, 0'))
SOGetSockName | R10 declsearch #7: int size; / s32 rm; / int result; / SOSockAddr* addr; / SOSockAddr* reply; / NameRequest* request; | 63/63 instructions; structural/exact (2, 11); first (6, ('mr', 'r29, r4'), ('mr', 'r27, r4'))
CDBRecordEncrypt | R10 declsearch #10: CDBRecordFile* recordFile; / u32 cryptSize; / u32 dataSize; / u32 fileSize; / CDBErr err; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #8: int size; / SOSockAddr* addr; / s32 rm; / int result; / SOSockAddr* reply; / NameRequest* request; | 63/63 instructions; structural/exact (2, 15); first (6, ('mr', 'r30, r4'), ('mr', 'r27, r4'))
CDBRecordEncrypt | R10 declsearch #11: CDBRecordFile* recordFile; / u32 authenticatedSize; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / CDBErr err; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #9: int size; / SOSockAddr* reply; / s32 rm; / SOSockAddr* addr; / int result; / NameRequest* request; | 63/63 instructions; structural/exact (2, 19); first (6, ('mr', 'r29, r4'), ('mr', 'r27, r4'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 declsearch #5: u32 animationCount; / u32 paneIndex = 0; / const char* forceName; | 221/221 instructions; structural/exact (0, 13); first (58, ('li', 'r22, 0'), ('li', 'r21, 0'))
CDBRecordEncrypt | R10 declsearch #12: CDBRecordFile* recordFile; / int fileOffset; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / CDBErr err; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #10: int size; / NameRequest* request; / s32 rm; / SOSockAddr* addr; / SOSockAddr* reply; / int result; | 63/63 instructions; structural/exact (2, 17); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
SOGetSockName | R10 declsearch #11: int size; / int result; / SOSockAddr* addr; / s32 rm; / SOSockAddr* reply; / NameRequest* request; | 63/63 instructions; structural/exact (2, 11); first (6, ('mr', 'r29, r4'), ('mr', 'r27, r4'))
CDBRecordEncrypt | R10 declsearch #13: CDBRecordFile* recordFile; / CDBErr err; / u32 fileSize; / u32 dataSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (6, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #12: int size; / int result; / SOSockAddr* reply; / SOSockAddr* addr; / s32 rm; / NameRequest* request; | 63/63 instructions; structural/exact (2, 17); first (5, ('mr', 'r29, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #14: CDBRecordFile* recordFile; / CDBErr err; / u32 cryptSize; / u32 fileSize; / u32 dataSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (7, 51); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #13: int size; / int result; / NameRequest* request; / SOSockAddr* addr; / SOSockAddr* reply; / s32 rm; | 63/63 instructions; structural/exact (2, 14); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 declsearch #6: u32 paneIndex = 0; / const char* forceName; / u32 animationCount; | 221/221 instructions; structural/exact (0, 13); first (58, ('li', 'r23, 0'), ('li', 'r21, 0'))
CDBRecordEncrypt | R10 declsearch #15: CDBRecordFile* recordFile; / CDBErr err; / u32 authenticatedSize; / u32 fileSize; / u32 cryptSize; / u32 dataSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #14: int size; / int result; / s32 rm; / SOSockAddr* reply; / SOSockAddr* addr; / NameRequest* request; | 63/63 instructions; structural/exact (2, 17); first (5, ('mr', 'r29, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #16: CDBRecordFile* recordFile; / CDBErr err; / int fileOffset; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / u32 dataSize; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #15: int size; / int result; / s32 rm; / NameRequest* request; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 declsearch #16: int result; / int size; / s32 rm; / NameRequest* request; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 10); first (18, ('li', 'r31, -0x1c'), ('li', 'r30, -0x1c'))
CDBRecordEncrypt | R10 declsearch #17: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 cryptSize; / u32 fileSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (5, 49); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 declsearch #18: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 authenticatedSize; / u32 cryptSize; / u32 fileSize; / int fileOffset; | 284/284 instructions; structural/exact (5, 49); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #17: s32 rm; / int result; / int size; / NameRequest* request; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 10); first (18, ('li', 'r31, -0x1c'), ('li', 'r30, -0x1c'))
SOGetSockName | R10 declsearch #18: NameRequest* request; / int result; / s32 rm; / int size; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 9); first (22, ('rlwinm', 'r29, r0, 0, 0, 0x1a'), ('rlwinm', 'r31, r0, 0, 0, 0x1a'))
CDBRecordEncrypt | R10 declsearch #19: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / int fileOffset; / u32 cryptSize; / u32 authenticatedSize; / u32 fileSize; | 284/284 instructions; structural/exact (5, 49); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R10 declsearch complete 6 evaluated permutations; no source change.
SOGetSockName | R10 declsearch #19: SOSockAddr* reply; / int result; / s32 rm; / NameRequest* request; / int size; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 12); first (5, ('mr', 'r30, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #20: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 authenticatedSize; / u32 cryptSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #20: SOSockAddr* addr; / int result; / s32 rm; / NameRequest* request; / SOSockAddr* reply; / int size; | 63/63 instructions; structural/exact (2, 11); first (6, ('mr', 'r31, r4'), ('mr', 'r27, r4'))
CDBRecordEncrypt | R10 declsearch #21: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / int fileOffset; / u32 authenticatedSize; / u32 cryptSize; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #21: int size; / s32 rm; / int result; / NameRequest* request; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
CDBRecordEncrypt | R10 declsearch #22: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / int fileOffset; / u32 authenticatedSize; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #22: int size; / NameRequest* request; / s32 rm; / int result; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 10); first (18, ('li', 'r29, -0x1c'), ('li', 'r30, -0x1c'))
CDBRecordEncrypt | R10 declsearch #23: CDBErr err; / u32 dataSize; / CDBRecordFile* recordFile; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #23: int size; / SOSockAddr* reply; / s32 rm; / NameRequest* request; / int result; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 11); first (18, ('li', 'r28, -0x1c'), ('li', 'r30, -0x1c'))
CDBRecordEncrypt | R10 declsearch #24: CDBErr err; / u32 dataSize; / u32 fileSize; / CDBRecordFile* recordFile; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #24: int size; / SOSockAddr* addr; / s32 rm; / NameRequest* request; / SOSockAddr* reply; / int result; | 63/63 instructions; structural/exact (2, 14); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #25: CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / CDBRecordFile* recordFile; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #25: int size; / int result; / NameRequest* request; / s32 rm; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
CDBRecordEncrypt | R10 declsearch #26: CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / CDBRecordFile* recordFile; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #26: int size; / int result; / SOSockAddr* reply; / NameRequest* request; / s32 rm; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 12); first (5, ('mr', 'r29, r3'), ('mr', 'r28, r3'))
SOGetSockName | R10 declsearch #27: int size; / int result; / SOSockAddr* addr; / NameRequest* request; / SOSockAddr* reply; / s32 rm; | 63/63 instructions; structural/exact (2, 17); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #27: CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; / CDBRecordFile* recordFile; | 284/284 instructions; structural/exact (0, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 declsearch #28: CDBRecordFile* recordFile; / u32 dataSize; / u32 fileSize; / CDBErr err; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #28: int size; / int result; / s32 rm; / SOSockAddr* reply; / NameRequest* request; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 12); first (5, ('mr', 'r29, r3'), ('mr', 'r28, r3'))
SOGetSockName | R10 declsearch #29: int size; / int result; / s32 rm; / NameRequest* request; / SOSockAddr* addr; / SOSockAddr* reply; | 63/63 instructions; structural/exact (2, 14); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #29: CDBRecordFile* recordFile; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / CDBErr err; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #30: int result; / s32 rm; / int size; / NameRequest* request; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 10); first (18, ('li', 'r31, -0x1c'), ('li', 'r30, -0x1c'))
CDBRecordEncrypt | R10 declsearch #30: CDBRecordFile* recordFile; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / CDBErr err; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #31: int result; / s32 rm; / NameRequest* request; / int size; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 13); first (18, ('li', 'r31, -0x1c'), ('li', 'r30, -0x1c'))
SOGetSockName | R10 declsearch #32: int result; / s32 rm; / NameRequest* request; / SOSockAddr* reply; / int size; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 19); first (5, ('mr', 'r29, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #31: CDBRecordFile* recordFile; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; / CDBErr err; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #33: int result; / s32 rm; / NameRequest* request; / SOSockAddr* reply; / SOSockAddr* addr; / int size; | 63/63 instructions; structural/exact (2, 24); first (5, ('mr', 'r29, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #32: u32 dataSize; / CDBRecordFile* recordFile; / CDBErr err; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 declsearch #33: CDBRecordFile* recordFile; / CDBErr err; / u32 fileSize; / u32 cryptSize; / u32 dataSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #34: int size; / s32 rm; / NameRequest* request; / int result; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 10); first (18, ('li', 'r29, -0x1c'), ('li', 'r30, -0x1c'))
SOGetSockName | R10 declsearch #35: int size; / s32 rm; / NameRequest* request; / SOSockAddr* reply; / int result; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 14); first (18, ('li', 'r28, -0x1c'), ('li', 'r30, -0x1c'))
CDBRecordEncrypt | R10 declsearch #34: CDBRecordFile* recordFile; / CDBErr err; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / u32 dataSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #36: int size; / s32 rm; / NameRequest* request; / SOSockAddr* reply; / SOSockAddr* addr; / int result; | 63/63 instructions; structural/exact (2, 21); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #35: CDBRecordFile* recordFile; / CDBErr err; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; / u32 dataSize; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #37: s32 rm; / int size; / int result; / NameRequest* request; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
CDBRecordEncrypt | R10 declsearch #36: u32 fileSize; / CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (6, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #38: int size; / int result; / NameRequest* request; / SOSockAddr* reply; / s32 rm; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
CDBRecordEncrypt | R10 declsearch #37: CDBRecordFile* recordFile; / u32 fileSize; / CDBErr err; / u32 dataSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (6, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #39: int size; / int result; / NameRequest* request; / SOSockAddr* reply; / SOSockAddr* addr; / s32 rm; | 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
CDBRecordEncrypt | R10 declsearch #38: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 cryptSize; / u32 authenticatedSize; / u32 fileSize; / int fileOffset; | 284/284 instructions; structural/exact (5, 49); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #40: NameRequest* request; / int size; / int result; / s32 rm; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 13); first (18, ('li', 'r29, -0x1c'), ('li', 'r30, -0x1c'))
SOGetSockName | R10 declsearch #41: int size; / NameRequest* request; / int result; / s32 rm; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 10); first (18, ('li', 'r29, -0x1c'), ('li', 'r30, -0x1c'))
CDBRecordEncrypt | R10 declsearch #39: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; / u32 fileSize; | 284/284 instructions; structural/exact (5, 49); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #42: SOSockAddr* reply; / int size; / int result; / s32 rm; / NameRequest* request; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 19); first (5, ('mr', 'r29, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #40: u32 cryptSize; / CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 declsearch #41: CDBRecordFile* recordFile; / u32 cryptSize; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #43: int size; / SOSockAddr* reply; / int result; / s32 rm; / NameRequest* request; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 16); first (5, ('mr', 'r29, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #42: CDBRecordFile* recordFile; / CDBErr err; / u32 cryptSize; / u32 dataSize; / u32 fileSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #44: int size; / int result; / SOSockAddr* reply; / s32 rm; / NameRequest* request; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 12); first (5, ('mr', 'r29, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #43: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 authenticatedSize; / int fileOffset; / u32 cryptSize; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #45: SOSockAddr* addr; / int size; / int result; / s32 rm; / NameRequest* request; / SOSockAddr* reply; | 63/63 instructions; structural/exact (2, 24); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
SOGetSockName | R10 declsearch #46: int size; / SOSockAddr* addr; / int result; / s32 rm; / NameRequest* request; / SOSockAddr* reply; | 63/63 instructions; structural/exact (2, 21); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #44: u32 authenticatedSize; / CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #47: int size; / int result; / SOSockAddr* addr; / s32 rm; / NameRequest* request; / SOSockAddr* reply; | 63/63 instructions; structural/exact (2, 17); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
SOGetSockName | R10 declsearch #48: int size; / int result; / s32 rm; / SOSockAddr* addr; / NameRequest* request; / SOSockAddr* reply; | 63/63 instructions; structural/exact (2, 17); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R10 declsearch #45: CDBRecordFile* recordFile; / u32 authenticatedSize; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 declsearch #46: CDBRecordFile* recordFile; / CDBErr err; / u32 authenticatedSize; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch #49: int size; / int result; / s32 rm; / NameRequest* request; / SOSockAddr* reply; / SOSockAddr* addr; | 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
CDBRecordEncrypt | R10 declsearch #47: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 authenticatedSize; / u32 fileSize; / u32 cryptSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
SOGetSockName | R10 declsearch final best confirmation | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
CDBRecordEncrypt | R10 declsearch #48: int fileOffset; / CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; | 284/284 instructions; structural/exact (0, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 declsearch #49: CDBRecordFile* recordFile; / int fileOffset; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 declsearch #50: CDBRecordFile* recordFile; / CDBErr err; / int fileOffset; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 declsearch #51: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / int fileOffset; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 declsearch #52: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / int fileOffset; / u32 cryptSize; / u32 authenticatedSize; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 declsearch complete 52 evaluated permutations; no source change.
TMCJPEGDEC_decode_iquant | R10 fetched origin 5518cb16; source equal original=True; baseline open per fresh report, no duplicate remote match.
TMCJPEGDEC_decode_iquant | R10 pool first POOL IDENTICAL up to 0 (mine=0 base=0)
TMCJPEGDEC_decode_iquant | R10 first difference #42 DC long-table cursor r4 vs targetr7; 276/276/frame50. DC fast struct1c correct, DClimit14 correct, DCdecoded10 vs target18; ACfast18 vs target8; AClimitc correct, ACdecoded8 vs target10. The overlapping lifetimes and helper result scopes are structural; operand order #74 sum reversed and AC code #188 subf uses wrong source operand placement. No extent overlap, no literals/data. Try scope/aggregate helper/operands before declaration coloring.
TMCJPEGDEC_decode_iquant | R10 AC aggregate local within AC decoding scope | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 DC aggregate local within DC fast lookup scope | objdiff 99.097824; 276/276 instructions; structural/exact (14, 48); first (26, ('sth', 'r0, 0x18(r1)'), ('sth', 'r0, 0x1c(r1)'))
TMCJPEGDEC_decode_iquant | R10 each fast aggregate local within its decoding scope | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 AC aggregate declared before DC aggregate | objdiff 99.097824; 276/276 instructions; structural/exact (14, 48); first (26, ('sth', 'r0, 0x18(r1)'), ('sth', 'r0, 0x1c(r1)'))
TMCJPEGDEC_decode_iquant | R10 both aggregates declared together after scalar temporaries | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 decoded helper return separated from assignment | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 decoded helper return readonly aggregate | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 decoded limit fields reused for symbol index | objdiff 98.30797; 278/276 instructions; structural/exact (25, 216); first (16, ('b', '1028'), ('b', '1020'))
TMCJPEGDEC_decode_iquant | R10 named relative code before symbol addition | objdiff 99.141304; 276/276 instructions; structural/exact (12, 45); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 named symbol base added to relative code | objdiff 99.141304; 276/276 instructions; structural/exact (12, 45); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 helper structure return via whole entry copy | objdiff 93.98913; 274/276 instructions; structural/exact (41, 219); first (16, ('b', '1012'), ('b', '1020'))
TMCJPEGDEC_decode_iquant | R10 helper limit structure initialized at definition | objdiff 93.98913; 274/276 instructions; structural/exact (41, 219); first (16, ('b', '1012'), ('b', '1020'))
TMCJPEGDEC_decode_iquant | R10 separate limit helper definitions for DC and AC | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 DC helper input order work,table,symbols,bitCount | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 DC helper input order table,symbols,work,bitCount | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 DC helper input order symbols,bitCount,table,work | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 readonly typed Huffman table pointer throughout main | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 unsigned Huffman symbols readonly throughout main | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 DC and AC readonly table input lifetimes separated by decoding scopes | objdiff 98.68841; 276/276 instructions; structural/exact (12, 65); first (33, ('lwz', 'r26, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 DC sign extension power declared within DC phase | objdiff 99.06884; 276/276 instructions; structural/exact (12, 48); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 DC bit count consumed directly before shift mask | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 AC helper code relative index separated from running bit code | BUILD FAIL ath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -use_lmw_stmw on -lang=c -MMD -c libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32.c -o build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/b65 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32.d build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32.d ### mwcceppc.exe Compiler: # File: libs\RVLMiddleware\TMC_JPEG\src\b65\iqdec_b65_frv32.c # -------------------------------------------------------------- # 101: u32 relativeCode = code - entry->bitLength; # Error: ^^^ # (10141) expression syntax error # Too many errors printed, aborting program User break, cancelled... ninja: build stopped: subcommand failed.
TMCJPEGDEC_decode_iquant | R10 structural phase best (99.141304, 'named relative code before symbol addition'); saved /tmp/fz3-r10-jpeg-best.c if improved; original restored before further diagnosis.
SOGetSockName | R10 request field used directly as first memcpy destination | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 original void address argument used as memcpy source | objdiff 96.349205; 63/63 instructions; structural/exact (2, 5); first (5, ('mr', 'r27, r4'), ('mr', 'r28, r3'))
SOGetSockName | R10 readonly source alias confined to memcpy expression | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input copy helper source first and destination second | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input copy helper source and length before destination | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input copy helper destination last with signed length | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input copy helper readonly destination owner request | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input length local read before destination derivation | BUILD FAIL -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/so/SOBasic.c -o build/43U/src/libs/RevoEX/src/so && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/so/SOBasic.d build/43U/src/libs/RevoEX/src/so/SOBasic.d ### mwcceppc.exe Compiler: # File: libs\RevoEX\src\so\SOBasic.c # ------------------------------------- # 153: u32 length = addr->len; # Error: ^^^ # (10141) expression syntax error # Too many errors printed, aborting program User break, cancelled... ninja: build stopped: subcommand failed.
SOGetSockName | R10 input length local read after destination derivation | BUILD FAIL -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/so/SOBasic.c -o build/43U/src/libs/RevoEX/src/so && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/so/SOBasic.d build/43U/src/libs/RevoEX/src/so/SOBasic.d ### mwcceppc.exe Compiler: # File: libs\RevoEX\src\so\SOBasic.c # ------------------------------------- # 154: u32 length = addr->len; # Error: ^^^ # (10141) expression syntax error # Too many errors printed, aborting program User break, cancelled... ninja: build stopped: subcommand failed.
SOGetSockName | R10 request initialization occurs after derived reply pointer | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input helper copies source bytes viewed through char pointer | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input helper returns destination with unused memcpy result | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 readonly socket input with corrected allocation declaration order | objdiff 96.349205; 63/63 instructions; structural/exact (2, 5); first (5, ('mr', 'r27, r4'), ('mr', 'r28, r3'))
SOGetSockName | R10 immutable readonly socket input with corrected allocation declaration order | objdiff 96.349205; 63/63 instructions; structural/exact (2, 5); first (5, ('mr', 'r27, r4'), ('mr', 'r28, r3'))
SOGetSockName | R10 request address formed in first memcpy destination expression | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input pointer local declared after output allocation locals | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input byte length computed before output pointer local within real inner scope | objdiff 98.01588; 63/63 instructions; structural/exact (2, 3); first (5, ('mr', 'r30, r3'), ('mr', 'r28, r3'))
SOGetSockName | R10 input byte length uses external declaration with expression assigned before copy | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 reply pointer typed const address owner with mutable output field view | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 confirm scoped input length candidate for register allocation | objdiff 98.01588; 63/63 instructions; structural/exact (2, 3); first (5, ('mr', 'r30, r3'), ('mr', 'r28, r3'))
SOGetSockName | R10 input length block begins after socket request store before reply calculation | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input length block begins after reply pointer derivation | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input length declaration precedes allocation but assignment follows socket store | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 inner input readonly view uses shared count after socket store | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
CDBRecordEncrypt | R10 immutable key pointer argument definition | objdiff 99.19014; 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 immutable record pointer argument definition | objdiff 99.19014; 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 immutable buffer pointer argument definition | objdiff 99.19014; 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 readonly record view for file field loads with mutable record API input retained | objdiff 99.19014; 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 record key parameter read through immutable typed local | objdiff 99.22535; 284/284 instructions; structural/exact (0, 42); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 Wii ID field validation as genuine inline helper boundary | objdiff 98.67958; 285/284 instructions; structural/exact (5, 255); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 Wii ID helper readonly record field input owner | objdiff 98.67958; 285/284 instructions; structural/exact (5, 255); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 Wii ID inline helper preserves explicit result variable and file lifetime | objdiff 99.22535; 284/284 instructions; structural/exact (0, 42); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 Wii ID validation declarations file before error result | objdiff 99.19014; 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R10 Wii ID validation result returned through persistent error status | objdiff 99.11972; 284/284 instructions; structural/exact (0, 48); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
TMCJPEGDEC_decode_iquant | R10 volatility proof candidate: target DC at114 stw word to18(r1),118 lhz same18 immediately; AC2e0 stw to10(r1),2e4 lhz same10 immediately. Test decoded aggregate volatile at definition only; keep only if exact code and no added accesses.
TMCJPEGDEC_decode_iquant | R10 decoded aggregate volatile at definition with immediate reload proof | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 DC decoded aggregate volatile only | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 AC decoded aggregate volatile only | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 limit caller receives structure through output argument helper | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 fast entry fields explicitly copied in inline reader | objdiff 94.21377; 286/276 instructions; structural/exact (46, 269); first (0, ('stwu', 'r1, -0x60(r1)'), ('stwu', 'r1, -0x50(r1)'))
TMCJPEGDEC_decode_iquant | R10 fast entry output populated through typed pointer helper | objdiff 99.10507; 276/276 instructions; structural/exact (12, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 AC traversal in a distinct inline decoding phase | objdiff 97.1558; 276/276 instructions; structural/exact (5, 122); first (4, ('mr', 'r23, r3'), ('mr', 'r21, r3'))
TMCJPEGDEC_decode_iquant | R10 AC phase decoded aggregates volatile with immediate reload proof | objdiff 97.1558; 276/276 instructions; structural/exact (5, 122); first (4, ('mr', 'r23, r3'), ('mr', 'r21, r3'))
TMCJPEGDEC_decode_iquant | R10 AC phase relative code addition named before symbol offset | objdiff 97.19203; 276/276 instructions; structural/exact (5, 121); first (4, ('mr', 'r23, r3'), ('mr', 'r21, r3'))
TMCJPEGDEC_decode_iquant | R10 AC symbol index is separate from running bit code C90 block | objdiff 99.23189; 276/276 instructions; structural/exact (12, 43); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
SOGetInterfaceOpt | R10 immutable selector arguments level | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R10 immutable selector arguments option | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R10 immutable selector arguments level,option | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R10 saved level local before command pointer declaration | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R10 saved option local after command pointer declaration | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R10 option code comparison through unsigned local | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R10 selectors initialized by typed command setter inline helper | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R10 selectors input first before output command in setter helper | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R10 option selector validity named inline helper with immutable input | objdiff 93.36134; 124/119 instructions; structural/exact (9, 112); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
TMCJPEGDEC_decode_iquant | R10 volatility proof candidate: target DC at114 stw word to18(r1),118 lhz same18 immediately; AC2e0 stw to10(r1),2e4 lhz same10 immediately. Test decoded aggregate volatile at definition only; keep only if exact code and no added accesses.
TMCJPEGDEC_decode_iquant | R10 AC phase candidate structural five before declaration search | objdiff 97.19203; 276/276 instructions; structural/exact (5, 121); first (4, ('mr', 'r23, r3'), ('mr', 'r21, r3'))
TMCJPEGDEC_decode_iquant | R10 stack-slot diagnosis: six real aggregate objects are allocated dcFast1c/acFast18/DCreturnLimit14/DCcopy10/ACreturnLimitc/ACcopy8. Target six corresponding objects dcFast1c/DCcopy18/DCreturnLimit14/ACcopy10/ACreturnLimitc/acFast8. Test explicit typed result workspaces and ordinary local declaration order; each field is consumed by actual lookup/copy, no extra objects.
TMCJPEGDEC_decode_iquant | R10 DC and AC aggregate result workspaces passed to inline decoders | objdiff 99.14855; 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 aggregate copy destinations definition volatile dcDecoded | objdiff 99.14855; 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 aggregate copy destinations definition volatile acDecoded | objdiff 99.14855; 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 aggregate copy destinations definition volatile dcDecoded,acDecoded | objdiff 99.14855; 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 one typed decoder scratch containing all six actual aggregate copies | objdiff 99.14855; 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 typed scratch copy destination fields volatile with immediate reload proof | objdiff 99.14855; 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
SOGetInterfaceOpt | R10 initial declsearch evaluated #1: s32 rm; / int temporary; / int size; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #2: int temporary; / s32 rm; / int size; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #3: int size; / int temporary; / s32 rm; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #4: int result; / int temporary; / int size; / s32 rm; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #5: InterfaceOption* request; / int temporary; / int size; / int result; / s32 rm; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #6: InterfaceCommand* command; / int temporary; / int size; / int result; / InterfaceOption* request; / s32 rm; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #7: int* returnedLength; / int temporary; / int size; / int result; / InterfaceOption* request; / InterfaceCommand* command; / s32 rm; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #8: u8* reply; / int temporary; / int size; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / s32 rm; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #9: s32 rm; / int size; / int temporary; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #10: s32 rm; / int result; / int size; / int temporary; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #11: s32 rm; / InterfaceOption* request; / int size; / int result; / int temporary; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #12: s32 rm; / InterfaceCommand* command; / int size; / int result; / InterfaceOption* request; / int temporary; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #13: s32 rm; / int* returnedLength; / int size; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int temporary; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #14: s32 rm; / u8* reply; / int size; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / int temporary; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #15: s32 rm; / int temporary; / int result; / int size; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #16: s32 rm; / int temporary; / InterfaceOption* request; / int result; / int size; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #17: s32 rm; / int temporary; / InterfaceCommand* command; / int result; / InterfaceOption* request; / int size; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #18: s32 rm; / int temporary; / int* returnedLength; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int size; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #19: s32 rm; / int temporary; / u8* reply; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / int size; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #20: s32 rm; / int temporary; / int size; / InterfaceOption* request; / int result; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #21: s32 rm; / int temporary; / int size; / InterfaceCommand* command; / InterfaceOption* request; / int result; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #22: s32 rm; / int temporary; / int size; / int* returnedLength; / InterfaceOption* request; / InterfaceCommand* command; / int result; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #23: s32 rm; / int temporary; / int size; / u8* reply; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / int result; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #24: s32 rm; / int temporary; / int size; / int result; / InterfaceCommand* command; / InterfaceOption* request; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #25: s32 rm; / int temporary; / int size; / int result; / int* returnedLength; / InterfaceCommand* command; / InterfaceOption* request; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #26: s32 rm; / int temporary; / int size; / int result; / u8* reply; / InterfaceCommand* command; / int* returnedLength; / InterfaceOption* request; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #27: s32 rm; / int temporary; / int size; / int result; / InterfaceOption* request; / int* returnedLength; / InterfaceCommand* command; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #28: s32 rm; / int temporary; / int size; / int result; / InterfaceOption* request; / u8* reply; / int* returnedLength; / InterfaceCommand* command; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #29: s32 rm; / int temporary; / int size; / int result; / InterfaceOption* request; / InterfaceCommand* command; / u8* reply; / int* returnedLength; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #30: int temporary; / int size; / s32 rm; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #31: int temporary; / int size; / int result; / s32 rm; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #32: int temporary; / int size; / int result; / InterfaceOption* request; / s32 rm; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #33: int temporary; / int size; / int result; / InterfaceOption* request; / InterfaceCommand* command; / s32 rm; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #34: int temporary; / int size; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / s32 rm; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #35: int temporary; / int size; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; / s32 rm; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #36: s32 rm; / int size; / int result; / int temporary; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #37: s32 rm; / int size; / int result; / InterfaceOption* request; / int temporary; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #38: s32 rm; / int size; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int temporary; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #39: s32 rm; / int size; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / int temporary; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #40: s32 rm; / int size; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; / int temporary; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #41: int size; / s32 rm; / int temporary; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #42: s32 rm; / int temporary; / int result; / InterfaceOption* request; / int size; / InterfaceCommand* command; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #43: s32 rm; / int temporary; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int size; / int* returnedLength; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #44: s32 rm; / int temporary; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / int size; / u8* reply; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
SOGetInterfaceOpt | R10 initial declsearch evaluated #45: s32 rm; / int temporary; / int result; / InterfaceOption* request; / InterfaceCommand* command; / int* returnedLength; / u8* reply; / int size; | structural/exact (0,5), no improvement; reconstructed evaluated order list from deterministic tool and saved stdout, not a new build.
R10 gate behavior correction: gate.py reports CDBRecord pre-existing pool divergence but does not append pool mismatches to its failure reasons; full gate can PASS while incomplete data remains. Never claim CDBRecord complete until pool fixed. Previous assumption that pool forces GATE FAIL was incorrect.
TMCJPEGDEC_decode_iquant | R10 stack-slot diagnosis: six real aggregate objects are allocated dcFast1c/acFast18/DCreturnLimit14/DCcopy10/ACreturnLimitc/ACcopy8. Target six corresponding objects dcFast1c/DCcopy18/DCreturnLimit14/ACcopy10/ACreturnLimitc/acFast8. Test explicit typed result workspaces and ordinary local declaration order; each field is consumed by actual lookup/copy, no extra objects.
TMCJPEGDEC_decode_iquant | R10 workspace relative code addition temporaries in both long decoders | objdiff 99.184784; 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 workspace AC decoded symbol index separate from running bit code | objdiff 99.27536; 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 workspace zigzag table immutable owner view at actual first use | objdiff 99.14855; 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 workspace DC and AC table owners declared in respective scopes | objdiff 98.73189; 276/276 instructions; structural/exact (0, 53); first (33, ('lwz', 'r26, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 workspace quantization input typed readonly pointer | objdiff 99.14855; 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 workspace DC bit count input uses separate remaining count temporary | objdiff 99.0942; 276/276 instructions; structural/exact (0, 36); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 workspace GPR phase best structural/exact (0, 31)
TMCJPEGDEC_decode_iquant | R10 declsearch #1: u32 bitData; / u32 code; / u32 length; / const TMCHuffmanEntry* entry; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #2: u32 code; / u32 bitData; / u32 length; / const TMCHuffmanEntry* entry; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #3: u32 length; / u32 code; / u32 bitData; / const TMCHuffmanEntry* entry; | 276/276 instructions; structural/exact (0, 38); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #4: const TMCHuffmanEntry* entry; / u32 code; / u32 length; / u32 bitData; | 276/276 instructions; structural/exact (0, 38); first (42, ('addi', 'r6, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #5: u32 bitData; / u32 length; / u32 code; / const TMCHuffmanEntry* entry; | 276/276 instructions; structural/exact (0, 38); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #6: u32 bitData; / const TMCHuffmanEntry* entry; / u32 length; / u32 code; | 276/276 instructions; structural/exact (0, 35); first (42, ('addi', 'r6, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #7: u32 bitData; / u32 code; / const TMCHuffmanEntry* entry; / u32 length; | 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r5, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #8: u32 code; / u32 length; / u32 bitData; / const TMCHuffmanEntry* entry; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #9: u32 code; / u32 length; / const TMCHuffmanEntry* entry; / u32 bitData; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #10: u32 bitData; / u32 length; / const TMCHuffmanEntry* entry; / u32 code; | 276/276 instructions; structural/exact (0, 38); first (42, ('addi', 'r5, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #11: u32 length; / u32 bitData; / u32 code; / const TMCHuffmanEntry* entry; | 276/276 instructions; structural/exact (0, 38); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #12: const TMCHuffmanEntry* entry; / u32 bitData; / u32 code; / u32 length; | 276/276 instructions; structural/exact (0, 38); first (42, ('addi', 'r6, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #13: u32 bitData; / const TMCHuffmanEntry* entry; / u32 code; / u32 length; | 276/276 instructions; structural/exact (0, 38); first (42, ('addi', 'r6, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch complete 13 evaluated permutations; no source change.
TMCJPEGDEC_decode_iquant | R10 declsearch #1: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #2: const TMCHuffmanEntry* ac_fast; / u8* huff_sym; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 33); first (33, ('lwz', 'r28, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #3: s32 idx; / const TMCHuffmanEntry* ac_fast; / u8* huff_sym; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 48); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #4: u32* huff_tbl; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u8* huff_sym; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 33); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #5: s32 bit_pos; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / u8* huff_sym; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 33); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #6: u32 bit_data; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u8* huff_sym; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 33); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #7: u32 tmp; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u8* huff_sym; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 37); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #8: s32 r; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / u8* huff_sym; / s32 blk0; | 276/276 instructions; structural/exact (0, 33); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #9: s32 blk0; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / u8* huff_sym; | 276/276 instructions; structural/exact (0, 35); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #10: u8* huff_sym; / s32 idx; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #11: u8* huff_sym; / u32* huff_tbl; / s32 idx; / const TMCHuffmanEntry* ac_fast; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #12: u8* huff_sym; / s32 bit_pos; / s32 idx; / u32* huff_tbl; / const TMCHuffmanEntry* ac_fast; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #13: u8* huff_sym; / u32 bit_data; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / const TMCHuffmanEntry* ac_fast; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #14: u8* huff_sym; / u32 tmp; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / const TMCHuffmanEntry* ac_fast; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 50); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #15: u8* huff_sym; / s32 r; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / const TMCHuffmanEntry* ac_fast; / s32 blk0; | 276/276 instructions; structural/exact (0, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #16: u8* huff_sym; / s32 blk0; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / const TMCHuffmanEntry* ac_fast; | 276/276 instructions; structural/exact (0, 48); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #17: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 idx; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #18: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 bit_pos; / u32* huff_tbl; / s32 idx; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #19: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32 bit_data; / u32* huff_tbl; / s32 bit_pos; / s32 idx; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #20: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32 tmp; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / s32 idx; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 35); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #21: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 r; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 idx; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #22: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 blk0; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 idx; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #23: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / s32 bit_pos; / u32* huff_tbl; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #24: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32 bit_data; / s32 bit_pos; / u32* huff_tbl; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #25: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32 tmp; / s32 bit_pos; / u32 bit_data; / u32* huff_tbl; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 35); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #26: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / s32 r; / s32 bit_pos; / u32 bit_data; / u32 tmp; / u32* huff_tbl; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #27: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / s32 blk0; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / u32* huff_tbl; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #28: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / u32 bit_data; / s32 bit_pos; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #29: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / u32 tmp; / u32 bit_data; / s32 bit_pos; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 35); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #30: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 r; / u32 bit_data; / u32 tmp; / s32 bit_pos; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #31: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 blk0; / u32 bit_data; / u32 tmp; / s32 r; / s32 bit_pos; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #32: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 tmp; / u32 bit_data; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 35); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #33: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / s32 r; / u32 tmp; / u32 bit_data; / s32 blk0; | 276/276 instructions; structural/exact (0, 35); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #34: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / s32 blk0; / u32 tmp; / s32 r; / u32 bit_data; | 276/276 instructions; structural/exact (0, 37); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #35: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / s32 r; / u32 tmp; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #36: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / s32 blk0; / s32 r; / u32 tmp; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #37: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 blk0; / s32 r; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #38: const TMCHuffmanEntry* ac_fast; / s32 idx; / u8* huff_sym; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 33); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #39: const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / u8* huff_sym; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 33); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #40: const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u8* huff_sym; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 33); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #41: const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u8* huff_sym; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 33); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #42: const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / u8* huff_sym; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 33); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #43: const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / u8* huff_sym; / s32 blk0; | 276/276 instructions; structural/exact (0, 33); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #44: const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; / u8* huff_sym; | 276/276 instructions; structural/exact (0, 33); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #45: u8* huff_sym; / s32 idx; / u32* huff_tbl; / const TMCHuffmanEntry* ac_fast; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #46: u8* huff_sym; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / const TMCHuffmanEntry* ac_fast; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #47: u8* huff_sym; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / const TMCHuffmanEntry* ac_fast; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #48: u8* huff_sym; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / const TMCHuffmanEntry* ac_fast; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #49: u8* huff_sym; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / const TMCHuffmanEntry* ac_fast; / s32 blk0; | 276/276 instructions; structural/exact (0, 46); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #50: u8* huff_sym; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; / const TMCHuffmanEntry* ac_fast; | 276/276 instructions; structural/exact (0, 48); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #51: s32 idx; / u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 48); first (33, ('lwz', 'r28, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R10 declsearch #52: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 bit_pos; / s32 idx; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #53: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / s32 idx; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #54: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 idx; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #55: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 idx; / s32 blk0; | 276/276 instructions; structural/exact (0, 31); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch complete 55 evaluated permutations; no source change.
TMCJPEGDEC_decode_iquant | R10 both Huffman relative indices independent of running code | objdiff 99.31159; 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 both indices plus named limit and symbol scalar loads before aggregate writes | objdiff 99.31159; 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 limit and symbol readonly scalar inputs into aggregate helper | objdiff 99.31159; 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 DC and AC limit-copy pairs grouped as typed decode result objects | objdiff 99.26811; 276/276 instructions; structural/exact (12, 40); first (26, ('sth', 'r0, 0xc(r1)'), ('sth', 'r0, 0x1c(r1)'))
TMCJPEGDEC_decode_iquant | R10 typed results limit scalar inputs named before stores | objdiff 99.26811; 276/276 instructions; structural/exact (12, 40); first (26, ('sth', 'r0, 0xc(r1)'), ('sth', 'r0, 0x1c(r1)'))
TMCJPEGDEC_decode_iquant | R10 DC value bit count and bit data scoped to decoded coefficient | objdiff 99.25725; 276/276 instructions; structural/exact (0, 32); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 final representation phase best (0, 30)
SOBasic | R10 extent proof: soSocketRegistered at .sbss:81698E60 is source static int (ELF size4); target SOSocket lwz28/stw40 both relocate only offset0 of this scalar; next sslRegistered81698E68. Correct extent8->4 leaving81698E64..67 unowned alignment; address and .sbss section/split size8 unchanged. No function extent changes or symbol renames.
R10 owned data audit: tiString288/288 and tiSignWindow3468/3468 already exact; SOOption and JPEG no owned data; CDBRecord actual missing literal bytes19/47, not a proven object-name mismatch, retain all extents/names; SOBasic sole gap proven scalar alignment extent corrected above.
R10 retained state gate quick all six units: GATE PASS; DOL26116613f624061ba99c8d1a299aaa6efa85670d; regressions0/forbidden0/readability0. SOBasic .sbss100,data136->144; SOGetSockName eleven->three differing instructions (96.666664%); JPEG structural12->0,46->30 differing instructions (99.31159%). Instruction-exact counts unchanged, no new match claimed. All six actual Huffman aggregate fields mirror target load/store slots, no padding or retained volatility.
inputChar | R10 further structural trial: mode3 is literal conversion stub of the original Hangul stream, not a Hangul character-range test; target dead newline cmpl at7dc then indexed append count6. Previous R9 u32 reference used const character reference, u16 reference used value character, leaving alias/type alternatives unresolved. Try real count resets and append with signed/unsigned32 index and value/readonly input; retain only correct behavior, no empty newline helper.
inputChar__Q39textinput8tistring9DecolatedFw | R10 literal newline count reset u32 reference with wchar_t input | objdiff 93.60294; 135/136 instructions; structural/exact (15, 61); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R10 literal newline count reset u32 pointer with wchar_t input | objdiff 93.60294; 135/136 instructions; structural/exact (15, 61); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R10 literal newline count reset u32 reference with const wchar_t& input | objdiff 93.60294; 135/136 instructions; structural/exact (15, 61); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R10 literal newline count reset u32 pointer with const wchar_t& input | objdiff 93.60294; 135/136 instructions; structural/exact (15, 61); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R10 literal newline count reset s32 reference with wchar_t input | objdiff 93.60294; 135/136 instructions; structural/exact (15, 61); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R10 literal newline count reset s32 pointer with wchar_t input | objdiff 93.60294; 135/136 instructions; structural/exact (15, 61); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R10 literal newline count reset s32 reference with const wchar_t& input | objdiff 93.60294; 135/136 instructions; structural/exact (15, 61); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R10 literal newline count reset s32 pointer with const wchar_t& input | objdiff 93.60294; 135/136 instructions; structural/exact (15, 61); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R10 readonly old cursor input and mutable new cursor output views | objdiff 91.06618; 135/136 instructions; structural/exact (17, 62); first (10, ('beq', '468'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R10 literal stream cursor mutable class with by-value character append | objdiff 92.52941; 135/136 instructions; structural/exact (16, 61); first (10, ('beq', '468'), ('beq', '472'))
inputChar | R10 state variant phase best (93.60294, 'literal newline count reset u32 reference with wchar_t input'); original restored pending matching proof.
SOGetSockName | R10 input address length from readonly scalar accessor u8 | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input address length from readonly scalar accessor u32 | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input address length from readonly scalar accessor size_t | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 reply object derived through typed inline request accessor | objdiff 95.39683; 63/63 instructions; structural/exact (2, 19); first (5, ('mr', 'r29, r3'), ('mr', 'r28, r3'))
SOGetSockName | R10 input object bytes through readonly inline source view | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R10 input object representation uses unsigned byte view for copy | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
TMCJPEGDEC_decode_iquant | R10 declsearch #1: s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; /  / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #2: const TMCHuffmanEntry* dc_fast; / s32 q; / const u8* zztbl; /  / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #3: const u8* zztbl; / const TMCHuffmanEntry* dc_fast; / s32 q; /  / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #4:  / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; / s32 q; / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #5: s32 q; / const u8* zztbl; / const TMCHuffmanEntry* dc_fast; /  / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #6: s32 q; /  / const u8* zztbl; / const TMCHuffmanEntry* dc_fast; / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #7: s32 q; / const TMCHuffmanEntry* dc_fast; /  / const u8* zztbl; / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #8: s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; / bit_pos = work->bitCount; /  / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #9: s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; / bit_pos = work->bitCount; /  | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #10: s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; /  / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; / bit_pos = work->bitCount; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #11: const TMCHuffmanEntry* dc_fast; / const u8* zztbl; / s32 q; /  / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #12: const TMCHuffmanEntry* dc_fast; / const u8* zztbl; /  / s32 q; / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #13: s32 q; / const u8* zztbl; /  / const TMCHuffmanEntry* dc_fast; / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #14: const u8* zztbl; / s32 q; / const TMCHuffmanEntry* dc_fast; /  / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #15:  / s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #16: s32 q; /  / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #17: s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; / bit_pos = work->bitCount; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; /  | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #18: s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; / dc_fast = (const TMCHuffmanEntry*)work->pDCFast; /  / bit_pos = work->bitCount; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch complete 18 evaluated permutations; no source change.
R10 JPEG final declaration range correction: initially selected132..137, which accidentally included two following statements; discarded all candidate changes and restored accepted commit source before rerunning correct declaration-only129..134. No candidate from mistaken range retained or counted toward structural matching.
TMCJPEGDEC_decode_iquant | R10 declsearch #1: s32 extra; / s32 t; / s32 zz; / s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #2: s32 t; / s32 extra; / s32 zz; / s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #3: s32 zz; / s32 t; / s32 extra; / s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #4: s32 q; / s32 t; / s32 zz; / s32 extra; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #5: const TMCHuffmanEntry* dc_fast; / s32 t; / s32 zz; / s32 q; / s32 extra; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #6: const u8* zztbl; / s32 t; / s32 zz; / s32 q; / const TMCHuffmanEntry* dc_fast; / s32 extra; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #7: s32 extra; / s32 zz; / s32 t; / s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #8: s32 extra; / s32 q; / s32 zz; / s32 t; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #9: s32 extra; / const TMCHuffmanEntry* dc_fast; / s32 zz; / s32 q; / s32 t; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #10: s32 extra; / const u8* zztbl; / s32 zz; / s32 q; / const TMCHuffmanEntry* dc_fast; / s32 t; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #11: s32 extra; / s32 t; / s32 q; / s32 zz; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #12: s32 extra; / s32 t; / const TMCHuffmanEntry* dc_fast; / s32 q; / s32 zz; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #13: s32 extra; / s32 t; / const u8* zztbl; / s32 q; / const TMCHuffmanEntry* dc_fast; / s32 zz; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #14: s32 extra; / s32 t; / s32 zz; / const TMCHuffmanEntry* dc_fast; / s32 q; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #15: s32 extra; / s32 t; / s32 zz; / const u8* zztbl; / const TMCHuffmanEntry* dc_fast; / s32 q; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #16: s32 extra; / s32 t; / s32 zz; / s32 q; / const u8* zztbl; / const TMCHuffmanEntry* dc_fast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #17: s32 t; / s32 zz; / s32 extra; / s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #18: s32 t; / s32 zz; / s32 q; / s32 extra; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #19: s32 t; / s32 zz; / s32 q; / const TMCHuffmanEntry* dc_fast; / s32 extra; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #20: s32 t; / s32 zz; / s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; / s32 extra; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #21: s32 extra; / s32 zz; / s32 q; / s32 t; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #22: s32 extra; / s32 zz; / s32 q; / const TMCHuffmanEntry* dc_fast; / s32 t; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #23: s32 extra; / s32 zz; / s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; / s32 t; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #24: s32 zz; / s32 extra; / s32 t; / s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #25: s32 extra; / s32 t; / s32 q; / const TMCHuffmanEntry* dc_fast; / s32 zz; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #26: s32 extra; / s32 t; / s32 q; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; / s32 zz; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #27: s32 q; / s32 extra; / s32 t; / s32 zz; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #28: s32 extra; / s32 q; / s32 t; / s32 zz; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #29: s32 extra; / s32 t; / s32 zz; / const TMCHuffmanEntry* dc_fast; / const u8* zztbl; / s32 q; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #30: const TMCHuffmanEntry* dc_fast; / s32 extra; / s32 t; / s32 zz; / s32 q; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #31: s32 extra; / const TMCHuffmanEntry* dc_fast; / s32 t; / s32 zz; / s32 q; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #32: s32 extra; / s32 t; / const TMCHuffmanEntry* dc_fast; / s32 zz; / s32 q; / const u8* zztbl; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #33: const u8* zztbl; / s32 extra; / s32 t; / s32 zz; / s32 q; / const TMCHuffmanEntry* dc_fast; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #34: s32 extra; / const u8* zztbl; / s32 t; / s32 zz; / s32 q; / const TMCHuffmanEntry* dc_fast; | 276/276 instructions; structural/exact (0, 33); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #35: s32 extra; / s32 t; / const u8* zztbl; / s32 zz; / s32 q; / const TMCHuffmanEntry* dc_fast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch #36: s32 extra; / s32 t; / s32 zz; / const u8* zztbl; / s32 q; / const TMCHuffmanEntry* dc_fast; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R10 declsearch complete 36 evaluated permutations; no source change.
R10 final open audit | create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | 99.86425% | 6 compiled distinct source-level attempts plus logged declaration permutations | six animation-count/slot registers, identical221/frame50
R10 final open audit | inputChar__Q39textinput8tistring9DecolatedFw | 90.132355% | 14 compiled distinct source-level attempts plus logged declaration permutations | literal converter helper boundary, indexed cursor and dead newline compare,125/136
R10 final open audit | CDBCryptBuffer | 99.97479% | 3 compiled distinct source-level attempts plus logged declaration permutations | three OSReport literal offsets caused by missing earlier28literals;119/119otherwise
R10 final open audit | CDBRecordEncrypt | 99.19014% | 16 compiled distinct source-level attempts plus logged declaration permutations | 44GPR operands,284/284alignedframe400 exact; metadata origin unresolved
R10 final open audit | SOGetSockName | 96.666664% | 35 compiled distinct source-level attempts plus logged declaration permutations | first memcpy three argument setup instructions rotate;63/63otherwise exact; data144/144 nowexact
R10 final open audit | SOGetInterfaceOpt | 99.78992% | 14 compiled distinct source-level attempts plus logged declaration permutations | five parameter allocation operands, identical119/frame30
R10 final open audit | TMCJPEGDEC_decode_iquant | 99.31159% | 50 compiled distinct source-level attempts plus logged declaration permutations | 30GPR operands,276/276frame50andallaggregatecopyaddresses nowexact
R10 completion boundary: zero new exact functions; eight matched data bytes recovered by verified SOBasic extent correction. Every seven remaining functions has >=3 compiled source attempts; all rejected variants restored. Remaining CDBRecord literal provenance (retained APIs linker-stripped or extraction grouping) is still an inference, not proved; no speculative strings/functions/renames added. Final clean gate all six units follows.

### R10 final clean full gate, all six owned units
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/so/SOOption] pool: IDENTICAL
[libs/RevoEX/src/so/SOOption] objdiff: code 816/1292 data None/None functions 3/4 fuzzy 99.9226 linked code 0
[libs/RevoEX/src/so/SOOption] instruction-exact functions: 3/4
[libs/RevoEX/src/so/SOOption]   section .text size 1292 match 99.9226
[libs/RevoEX/src/so/SOOption]   below 100: SOGetInterfaceOpt 99.78992
[libs/RevoEX/src/so/SOOption] baseline: code 816/1292 data None functions 3 fuzzy 99.9226
[src/keyboard/tiString] pool: IDENTICAL
[src/keyboard/tiString] objdiff: code 4632/5176 data 288/288 functions 41/42 fuzzy 98.9629 linked code 0
[src/keyboard/tiString] instruction-exact functions: 41/42
[src/keyboard/tiString]   section .data size 288 match 100.0
[src/keyboard/tiString]   section .text size 5176 match 98.962906
[src/keyboard/tiString]   below 100: inputChar__Q39textinput8tistring9DecolatedFw 90.132355
[src/keyboard/tiString] baseline: code 4632/5176 data 288 functions 41 fuzzy 98.9629
[src/keyboard/tiSignWindow] pool: IDENTICAL
[src/keyboard/tiSignWindow] objdiff: code 6300/7184 data 3468/3468 functions 55/56 fuzzy 99.9833 linked code 0
[src/keyboard/tiSignWindow] instruction-exact functions: 55/56
[src/keyboard/tiSignWindow]   section .ctors size 4 match 100.0
[src/keyboard/tiSignWindow]   section .data size 2672 match 100.0
[src/keyboard/tiSignWindow]   section .rodata size 784 match 100.0
[src/keyboard/tiSignWindow]   section .sdata size 8 match 100.0
[src/keyboard/tiSignWindow]   section .text size 7184 match 99.9833
[src/keyboard/tiSignWindow]   below 100: create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.86425
[src/keyboard/tiSignWindow] baseline: code 6300/7184 data 3468 functions 55 fuzzy 99.9833
[libs/RevoEX/src/cdb/CDBRecord] pool: DIVERGES at string 10 (mine=19 orig=47)
[libs/RevoEX/src/cdb/CDBRecord] objdiff: code 5464/7076 data 144/2640 functions 27/29 fuzzy 99.8683 linked code 0
[libs/RevoEX/src/cdb/CDBRecord] instruction-exact functions: 27/29
[libs/RevoEX/src/cdb/CDBRecord]   section .bss size 128 match 100.0
[libs/RevoEX/src/cdb/CDBRecord]   section .data size 2496 match 52.795387
[libs/RevoEX/src/cdb/CDBRecord]   section .rodata size 16 match 100.0
[libs/RevoEX/src/cdb/CDBRecord]   section .text size 7076 match 99.868286
[libs/RevoEX/src/cdb/CDBRecord]   below 100: CDBCryptBuffer 99.97479
[libs/RevoEX/src/cdb/CDBRecord]   below 100: CDBRecordEncrypt 99.19014
[libs/RevoEX/src/cdb/CDBRecord] baseline: code 5464/7076 data 144 functions 27 fuzzy 99.8683
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 99.3116 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 99.31159
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 99.31159
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 99.1051
[libs/RevoEX/src/so/SOBasic] pool: IDENTICAL
[libs/RevoEX/src/so/SOBasic] objdiff: code 3836/4088 data 144/144 functions 21/22 fuzzy 99.7945 linked code 0
[libs/RevoEX/src/so/SOBasic] instruction-exact functions: 21/22
[libs/RevoEX/src/so/SOBasic]   section .bss size 40 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .data size 88 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .sbss size 8 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .sdata size 8 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .text size 4088 match 99.79452
[libs/RevoEX/src/so/SOBasic]   below 100: SOGetSockName 96.666664
[libs/RevoEX/src/so/SOBasic] baseline: code 3836/4088 data 136 functions 21 fuzzy 99.7505
regressions vs baseline: 0
global matched_code_percent: 90.37653 -> 90.37653
global fuzzy_match_percent: 99.55215 -> 99.55229
global complete_code_percent: 69.36874 -> 69.36874
global matched_data_percent: 99.36508 -> 99.36552
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```
R10 before -> after (instruction-exact functions, objdiff matched code bytes, objdiff matched data bytes):
libs/RevoEX/src/so/SOOption | functions 3/4 -> 3/4 | code 816/1292 -> 816/1292 | data 0/0 -> None/None
src/keyboard/tiString | functions 41/42 -> 41/42 | code 4632/5176 -> 4632/5176 | data 288/288 -> 288/288
src/keyboard/tiSignWindow | functions 55/56 -> 55/56 | code 6300/7184 -> 6300/7184 | data 3468/3468 -> 3468/3468
libs/RevoEX/src/cdb/CDBRecord | functions 27/29 -> 27/29 | code 5464/7076 -> 5464/7076 | data 144/2640 -> 144/2640
libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32 | functions 0/1 -> 0/1 | code 0/1104 -> None/1104 | data 0/0 -> None/None
libs/RevoEX/src/so/SOBasic | functions 21/22 -> 21/22 | code 3836/4088 -> 3836/4088 | data 136/144 -> 144/144
R10 final scope: changed only config/43U/symbols.txt, libs/RevoEX/src/so/SOBasic.c, libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32.c and this attempts log; commit64e181a4 carries verified data/structural improvements. No new exact code function; no linked flags changed. Seven remaining functions all logged with >=3 compiled attempts and first-difference diagnoses; all rejects restored. CDBRecord pool provenance remains uncertain. Full gate PASS is a regression/build/hash result, not full unit completion.

## R11 max round
Initial HEAD 9077ef8c7a1ab5bf7605f439ed621214b97999e3; origin 9077ef8c7a1ab5bf7605f439ed621214b97999e3; clean worktree. Nine owned units; no workers/delegation/remote writes. AGENTS and unslop read. Fresh source snapshots in /tmp/fz3-r11-*.original.
R11 unit initial pool libs/RevoEX/src/so/SOOption
POOL IDENTICAL up to 0 (mine=0 base=0)
R11 unit initial pool src/keyboard/tiString
POOL IDENTICAL up to 0 (mine=0 base=0)
R11 unit initial pool src/keyboard/tiSignWindow
POOL IDENTICAL up to 30 (mine=30 base=30)
R11 unit initial pool libs/RevoEX/src/cdb/CDBRecord
FIRST DIVERGENCE at index 10
    8 mine=0x1b0    base=0x1b0
      M "can't get file size of the record ; the record is closed\n"
      B "can't get file size of the record ; the record is closed\n"
    9 mine=0x1ec    base=0x1ec
      M "can't get data size of the record ; the record is closed\n"
      B "can't get data size of the record ; the record is closed\n"
*  10 mine=0x228    base=0x228
      M "can't remove the record ; the record is opened\n"
      B "can't reduce file size of the record ; the record is closed\n"
*  11 mine=0x258    base=0x268
      M "can't remove the record ; permission denied\n"
      B "can't reduce file size of the record ; the record is opened as READONL"
*  12 mine=0x288    base=0x2b8
      M "can't get CDBId of the record ; the record is closed\n"
      B "can't reduce file size of the record ; file size must be over %d bytes"
*  13 mine=0x2c0    base=0x300
      M "can't get maker code of the record ; the record is closed\n"
      B "can't reduce data size of the record ; the record is closed\n"
*  14 mine=0x2fc    base=0x340
      M "can't set modified time of the record; the database is opened as READO"
      B "can't reduce data size of the record ; the record is opened as READONL"

mine has 19 strings, base has 47
R11 unit initial pool libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32
POOL IDENTICAL up to 0 (mine=0 base=0)
R11 unit initial pool libs/RevoEX/src/so/SOBasic
POOL IDENTICAL up to 1 (mine=1 base=1)
R11 unit initial pool libs/RVLMiddleware/eZiText/src/clib/zoemdata
POOL IDENTICAL up to 0 (mine=0 base=0)
R11 unit initial pool src/scene/sdChannelTitle/iplSDChannelTitle
POOL IDENTICAL up to 55 (mine=55 base=55)
R11 unit initial pool libs/MSL/src/MSL_Common/wprintf
POOL IDENTICAL up to 0 (mine=0 base=0)
R11 retry remote freshness: SDChannelTitle already68/69, four of the five functions in stale task counts64/69 already exact on fresh HEAD; skip those four. All other supplied counts confirmed. Ten functions remain open in nine units. Baseline data: SO/no data; tiString288/288; tiSign3468/3468; CDB144/2640(pool missing28literals); JPEG/no data; SOBasic144/144(proven extent landed); zoemdata60/60; SD1976/1976; wprintf836/836. No remaining proven data-name mismatch or extent gap besides CDB actual literal pool.
SOGetInterfaceOpt | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 99.78992% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
SOGetInterfaceOpt | R11 pool first
POOL IDENTICAL up to 0 (mine=0 base=0)
SOGetInterfaceOpt | R11 initial ctxdiff
src 0x1dc base 0x1dc insns 119/119
diffs 5: [5, 6, 15, 42, 47]
     5 M mr r25, r4
       B mr r26, r4
     6 M mr r28, r5
       B mr r25, r5
    15 M addi r0, r28, -0x1001
       B addi r0, r25, -0x1001
    42 M stw r25, 0x20(r3)
       B stw r26, 0x20(r3)
    47 M stw r28, 0x24(r3)
       B stw r25, 0x24(r3)
SOGetInterfaceOpt | R11 initial structural/exact (0, 5)
SOGetInterfaceOpt | R11 classify first #5 mrlevel25 vs26, thenoption28vs25; five operands only119/119/frame30. All conditional branches/OptionLength alias/temporaries/helpers and memory operand offsets identical. No back-to-back local reload evidence and no extent overlap. Prior scalar local/const selector tests exhausted; new query object lifetime and real helper boundary before last declaration search.
SOGetInterfaceOpt | R11 selector query object initialized at input boundary level-first | BUILD FAIL RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/so/SOOption.c -o build/43U/src/libs/RevoEX/src/so && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/so/SOOption.d build/43U/src/libs/RevoEX/src/so/SOOption.d ### mwcceppc.exe Compiler: # File: libs\RevoEX\src\so\SOOption.c # -------------------------------------- # 101: const InterfaceSelectors selectors = {level,option}; # Error: ^ # (10124) illegal constant expression # Too many errors printed, aborting program User break, cancelled... ninja: build stopped: subcommand failed.
SOGetInterfaceOpt | R11 selector query object initialized at input boundary option-first | BUILD FAIL RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/so/SOOption.c -o build/43U/src/libs/RevoEX/src/so && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/so/SOOption.d build/43U/src/libs/RevoEX/src/so/SOOption.d ### mwcceppc.exe Compiler: # File: libs\RevoEX\src\so\SOOption.c # -------------------------------------- # 101: const InterfaceSelectors selectors = {option,level}; # Error: ^ # (10124) illegal constant expression # Too many errors printed, aborting program User break, cancelled... ninja: build stopped: subcommand failed.
SOGetInterfaceOpt | R11 readonly selector object passed through command encoder helper | BUILD FAIL RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/so/SOOption.c -o build/43U/src/libs/RevoEX/src/so && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/so/SOOption.d build/43U/src/libs/RevoEX/src/so/SOOption.d ### mwcceppc.exe Compiler: # File: libs\RevoEX\src\so\SOOption.c # -------------------------------------- # 105: const InterfaceSelectors selectors = {level,option}; # Error: ^ # (10124) illegal constant expression # Too many errors printed, aborting program User break, cancelled... ninja: build stopped: subcommand failed.
iplSDChannelTitle_flushSaveBeforeExit | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 98.5946% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
iplSDChannelTitle_flushSaveBeforeExit | R11 pool first
POOL IDENTICAL up to 55 (mine=55 base=55)
iplSDChannelTitle_flushSaveBeforeExit | R11 initial ctxdiff
src 0x94 base 0x94 insns 37/37
diffs 6: [20, 22, 23, 24, 25, 26]
    20 M lis r4, 0
       B lis r3, 0
    22 M addi r4, r4, 0
       B addi r3, r3, 0
    23 M lwz r3, 0x94(r4)
       B lwz r4, 0x94(r3)
    24 M stw r0, 0x4c0(r3)
       B stw r0, 0x4c0(r4)
    25 M lwz r3, 0x94(r4)
       B lwz r4, 0x28(r3)
    26 M lwz r4, 0x28(r4)
       B lwz r3, 0x94(r3)
iplSDChannelTitle_flushSaveBeforeExit | R11 initial structural/exact (2, 6)
Zi8MatchOEMdata | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 97.83854% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
Zi8MatchOEMdata | R11 pool first
POOL IDENTICAL up to 0 (mine=0 base=0)
Zi8MatchOEMdata | R11 initial ctxdiff
src 0x300 base 0x300 insns 192/192
diffs 40: [5, 6, 12, 18, 19, 20, 21, 23, 26, 27, 41, 46, 54, 62, 69, 73, 79, 83, 91, 94]
     5 M mr r27, r3
       B mr r28, r3
     6 M mr r26, r4
       B mr r27, r4
    12 M mr r28, r10
       B mr r29, r10
    18 M stw r0, 0x328(r28)
       B stw r0, 0x328(r29)
    19 M lwz r29, 0x328(r28)
       B lwz r26, 0x328(r29)
    20 M lhz r0, 0x324(r28)
       B lhz r0, 0x324(r29)
    21 M cmpw r29, r0
       B cmpw r26, r0
    23 M lwz r0, 0x320(r28)
       B lwz r0, 0x320(r29)
    26 M addi r24, r24, -1
       B clrlwi r3, r27, 0x18
    27 M clrlwi r3, r26, 0x18
       B addi r24, r24, -1
    41 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
    46 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
    54 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
    62 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
    69 M lhzx r0, r27, r0
       B lhzx r0, r28, r0
    73 M lhzx r0, r27, r0
       B lhzx r0, r28, r0
    79 M mr r5, r28
       B mr r5, r29
    83 M lhzx r0, r27, r0
       B lhzx r0, r28, r0
    91 M lhzx r0, r27, r0
       B lhzx r0, r28, r0
    94 M lbz r0, 0x1f(r28)
       B lbz r0, 0x1f(r29)
   101 M lhzx r0, r27, r0
       B lhzx r0, r28, r0
   107 M mr r6, r28
       B mr r6, r29
   119 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
   122 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
   129 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
   134 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
   137 M addi r29, r29, 1
       B addi r26, r26, 1
   138 M lhz r0, 0x324(r28)
       B lhz r0, 0x324(r29)
   139 M cmpw r29, r0
       B cmpw r26, r0
   144 M li r29, 0
       B li r26, 0
   145 M lhz r0, 0(r27)
       B lhz r0, 0(r28)
   149 M addi r29, r29, 1
       B addi r26, r26, 1
   150 M stw r29, 0x328(r28)
       B stw r26, 0x328(r29)
   159 M lhz r0, 0x324(r28)
       B lhz r0, 0x324(r29)
   160 M cmpw r29, r0
       B cmpw r26, r0
   162 M clrlwi r3, r29, 0x10
       B clrlwi r3, r26, 0x10
   165 M lwz r6, 0x32c(r28)
       B lwz r6, 0x32c(r29)
   166 M lwz r12, 0x320(r28)
       B lwz r12, 0x320(r29)
   172 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
   183 M li r29, 0
       B li r26, 0
Zi8MatchOEMdata | R11 initial structural/exact (2, 40)
__wpformatter | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 99.13997% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
__wpformatter | R11 pool first
POOL IDENTICAL up to 0 (mine=0 base=0)
__wpformatter | R11 initial ctxdiff
src 0x944 base 0x944 insns 593/593
diffs 98: [4, 5, 6, 7, 9, 10, 11, 13, 14, 15, 16, 30, 31, 45, 46, 55, 114, 121, 129, 137]
     4 M li r21, 0x20
       B li r20, 0x20
     5 M lis r17, 0
       B lis r16, 0
     6 M mr r22, r3
       B mr r21, r3
     7 M mr r23, r4
       B mr r22, r4
     9 M mr r24, r6
       B mr r23, r6
    10 M addi r17, r17, 0
       B addi r16, r16, 0
    11 M addi r16, r1, 0x47e
       B addi r15, r1, 0x47e
    13 M lis r18, 0
       B lis r17, 0
    14 M li r20, 0x25
       B li r19, 0x25
    15 M lis r19, 0
       B lis r18, 0
    16 M sth r21, 0xc(r1)
       B sth r20, 0xc(r1)
    30 M mr r12, r22
       B mr r12, r21
    31 M mr r3, r23
       B mr r3, r22
    45 M mr r12, r22
       B mr r12, r21
    46 M mr r3, r23
       B mr r3, r22
    55 M mr r4, r24
       B mr r4, r23
   114 M mr r3, r24
       B mr r3, r23
   121 M mr r3, r24
       B mr r3, r23
   129 M mr r3, r24
       B mr r3, r23
   137 M mr r3, r24
       B mr r3, r23
   144 M mr r3, r24
       B mr r3, r23
   149 M mr r3, r24
       B mr r3, r23
   193 M subf r3, r25, r16
       B subf r3, r25, r15
   196 M srawi r15, r0, 1
       B srawi r24, r0, 1
   201 M mr r3, r24
       B mr r3, r23
   208 M mr r3, r24
       B mr r3, r23
   216 M mr r3, r24
       B mr r3, r23
   224 M mr r3, r24
       B mr r3, r23
   231 M mr r3, r24
       B mr r3, r23
   236 M mr r3, r24
       B mr r3, r23
   280 M subf r3, r25, r16
       B subf r3, r25, r15
   283 M srawi r15, r0, 1
       B srawi r24, r0, 1
   288 M mr r3, r24
       B mr r3, r23
   293 M mr r3, r24
       B mr r3, r23
   311 M subf r3, r3, r16
       B subf r3, r3, r15
   314 M srawi r15, r0, 1
       B srawi r24, r0, 1
   319 M mr r3, r24
       B mr r3, r23
   324 M mr r3, r24
       B mr r3, r23
   342 M subf r3, r3, r16
       B subf r3, r3, r15
   345 M srawi r15, r0, 1
       B srawi r24, r0, 1
   350 M mr r3, r24
       B mr r3, r23
   356 M addi r25, r17, 0x54
       B addi r25, r16, 0x54
   364 M clrlwi r15, r3, 0x18
       B clrlwi r24, r3, 0x18
   367 M cmpw r15, r0
       B cmpw r24, r0
   369 M mr r15, r0
       B mr r24, r0
   374 M lwz r15, 0x7c(r1)
       B lwz r24, 0x7c(r1)
   377 M mr r5, r15
       B mr r5, r24
   384 M srawi r15, r0, 1
       B srawi r24, r0, 1
   388 M mr r15, r3
       B mr r24, r3
   390 M mr r3, r24
       B mr r3, r23
   393 M lwz r25, 0(r3)
       B lwz r24, 0(r3)
   394 M cmpwi r25, 0
       B cmpwi r24, 0
   396 M addi r25, r18, 0
       B addi r24, r17, 0
   403 M clrlwi r15, r3, 0x18
       B clrlwi r25, r3, 0x18
   406 M cmpw r15, r0
       B cmpw r25, r0
   408 M mr r15, r0
       B mr r25, r0
   413 M lwz r15, 0x7c(r1)
       B lwz r25, 0x7c(r1)
   414 M mr r3, r25
       B mr r3, r24
   416 M mr r5, r15
       B mr r5, r25
   420 M subf r15, r25, r3
       B subf r25, r24, r3
   422 M mr r3, r25
       B mr r3, r24
   424 M mr r15, r3
       B mr r25, r3
   425 M mr r4, r25
       B mr r4, r24
   426 M mr r5, r15
       B mr r5, r25
   430 M mr r15, r3
       B mr r24, r3
   434 M mr r3, r24
       B mr r3, r23
   438 M lwz r4, 0(r3)
       B lwz r25, 0(r3)
   441 M addi r3, r19, 0
       B addi r3, r18, 0
   446 M stw r31, 0(r4)
       B stw r31, 0(r25)
   448 M sth r31, 0(r4)
       B sth r31, 0(r25)
   450 M stw r31, 0(r4)
       B stw r31, 0(r25)
   452 M stw r31, 4(r4)
       B stw r31, 4(r25)
   454 M stw r0, 0(r4)
       B stw r0, 0(r25)
   456 M stw r31, 0(r4)
       B stw r31, 0(r25)
   458 M stw r31, 0(r4)
       B stw r31, 0(r25)
   460 M stw r31, 4(r4)
       B stw r31, 4(r25)
   462 M stw r0, 0(r4)
       B stw r0, 0(r25)
   468 M mr r3, r24
       B mr r3, r23
   472 M li r15, 1
       B li r24, 1
   475 M mr r3, r24
       B mr r3, r23
   484 M mr r15, r3
       B mr r24, r3
   486 M sth r20, 0x80(r1)
       B sth r19, 0x80(r1)
   488 M li r15, 1
       B li r24, 1
   496 M mr r12, r22
       B mr r12, r21
   497 M mr r3, r23
       B mr r3, r22
   508 M mr r29, r15
       B mr r29, r24
   525 M mr r12, r22
       B mr r12, r21
   526 M mr r3, r23
       B mr r3, r22
   536 M addi r15, r15, -1
       B addi r24, r24, -1
   538 M mr r12, r22
       B mr r12, r21
   539 M mr r3, r23
       B mr r3, r22
   552 M cmpwi r15, 0
       B cmpwi r24, 0
   554 M mr r12, r22
       B mr r12, r21
   555 M mr r3, r23
       B mr r3, r22
   557 M mr r5, r15
       B mr r5, r24
   568 M mr r12, r22
       B mr r12, r21
   569 M mr r3, r23
       B mr r3, r22
   570 M sth r21, 0xa(r1)
       B sth r20, 0xa(r1)
__wpformatter | R11 initial structural/exact (0, 98)
SOGetInterfaceOpt | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 99.78992% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
SOGetInterfaceOpt | R11 pool first
POOL IDENTICAL up to 0 (mine=0 base=0)
SOGetInterfaceOpt | R11 initial ctxdiff
src 0x1dc base 0x1dc insns 119/119
diffs 5: [5, 6, 15, 42, 47]
     5 M mr r25, r4
       B mr r26, r4
     6 M mr r28, r5
       B mr r25, r5
    15 M addi r0, r28, -0x1001
       B addi r0, r25, -0x1001
    42 M stw r25, 0x20(r3)
       B stw r26, 0x20(r3)
    47 M stw r28, 0x24(r3)
       B stw r25, 0x24(r3)
SOGetInterfaceOpt | R11 initial structural/exact (0, 5)
SOGetInterfaceOpt | R11 classify first #5 mrlevel25 vs26, thenoption28vs25; five operands only119/119/frame30. All conditional branches/OptionLength alias/temporaries/helpers and memory operand offsets identical. No back-to-back local reload evidence and no extent overlap. Prior scalar local/const selector tests exhausted; new query object lifetime and real helper boundary before last declaration search.
SOGetInterfaceOpt | R11 selector query object assigned at input boundary C90 level-first | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R11 selector query object assigned at input boundary C90 option-first | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
SOGetInterfaceOpt | R11 readonly selector object passed through command encoder helper C90 | objdiff 99.78992; 119/119 instructions; structural/exact (0, 5); first (5, ('mr', 'r25, r4'), ('mr', 'r26, r4'))
iplSDChannelTitle_flushSaveBeforeExit | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 98.5946% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
iplSDChannelTitle_flushSaveBeforeExit | R11 classify first #20 lis global base4 versus3; #25/#26 load manager then heap source, heap then manager target. Frame20/local pagec/index8 identical; no branches differ; volatile manager field prevSDPage store target does not show immediate scalar reload. Source saveHeap temp extends globalbase4 through call; use actual direct call argument or typed readonly heap view before any register search. Four other supplied opens already exact; this is only remaining SD function.
iplSDChannelTitle_flushSaveBeforeExit | R11 heap getter used directly as flush argument instead of extra local | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
iplSDChannelTitle_flushSaveBeforeExit | R11 manager cached after page store before heap argument evaluation | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
iplSDChannelTitle_flushSaveBeforeExit | R11 immutable heap pointer local at final call input boundary | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
__wpformatter | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 99.13997% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
__wpformatter | R11 first #4 space fill constant21 vs20;98operands,593/593/frame4d0/smw15 identical. All branches, loads/stores, field offsets and calls exact; num_chars15vs24 rotates bufferEnd/data bases/constant/argument registers by one. Character string branch uses targetpointer24,length25 versus sourcepointer25,length15, so investigate counter declaration lifetime and inline branch-specific pointer before final declaration search. Pool wide-literals836/836, no extent overlap, no added volatile needed.
__wpformatter | R11 character span counter local to actual format traversal loop | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 counter declared after buffer and fill character inputs | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 three format counters split with span length declared last | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
Zi8MatchOEMdata | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 97.83854% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
Zi8MatchOEMdata | R11 first structural difference #26 capacity decrement precedes length promotion; target promotes length first. Frame40/192 instructions, no extent overlap, case fold at stack8 correct; pattern/work/index/length form four-color rotation. Move decrement to comparison operand, then readonly pattern/context, no use-site volatile.
Zi8MatchOEMdata | R11 predecrement capacity in comparison right operand | objdiff 98.645836; 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 readonly pattern input and predecrement comparison | objdiff 97.604164; 194/192 instructions; structural/exact (19, 129); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 typed mutable work context and comparison decrement | BUILD FAIL xt/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -inline off -opt off -str readonly -sdata 0 -fp_contract off -Cpp_exceptions on -lang=c -MMD -c libs/RVLMiddleware/eZiText/src/clib/zoemdata.c -o build/43U/src/libs/RVLMiddleware/eZiText/src/clib && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zoemdata.d build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zoemdata.d ### mwcceppc.exe Compiler: # File: libs\RVLMiddleware\eZiText\src\clib\zoemdata.c # ------------------------------------------------------- # 8: context->oemMatch = match; # Error: ^^^^^^^ # (10140) undefined identifier 'context' # Too many errors printed, aborting program User break, cancelled... ninja: build stopped: subcommand failed.
Zi8MatchOEMdata | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 97.83854% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
Zi8MatchOEMdata | R11 typed context local confined to matcher body | objdiff 96.27604; 196/192 instructions; structural/exact (16, 184); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 unsigned saved OEM index with signed comparisons retained | objdiff 98.645836; 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 comparison ordering candidate before last declaration search | objdiff 98.645836; 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 register-only last declsearch on four real locals;
declaration block:
      ziWChar folded;
      ziS32 index;
      ziU32 position;
      ziU32 fallback = 0;
start (0, 47)
best (0, 47) after 13 builds; source restored; best order was:
    ziWChar folded;
    ziS32 index;
    ziU32 position;
    ziU32 fallback = 0;
Zi8MatchOEMdata | R11 best real declaration order after structurally exact decrement | objdiff 98.645836; 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
iplSDChannelTitle_flushSaveBeforeExit | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 98.5946% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
iplSDChannelTitle_flushSaveBeforeExit | R11 readonly save manager getter guarded to this source | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
iplSDChannelTitle_flushSaveBeforeExit | R11 readonly heap getter guarded to this source | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
iplSDChannelTitle_flushSaveBeforeExit | R11 both readonly global argument getters guarded to this source | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
CDBCryptBuffer | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 99.97479% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
CDBCryptBuffer | R11 pool first
FIRST DIVERGENCE at index 10
    8 mine=0x1b0    base=0x1b0
      M "can't get file size of the record ; the record is closed\n"
      B "can't get file size of the record ; the record is closed\n"
    9 mine=0x1ec    base=0x1ec
      M "can't get data size of the record ; the record is closed\n"
      B "can't get data size of the record ; the record is closed\n"
*  10 mine=0x228    base=0x228
      M "can't remove the record ; the record is opened\n"
      B "can't reduce file size of the record ; the record is closed\n"
*  11 mine=0x258    base=0x268
      M "can't remove the record ; permission denied\n"
      B "can't reduce file size of the record ; the record is opened as READONL"
*  12 mine=0x288    base=0x2b8
      M "can't get CDBId of the record ; the record is closed\n"
      B "can't reduce file size of the record ; file size must be over %d bytes"
*  13 mine=0x2c0    base=0x300
      M "can't get maker code of the record ; the record is closed\n"
      B "can't reduce data size of the record ; the record is closed\n"
*  14 mine=0x2fc    base=0x340
      M "can't set modified time of the record; the database is opened as READO"
      B "can't reduce data size of the record ; the record is opened as READONL"

mine has 19 strings, base has 47
CDBCryptBuffer | R11 initial ctxdiff
src 0x1dc base 0x1dc insns 119/119
diffs 3: [32, 75, 95]
    32 M addi r3, r29, 0x388
       B addi r3, r29, 0x90c
    75 M addi r3, r29, 0x398
       B addi r3, r29, 0x91c
    95 M addi r3, r29, 0x3a8
       B addi r3, r29, 0x92c
CDBCryptBuffer | R11 initial structural/exact (3, 3)
CDBCryptBuffer | R11 first #36 OSReport string addi388 vs90c; all119 instructions, aligned frame200 and local order/AES helper boundaries/branches exact. Three differences exclusively literal pool after index10, 28 real API error literals lack source/call provenance; no legitimate rename or extent correction. Try typed buffer view/ordinary block-size expression and loop form without artificial literals.
CDBCryptBuffer | R11 byte buffer local gives read and write spans a shared ordinary typed view | objdiff 99.97479; 119/119 instructions; structural/exact (3, 3); first (32, ('addi', 'r3, r29, 0x388'), ('addi', 'r3, r29, 0x90c'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 99.86425% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 pool first
POOL IDENTICAL up to 30 (mine=30 base=30)
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 initial ctxdiff
src 0x374 base 0x374 insns 221/221
diffs 6: [159, 163, 167, 187, 196, 205]
   159 M lwz r22, 0x18(r20)
       B lwz r31, 0x18(r20)
   163 M add r31, r20, r0
       B add r22, r20, r0
   167 M lwz r5, 0x20(r31)
       B lwz r5, 0x20(r22)
   187 M lwz r5, 0x20(r31)
       B lwz r5, 0x20(r22)
   196 M lwz r5, 0x20(r31)
       B lwz r5, 0x20(r22)
   205 M cmplw r0, r22
       B cmplw r0, r31
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 initial structural/exact (0, 6)
create | R11 first #159 lwz animationCount22 vs31;221/frame50/6 register operands. Loop branches, field offsets, operand/load order and other locals exact; animation-slot22vs31 lifetime intersects invariant count. Try counter for-loop, postincrement and slot value/readonly record boundary before declaration search; no stack reload volatile evidence.
CDBCryptBuffer | R11 block traversal expressed as normal bounded for loop | objdiff 99.97479; 119/119 instructions; structural/exact (3, 3); first (32, ('addi', 'r3, r29, 0x388'), ('addi', 'r3, r29, 0x90c'))
CDBCryptBuffer | R11 block size derived from actual cipher block array type | BUILD FAIL evoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/cdb/CDBRecord.c -o build/43U/src/libs/RevoEX/src/cdb && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/cdb/CDBRecord.d build/43U/src/libs/RevoEX/src/cdb/CDBRecord.d ### mwcceppc.exe Compiler: # File: libs\RevoEX\src\cdb\CDBRecord.c # ---------------------------------------- # 626: NETAESContext context __attribute__((aligned(blockSize))); # Error: ^ # (10140) undefined identifier 'blockSize' # Too many errors printed, aborting program User break, cancelled... ninja: build stopped: subcommand failed.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 inner animation traversal as real for loop | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 animation index advanced while obtaining current metadata slot | objdiff 98.959274; 221/221 instructions; structural/exact (2, 37); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 metadata slot loaded as readonly animation value rather than slot reference | objdiff 97.004524; 219/221 instructions; structural/exact (9, 91); first (48, ('lis', 'r26, 0'), ('lis', 'r25, 0'))
SOGetSockName | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 96.666664% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
SOGetSockName | R11 pool first
POOL IDENTICAL up to 1 (mine=1 base=1)
SOGetSockName | R11 initial ctxdiff
src 0xfc base 0xfc insns 63/63
diffs 3: [32, 33, 34]
    32 M mr r3, r28
       B mr r4, r27
    33 M mr r4, r27
       B lbz r5, 0(r27)
    34 M lbz r5, 0(r27)
       B mr r3, r28
SOGetSockName | R11 initial structural/exact (2, 3)
SOGetSockName | R11 first #32 copy destination move precedes source+length; target source+length first, destination last.63/frame30; all fields, validations, calls and branches exact, data144/144 fixed already; no symbol extent problem or store/reload volatile evidence. Try lifetime of reply reference and mutable destination separate from read-only input address view.
SOGetSockName | R11 reply pointer lifetime confined to successful request branch | objdiff 95.79365; 63/63 instructions; structural/exact (2, 14); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
SOGetSockName | R11 copy reads through const address while response uses mutable output view | objdiff 96.349205; 63/63 instructions; structural/exact (2, 5); first (5, ('mr', 'r27, r4'), ('mr', 'r28, r3'))
SOGetSockName | R11 read-only request view forms response address at copy boundary | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
inputChar__Q39textinput8tistring9DecolatedFw | R11 fetched origin 2050ad76; source equal fresh original=True; live baseline 90.132355% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
inputChar__Q39textinput8tistring9DecolatedFw | R11 pool first
POOL IDENTICAL up to 0 (mine=0 base=0)
inputChar__Q39textinput8tistring9DecolatedFw | R11 initial ctxdiff
src 0x1f4 base 0x220 insns 125/136
--- replace mine 10:11 base 10:11
  M   10 beq 428
  B   10 beq 472
--- replace mine 63:64 base 63:64
  M   63 b 44
  B   63 b 80
--- replace mine 65:69 base 65:78
  M   65 bne 24
  M   66 sth r4, 0x10(r1)
  M   67 li r29, 1
  M   68 sth r5, 0x12(r1)
  B   65 bne 60
  B   66 li r6, 0
  B   67 sth r6, 0x10(r1)
  B   68 cmplwi r4, 0xa
  B   69 slwi r0, r6, 1
  B   70 addi r5, r1, 0x10
  B   71 sthx r4, r5, r0
  B   72 addi r6, r6, 1
  B   73 mr r4, r5
  B   74 li r5, 0
  B   75 slwi r0, r6, 1
  B   76 clrlwi r29, r6, 0x10
  B   77 sthx r5, r4, r0
--- replace mine 90:91 base 99:100
  M   90 bne 52
  B   99 bne 56
--- replace mine 99:101 base 108:111
  M   99 lwz r0, 0x18(r31)
  M  100 add r0, r0, r29
  B  108 lwz r3, 0x18(r31)
  B  109 clrlwi r0, r29, 0x10
  B  110 add r0, r3, r0
--- replace mine 102:103 base 112:113
  M  102 b 52
  B  112 b 56
--- replace mine 112:114 base 122:125
  M  112 lwz r0, 0xc(r1)
  M  113 add r0, r0, r29
  B  122 lwz r3, 0xc(r1)
  B  123 clrlwi r0, r29, 0x10
  B  124 add r0, r3, r0
inputChar__Q39textinput8tistring9DecolatedFw | R11 initial structural/exact (18, 73)
inputChar__Q39textinput8tistring9DecolatedFw | R11 fetched origin c1183780; source equal fresh original=True; live baseline 90.132355% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
inputChar | R11 first structural branch10 reflects missing11-mode3 instructions; target #66 starts indexed literal converter count6 then deadnewline compare #68; no immediate stack reload or extent overlap. Target count masked again atcursoradd. New literal converter helper clears real preview state on newline versus result completion, actual typed buffer construction/field order; no empty helper, fabricated state or volatile.
inputChar__Q39textinput8tistring9DecolatedFw | R11 literal buffer constructor and newline preview clear u32 cursor | objdiff 90.80147; 131/136 instructions; structural/exact (22, 73); first (10, ('beq', '452'), ('beq', '472'))
inputChar__Q39textinput8tistring9DecolatedFw | R11 literal buffer constructor and newline preview clear u16 cursor | objdiff 90.80147; 131/136 instructions; structural/exact (22, 73); first (10, ('beq', '452'), ('beq', '472'))
CDBCryptBuffer | R11 fetched origin c1183780; source equal fresh original=True; live baseline 99.97479% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
CDBCryptBuffer | R11 correction: first differing index32 (not36); target aligned prologue confirmed independently; constant scalar prior trial replaced ATTRIBUTE_ALIGN and failed, excluded from compiled attempt count.
inputChar__Q39textinput8tistring9DecolatedFw | R11 literal buffer constructor and newline preview clear s32 cursor | objdiff 90.80147; 131/136 instructions; structural/exact (22, 73); first (10, ('beq', '452'), ('beq', '472'))
CDBCryptBuffer | R11 cipher block array sizeof as real enumeration constant, alignment unchanged | objdiff 99.97479; 119/119 instructions; structural/exact (3, 3); first (32, ('addi', 'r3, r29, 0x388'), ('addi', 'r3, r29, 0x90c'))
TMCJPEGDEC_decode_iquant | R11 fetched origin c1183780; source equal fresh original=True; live baseline 99.31159% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
TMCJPEGDEC_decode_iquant | R11 pool first
POOL IDENTICAL up to 0 (mine=0 base=0)
TMCJPEGDEC_decode_iquant | R11 initial ctxdiff
src 0x450 base 0x450 insns 276/276
diffs 30: [42, 51, 64, 65, 66, 73, 92, 93, 95, 96, 115, 116, 128, 130, 157, 166, 179, 180, 181, 188]
    42 M addi r4, r25, 0x24
       B addi r7, r25, 0x24
    51 M addi r4, r4, 4
       B addi r7, r7, 4
    64 M lhz r7, 0(r4)
       B lhz r4, 0(r7)
    65 M lhz r3, 2(r4)
       B lhz r3, 2(r7)
    66 M sth r7, 0x14(r1)
       B sth r4, 0x14(r1)
    73 M subf r0, r7, r6
       B subf r0, r4, r6
    92 M lwz r4, 4(r23)
       B lwz r0, 4(r23)
    93 M li r0, 1
       B li r4, 1
    95 M slw r6, r0, r25
       B slw r6, r4, r25
    96 M subf r4, r25, r4
       B subf r4, r25, r0
   115 M lwz r29, 0x4ac(r23)
       B lwz r25, 0x4ac(r23)
   116 M lwz r30, 0x4b0(r23)
       B lwz r24, 0x4b0(r23)
   128 M lis r24, 0
       B lis r29, 0
   130 M addi r24, r24, 0
       B addi r29, r29, 0
   157 M addi r4, r29, 0x24
       B addi r7, r25, 0x24
   166 M addi r4, r4, 4
       B addi r7, r7, 4
   179 M lhz r7, 0(r4)
       B lhz r4, 0(r7)
   180 M lhz r3, 2(r4)
       B lhz r3, 2(r7)
   181 M sth r7, 0xc(r1)
       B sth r4, 0xc(r1)
   188 M subf r0, r7, r6
       B subf r0, r4, r6
   191 M lbzx r3, r30, r0
       B lbzx r3, r24, r0
   205 M lbzx r25, r24, r27
       B lbzx r30, r29, r27
   213 M lwz r4, 4(r23)
       B lwz r0, 4(r23)
   216 M addi r7, r3, -1
       B addi r6, r3, -1
   217 M subf r4, r26, r4
       B subf r4, r26, r0
   224 M rlwinm r6, r25, 2, 0x16, 0x1d
       B rlwinm r7, r30, 2, 0x16, 0x1d
   226 M and r5, r7, r5
       B and r5, r6, r5
   231 M lwzx r3, r22, r6
       B lwzx r3, r22, r7
   234 M subf r5, r7, r5
       B subf r5, r6, r5
   237 M stwx r0, r21, r6
       B stwx r0, r21, r7
TMCJPEGDEC_decode_iquant | R11 initial structural/exact (0, 30)
TMCJPEGDEC_decode_iquant | R11 first #42 addi tablecursor4 vs7;276/frame50 and all six aggregate frame slots nowexact. Only30 GPR differences, long-entry threshold4vs7; DCremaining count0vs4 and ACtables/zigzag threecycle. No extent/pool gaps. Try meaningful cursor reuse, entry comparison temporary boundary and DC remaining bit local before final declaration search.
TMCJPEGDEC_decode_iquant | R11 DC long code advances actual input table cursor without redundant alias | objdiff 98.333336; 276/276 instructions; structural/exact (4, 54); first (33, ('lwz', 'r30, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 decoded threshold named explicitly after real aggregate copy in both helpers | objdiff 99.31159; 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 DC signed coefficient consumes scoped remaining bit count | objdiff 99.11232; 276/276 instructions; structural/exact (0, 38); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
CDBRecordEncrypt | R11 fetched origin c1183780; source equal fresh original=True; live baseline 99.19014% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
CDBRecordEncrypt | R11 pool first
FIRST DIVERGENCE at index 10
    8 mine=0x1b0    base=0x1b0
      M "can't get file size of the record ; the record is closed\n"
      B "can't get file size of the record ; the record is closed\n"
    9 mine=0x1ec    base=0x1ec
      M "can't get data size of the record ; the record is closed\n"
      B "can't get data size of the record ; the record is closed\n"
*  10 mine=0x228    base=0x228
      M "can't remove the record ; the record is opened\n"
      B "can't reduce file size of the record ; the record is closed\n"
*  11 mine=0x258    base=0x268
      M "can't remove the record ; permission denied\n"
      B "can't reduce file size of the record ; the record is opened as READONL"
*  12 mine=0x288    base=0x2b8
      M "can't get CDBId of the record ; the record is closed\n"
      B "can't reduce file size of the record ; file size must be over %d bytes"
*  13 mine=0x2c0    base=0x300
      M "can't get maker code of the record ; the record is closed\n"
      B "can't reduce data size of the record ; the record is closed\n"
*  14 mine=0x2fc    base=0x340
      M "can't set modified time of the record; the database is opened as READO"
      B "can't reduce data size of the record ; the record is opened as READONL"

mine has 19 strings, base has 47
CDBRecordEncrypt | R11 initial ctxdiff
src 0x470 base 0x470 insns 284/284
diffs 44: [8, 10, 11, 12, 13, 14, 15, 24, 25, 37, 41, 42, 46, 54, 61, 78, 88, 97, 106, 111]
     8 M lis r31, 0
       B lis r25, 0
    10 M mr r25, r3
       B mr r26, r3
    11 M mr r26, r4
       B mr r27, r4
    12 M mr r29, r5
       B mr r24, r5
    13 M mr r27, r6
       B mr r28, r6
    14 M mr r28, r7
       B mr r29, r7
    15 M addi r31, r31, 0
       B addi r25, r25, 0
    24 M mr r3, r26
       B mr r3, r27
    25 M mr r5, r27
       B mr r5, r28
    37 M cmpwi r26, 0
       B cmpwi r27, 0
    41 M lwz r24, 0x38(r25)
       B lwz r31, 0x38(r26)
    42 M cmpwi r24, 0
       B cmpwi r31, 0
    46 M lwz r0, 0x1c(r24)
       B lwz r0, 0x1c(r31)
    54 M addi r3, r24, 0x20
       B addi r3, r31, 0x20
    61 M lwz r3, 0x38(r25)
       B lwz r3, 0x38(r26)
    78 M lwz r3, 0x38(r25)
       B lwz r3, 0x38(r26)
    88 M mr r4, r29
       B mr r4, r24
    97 M lwz r0, 0x38(r25)
       B lwz r0, 0x38(r26)
   106 M addi r3, r31, 0x1b0
       B addi r3, r25, 0x1b0
   111 M mr r3, r25
       B mr r3, r26
   124 M lwz r0, 0x38(r25)
       B lwz r0, 0x38(r26)
   133 M addi r3, r31, 0x1ec
       B addi r3, r25, 0x1ec
   138 M mr r3, r25
       B mr r3, r26
   149 M cmplw r27, r0
       B cmplw r28, r0
   153 M mr r3, r26
       B mr r3, r27
   158 M lwz r0, 0x38(r25)
       B lwz r0, 0x38(r26)
   163 M mr r3, r25
       B mr r3, r26
   169 M mr r29, r3
       B mr r31, r3
   177 M lwz r0, 0x38(r25)
       B lwz r0, 0x38(r26)
   182 M mr r3, r25
       B mr r3, r26
   193 M lwz r0, 0x38(r25)
       B lwz r0, 0x38(r26)
   202 M addi r3, r31, 0x178
       B addi r3, r25, 0x178
   207 M mr r3, r25
       B mr r3, r26
   208 M addi r4, r26, 0x400
       B addi r4, r27, 0x400
   209 M addi r5, r27, -0x400
       B addi r5, r28, -0x400
   219 M lwz r0, 0x38(r25)
       B lwz r0, 0x38(r26)
   224 M mr r3, r25
       B mr r3, r26
   225 M mr r4, r29
       B mr r4, r31
   238 M addi r3, r26, 0x400
       B addi r3, r27, 0x400
   250 M mr r3, r26
       B mr r3, r27
   260 M mr r4, r26
       B mr r4, r27
   267 M addi r3, r26, 0xb0
       B addi r3, r27, 0xb0
   271 M cmpwi r28, 0
       B cmpwi r29, 0
   275 M stw r0, 0(r28)
       B stw r0, 0(r29)
CDBRecordEncrypt | R11 initial structural/exact (0, 44)
CDBRecordEncrypt | R11 first #8 literal base31 vs25;284/frame400/44 GPR operands, pool shifts are genuine missing earlier literals. All data/branch/offset/call orders and auth temporaries exact. Test readonly descriptor owner, field snapshot boundary and real WiiId helper lifetime instead of artificial pool data; no store/reload volatility evidence or extent overlap.
CDBRecordEncrypt | R11 descriptor ownership fields read through immutable descriptor view | objdiff 99.19014; 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 first metadata setter file snapshot has constant pointer identity | objdiff 99.19014; 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 WiiId metadata validation helper accepts read-only record owner | objdiff 99.22535; 284/284 instructions; structural/exact (0, 42); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
__wpformatter | R11 fetched origin c1183780; source equal fresh original=True; live baseline 99.13997% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
__wpformatter | R11 narrow argument fetched using actual char pointer type | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 narrow string end uses char pointer and pointer difference | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 narrow character input declared mutable as original va_arg type | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 wide string source readonly until output callback view | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 signed long character counter retaining signed comparisons | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 size_t character count with signed formatter comparisons | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 real buffer limit declared once for conversion helpers | objdiff 98.09444; 597/593 instructions; structural/exact (50, 439); first (10, ('addi', 'r25, r1, 0x480'), ('addi', 'r16, r16, 0'))
__wpformatter | R11 format object read through const pointer | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 fetched origin c1183780; source equal fresh original=True; live baseline 99.13997% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
__wpformatter | R11 second diagnosis: implicit buff+511 common constant occupies16 vs target15; fieldnum15 vs24 cycle unchanged by all pointer/int qualifiers. Name actual last buffer element at natural declaration scope, or normal pointer-difference expression before final declsearch; no dummy local or alignment changes.
__wpformatter | R11 actual last buffer element declared alongside buffer | objdiff 99.37605; 593/593 instructions; structural/exact (2, 66); first (10, ('addi', 'r25, r1, 0x47e'), ('addi', 'r16, r16, 0'))
__wpformatter | R11 last buffer element declaration after other conversion state | objdiff 99.37605; 593/593 instructions; structural/exact (2, 66); first (10, ('addi', 'r25, r1, 0x47e'), ('addi', 'r16, r16, 0'))
__wpformatter | R11 buffer end as subscript address in all result lengths | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 buffer count uses direct last element plus offset | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 buffer length difference computed before subtracting terminator | objdiff 98.463745; 597/593 instructions; structural/exact (43, 453); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 span count assigned in switch completion after buffer creation | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
Zi8MatchOEMdata | R11 fetched origin c1183780; source equal fresh original=True; live baseline 97.83854% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
Zi8MatchOEMdata | R11 promoted length captured before capacity decrement in real validation | objdiff 97.8125; 194/192 instructions; structural/exact (4, 177); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 capacity assignment in right comparison operand | objdiff 98.59375; 192/192 instructions; structural/exact (0, 48); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 fallback state expressed as actual boolean | objdiff 98.125; 193/192 instructions; structural/exact (7, 89); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 readonly pattern length snapshot for comparison and sentinels | objdiff 94.4375; 197/192 instructions; structural/exact (23, 186); first (5, ('mr', 'r26, r3'), ('mr', 'r28, r3'))
create | R11 continue same already-fetched open function: count/slot lifetime boundary allstructural exact. Distinct natural bound types, induction form and allocation input qualification before final manual declaration search.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 animation count signed source type with unsigned comparison view | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 animation count unsigned int instead of SDK unsigned long | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 count immutable within each pane iteration | objdiff 98.8914; 221/221 instructions; structural/exact (0, 46); first (58, ('li', 'r22, 0'), ('li', 'r21, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 count inner iteration initialized after induction variable | objdiff 98.77828; 221/221 instructions; structural/exact (0, 50); first (58, ('li', 'r22, 0'), ('li', 'r21, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 animation slot pointer refers to const table entry explicitly | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 animation index postfix increment after actual metadata use | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 allocation input pointer has fixed function-local identity | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
SOGetInterfaceOpt | R11 command address readonly with fields written through request object | objdiff 100.0; 119/119 instructions; structural/exact (0, 0); first None
SOGetInterfaceOpt | R11 accepted const command input view with selectors stored through owning request; no shared header changes, C ABI and all other functions unchanged. Compiler alias/read-only lever resolves all five selector colors,119/119/diffs0. Authority gate follows before local commit.

R11 SOOption gate-passing exact improvement
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/so/SOOption] pool: IDENTICAL
[libs/RevoEX/src/so/SOOption] objdiff: code 1292/1292 data None/None functions 4/4 fuzzy 100.0000 linked code 0
[libs/RevoEX/src/so/SOOption] instruction-exact functions: 4/4
[libs/RevoEX/src/so/SOOption]   section .text size 1292 match 100.0
[libs/RevoEX/src/so/SOOption] baseline: code 816/1292 data None functions 3 fuzzy 99.9226
regressions vs baseline: 0
global matched_code_percent: 90.43582 -> 90.45171
global fuzzy_match_percent: 99.56501 -> 99.56503
global complete_code_percent: 70.30611 -> 70.30611
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
SOGetInterfaceOpt | R11119/119/diffs0; poolidentical; clean C ABI, only readonly command input pointer and real owner field writes changed. This is the proven const-input alias lever.
__wpformatter | R11 fetched origin c1183780; source equal fresh original=True; live baseline 99.13997% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
iplSDChannelTitle_flushSaveBeforeExit | R11 fetched origin c1183780; source equal fresh original=True; live baseline 98.5946% remains open. Before starts pool below; all target function extents checked separately, no hidden rename/resize.
__wpformatter | R11 literal callback lengths separated from conversion result length | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 narrow conversion has its own byte length and exports character count | objdiff 98.01855; 593/593 instructions; structural/exact (2, 170); first (4, ('li', 'r24, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 wide input scan has separate case-local output count | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
iplSDChannelTitle_flushSaveBeforeExit | R11 page stored through named manager page reference | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
__wpformatter | R11 all literal output paths use separate prefix count | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
iplSDChannelTitle_flushSaveBeforeExit | R11 current page readonly value captured before manager getter | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
R11 WP/SD continued same functions after their completed pre-start origin2050ad76 fetch, pool and ctxdiff diagnosis. Canceled only our redundant queued fetch requests after >4 minutes waiting behind external lock holder; resumed source experiments from verified originals without restarting any function. No other processes or refs changed.
__wpformatter | R11 literal callback lengths separated from conversion result length | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 narrow conversion has its own byte length and exports character count | objdiff 98.01855; 593/593 instructions; structural/exact (2, 170); first (4, ('li', 'r24, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 wide input scan has separate case-local output count | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 all literal output paths use separate prefix count | objdiff 99.13997; 593/593 instructions; structural/exact (0, 98); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
iplSDChannelTitle_flushSaveBeforeExit | R11 page stored through named manager page reference | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
iplSDChannelTitle_flushSaveBeforeExit | R11 current page readonly value captured before manager getter | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
iplSDChannelTitle_flushSaveBeforeExit | R11 page setter helper with int input | BUILD FAIL om: # Z:\mnt\drive2\projects\wii-ipl-workers\data- # d2\include\scene\iplSceneBase.h:6 # Z:\mnt\drive2\projects\wii-ipl-workers\data- # d2\include\scene\iplFaderSceneBase.h:4 # Z:\mnt\drive2\projects\wii-ipl-workers\data- # d2\include\iplSceneHeader.h:5 # Z:\mnt\drive2\projects\wii-ipl-workers\data- # d2\include\scene\sdChannelTitle\iplSDChannelTitle.h:4 # Z:\mnt\drive2\projects\wii-ipl-workers\data- # d2\src\scene\sdChannelTitle\iplSDChannelTitle.cpp:6) ### mwcceppc.exe Compiler: # File: src\scene\sdChannelTitle\iplSDChannelTitle.cpp # ------------------------------------------------------- # 1354: ic inline void saveSDPage(savedata::Manager* manager, int page) { # Error: ^ # (10333) object 'ipl::scene::saveSDPage(ipl::savedata::Manager *, int)' # redefined # Too many errors printed, aborting program User break, cancelled... ninja: build stopped: subcommand failed.
iplSDChannelTitle_flushSaveBeforeExit | R11 page setter helper with const SDChannelTitle* input | BUILD FAIL cts\wii-ipl-workers\data- # d2\include\scene\iplSceneBase.h:6 # Z:\mnt\drive2\projects\wii-ipl-workers\data- # d2\include\scene\iplFaderSceneBase.h:4 # Z:\mnt\drive2\projects\wii-ipl-workers\data- # d2\include\iplSceneHeader.h:5 # Z:\mnt\drive2\projects\wii-ipl-workers\data- # d2\include\scene\sdChannelTitle\iplSDChannelTitle.h:4 # Z:\mnt\drive2\projects\wii-ipl-workers\data- # d2\src\scene\sdChannelTitle\iplSDChannelTitle.cpp:6) ### mwcceppc.exe Compiler: # File: src\scene\sdChannelTitle\iplSDChannelTitle.cpp # ------------------------------------------------------- # 1354: SDPage(savedata::Manager* manager, const SDChannelTitle* title) { # Error: ^ # (10333) object 'ipl::scene::saveSDPage(ipl::savedata::Manager *, const # ipl::scene::SDChannelTitle *)' redefined # Too many errors printed, aborting program User break, cancelled... ninja: build stopped: subcommand failed.
iplSDChannelTitle_flushSaveBeforeExit | R11 heap first input of real flush helper | BUILD FAIL nt\drive2\projects\wii-ipl-workers\data- # d2\include\scene\iplSceneBase.h:6 # Z:\mnt\drive2\projects\wii-ipl-workers\data- # d2\include\scene\iplFaderSceneBase.h:4 # Z:\mnt\drive2\projects\wii-ipl-workers\data- # d2\include\iplSceneHeader.h:5 # Z:\mnt\drive2\projects\wii-ipl-workers\data- # d2\include\scene\sdChannelTitle\iplSDChannelTitle.h:4 # Z:\mnt\drive2\projects\wii-ipl-workers\data- # d2\src\scene\sdChannelTitle\iplSDChannelTitle.cpp:6) ### mwcceppc.exe Compiler: # File: src\scene\sdChannelTitle\iplSDChannelTitle.cpp # ------------------------------------------------------- # 1354: saveSDChannelState(EGG::Heap* heap, savedata::Manager* manager) { # Error: ^ # (10333) object 'ipl::scene::saveSDChannelState(EGG::Heap *, # ipl::savedata::Manager *)' redefined # Too many errors printed, aborting program User break, cancelled... ninja: build stopped: subcommand failed.
__wpformatter | R11 wide case count lifetime splits same buffer/count interference graph; prologue15..23 constants/arguments now exact,67 remaining mostly num_chars25 and buffer pointer24 versus target24/25. This structural source-scope lever is real and compiles593/593/zero structural differences. Try assignment and readonly output boundaries next, declaration search last.
__wpformatter | R11 wide scan count separate, preserved as candidate | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 wide scan output pointer assigned before character count | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 wide count uses standard size type with signed comparisons | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 formatted output read through readonly buffer view | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
TMCJPEGDEC_decode_iquant | R11 declsearch #1: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #2: const TMCHuffmanEntry* ac_fast; / u8* huff_sym; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 32); first (33, ('lwz', 'r28, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 declsearch #3: s32 idx; / const TMCHuffmanEntry* ac_fast; / u8* huff_sym; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 47); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
__wpformatter | R11 scan end pointer confined to actual string conversion cases | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
TMCJPEGDEC_decode_iquant | R11 declsearch #4: u32* huff_tbl; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u8* huff_sym; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 32); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 declsearch #5: s32 bit_pos; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / u8* huff_sym; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 32); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 declsearch #6: u32 bit_data; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u8* huff_sym; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 32); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 declsearch #7: u32 tmp; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u8* huff_sym; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 36); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 declsearch #8: s32 r; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / u8* huff_sym; / s32 blk0; | 276/276 instructions; structural/exact (0, 32); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
__wpformatter | R11 field length and formatted pointer declared together after buffer | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
TMCJPEGDEC_decode_iquant | R11 declsearch #9: s32 blk0; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / u8* huff_sym; | 276/276 instructions; structural/exact (0, 34); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 declsearch #10: u8* huff_sym; / s32 idx; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 45); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
iplSDChannelTitle_flushSaveBeforeExit | R11 page stored through named manager page reference | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
TMCJPEGDEC_decode_iquant | R11 declsearch #11: u8* huff_sym; / u32* huff_tbl; / s32 idx; / const TMCHuffmanEntry* ac_fast; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 45); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #12: u8* huff_sym; / s32 bit_pos; / s32 idx; / u32* huff_tbl; / const TMCHuffmanEntry* ac_fast; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 45); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
__wpformatter | R11 field length declaration directly follows formatted pointer | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
TMCJPEGDEC_decode_iquant | R11 declsearch #13: u8* huff_sym; / u32 bit_data; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / const TMCHuffmanEntry* ac_fast; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 45); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #14: u8* huff_sym; / u32 tmp; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / const TMCHuffmanEntry* ac_fast; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 49); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #15: u8* huff_sym; / s32 r; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / const TMCHuffmanEntry* ac_fast; / s32 blk0; | 276/276 instructions; structural/exact (0, 45); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #16: u8* huff_sym; / s32 blk0; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / const TMCHuffmanEntry* ac_fast; | 276/276 instructions; structural/exact (0, 47); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #17: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 idx; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #18: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 bit_pos; / u32* huff_tbl; / s32 idx; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #19: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32 bit_data; / u32* huff_tbl; / s32 bit_pos; / s32 idx; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #20: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32 tmp; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / s32 idx; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #21: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 r; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 idx; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #22: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 blk0; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 idx; | 276/276 instructions; structural/exact (0, 32); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #23: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / s32 bit_pos; / u32* huff_tbl; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #24: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32 bit_data; / s32 bit_pos; / u32* huff_tbl; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #25: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32 tmp; / s32 bit_pos; / u32 bit_data; / u32* huff_tbl; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #26: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / s32 r; / s32 bit_pos; / u32 bit_data; / u32 tmp; / u32* huff_tbl; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
iplSDChannelTitle_flushSaveBeforeExit | R11 current page readonly value captured before manager getter | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
TMCJPEGDEC_decode_iquant | R11 declsearch #27: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / s32 blk0; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / u32* huff_tbl; | 276/276 instructions; structural/exact (0, 32); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #28: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / u32 bit_data; / s32 bit_pos; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #29: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / u32 tmp; / u32 bit_data; / s32 bit_pos; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #30: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 r; / u32 bit_data; / u32 tmp; / s32 bit_pos; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #31: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 blk0; / u32 bit_data; / u32 tmp; / s32 r; / s32 bit_pos; | 276/276 instructions; structural/exact (0, 32); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #32: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 tmp; / u32 bit_data; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #33: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / s32 r; / u32 tmp; / u32 bit_data; / s32 blk0; | 276/276 instructions; structural/exact (0, 34); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #34: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / s32 blk0; / u32 tmp; / s32 r; / u32 bit_data; | 276/276 instructions; structural/exact (0, 36); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #35: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / s32 r; / u32 tmp; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #36: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / s32 blk0; / s32 r; / u32 tmp; | 276/276 instructions; structural/exact (0, 32); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #37: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 blk0; / s32 r; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #38: const TMCHuffmanEntry* ac_fast; / s32 idx; / u8* huff_sym; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 32); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 declsearch #39: const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / u8* huff_sym; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 32); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 declsearch #40: const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u8* huff_sym; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 32); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 declsearch #41: const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u8* huff_sym; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 32); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 declsearch #42: const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / u8* huff_sym; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 32); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
iplSDChannelTitle_flushSaveBeforeExit | R11 page setter helper with int input | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
TMCJPEGDEC_decode_iquant | R11 declsearch #43: const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / u8* huff_sym; / s32 blk0; | 276/276 instructions; structural/exact (0, 32); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 declsearch #44: const TMCHuffmanEntry* ac_fast; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; / u8* huff_sym; | 276/276 instructions; structural/exact (0, 32); first (33, ('lwz', 'r27, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 declsearch #45: u8* huff_sym; / s32 idx; / u32* huff_tbl; / const TMCHuffmanEntry* ac_fast; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 45); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #46: u8* huff_sym; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / const TMCHuffmanEntry* ac_fast; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 45); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #47: u8* huff_sym; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / const TMCHuffmanEntry* ac_fast; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 45); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #48: u8* huff_sym; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / const TMCHuffmanEntry* ac_fast; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 45); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #49: u8* huff_sym; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / const TMCHuffmanEntry* ac_fast; / s32 blk0; | 276/276 instructions; structural/exact (0, 45); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #50: u8* huff_sym; / s32 idx; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; / const TMCHuffmanEntry* ac_fast; | 276/276 instructions; structural/exact (0, 47); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #51: s32 idx; / u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 47); first (33, ('lwz', 'r28, 0x4a0(r23)'), ('lwz', 'r29, 0x4a0(r23)'))
TMCJPEGDEC_decode_iquant | R11 declsearch #52: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 bit_pos; / s32 idx; / u32 bit_data; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #53: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / s32 idx; / u32 tmp; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #54: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 idx; / s32 r; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch #55: u8* huff_sym; / const TMCHuffmanEntry* ac_fast; / u32* huff_tbl; / s32 bit_pos; / u32 bit_data; / u32 tmp; / s32 r; / s32 idx; / s32 blk0; | 276/276 instructions; structural/exact (0, 30); first (42, ('addi', 'r4, r25, 0x24'), ('addi', 'r7, r25, 0x24'))
TMCJPEGDEC_decode_iquant | R11 declsearch complete 55 evaluated real permutations; source unchanged.
iplSDChannelTitle_flushSaveBeforeExit | R11 page setter helper with const SDChannelTitle* input | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
iplSDChannelTitle_flushSaveBeforeExit | R11 heap first input of real flush helper | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
SOGetSockName | R11 apply newly proved SOOption lever: readonly view of response record, every response write through actual mutable request owner. Test reply and input read boundaries without const-changing public ABI. First remaining copy order #32..34 and all63instructions exact except ordering.
SOGetSockName | R11 response readonly view with all writes through owning request field | objdiff 96.666664; 63/63 instructions; structural/exact (2, 3); first (32, ('mr', 'r3, r28'), ('mr', 'r4, r27'))
SOGetSockName | R11 input address readonly view, output copy through public address owner | objdiff 96.349205; 63/63 instructions; structural/exact (2, 5); first (5, ('mr', 'r27, r4'), ('mr', 'r28, r3'))
SOGetSockName | R11 both request and address read views readonly, writes through mutable owners | objdiff 96.349205; 63/63 instructions; structural/exact (2, 5); first (5, ('mr', 'r27, r4'), ('mr', 'r28, r3'))
iplSDChannelTitle_flushSaveBeforeExit | R11 readonly System::Arg through actual getter helper formal boundary, default const reference/pointer; functions guarded to only this source and used only at final flush, no unrelated translation unit output can change. Local readonly Arg view before failed to affect IR alias boundaries.
iplSDChannelTitle_flushSaveBeforeExit | R11 reference readonly args formal for manager getter | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
iplSDChannelTitle_flushSaveBeforeExit | R11 reference readonly args formal for heap getter | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
iplSDChannelTitle_flushSaveBeforeExit | R11 reference readonly args formal for both getter | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
iplSDChannelTitle_flushSaveBeforeExit | R11 pointer readonly args formal for manager getter | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
iplSDChannelTitle_flushSaveBeforeExit | R11 pointer readonly args formal for heap getter | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
iplSDChannelTitle_flushSaveBeforeExit | R11 pointer readonly args formal for both getter | objdiff 98.5946; 37/37 instructions; structural/exact (2, 6); first (20, ('lis', 'r4, 0'), ('lis', 'r3, 0'))
__wpformatter | R11 real wide-scan candidate leading locals normalized for final declaration search | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #1: int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #2: int chars_written; / int num_chars; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #3: int field_width; / int chars_written; / int num_chars; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #4: const wchar_t* format_ptr; / int chars_written; / int field_width; / int num_chars; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 84); first (8, ('mr', 'r31, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #5: const wchar_t* curr_format; / int chars_written; / int field_width; / const wchar_t* format_ptr; / int num_chars; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 92); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #6: print_format format; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / int num_chars; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #7: print_format* fmt_ptr; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / int num_chars; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #8: signed long long_num; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / int num_chars; | 593/593 instructions; structural/exact (0, 104); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #9: int num_chars; / int field_width; / int chars_written; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #10: int num_chars; / const wchar_t* format_ptr; / int field_width; / int chars_written; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 84); first (8, ('mr', 'r31, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #11: int num_chars; / const wchar_t* curr_format; / int field_width; / const wchar_t* format_ptr; / int chars_written; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 84); first (12, ('li', 'r29, 0'), ('li', 'r31, 0'))
__wpformatter | R11 declsearch #12: int num_chars; / print_format format; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / int chars_written; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 92); first (8, ('mr', 'r31, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #13: int num_chars; / print_format* fmt_ptr; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / int chars_written; / signed long long_num; | 593/593 instructions; structural/exact (0, 92); first (8, ('mr', 'r31, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #14: int num_chars; / signed long long_num; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / int chars_written; | 593/593 instructions; structural/exact (0, 88); first (12, ('li', 'r28, 0'), ('li', 'r31, 0'))
__wpformatter | R11 declsearch #15: int num_chars; / int chars_written; / const wchar_t* format_ptr; / int field_width; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #16: int num_chars; / int chars_written; / const wchar_t* curr_format; / const wchar_t* format_ptr; / int field_width; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 84); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #17: int num_chars; / int chars_written; / print_format format; / const wchar_t* format_ptr; / const wchar_t* curr_format; / int field_width; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #18: int num_chars; / int chars_written; / print_format* fmt_ptr; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / int field_width; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #19: int num_chars; / int chars_written; / signed long long_num; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / int field_width; | 593/593 instructions; structural/exact (0, 96); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #20: int num_chars; / int chars_written; / int field_width; / const wchar_t* curr_format; / const wchar_t* format_ptr; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 84); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #21: int num_chars; / int chars_written; / int field_width; / print_format format; / const wchar_t* curr_format; / const wchar_t* format_ptr; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 84); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #22: int num_chars; / int chars_written; / int field_width; / print_format* fmt_ptr; / const wchar_t* curr_format; / print_format format; / const wchar_t* format_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 84); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #23: int num_chars; / int chars_written; / int field_width; / signed long long_num; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / const wchar_t* format_ptr; | 593/593 instructions; structural/exact (0, 87); first (8, ('mr', 'r28, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #24: int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / print_format format; / const wchar_t* curr_format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #25: int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / print_format* fmt_ptr; / print_format format; / const wchar_t* curr_format; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #26: int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / signed long long_num; / print_format format; / print_format* fmt_ptr; / const wchar_t* curr_format; | 593/593 instructions; structural/exact (0, 88); first (22, ('mr', 'r28, r3'), ('mr', 'r29, r3'))
__wpformatter | R11 declsearch #27: int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format* fmt_ptr; / print_format format; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #28: int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / signed long long_num; / print_format* fmt_ptr; / print_format format; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #29: int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / signed long long_num; / print_format* fmt_ptr; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #30: int chars_written; / int field_width; / int num_chars; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #31: int chars_written; / int field_width; / const wchar_t* format_ptr; / int num_chars; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #32: int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / int num_chars; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #33: int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / int num_chars; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #34: int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / int num_chars; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #35: int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; / int num_chars; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #36: int num_chars; / int field_width; / const wchar_t* format_ptr; / int chars_written; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 84); first (8, ('mr', 'r31, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #37: int num_chars; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / int chars_written; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 92); first (8, ('mr', 'r31, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #38: int num_chars; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / int chars_written; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 92); first (8, ('mr', 'r31, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #39: int num_chars; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / int chars_written; / signed long long_num; | 593/593 instructions; structural/exact (0, 92); first (8, ('mr', 'r31, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #40: int num_chars; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; / int chars_written; | 593/593 instructions; structural/exact (0, 104); first (8, ('mr', 'r31, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #41: int field_width; / int num_chars; / int chars_written; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #42: int num_chars; / int chars_written; / const wchar_t* format_ptr; / const wchar_t* curr_format; / int field_width; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #43: int num_chars; / int chars_written; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / int field_width; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #44: int num_chars; / int chars_written; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / int field_width; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #45: int num_chars; / int chars_written; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; / int field_width; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #46: const wchar_t* format_ptr; / int num_chars; / int chars_written; / int field_width; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 84); first (8, ('mr', 'r31, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #47: int num_chars; / const wchar_t* format_ptr; / int chars_written; / int field_width; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 84); first (8, ('mr', 'r31, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #48: int num_chars; / int chars_written; / int field_width; / const wchar_t* curr_format; / print_format format; / const wchar_t* format_ptr; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 84); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #49: int num_chars; / int chars_written; / int field_width; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / const wchar_t* format_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 84); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #50: int num_chars; / int chars_written; / int field_width; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; / signed long long_num; / const wchar_t* format_ptr; | 593/593 instructions; structural/exact (0, 96); first (8, ('mr', 'r28, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #51: const wchar_t* curr_format; / int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 92); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #52: int num_chars; / const wchar_t* curr_format; / int chars_written; / int field_width; / const wchar_t* format_ptr; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 92); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #53: int num_chars; / int chars_written; / const wchar_t* curr_format; / int field_width; / const wchar_t* format_ptr; / print_format format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 84); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #54: int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / print_format format; / print_format* fmt_ptr; / const wchar_t* curr_format; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #55: int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / print_format format; / print_format* fmt_ptr; / signed long long_num; / const wchar_t* curr_format; | 593/593 instructions; structural/exact (0, 88); first (22, ('mr', 'r28, r3'), ('mr', 'r29, r3'))
__wpformatter | R11 declsearch #56: print_format format; / int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #57: int num_chars; / print_format format; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #58: int num_chars; / int chars_written; / print_format format; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #59: int num_chars; / int chars_written; / int field_width; / print_format format; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format* fmt_ptr; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #60: int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format* fmt_ptr; / signed long long_num; / print_format format; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #61: print_format* fmt_ptr; / int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #62: int num_chars; / print_format* fmt_ptr; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #63: int num_chars; / int chars_written; / print_format* fmt_ptr; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #64: int num_chars; / int chars_written; / int field_width; / print_format* fmt_ptr; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #65: int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / print_format* fmt_ptr; / const wchar_t* curr_format; / print_format format; / signed long long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #66: signed long long_num; / int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; | 593/593 instructions; structural/exact (0, 104); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #67: int num_chars; / signed long long_num; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; | 593/593 instructions; structural/exact (0, 104); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #68: int num_chars; / int chars_written; / signed long long_num; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; | 593/593 instructions; structural/exact (0, 96); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #69: int num_chars; / int chars_written; / int field_width; / signed long long_num; / const wchar_t* format_ptr; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; | 593/593 instructions; structural/exact (0, 96); first (8, ('mr', 'r29, r5'), ('mr', 'r30, r5'))
__wpformatter | R11 declsearch #70: int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / signed long long_num; / const wchar_t* curr_format; / print_format format; / print_format* fmt_ptr; | 593/593 instructions; structural/exact (0, 88); first (22, ('mr', 'r28, r3'), ('mr', 'r29, r3'))
__wpformatter | R11 declsearch #71: int num_chars; / int chars_written; / int field_width; / const wchar_t* format_ptr; / const wchar_t* curr_format; / signed long long_num; / print_format format; / print_format* fmt_ptr; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch complete 71 evaluated real permutations; source unchanged.
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 animation bound direct readonly table-field reference without scalar copy | objdiff 96.53846; 221/221 instructions; structural/exact (3, 126); first (5, ('li', 'r16, 0'), ('li', 'r14, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 animation bounds and slots share readonly table owner view | objdiff 96.53846; 221/221 instructions; structural/exact (3, 126); first (5, ('li', 'r16, 0'), ('li', 'r14, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 const animation resource input alongside actual per-pane bound | objdiff 98.8914; 221/221 instructions; structural/exact (0, 46); first (58, ('li', 'r22, 0'), ('li', 'r21, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 readonly resource pointer passed to layout animation constructor | objdiff 99.86425; 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 readonly pointer to actual animation-count field across traversal | objdiff 96.53846; 221/221 instructions; structural/exact (3, 126); first (5, ('li', 'r16, 0'), ('li', 'r14, 0'))
iplSDChannelTitle_flushSaveBeforeExit | R11 remaining first globalbase3/4 and final manager/heap load ordering: test true member this input boundary instead of free-function scene parameter, guarded only to this file. Existing object fields/vtable unchanged; new ordinary inline saving helper, original C symbol retained.
__wpformatter | R11 wide scan uses actual output cursor directly instead of alias | objdiff 98.97977; 593/593 instructions; structural/exact (0, 113); first (4, ('li', 'r21, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 wide input cursor exported through its own output pointer view | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
iplSDChannelTitle_flushSaveBeforeExit | R11 member save helper inline with same source behavior | objdiff 98.54054; 37/37 instructions; structural/exact (4, 8); first (3, ('addi', 'r7, r1, 8'), ('addi', 'r7, r1, 0xc'))
__wpformatter | R11 wide count signed long with conversion counter unchanged | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 wide input length unsigned int promoted at signed precision comparison | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
iplSDChannelTitle_flushSaveBeforeExit | R11 reference owner helper save helper inline with same source behavior | objdiff 98.54054; 37/37 instructions; structural/exact (4, 8); first (3, ('addi', 'r7, r1, 8'), ('addi', 'r7, r1, 0xc'))
__wpformatter | R11 pascal wide string first character consumed in explicit pointer increment | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 wide count export after pointer snapshot with explicit return type | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 wide character pointer declaration precedes scan counter at real case boundary | objdiff 99.78921; 593/593 instructions; structural/exact (0, 24); first (393, ('lwz', 'r25, 0(r3)'), ('lwz', 'r24, 0(r3)'))
__wpformatter | R11 declaration search last on actual integer/double/buffer/output/fill variables; literals/data preserved and no statements permuted.
__wpformatter | R11 declsearch #1: signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #2: signed long long long_long_num; / signed long long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 91); first (117, ('lwz', 'r26, 0(r3)'), ('lwz', 'r28, 0(r3)'))
__wpformatter | R11 declsearch #3: long double long_double_num; / signed long long long_long_num; / signed long long_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 91); first (117, ('lwz', 'r26, 0(r3)'), ('lwz', 'r28, 0(r3)'))
__wpformatter | R11 declsearch #4: wchar_t buff[512]; / signed long long long_long_num; / long double long_double_num; / signed long long_num; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 91); first (117, ('lwz', 'r26, 0(r3)'), ('lwz', 'r28, 0(r3)'))
__wpformatter | R11 declsearch #5: wchar_t* buff_ptr; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / signed long long_num; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 91); first (117, ('lwz', 'r26, 0(r3)'), ('lwz', 'r28, 0(r3)'))
__wpformatter | R11 declsearch #6: const wchar_t* string_end; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / signed long long_num; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 91); first (117, ('lwz', 'r26, 0(r3)'), ('lwz', 'r28, 0(r3)'))
__wpformatter | R11 declsearch #7: wchar_t fill_char = ' '; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / signed long long_num; | 593/593 instructions; structural/exact (0, 91); first (117, ('lwz', 'r26, 0(r3)'), ('lwz', 'r28, 0(r3)'))
__wpformatter | R11 declsearch #8: signed long long_num; / long double long_double_num; / signed long long long_long_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #9: signed long long_num; / wchar_t buff[512]; / long double long_double_num; / signed long long long_long_num; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #10: signed long long_num; / wchar_t* buff_ptr; / long double long_double_num; / wchar_t buff[512]; / signed long long long_long_num; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #11: signed long long_num; / const wchar_t* string_end; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / signed long long long_long_num; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #12: signed long long_num; / wchar_t fill_char = ' '; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / signed long long long_long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #13: signed long long_num; / signed long long long_long_num; / wchar_t buff[512]; / long double long_double_num; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #14: signed long long_num; / signed long long long_long_num; / wchar_t* buff_ptr; / wchar_t buff[512]; / long double long_double_num; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #15: signed long long_num; / signed long long long_long_num; / const wchar_t* string_end; / wchar_t buff[512]; / wchar_t* buff_ptr; / long double long_double_num; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #16: signed long long_num; / signed long long long_long_num; / wchar_t fill_char = ' '; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / long double long_double_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #17: signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t* buff_ptr; / wchar_t buff[512]; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #18: signed long long_num; / signed long long long_long_num; / long double long_double_num; / const wchar_t* string_end; / wchar_t* buff_ptr; / wchar_t buff[512]; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #19: signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t fill_char = ' '; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t buff[512]; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #20: signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / const wchar_t* string_end; / wchar_t* buff_ptr; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #21: signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t fill_char = ' '; / const wchar_t* string_end; / wchar_t* buff_ptr; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #22: signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / wchar_t fill_char = ' '; / const wchar_t* string_end; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #23: signed long long long_long_num; / long double long_double_num; / signed long long_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 91); first (117, ('lwz', 'r26, 0(r3)'), ('lwz', 'r28, 0(r3)'))
__wpformatter | R11 declsearch #24: signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / signed long long_num; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 91); first (117, ('lwz', 'r26, 0(r3)'), ('lwz', 'r28, 0(r3)'))
__wpformatter | R11 declsearch #25: signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / signed long long_num; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 91); first (117, ('lwz', 'r26, 0(r3)'), ('lwz', 'r28, 0(r3)'))
__wpformatter | R11 declsearch #26: signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / signed long long_num; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 91); first (117, ('lwz', 'r26, 0(r3)'), ('lwz', 'r28, 0(r3)'))
__wpformatter | R11 declsearch #27: signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; / signed long long_num; | 593/593 instructions; structural/exact (0, 91); first (117, ('lwz', 'r26, 0(r3)'), ('lwz', 'r28, 0(r3)'))
__wpformatter | R11 declsearch #28: signed long long_num; / long double long_double_num; / wchar_t buff[512]; / signed long long long_long_num; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #29: signed long long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / signed long long long_long_num; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #30: signed long long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / signed long long long_long_num; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #31: signed long long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; / signed long long long_long_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #32: long double long_double_num; / signed long long_num; / signed long long long_long_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #33: signed long long_num; / signed long long long_long_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / long double long_double_num; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #34: signed long long_num; / signed long long long_long_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / long double long_double_num; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #35: signed long long_num; / signed long long long_long_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; / long double long_double_num; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #36: wchar_t buff[512]; / signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #37: signed long long_num; / wchar_t buff[512]; / signed long long long_long_num; / long double long_double_num; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #38: signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t buff[512]; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #39: signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t* buff_ptr; / const wchar_t* string_end; / wchar_t fill_char = ' '; / wchar_t buff[512]; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #40: wchar_t* buff_ptr; / signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #41: signed long long_num; / wchar_t* buff_ptr; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #42: signed long long_num; / signed long long long_long_num; / wchar_t* buff_ptr; / long double long_double_num; / wchar_t buff[512]; / const wchar_t* string_end; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #43: signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / const wchar_t* string_end; / wchar_t fill_char = ' '; / wchar_t* buff_ptr; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #44: const wchar_t* string_end; / signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #45: signed long long_num; / const wchar_t* string_end; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #46: signed long long_num; / signed long long long_long_num; / const wchar_t* string_end; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #47: signed long long_num; / signed long long long_long_num; / long double long_double_num; / const wchar_t* string_end; / wchar_t buff[512]; / wchar_t* buff_ptr; / wchar_t fill_char = ' '; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #48: wchar_t fill_char = ' '; / signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #49: signed long long_num; / wchar_t fill_char = ' '; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #50: signed long long_num; / signed long long long_long_num; / wchar_t fill_char = ' '; / long double long_double_num; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #51: signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t fill_char = ' '; / wchar_t buff[512]; / wchar_t* buff_ptr; / const wchar_t* string_end; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch #52: signed long long_num; / signed long long long_long_num; / long double long_double_num; / wchar_t buff[512]; / wchar_t fill_char = ' '; / wchar_t* buff_ptr; / const wchar_t* string_end; | 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 declsearch complete 52 evaluated real permutations; source unchanged.
__wpformatter | R11 confirmed best conversion/output declarations | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
Zi8MatchOEMdata | R11 continuation mirrors SOOption exact readonly input-view lever without cached-context extra instructions: read work fields through actual const typed view; state index writes through mutable owner. No raw offsets, fake casts or target metadata changes.
Zi8MatchOEMdata | R11 readonly work owner at field reads, mutable original index writes | objdiff 98.645836; 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 fallback indicator signed integer state matching index arithmetic | objdiff 98.645836; 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 comparison position signed index with existing signed length conditions | objdiff 98.645836; 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 saved OEM search index advanced using prefix updates | objdiff 98.645836; 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 search index lifetime starts only after work state reset | objdiff 94.00521; 196/192 instructions; structural/exact (10, 191); first (5, ('mr', 'r31, r1'), ('mr', 'r28, r3'))
__wpformatter | R11 retain case pointer-before-wide-count source order,24 register-only differences | objdiff 99.78921; 593/593 instructions; structural/exact (0, 24); first (393, ('lwz', 'r25, 0(r3)'), ('lwz', 'r24, 0(r3)'))
__wpformatter | R11 first remaining #393 narrow string pointer25 vs24; all other branches/scopes now exact593/593/frame4d0. Target narrow byte length25 and returned common charcount24 overlap opposite source local pointer25 and commoncount24. Split actual byte scan length from resulting character count; field semantics identical and no extra instruction required.
__wpformatter | R11 narrow byte scan count separate from resulting wide count pointer-first | objdiff 98.35582; 593/593 instructions; structural/exact (0, 169); first (4, ('li', 'r23, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 narrow byte scan size_t pointer-first | objdiff 98.35582; 593/593 instructions; structural/exact (0, 169); first (4, ('li', 'r23, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 narrow byte scan long pointer-first | objdiff 98.35582; 593/593 instructions; structural/exact (0, 169); first (4, ('li', 'r23, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 narrow byte scan count separate from resulting wide count length-first | objdiff 98.35582; 593/593 instructions; structural/exact (0, 169); first (4, ('li', 'r23, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 narrow byte scan size_t length-first | objdiff 98.35582; 593/593 instructions; structural/exact (0, 169); first (4, ('li', 'r23, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 narrow byte scan long length-first | objdiff 98.35582; 593/593 instructions; structural/exact (0, 169); first (4, ('li', 'r23, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 multibyte input uses distinct mbs_ptr name from wide input cursor | objdiff 99.78921; 593/593 instructions; structural/exact (0, 24); first (393, ('lwz', 'r25, 0(r3)'), ('lwz', 'r24, 0(r3)'))
__wpformatter | R11 multibyte input actual char argument type and distinct pointer declaration | objdiff 99.78921; 593/593 instructions; structural/exact (0, 24); first (393, ('lwz', 'r25, 0(r3)'), ('lwz', 'r24, 0(r3)'))
__wpformatter | R11 wide scan local count named independently from common field count | objdiff 99.78921; 593/593 instructions; structural/exact (0, 24); first (393, ('lwz', 'r25, 0(r3)'), ('lwz', 'r24, 0(r3)'))
__wpformatter | R11 va_arg wide pointer representation retained at multibyte call views | objdiff 99.78921; 593/593 instructions; structural/exact (0, 24); first (393, ('lwz', 'r25, 0(r3)'), ('lwz', 'r24, 0(r3)'))
__wpformatter | R11 string scan count scoped to complete wide or multibyte conversion case | objdiff 99.40135; 593/593 instructions; structural/exact (0, 67); first (175, ('mr', 'r24, r3'), ('mr', 'r25, r3'))
__wpformatter | R11 multibyte conversion character-count assignment separate from error predicate | objdiff 98.35582; 593/593 instructions; structural/exact (0, 169); first (4, ('li', 'r23, 0x20'), ('li', 'r20, 0x20'))
__wpformatter | R11 multibyte byte cursor and converted count share case-local variable before export | objdiff 98.01855; 593/593 instructions; structural/exact (2, 170); first (4, ('li', 'r28, 0x20'), ('li', 'r20, 0x20'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 declsearch #1: const char* forceName; / u32 animationCount; / u32 paneIndex = 0; | 221/221 instructions; structural/exact (0, 6); first (159, ('lwz', 'r22, 0x18(r20)'), ('lwz', 'r31, 0x18(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 declsearch #2: u32 animationCount; / const char* forceName; / u32 paneIndex = 0; | 221/221 instructions; structural/exact (0, 9); first (157, ('lwz', 'r22, 0x1c(r20)'), ('lwz', 'r23, 0x1c(r20)'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 declsearch #3: u32 paneIndex = 0; / u32 animationCount; / const char* forceName; | 221/221 instructions; structural/exact (0, 13); first (58, ('li', 'r23, 0'), ('li', 'r21, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 declsearch #4: const char* forceName; / u32 paneIndex = 0; / u32 animationCount; | 221/221 instructions; structural/exact (0, 10); first (58, ('li', 'r22, 0'), ('li', 'r21, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 declsearch #5: u32 animationCount; / u32 paneIndex = 0; / const char* forceName; | 221/221 instructions; structural/exact (0, 13); first (58, ('li', 'r22, 0'), ('li', 'r21, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 declsearch #6: u32 paneIndex = 0; / const char* forceName; / u32 animationCount; | 221/221 instructions; structural/exact (0, 13); first (58, ('li', 'r23, 0'), ('li', 'r21, 0'))
create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | R11 declsearch complete 6 evaluated real permutations; source unchanged.
R11 retain additional readable structural improvements: WP separate wide scan length at actual case-local pointer declaration,24 pure register differences instead98; OEM validation predecrement in right comparison operand,structural0 instead2 and47 GPR operands. No exact-count claim for these two candidates, data/pool unchanged. Full quick authority gate over all nine before commit. CDBCryptBuffer frame correction: actual target aligned subfic -0x1c0 (earlier logged200 was incorrect); first offset difference32, current119/119 otherwise.
__wpformatter | R11 minimal final diff keeps original leading grouped counters | objdiff 99.78921; 593/593 instructions; structural/exact (0, 24); first (393, ('lwz', 'r25, 0(r3)'), ('lwz', 'r24, 0(r3)'))

R11 WP/OEM minimal candidate gate before commit
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/MSL/src/MSL_Common/wprintf] pool: IDENTICAL
[libs/MSL/src/MSL_Common/wprintf] objdiff: code 6264/8636 data 836/836 functions 8/9 fuzzy 99.9421 linked code 0
[libs/MSL/src/MSL_Common/wprintf] instruction-exact functions: 8/9
[libs/MSL/src/MSL_Common/wprintf]   section .data size 680 match 100.0
[libs/MSL/src/MSL_Common/wprintf]   section .rodata size 8 match 100.0
[libs/MSL/src/MSL_Common/wprintf]   section .sdata2 size 8 match 100.0
[libs/MSL/src/MSL_Common/wprintf]   section .text size 8636 match 99.9421
[libs/MSL/src/MSL_Common/wprintf]   section extab size 56 match 100.0
[libs/MSL/src/MSL_Common/wprintf]   section extabindex size 84 match 100.0
[libs/MSL/src/MSL_Common/wprintf]   below 100: __wpformatter 99.78921
[libs/MSL/src/MSL_Common/wprintf] baseline: code 6264/8636 data 836 functions 8 fuzzy 99.7638
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] objdiff: code 208/976 data 60/60 functions 2/3 fuzzy 98.9344 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] instruction-exact functions: 2/3
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section .text size 976 match 98.934425
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section extab size 24 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section extabindex size 36 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   below 100: Zi8MatchOEMdata 98.645836
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] baseline: code 208/976 data 60 functions 2 fuzzy 98.2992
regressions vs baseline: 0
global matched_code_percent: 90.43582 -> 90.45171
global fuzzy_match_percent: 99.56501 -> 99.56576
global complete_code_percent: 70.30611 -> 70.30611
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
R11 source review: WP original leading declarations retained; only meaningful wide string scan count localized after pointer acquisition,98->24 pure GPR differences. OEM predecrement right operand restores target length-before-capacity instruction order,2->0 structural differences, remaining47 GPR colors; 97.83854->98.645836%. Neither is a new exact function. Both preserve all previous exact functions, pool/data sizes and bytes; no artificial declarations or header changes retained.

## R11 final completeness and ownership audit
libs/RevoEX/src/so/SOOption | before -> after instruction-exact 3/4 -> 4/4; objdiff code 816/1292 -> 1292/1292; data 0/0 -> 0/0.
EXACT SOGetInterfaceOpt | 100.0% | 4 compiled R11 source labels; target/source119 instructions and zero ctxdiff for SOOption.
Extent SOGetInterfaceOpt: 0x814B476C+0x1DC=0x814B4948, next SOSetInterfaceOpt at0x814B4948; no overlap and no size/address change.
src/keyboard/tiString | before -> after instruction-exact 41/42 -> 41/42; objdiff code 4632/5176 -> 4632/5176; data 288/288 -> 288/288.
OPEN inputChar__Q39textinput8tistring9DecolatedFw | 90.132355% | 3 distinct compiled R11 source labels (build failures excluded), 0 logged successful declaration evaluations | 125/136/frame30; mode3 original Hangul/literal converter counter helper and dead newline comparison remain unknown; no verified volatile reload.
Extent inputChar__Q39textinput8tistring9DecolatedFw: 0x81432CE4+0x220=0x81432F04, next confirmKana__Q39textinput8tistring9DecolatedFv at0x81432F04; no overlap and no size/address change.
src/keyboard/tiSignWindow | before -> after instruction-exact 55/56 -> 55/56; objdiff code 6300/7184 -> 6300/7184; data 3468/3468 -> 3468/3468.
OPEN create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | 99.86425% | 15 distinct compiled R11 source labels (build failures excluded), 6 logged successful declaration evaluations | 221/221/frame50; six bound/slot register operands22/31, first159, all local offsets, fields, branches, call and operand ordering exact.
Extent create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator: 0x81430E50+0x374=0x814311C4, next __dt__Q49textinput8keyboard10signwindow7AnmPaneFv at0x814311C4; no overlap and no size/address change.
libs/RevoEX/src/cdb/CDBRecord | before -> after instruction-exact 27/29 -> 27/29; objdiff code 5464/7076 -> 5464/7076; data 144/2640 -> 144/2640.
OPEN CDBCryptBuffer | 99.97479% | 3 distinct compiled R11 source labels (build failures excluded), 0 logged successful declaration evaluations | 119/119/aligned frame1c0; only three OSReport literal offsets32,75,95; original pool47 versus source19, first missing literal10; retained/unimplemented SDK API provenance uncertain, no speculative pool filler.
Extent CDBCryptBuffer: 0x8148D14C+0x1DC=0x8148D328, next CDBRecordEncrypt at0x8148D328; no overlap and no size/address change.
OPEN CDBRecordEncrypt | 99.19014% | 3 distinct compiled R11 source labels (build failures excluded), 0 logged successful declaration evaluations | 284/284/aligned frame400;44 descriptor/input/key/temporary/pool-base register operands, first8; all other structure exact.
Extent CDBRecordEncrypt: 0x8148D328+0x470=0x8148D798, next CDBRecordDecrypt at0x8148D798; no overlap and no size/address change.
libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32 | before -> after instruction-exact 0/1 -> 0/1; objdiff code 0/1104 -> 0/1104; data 0/0 -> 0/0.
OPEN TMCJPEGDEC_decode_iquant | 99.31159% | 3 distinct compiled R11 source labels (build failures excluded), 55 logged successful declaration evaluations | 276/276/frame50;30 cursor/threshold/bitcount and AC table/zigzag register operands, first42; all six aggregate local slots and branch/call/operand orders exact.
Extent TMCJPEGDEC_decode_iquant: 0x814F6BD4+0x450=0x814F7024, next __ct__Q44nw4r3snd6detail9AxManagerFv at0x814F7024; no overlap and no size/address change.
libs/RevoEX/src/so/SOBasic | before -> after instruction-exact 21/22 -> 21/22; objdiff code 3836/4088 -> 3836/4088; data 144/144 -> 144/144.
OPEN SOGetSockName | 96.666664% | 6 distinct compiled R11 source labels (build failures excluded), 0 logged successful declaration evaluations | 63/63/frame30; three memcpy input/destination load order differences32..34; no observed volatile reload.
Extent SOGetSockName: 0x814B33D0+0xFC=0x814B34CC, next SORecvFrom at0x814B34CC; no overlap and no size/address change.
libs/RVLMiddleware/eZiText/src/clib/zoemdata | before -> after instruction-exact 2/3 -> 2/3; objdiff code 208/976 -> 208/976; data 60/60 -> 60/60.
OPEN Zi8MatchOEMdata | 98.645836% | 15 distinct compiled R11 source labels (build failures excluded), 0 logged successful declaration evaluations | 192/192/frame40;47 parameter/index/fallback register operands; validation instruction order and all other structure exact.
Extent Zi8MatchOEMdata: 0x81484DFC+0x300=0x814850FC, next Zi8PrepareMatch at0x814850FC; no overlap and no size/address change.
src/scene/sdChannelTitle/iplSDChannelTitle | before -> after instruction-exact 68/69 -> 68/69; objdiff code 18476/18624 -> 18476/18624; data 1976/1976 -> 1976/1976.
OPEN iplSDChannelTitle_flushSaveBeforeExit | 98.5946% | 19 distinct compiled R11 source labels (build failures excluded), 0 logged successful declaration evaluations | 37/37/frame20; global argument base4 vs3 and heap/manager load order25..26,6 total differences; page/index offsets exact, const formal/getter/member experiments rejected.
Extent iplSDChannelTitle_flushSaveBeforeExit: 0x813E8A20+0x94=0x813E8AB4, next iplSDChannelTitle_rebootSystem at0x813E8AB4; no overlap and no size/address change.
libs/MSL/src/MSL_Common/wprintf | before -> after instruction-exact 8/9 -> 8/9; objdiff code 6264/8636 -> 6264/8636; data 836/836 -> 836/836.
OPEN __wpformatter | 99.78921% | 52 distinct compiled R11 source labels (build failures excluded), 123 logged successful declaration evaluations | 593/593/frame4d0;24 narrow input pointer/byte length register operands24/25, first393; all prior prologue/constants/args/buffer and wide scan homes nowexact.
Extent __wpformatter: 0x81607C20+0x944=0x81608564, next __wStringWrite at0x81608564; no overlap and no size/address change.
R11 123 compiled source-variation labels and 184 logged successful declaration-order evaluations; same-source confirmation labels are not counted toward the distinct >=3 audit. Every nine remaining open functions exceeds three actual source constructs; SOGetInterfaceOpt complete.
Four stale task SD functions were already exact on fresh origin/main before work; baseline is68/69, not64/69. No out-of-scope source edits, data symbol renames/extents, shared headers, inline asm, volatile, register keyword, forced sections/activity, artificial strings, padding or uninitialized values retained. All nine unit data metrics unchanged; CDB literal provenance remains the sole actual data gap. SOOption no owned data; target weak/linker-deduplicated data never suppressed.
Accepted source paths: libs/RevoEX/src/so/SOOption.c; libs/MSL/src/MSL_Common/wprintf.c; libs/RVLMiddleware/eZiText/src/clib/zoemdata.c. Source commits8f7f0036 andccd10864 both preceded by GATE PASS/correct DOL/0regressions/forbidden/readability. Whole-unit exact gains SOOption3/4->4/4 and476newmatchedcodebytes; WP/OEM remain fuzzy-only and are not counted as exact gains.
Final non-quick gate all nine follows; unit lines, SHA1 and GATE will be copied below.

R11 final register-only coverage check: CDBRecordEncrypt original seven leading scalar declarations have no initializers or stack aggregate dependencies; all284instructions and frame400 are structurally exact. Run declared-only search last after three const/lifetime/helper trials; OEM four real declarations rerun with per-permutation logger because earlier13-evaluation tool output logged only aggregate. No new source constructs or metadata will be invented.
CDBRecordEncrypt | R11 declsearch #1: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #2: CDBErr err; / CDBRecordFile* recordFile; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #3: u32 dataSize; / CDBErr err; / CDBRecordFile* recordFile; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
Zi8MatchOEMdata | R11 declsearch #1: ziWChar folded; / ziS32 index; / ziU32 position; / ziU32 fallback = 0; | 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 declsearch #2: ziS32 index; / ziWChar folded; / ziU32 position; / ziU32 fallback = 0; | 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R11 declsearch #4: u32 fileSize; / CDBErr err; / u32 dataSize; / CDBRecordFile* recordFile; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (6, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
Zi8MatchOEMdata | R11 declsearch #3: ziU32 position; / ziS32 index; / ziWChar folded; / ziU32 fallback = 0; | 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R11 declsearch #5: u32 cryptSize; / CDBErr err; / u32 dataSize; / u32 fileSize; / CDBRecordFile* recordFile; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
Zi8MatchOEMdata | R11 declsearch #4: ziU32 fallback = 0; / ziS32 index; / ziU32 position; / ziWChar folded; | 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 declsearch #5: ziWChar folded; / ziU32 position; / ziS32 index; / ziU32 fallback = 0; | 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R11 declsearch #6: u32 authenticatedSize; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / CDBRecordFile* recordFile; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
Zi8MatchOEMdata | R11 declsearch #6: ziWChar folded; / ziU32 fallback = 0; / ziU32 position; / ziS32 index; | 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 declsearch #7: ziWChar folded; / ziS32 index; / ziU32 fallback = 0; / ziU32 position; | 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R11 declsearch #7: int fileOffset; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / CDBRecordFile* recordFile; | 284/284 instructions; structural/exact (0, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
Zi8MatchOEMdata | R11 declsearch #8: ziS32 index; / ziU32 position; / ziWChar folded; / ziU32 fallback = 0; | 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 declsearch #9: ziS32 index; / ziU32 position; / ziU32 fallback = 0; / ziWChar folded; | 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R11 declsearch #8: CDBRecordFile* recordFile; / u32 dataSize; / CDBErr err; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
Zi8MatchOEMdata | R11 declsearch #10: ziWChar folded; / ziU32 position; / ziU32 fallback = 0; / ziS32 index; | 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 declsearch #11: ziU32 position; / ziWChar folded; / ziS32 index; / ziU32 fallback = 0; | 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R11 declsearch #9: CDBRecordFile* recordFile; / u32 fileSize; / u32 dataSize; / CDBErr err; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (6, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
Zi8MatchOEMdata | R11 declsearch #12: ziU32 fallback = 0; / ziWChar folded; / ziS32 index; / ziU32 position; | 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
CDBRecordEncrypt | R11 declsearch #10: CDBRecordFile* recordFile; / u32 cryptSize; / u32 dataSize; / u32 fileSize; / CDBErr err; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
Zi8MatchOEMdata | R11 declsearch #13: ziWChar folded; / ziU32 fallback = 0; / ziS32 index; / ziU32 position; | 192/192 instructions; structural/exact (0, 47); first (5, ('mr', 'r27, r3'), ('mr', 'r28, r3'))
Zi8MatchOEMdata | R11 declsearch complete 13 evaluated real permutations; source unchanged.
CDBRecordEncrypt | R11 declsearch #11: CDBRecordFile* recordFile; / u32 authenticatedSize; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / CDBErr err; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #12: CDBRecordFile* recordFile; / int fileOffset; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / CDBErr err; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #13: CDBRecordFile* recordFile; / CDBErr err; / u32 fileSize; / u32 dataSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (6, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #14: CDBRecordFile* recordFile; / CDBErr err; / u32 cryptSize; / u32 fileSize; / u32 dataSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (7, 51); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #15: CDBRecordFile* recordFile; / CDBErr err; / u32 authenticatedSize; / u32 fileSize; / u32 cryptSize; / u32 dataSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #16: CDBRecordFile* recordFile; / CDBErr err; / int fileOffset; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / u32 dataSize; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #17: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 cryptSize; / u32 fileSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (5, 49); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #18: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 authenticatedSize; / u32 cryptSize; / u32 fileSize; / int fileOffset; | 284/284 instructions; structural/exact (5, 49); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #19: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / int fileOffset; / u32 cryptSize; / u32 authenticatedSize; / u32 fileSize; | 284/284 instructions; structural/exact (5, 49); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #20: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 authenticatedSize; / u32 cryptSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #21: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / int fileOffset; / u32 authenticatedSize; / u32 cryptSize; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #22: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / int fileOffset; / u32 authenticatedSize; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #23: CDBErr err; / u32 dataSize; / CDBRecordFile* recordFile; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #24: CDBErr err; / u32 dataSize; / u32 fileSize; / CDBRecordFile* recordFile; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #25: CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / CDBRecordFile* recordFile; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #26: CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / CDBRecordFile* recordFile; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #27: CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; / CDBRecordFile* recordFile; | 284/284 instructions; structural/exact (0, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #28: CDBRecordFile* recordFile; / u32 dataSize; / u32 fileSize; / CDBErr err; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #29: CDBRecordFile* recordFile; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / CDBErr err; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #30: CDBRecordFile* recordFile; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / CDBErr err; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #31: CDBRecordFile* recordFile; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; / CDBErr err; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #32: u32 dataSize; / CDBRecordFile* recordFile; / CDBErr err; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #33: CDBRecordFile* recordFile; / CDBErr err; / u32 fileSize; / u32 cryptSize; / u32 dataSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #34: CDBRecordFile* recordFile; / CDBErr err; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / u32 dataSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #35: CDBRecordFile* recordFile; / CDBErr err; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; / u32 dataSize; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #36: u32 fileSize; / CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (6, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #37: CDBRecordFile* recordFile; / u32 fileSize; / CDBErr err; / u32 dataSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (6, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #38: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 cryptSize; / u32 authenticatedSize; / u32 fileSize; / int fileOffset; | 284/284 instructions; structural/exact (5, 49); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #39: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 cryptSize; / u32 authenticatedSize; / int fileOffset; / u32 fileSize; | 284/284 instructions; structural/exact (5, 49); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #40: u32 cryptSize; / CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #41: CDBRecordFile* recordFile; / u32 cryptSize; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #42: CDBRecordFile* recordFile; / CDBErr err; / u32 cryptSize; / u32 dataSize; / u32 fileSize; / u32 authenticatedSize; / int fileOffset; | 284/284 instructions; structural/exact (9, 53); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #43: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 authenticatedSize; / int fileOffset; / u32 cryptSize; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #44: u32 authenticatedSize; / CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #45: CDBRecordFile* recordFile; / u32 authenticatedSize; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #46: CDBRecordFile* recordFile; / CDBErr err; / u32 authenticatedSize; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #47: CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 authenticatedSize; / u32 fileSize; / u32 cryptSize; / int fileOffset; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #48: int fileOffset; / CDBRecordFile* recordFile; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; | 284/284 instructions; structural/exact (0, 50); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #49: CDBRecordFile* recordFile; / int fileOffset; / CDBErr err; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch #50: CDBRecordFile* recordFile; / CDBErr err; / int fileOffset; / u32 dataSize; / u32 fileSize; / u32 cryptSize; / u32 authenticatedSize; | 284/284 instructions; structural/exact (0, 44); first (8, ('lis', 'r31, 0'), ('lis', 'r25, 0'))
CDBRecordEncrypt | R11 declsearch complete 50 evaluated real permutations; source unchanged.

## R11 final completeness and ownership audit
libs/RevoEX/src/so/SOOption | before -> after instruction-exact 3/4 -> 4/4; objdiff code 816/1292 -> 1292/1292; data 0/0 -> 0/0.
EXACT SOGetInterfaceOpt | 100.0% | 4 compiled R11 source labels; target/source119 instructions and zero ctxdiff for SOOption.
Extent SOGetInterfaceOpt: 0x814B476C+0x1DC=0x814B4948, next SOSetInterfaceOpt at0x814B4948; no overlap and no size/address change.
src/keyboard/tiString | before -> after instruction-exact 41/42 -> 41/42; objdiff code 4632/5176 -> 4632/5176; data 288/288 -> 288/288.
OPEN inputChar__Q39textinput8tistring9DecolatedFw | 90.132355% | 3 distinct compiled R11 source labels (build failures excluded), 0 logged successful declaration evaluations | 125/136/frame30; mode3 original Hangul/literal converter counter helper and dead newline comparison remain unknown; no verified volatile reload.
Extent inputChar__Q39textinput8tistring9DecolatedFw: 0x81432CE4+0x220=0x81432F04, next confirmKana__Q39textinput8tistring9DecolatedFv at0x81432F04; no overlap and no size/address change.
src/keyboard/tiSignWindow | before -> after instruction-exact 55/56 -> 55/56; objdiff code 6300/7184 -> 6300/7184; data 3468/3468 -> 3468/3468.
OPEN create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator | 99.86425% | 15 distinct compiled R11 source labels (build failures excluded), 6 logged successful declaration evaluations | 221/221/frame50; six bound/slot register operands22/31, first159, all local offsets, fields, branches, call and operand ordering exact.
Extent create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator: 0x81430E50+0x374=0x814311C4, next __dt__Q49textinput8keyboard10signwindow7AnmPaneFv at0x814311C4; no overlap and no size/address change.
libs/RevoEX/src/cdb/CDBRecord | before -> after instruction-exact 27/29 -> 27/29; objdiff code 5464/7076 -> 5464/7076; data 144/2640 -> 144/2640.
OPEN CDBCryptBuffer | 99.97479% | 3 distinct compiled R11 source labels (build failures excluded), 0 logged successful declaration evaluations | 119/119/aligned frame1c0; only three OSReport literal offsets32,75,95; original pool47 versus source19, first missing literal10; retained/unimplemented SDK API provenance uncertain, no speculative pool filler.
Extent CDBCryptBuffer: 0x8148D14C+0x1DC=0x8148D328, next CDBRecordEncrypt at0x8148D328; no overlap and no size/address change.
OPEN CDBRecordEncrypt | 99.19014% | 3 distinct compiled R11 source labels (build failures excluded), 50 logged successful declaration evaluations | 284/284/aligned frame400;44 descriptor/input/key/temporary/pool-base register operands, first8; all other structure exact.
Extent CDBRecordEncrypt: 0x8148D328+0x470=0x8148D798, next CDBRecordDecrypt at0x8148D798; no overlap and no size/address change.
libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32 | before -> after instruction-exact 0/1 -> 0/1; objdiff code 0/1104 -> 0/1104; data 0/0 -> 0/0.
OPEN TMCJPEGDEC_decode_iquant | 99.31159% | 3 distinct compiled R11 source labels (build failures excluded), 55 logged successful declaration evaluations | 276/276/frame50;30 cursor/threshold/bitcount and AC table/zigzag register operands, first42; all six aggregate local slots and branch/call/operand orders exact.
Extent TMCJPEGDEC_decode_iquant: 0x814F6BD4+0x450=0x814F7024, next __ct__Q44nw4r3snd6detail9AxManagerFv at0x814F7024; no overlap and no size/address change.
libs/RevoEX/src/so/SOBasic | before -> after instruction-exact 21/22 -> 21/22; objdiff code 3836/4088 -> 3836/4088; data 144/144 -> 144/144.
OPEN SOGetSockName | 96.666664% | 6 distinct compiled R11 source labels (build failures excluded), 0 logged successful declaration evaluations | 63/63/frame30; three memcpy input/destination load order differences32..34; no observed volatile reload.
Extent SOGetSockName: 0x814B33D0+0xFC=0x814B34CC, next SORecvFrom at0x814B34CC; no overlap and no size/address change.
libs/RVLMiddleware/eZiText/src/clib/zoemdata | before -> after instruction-exact 2/3 -> 2/3; objdiff code 208/976 -> 208/976; data 60/60 -> 60/60.
OPEN Zi8MatchOEMdata | 98.645836% | 15 distinct compiled R11 source labels (build failures excluded), 13 logged successful declaration evaluations | 192/192/frame40;47 parameter/index/fallback register operands; validation instruction order and all other structure exact.
Extent Zi8MatchOEMdata: 0x81484DFC+0x300=0x814850FC, next Zi8PrepareMatch at0x814850FC; no overlap and no size/address change.
src/scene/sdChannelTitle/iplSDChannelTitle | before -> after instruction-exact 68/69 -> 68/69; objdiff code 18476/18624 -> 18476/18624; data 1976/1976 -> 1976/1976.
OPEN iplSDChannelTitle_flushSaveBeforeExit | 98.5946% | 19 distinct compiled R11 source labels (build failures excluded), 0 logged successful declaration evaluations | 37/37/frame20; global argument base4 vs3 and heap/manager load order25..26,6 total differences; page/index offsets exact, const formal/getter/member experiments rejected.
Extent iplSDChannelTitle_flushSaveBeforeExit: 0x813E8A20+0x94=0x813E8AB4, next iplSDChannelTitle_rebootSystem at0x813E8AB4; no overlap and no size/address change.
libs/MSL/src/MSL_Common/wprintf | before -> after instruction-exact 8/9 -> 8/9; objdiff code 6264/8636 -> 6264/8636; data 836/836 -> 836/836.
OPEN __wpformatter | 99.78921% | 52 distinct compiled R11 source labels (build failures excluded), 123 logged successful declaration evaluations | 593/593/frame4d0;24 narrow input pointer/byte length register operands24/25, first393; all prior prologue/constants/args/buffer and wide scan homes nowexact.
Extent __wpformatter: 0x81607C20+0x944=0x81608564, next __wStringWrite at0x81608564; no overlap and no size/address change.
R11 123 compiled source-variation labels and 247 logged successful declaration-order evaluations; same-source confirmation labels are not counted toward the distinct >=3 audit. Every nine remaining open functions exceeds three actual source constructs; SOGetInterfaceOpt complete.
Four stale task SD functions were already exact on fresh origin/main before work; baseline is68/69, not64/69. No out-of-scope source edits, data symbol renames/extents, shared headers, inline asm, volatile, register keyword, forced sections/activity, artificial strings, padding or uninitialized values retained. All nine unit data metrics unchanged; CDB literal provenance remains the sole actual data gap. SOOption no owned data; target weak/linker-deduplicated data never suppressed.
Accepted source paths: libs/RevoEX/src/so/SOOption.c; libs/MSL/src/MSL_Common/wprintf.c; libs/RVLMiddleware/eZiText/src/clib/zoemdata.c. Source commits8f7f0036 andccd10864 both preceded by GATE PASS/correct DOL/0regressions/forbidden/readability. Whole-unit exact gains SOOption3/4->4/4 and476newmatchedcodebytes; WP/OEM remain fuzzy-only and are not counted as exact gains.
Final non-quick gate all nine follows; unit lines, SHA1 and GATE will be copied below.

## R11 final full clean non-quick gate over all nine units
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/so/SOOption] pool: IDENTICAL
[libs/RevoEX/src/so/SOOption] objdiff: code 1292/1292 data None/None functions 4/4 fuzzy 100.0000 linked code 0
[libs/RevoEX/src/so/SOOption] instruction-exact functions: 4/4
[libs/RevoEX/src/so/SOOption]   section .text size 1292 match 100.0
[libs/RevoEX/src/so/SOOption] baseline: code 816/1292 data None functions 3 fuzzy 99.9226
[src/keyboard/tiString] pool: IDENTICAL
[src/keyboard/tiString] objdiff: code 4632/5176 data 288/288 functions 41/42 fuzzy 98.9629 linked code 0
[src/keyboard/tiString] instruction-exact functions: 41/42
[src/keyboard/tiString]   section .data size 288 match 100.0
[src/keyboard/tiString]   section .text size 5176 match 98.962906
[src/keyboard/tiString]   below 100: inputChar__Q39textinput8tistring9DecolatedFw 90.132355
[src/keyboard/tiString] baseline: code 4632/5176 data 288 functions 41 fuzzy 98.9629
[src/keyboard/tiSignWindow] pool: IDENTICAL
[src/keyboard/tiSignWindow] objdiff: code 6300/7184 data 3468/3468 functions 55/56 fuzzy 99.9833 linked code 0
[src/keyboard/tiSignWindow] instruction-exact functions: 55/56
[src/keyboard/tiSignWindow]   section .ctors size 4 match 100.0
[src/keyboard/tiSignWindow]   section .data size 2672 match 100.0
[src/keyboard/tiSignWindow]   section .rodata size 784 match 100.0
[src/keyboard/tiSignWindow]   section .sdata size 8 match 100.0
[src/keyboard/tiSignWindow]   section .text size 7184 match 99.9833
[src/keyboard/tiSignWindow]   below 100: create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator 99.86425
[src/keyboard/tiSignWindow] baseline: code 6300/7184 data 3468 functions 55 fuzzy 99.9833
[libs/RevoEX/src/cdb/CDBRecord] pool: DIVERGES at string 10 (mine=19 orig=47)
[libs/RevoEX/src/cdb/CDBRecord] objdiff: code 5464/7076 data 144/2640 functions 27/29 fuzzy 99.8683 linked code 0
[libs/RevoEX/src/cdb/CDBRecord] instruction-exact functions: 27/29
[libs/RevoEX/src/cdb/CDBRecord]   section .bss size 128 match 100.0
[libs/RevoEX/src/cdb/CDBRecord]   section .data size 2496 match 52.795387
[libs/RevoEX/src/cdb/CDBRecord]   section .rodata size 16 match 100.0
[libs/RevoEX/src/cdb/CDBRecord]   section .text size 7076 match 99.868286
[libs/RevoEX/src/cdb/CDBRecord]   below 100: CDBCryptBuffer 99.97479
[libs/RevoEX/src/cdb/CDBRecord]   below 100: CDBRecordEncrypt 99.19014
[libs/RevoEX/src/cdb/CDBRecord] baseline: code 5464/7076 data 144 functions 27 fuzzy 99.8683
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] objdiff: code None/1104 data None/None functions 0/1 fuzzy 99.3116 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] instruction-exact functions: 0/1
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   section .text size 1104 match 99.31159
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32]   below 100: TMCJPEGDEC_decode_iquant 99.31159
[libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32] baseline: code None/1104 data None functions 0 fuzzy 99.3116
[libs/RevoEX/src/so/SOBasic] pool: IDENTICAL
[libs/RevoEX/src/so/SOBasic] objdiff: code 3836/4088 data 144/144 functions 21/22 fuzzy 99.7945 linked code 0
[libs/RevoEX/src/so/SOBasic] instruction-exact functions: 21/22
[libs/RevoEX/src/so/SOBasic]   section .bss size 40 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .data size 88 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .sbss size 8 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .sdata size 8 match 100.0
[libs/RevoEX/src/so/SOBasic]   section .text size 4088 match 99.79452
[libs/RevoEX/src/so/SOBasic]   below 100: SOGetSockName 96.666664
[libs/RevoEX/src/so/SOBasic] baseline: code 3836/4088 data 144 functions 21 fuzzy 99.7945
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] objdiff: code 208/976 data 60/60 functions 2/3 fuzzy 98.9344 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] instruction-exact functions: 2/3
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section .text size 976 match 98.934425
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section extab size 24 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section extabindex size 36 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   below 100: Zi8MatchOEMdata 98.645836
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] baseline: code 208/976 data 60 functions 2 fuzzy 98.2992
[src/scene/sdChannelTitle/iplSDChannelTitle] pool: IDENTICAL
[src/scene/sdChannelTitle/iplSDChannelTitle] objdiff: code 18476/18624 data 1976/1976 functions 68/69 fuzzy 99.9888 linked code 0
[src/scene/sdChannelTitle/iplSDChannelTitle] instruction-exact functions: 68/69
[src/scene/sdChannelTitle/iplSDChannelTitle]   section .data size 1696 match 100.0
[src/scene/sdChannelTitle/iplSDChannelTitle]   section .rodata size 48 match 100.0
[src/scene/sdChannelTitle/iplSDChannelTitle]   section .sdata size 192 match 100.0
[src/scene/sdChannelTitle/iplSDChannelTitle]   section .sdata2 size 40 match 100.0
[src/scene/sdChannelTitle/iplSDChannelTitle]   section .text size 18624 match 99.98883
[src/scene/sdChannelTitle/iplSDChannelTitle]   below 100: iplSDChannelTitle_flushSaveBeforeExit 98.5946
[src/scene/sdChannelTitle/iplSDChannelTitle] baseline: code 18476/18624 data 1976 functions 68 fuzzy 99.9888
[libs/MSL/src/MSL_Common/wprintf] pool: IDENTICAL
[libs/MSL/src/MSL_Common/wprintf] objdiff: code 6264/8636 data 836/836 functions 8/9 fuzzy 99.9421 linked code 0
[libs/MSL/src/MSL_Common/wprintf] instruction-exact functions: 8/9
[libs/MSL/src/MSL_Common/wprintf]   section .data size 680 match 100.0
[libs/MSL/src/MSL_Common/wprintf]   section .rodata size 8 match 100.0
[libs/MSL/src/MSL_Common/wprintf]   section .sdata2 size 8 match 100.0
[libs/MSL/src/MSL_Common/wprintf]   section .text size 8636 match 99.9421
[libs/MSL/src/MSL_Common/wprintf]   section extab size 56 match 100.0
[libs/MSL/src/MSL_Common/wprintf]   section extabindex size 84 match 100.0
[libs/MSL/src/MSL_Common/wprintf]   below 100: __wpformatter 99.78921
[libs/MSL/src/MSL_Common/wprintf] baseline: code 6264/8636 data 836 functions 8 fuzzy 99.7638
regressions vs baseline: 0
global matched_code_percent: 90.43582 -> 90.45171
global fuzzy_match_percent: 99.56501 -> 99.56576
global complete_code_percent: 70.30611 -> 70.30611
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
Final closeout declaration searches restored byte-for-byte committed sources: CDBEncrypt0/44 after50evals, OEM0/47 after13evals; no source changes after clean gate. Refreshed exact-name object report and whole-unit instruction count audit confirm identical final metrics. Clean gate remains the final full authority; no shared header/config edits retained, no code/data regressions, no forbidden/readability additions.
R11 final sources/commits: SOOption.c8f7f0036; wprintf.c+zoemdata.cccd10864; fz3.attempts.md bookkeeping commit follows. All9remaining functions have >=3 compiled source attempts and explicit first-difference/extent evidence above. CDBmissing28literal provenance and original tiString converter helper remain uncertain; no false completion or data-filler claims.
