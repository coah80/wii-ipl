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
