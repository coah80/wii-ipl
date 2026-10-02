# data-d3 attempts

Scope: data only. Applied unslop to the log and final report. No instruction-count gain is required for a data-only improvement; instruction-exact counts must not decrease.
Base: eecf16f0, identical to fetched origin/main.

iplSetting: initial instruction-exact 105/112. Initial pool identical.
iplUSBAP: initial instruction-exact 4/4. Initial pool identical.
AOSS: initial instruction-exact 15/21. Initial pool identical.
ATERM: initial instruction-exact 14/26. Initial pool identical.

## Relocation identity evidence

AOSS
lbl_81698C74 => s_accessPointConfig via AOSSi_Init+0xa4,AOSSi_Init+0xb8,AOSSi_Init+0xf8
lbl_81698C70 => s_accessPointList via AOSSi_Init+0xbc,AOSSi_Init+0xd0,AOSSi_Init+0x110
lbl_81698C8C => s_responseBuffer via AOSSi_Init+0xe8,AOSSi_Init+0x13c,AOSSSendDiscoveryRequest+0x14
lbl_81697200 => s_socket via AOSSi_Init+0x174
lbl_81698C88 => s_socketStarted via AOSSi_Init+0x184,AOSSi_Init+0x194,AOSSConnectAndAwaitHost+0x44
lbl_81697204 => s_manufacturer via AOSSHandleDiscoverReply+0x40,AOSSHandleDiscoverReply+0x54,AOSSHandleAuthReply+0x4c
lbl_81698C84 => s_errorCode via AOSSHandleDiscoverReply+0x110,AOSSHandleDiscoverReply+0x134,AOSSHandleDiscoverReply+0x184
lbl_81698C80 => s_connectionState via AOSSHandleDiscoverReply+0x1b8
lbl_81698C78 => s_accessPointName via AOSSCheckAccessPointName+0x8,AOSSCheckAccessPointName+0x1c,AOSSCheckAccessPointName+0x98
ATERM
lbl_81698CDC => gAtermCancelRequested via ATERMScanAccessPoints+0x148,ATERMi_ApConfigStart+0xe8,ATERMi_ApConfigEnd+0x30
lbl_81698C90 => gAtermState via ATERMi_ApConfigStart+0x18,ATERMi_ApConfigStart+0x44,ATERMi_ApConfigStart+0xb0
lbl_8169721C => gAtermScanLimit via ATERMi_ApConfigStart+0x40
lbl_81698C98 => gAtermProgressCallback via ATERMi_ApConfigStart+0x48,ATERMi_ApConfigStart+0x15c,ATERMi_ApConfigEnd+0x1d0
lbl_81698C9C => gAtermAllocate via ATERMi_ApConfigStart+0x4c
lbl_81698CA0 => gAtermRelease via ATERMi_ApConfigStart+0x50,ATERMi_ApConfigEnd+0x14c
lbl_81697220 => gAtermScanBufferSize via ATERMi_ApConfigStart+0x54,ATERMi_ApConfigStart+0x80
lbl_81698CA4 => gAtermAllocation via ATERMi_ApConfigStart+0x64,ATERMi_ApConfigEnd+0x140,ATERMi_ApConfigEnd+0x15c
lbl_81698C94 => gAtermResult via ATERMi_ApConfigStart+0x78,ATERMi_ApConfigStart+0x154,ATERMi_ApConfigEnd+0x1c8
lbl_81697218 => gAtermDeadline via ATERMi_ApConfigStart+0xf4,ATERMi_ApConfigStart+0x104,ATERMi_ApConfigStart+0x148
lbl_81698CA8 => gAtermThreadStarted via ATERMi_ApConfigStart+0x180,ATERMi_ApConfigEnd+0x1c,ATERMi_ApConfigEnd+0x168
iplSetting
lbl_816970E9 => @25504 via prepare__Q33ipl5scene7SettingFv+0xe8,prepare__Q33ipl5scene7SettingFv+0x118,prepare__Q33ipl5scene7SettingFv+0x148
lbl_816970ED => @25507 via prepare__Q33ipl5scene7SettingFv+0x178
lbl_816970F1 => @25617 via create__Q33ipl5scene7SettingFv+0x60
lbl_816970F6 => @25619 via create__Q33ipl5scene7SettingFv+0xc8,create__Q33ipl5scene7SettingFv+0x11c,create__Q33ipl5scene7SettingFv+0x1b4
lbl_816970FA => @25626 via create__Q33ipl5scene7SettingFv+0x1c4
lbl_81697101 => @25627 via create__Q33ipl5scene7SettingFv+0x1e0
lbl_81697010 => sSettingArrowNames__Q23ipl5scene via create__Q33ipl5scene7SettingFv+0x48c,initScroll__Q33ipl5scene7SettingFv+0x26c,initScroll__Q33ipl5scene7SettingFv+0x2f8
lbl_81694C1C => @25796 via updateController___Q33ipl5scene7SettingFv+0x64,updateController___Q33ipl5scene7SettingFv+0x1a8
lbl_8169716E => @26352 via calcFadeout__Q33ipl5scene7SettingFv+0x1d0
lbl_8169718C => @26851 via initProxy__Q33ipl5scene7SettingFv+0x5c,initMTU__Q33ipl5scene7SettingFv+0x34
lbl_816971B1 => @27556 via initScroll__Q33ipl5scene7SettingFv+0x28,initScroll__Q33ipl5scene7SettingFv+0x144
lbl_816971B7 => @27557 via initScroll__Q33ipl5scene7SettingFv+0x50,initScroll__Q33ipl5scene7SettingFv+0x16c
lbl_816971BD => @27558 via initScroll__Q33ipl5scene7SettingFv+0x78,initScroll__Q33ipl5scene7SettingFv+0x194
lbl_816971C3 => @27559 via initScroll__Q33ipl5scene7SettingFv+0xa0,initScroll__Q33ipl5scene7SettingFv+0x1bc
lbl_8169719F => @27405 via initScroll__Q33ipl5scene7SettingFv+0xc8,initScroll__Q33ipl5scene7SettingFv+0x1e4
lbl_816971AB => @27407 via initScroll__Q33ipl5scene7SettingFv+0xf0,initScroll__Q33ipl5scene7SettingFv+0x20c,start_trig_event__Q33ipl5scene7SettingFPCc+0x200
lbl_816971C9 => @27560 via initScroll__Q33ipl5scene7SettingFv+0x2d0,initScroll__Q33ipl5scene7SettingFv+0x374
lbl_816971A5 => @27406 via start_trig_event__Q33ipl5scene7SettingFPCc+0x1b4
lbl_816971D0 => @27862 via validateEULA___Q33ipl5scene7SettingFv+0xa0,validateEULA___Q33ipl5scene7SettingFv+0x104
lbl_816971D4 => @28152 via makeErrorMessage__Q33ipl5scene7SettingFv+0x78,makeSupportCode__Q33ipl5scene7SettingFv+0x54
lbl_81694C38 => @28153 via makeErrorMessage__Q33ipl5scene7SettingFv+0x150,makeErrorMessage__Q33ipl5scene7SettingFv+0x1b8
lbl_81697101 => @25626 via waitStart__Q33ipl5scene7SettingFv+0x34,waitFinish__Q33ipl5scene7SettingFv+0x28


## Initial data audit

- iplSetting: .data raw bytes identical, but extracted symbols combine unrelated literals and pointer arrays, and the retail Setting vtable's 252-byte symbol includes deduplicated weak vtables. Source has 104-byte Setting, 92-byte PaneManager, 24-byte EventHandler and 32-byte Interface vtables. No size edits to mask this. .rodata has one real title-ID initializer mismatch and two missing 20-byte digit tables. Other small sections differ only in trailing linker alignment or symbol identity.
- iplUSBAP: all bytes in the common section extents agree. usbapNickname source is 22 bytes versus the extracted 24-byte extent. The target copies 20 nickname bytes, so the two extra target bytes may be linker alignment; do not enlarge the buffer without further evidence.
- AOSS: all raw data bytes agree. .sbss identities are proven by relocations in instruction-exact functions. Source symbol enumeration differs from target enumeration; objdiff pairs unrelated anonymous globals. Rename only proven target symbols, preserving every byte and size.
- ATERM: all raw bytes agree, including the digest initializer at .data+0xd8. .data consists of compiler-generated switch tables and that initializer; differences are relocation destinations from nonexact functions. .sbss pairs anonymous globals by the wrong enumeration order. gAtermSelectedBssid is six bytes in an eight-byte extracted extent; no unsupported enlargement.

## AOSS accepted candidate

Renamed nine anonymous target data symbols using exact-function relocation identity. No addresses, sizes, splits or section bytes changed. .sbss increased from 42.857143% to 100%; matched_data 3896 -> 3928. Every non-text section is 100%. Existing five code mismatches remain outside this data assignment.

## iplSetting title IDs, attempt 1

Corrected the initializer's region 5 and 6 entries from slots 6 and 7 to slots 5 and 6, matching the 96 retail bytes. Source instructions unchanged. Data score unchanged because symbol pairing excludes this initializer. This is a real runtime correction, not an objdiff score trick.

## ATERM relocation identities, attempt 1

Named proven globals without altering any address or size. Exact ATERMi_ApConfigStart/End relocations prove state, result, allocation, callbacks and thread-started identities. ATERMi_AutoConfigThread proves socket-started at .sbss+0x24 and socket-ready at +0x20. ATERMBuildAssociationRequest relocations prove address buffer at +0x38. RunConfigProtocol target uses state at +0x40 throughout, response mode at +0x34 in receive calls, message length at +0x28, reply length at +0x2c and byte mode at +0x30, matching the same roles and source definitions. MD5Update calls reference the 64-byte .data+0xd8 initializer starting with 0x80, proving gAtermDigestFill. Target relocations at .text+0x1f8a/0x1fae correspond to source +0x1f96/0x1fc6. Bytes and total size unchanged.

## iplUSBAP nickname, attempt 1

Restored the UTF16 nickname object's 24-byte target extent as wchar_t[12]. The prior wchar_t[11] was 22 bytes. Target symbol usbapNickname has a distinct 24-byte allocation; only the first 20 bytes are copied by registration. This changes no instruction or following object offset and adds no dummy object.

## ATERM selected address, attempt 2

Restored the selected-BSSID storage's eight-byte target allocation as u8[8], retaining all six-byte MAC copies. Named it using ATERMDiscoverAccessPoints and BuildAssociationRequest relocations. No subsequent offsets change. .sbss is now 100%, matched_data 18504 -> 18584; instruction-exact remains 14/26. The full quick gate passed with zero regressions and the correct DOL hash.

## iplSetting digit tables, attempts 1 and 2

1. Added the two real ten-element UTF16 digit tables from retail .rodata+0x258 and +0x26c as static const wchar_t. MWCC removed both unreferenced internal tables; output remained 600 bytes.
2. Gave the same typed const objects external linkage so MWCC emits their proven data without forced sections or force-active entries. Target symbol names are scNumber and scNumber2 in namespace ipl::scene.

## iplSetting table identity and definition order, attempt 3

Named the three genuine pointer arrays at .data+0, +0x10 and +0x28 using create/initAP/redrawAP relocations and each table's pointed-to text. Their element counts and target sizes agree, with no size changes. Target relocations +0x6f76/+0x6f7e and source +0x701a/+0x7022 reference the four AP-button names; +0x6c5e/+0x6c6a and source +0x6cfa/+0x6d06 reference the six AP-text names; +0x67b6/+0x67ba and source +0x6846/+0x684a reference the six AP-number names. Reordered browserScrollDirection after the two existing Setting buffer definitions so the actual .sbss symbol offsets become 0, 4, 8 in target order. Named its target using updateScroll's load/store roles. All target addresses, sizes and totals remain unchanged.

Digit tables with external linkage emit at the exact target offsets 0x258 and 0x26c. The complete 640 .rodata bytes now agree, including the corrected title IDs. Score is 38.50412%, so the remaining cause is symbol/relocation partitioning rather than missing bytes.

## Required source-level rounds on all remaining functions

Each trial is compiled independently after the pool check. Only an exact-function gain with no lost instruction-exact functions or matched data can be retained. Three distinct declaration/control-expression trials per remaining function; failed candidates are restored.
createBrowser__Q33ipl5scene7SettingFv attempt 1: readonly mem1 allocation size; source 019fbd2fcb18; objdiff 98.8505%; instructions 299/301, diffs 114; unit exact 105; data 1040/5696.
createBrowser__Q33ipl5scene7SettingFv attempt 2: readonly mem2 allocation size; source 4b07d3801ad0; objdiff 98.8505%; instructions 299/301, diffs 114; unit exact 105; data 1040/5696.
createBrowser__Q33ipl5scene7SettingFv attempt 3: readonly mem1 heap pointer; source b2b32e5fe6d8; objdiff 98.8505%; instructions 299/301, diffs 114; unit exact 105; data 1040/5696.
draw__Q33ipl5scene7SettingFv attempt 1: reverse independent declarations u32 left;,u32 top;,u32 width;; source 52a11cf5440e; objdiff 91.52215%; instructions 595/632, diffs 570; unit exact 105; data 1040/5696.
draw__Q33ipl5scene7SettingFv attempt 2: rotate independent declarations u32 left;,u32 top;,u32 width;; source c3c6cea18781; objdiff 91.52057%; instructions 595/632, diffs 570; unit exact 105; data 1040/5696.
draw__Q33ipl5scene7SettingFv attempt 3: swap first independent declarations u32 left;,u32 top;,u32 width;; source 6848b182e5f8; objdiff 91.523735%; instructions 595/632, diffs 570; unit exact 105; data 1040/5696.
initKeyboard__Q33ipl5scene7SettingFPCc attempt 1: swap independent row/string limits; source f522f2f506e7; objdiff 98.07981%; instructions 215/213, diffs 195; unit exact 105; data 1040/5696.
initKeyboard__Q33ipl5scene7SettingFPCc attempt 2: readonly product area; source ba8ec44cca9c; objdiff 98.38498%; instructions 215/213, diffs 195; unit exact 105; data 1040/5696.
initKeyboard__Q33ipl5scene7SettingFPCc attempt 3: move invalid input declaration after limits; source 85624a719bc3; objdiff 97.99531%; instructions 215/213, diffs 195; unit exact 105; data 1040/5696.
calcKeyboard__Q33ipl5scene7SettingFv attempt 1: initialize selected form text; source 9e80dfbbf396; objdiff 98.0%; instructions 292/290, diffs 258; unit exact 105; data 1040/5696.
calcKeyboard__Q33ipl5scene7SettingFv attempt 2: readonly form identifiers; source 61ea4d9a22ca; objdiff 98.0%; instructions 292/290, diffs 258; unit exact 105; data 1040/5696.
calcKeyboard__Q33ipl5scene7SettingFv attempt 3: explicit pressOK comparison; source 118553a6ca4d; objdiff 98.0%; instructions 292/290, diffs 258; unit exact 105; data 1040/5696.
convertRevIP__Q33ipl5scene7SettingFPUcPCc attempt 1: reverse independent declarations char ascii[20];,int count = 0;,int index;; source a756d29859a8; objdiff 98.15069%; instructions 73/73, diffs 21; unit exact 105; data 1040/5696.
convertRevIP__Q33ipl5scene7SettingFPUcPCc attempt 2: rotate independent declarations char ascii[20];,int count = 0;,int index;; source 6bdcf9862666; objdiff 98.69863%; instructions 73/73, diffs 16; unit exact 105; data 1040/5696.
convertRevIP__Q33ipl5scene7SettingFPUcPCc attempt 3: swap first independent declarations char ascii[20];,int count = 0;,int index;; source 358ff4860b8a; objdiff 98.69863%; instructions 73/73, diffs 16; unit exact 105; data 1040/5696.
scanAP__Q33ipl5scene7SettingFv attempt 1: readonly animation index; source dee07bb51a23; objdiff 95.39338%; instructions 266/272, diffs 160; unit exact 105; data 1040/5696.
scanAP__Q33ipl5scene7SettingFv attempt 2: implicit count test; source 8accc6a48be9; objdiff 95.39338%; instructions 266/272, diffs 160; unit exact 105; data 1040/5696.
scanAP__Q33ipl5scene7SettingFv attempt 3: negated zero offset test; source 2580f28a59e6; objdiff 95.39338%; instructions 266/272, diffs 160; unit exact 105; data 1040/5696.
AOSS_Init_old attempt 1: reverse independent declarations s16 initialWait;,u64 tickRemainder;,AOSSReceiveBuffer* packetBuffer;; source 5c30692bda4a; objdiff 93.78725%; instructions 1575/1584, diffs 1524; unit exact 15; data 3928/3928.
AOSS_Init_old attempt 2: rotate independent declarations s16 initialWait;,u64 tickRemainder;,AOSSReceiveBuffer* packetBuffer;; source 7351eb86a582; objdiff 93.78725%; instructions 1575/1584, diffs 1524; unit exact 15; data 3928/3928.
AOSS_Init_old attempt 3: swap first independent declarations s16 initialWait;,u64 tickRemainder;,AOSSReceiveBuffer* packetBuffer;; source 706a211f5578; objdiff 93.78725%; instructions 1575/1584, diffs 1524; unit exact 15; data 3928/3928.
AOSSDecryptMessage attempt 1: reverse independent declarations u8* decryptedData;,u32 controlFlags;,u32 dataLength;; source f7b3ac943a8c; objdiff 97.3676%; instructions 321/321, diffs 113; unit exact 15; data 3928/3928.
AOSSDecryptMessage attempt 2: rotate independent declarations u8* decryptedData;,u32 controlFlags;,u32 dataLength;; source 7ffd1478855d; objdiff 97.3676%; instructions 321/321, diffs 113; unit exact 15; data 3928/3928.
AOSSDecryptMessage attempt 3: swap first independent declarations u8* decryptedData;,u32 controlFlags;,u32 dataLength;; source fec2235f89c3; objdiff 97.74143%; instructions 321/321, diffs 89; unit exact 15; data 3928/3928.
AOSSApplyAuthOptions attempt 1: reverse independent declarations AOSSConfigRecord* configRecord;,AOSSStoredConfig* wep40Config;,AOSSStoredConfig* wep104Config;; source 95a9300215fa; objdiff 98.59649%; instructions 114/114, diffs 26; unit exact 15; data 3928/3928.
AOSSApplyAuthOptions attempt 2: rotate independent declarations AOSSConfigRecord* configRecord;,AOSSStoredConfig* wep40Config;,AOSSStoredConfig* wep104Config;; source bf6d81c0ba25; objdiff 98.77193%; instructions 114/114, diffs 22; unit exact 15; data 3928/3928.
AOSSApplyAuthOptions attempt 3: swap first independent declarations AOSSConfigRecord* configRecord;,AOSSStoredConfig* wep40Config;,AOSSStoredConfig* wep104Config;; source f1a515f52069; objdiff 98.77193%; instructions 114/114, diffs 22; unit exact 15; data 3928/3928.
AOSSSendHelloRequest attempt 1: reverse independent declarations u32 checksum;,u16 nonce;,u32 stateLength;; source d059ca65aa5d; objdiff 92.190475%; instructions 271/273, diffs 254; unit exact 15; data 3928/3928.
AOSSSendHelloRequest attempt 2: rotate independent declarations u32 checksum;,u16 nonce;,u32 stateLength;; source a7659e25e005; objdiff 92.190475%; instructions 271/273, diffs 254; unit exact 15; data 3928/3928.
AOSSSendHelloRequest attempt 3: swap first independent declarations u32 checksum;,u16 nonce;,u32 stateLength;; source 844865b1bcd2; objdiff 92.190475%; instructions 271/273, diffs 254; unit exact 15; data 3928/3928.
AOSSXorBufferWithKey attempt 1: reverse independent declarations u8* packetHalf;,s32 round;,u8* keyMask;; source f82af7feda7f; objdiff 98.29932%; instructions 147/147, diffs 44; unit exact 15; data 3928/3928.
AOSSXorBufferWithKey attempt 2: rotate independent declarations u8* packetHalf;,s32 round;,u8* keyMask;; source 41287dd9e01e; objdiff 98.061226%; instructions 147/147, diffs 50; unit exact 15; data 3928/3928.
AOSSXorBufferWithKey attempt 3: swap first independent declarations u8* packetHalf;,s32 round;,u8* keyMask;; source e19bed9fdc58; objdiff 98.23129%; instructions 147/147, diffs 45; unit exact 15; data 3928/3928.
ATERMStartNetworkStack attempt 1: reverse independent declarations int status;,int waitCount = 0;,u32 convertedHost;; source 23d42a536d39; objdiff 97.91558%; instructions 154/154, diffs 51; unit exact 14; data 18584/18864.
ATERMStartNetworkStack attempt 2: rotate independent declarations int status;,int waitCount = 0;,u32 convertedHost;; source 347ce0ac1c10; objdiff 97.91558%; instructions 154/154, diffs 51; unit exact 14; data 18584/18864.
ATERMStartNetworkStack attempt 3: swap first independent declarations int status;,int waitCount = 0;,u32 convertedHost;; source ba2fac154a72; objdiff 97.91558%; instructions 154/154, diffs 51; unit exact 14; data 18584/18864.
ATERMFindChangedApRecord attempt 1: reverse independent declarations u32 previousIndex;,u32 currentIndex = 0;,int found = 0;; source 6206e4449cb5; objdiff 99.02299%; instructions 174/174, diffs 31; unit exact 14; data 18584/18864.
ATERMFindChangedApRecord attempt 2: rotate independent declarations u32 previousIndex;,u32 currentIndex = 0;,int found = 0;; source 4d6f8c454685; objdiff 99.56896%; instructions 174/174, diffs 15; unit exact 14; data 18584/18864.
ATERMFindChangedApRecord attempt 3: swap first independent declarations u32 previousIndex;,u32 currentIndex = 0;,int found = 0;; source 479cf7027f9d; objdiff 99.56896%; instructions 174/174, diffs 15; unit exact 14; data 18584/18864.
ATERMDiscoverAccessPoints attempt 1: reverse independent declarations s32 result = -1;,u32 scanBufferBytes;,u32 recordIndex;; source 38bdcd667907; objdiff 95.304184%; instructions 261/263, diffs 221; unit exact 14; data 18584/18864.
ATERMDiscoverAccessPoints attempt 2: rotate independent declarations s32 result = -1;,u32 scanBufferBytes;,u32 recordIndex;; source cf149ff96201; objdiff 95.304184%; instructions 261/263, diffs 221; unit exact 14; data 18584/18864.
ATERMDiscoverAccessPoints attempt 3: swap first independent declarations s32 result = -1;,u32 scanBufferBytes;,u32 recordIndex;; source fa4d3117c7a2; objdiff 95.304184%; instructions 261/263, diffs 221; unit exact 14; data 18584/18864.
ATERMBuildEncryptedMessage attempt 1: reverse independent declarations u8* end;,u8* cursor;,u32 checksum = 0;; source 9d1d353a8172; objdiff 98.072914%; instructions 96/96, diffs 28; unit exact 14; data 18584/18864.
ATERMBuildEncryptedMessage attempt 2: rotate independent declarations u8* end;,u8* cursor;,u32 checksum = 0;; source c8cbce624a1a; objdiff 98.072914%; instructions 96/96, diffs 28; unit exact 14; data 18584/18864.
ATERMBuildEncryptedMessage attempt 3: swap first independent declarations u8* end;,u8* cursor;,u32 checksum = 0;; source f0f6bbeb6b04; objdiff 99.791664%; instructions 96/96, diffs 4; unit exact 14; data 18584/18864.
ATERMBuildAssociationRequest attempt 1: reverse independent declarations u8 scanAddress[8];,u8 interfaceMacAddress[8];,char interfaceMacText[32];; source f5a4706f525e; objdiff 93.3609%; instructions 133/133, diffs 79; unit exact 14; data 18584/18864.
ATERMBuildAssociationRequest attempt 2: rotate independent declarations u8 scanAddress[8];,u8 interfaceMacAddress[8];,char interfaceMacText[32];; source ab3c0949359b; objdiff 93.3609%; instructions 133/133, diffs 79; unit exact 14; data 18584/18864.
ATERMBuildAssociationRequest attempt 3: swap first independent declarations u8 scanAddress[8];,u8 interfaceMacAddress[8];,char interfaceMacText[32];; source 4ba94c960472; objdiff 93.3609%; instructions 133/133, diffs 79; unit exact 14; data 18584/18864.
ATERMParseAssociationResponse attempt 1: reverse independent declarations u8* optionValue;,u16* responseEnd;,u32 optionType;; source ce08a2035d61; objdiff 98.9781%; instructions 137/137, diffs 26; unit exact 14; data 18584/18864.
ATERMParseAssociationResponse attempt 2: rotate independent declarations u8* optionValue;,u16* responseEnd;,u32 optionType;; source 504def96220c; objdiff 98.90511%; instructions 137/137, diffs 28; unit exact 14; data 18584/18864.
ATERMParseAssociationResponse attempt 3: swap first independent declarations u8* optionValue;,u16* responseEnd;,u32 optionType;; source e8f37744718f; objdiff 99.014595%; instructions 137/137, diffs 25; unit exact 14; data 18584/18864.
ATERMRunConfigProtocol attempt 1: reverse independent declarations u8 digestLength[8];,s32 socket = 0;,s32 result = -5;; source 79f186c37484; objdiff 87.43323%; instructions 972/951, diffs 946; unit exact 14; data 18584/18864.
ATERMRunConfigProtocol attempt 2: rotate independent declarations u8 digestLength[8];,s32 socket = 0;,s32 result = -5;; source 89e99ad28a12; objdiff 87.43323%; instructions 972/951, diffs 946; unit exact 14; data 18584/18864.
ATERMRunConfigProtocol attempt 3: swap first independent declarations u8 digestLength[8];,s32 socket = 0;,s32 result = -5;; source e938c8fda52f; objdiff 87.43323%; instructions 972/951, diffs 946; unit exact 14; data 18584/18864.
ATERMi_AutoConfigThread attempt 1: swap independent final-state declarations; source 2765e2a67e64; objdiff 94.75%; instructions 40/40, diffs 3; unit exact 14; data 18584/18864.
ATERMi_AutoConfigThread attempt 2: readonly protocol return; source 16e2c983b7db; objdiff 94.75%; instructions 40/40, diffs 3; unit exact 14; data 18584/18864.
ATERMi_AutoConfigThread attempt 3: implicit socket-started test; source 841ec1376692; objdiff 94.75%; instructions 40/40, diffs 3; unit exact 14; data 18584/18864.
ATERMAesKeyWrap attempt 1: reverse independent declarations u32 initialValue[2];,u8* outputBlock;,s32 blockOffset;; source 85b71a968e5f; objdiff 99.0%; instructions 117/117, diffs 20; unit exact 14; data 18584/18864.
ATERMAesKeyWrap attempt 2: rotate independent declarations u32 initialValue[2];,u8* outputBlock;,s32 blockOffset;; source 1b43fa7e9bd2; objdiff 99.0%; instructions 117/117, diffs 20; unit exact 14; data 18584/18864.
ATERMAesKeyWrap attempt 3: swap first independent declarations u32 initialValue[2];,u8* outputBlock;,s32 blockOffset;; source ed2e22983183; objdiff 99.0%; instructions 117/117, diffs 20; unit exact 14; data 18584/18864.
ATERMAesExpandEncryptKey attempt 1: reverse independent declarations u32 keyWord;,u32 fourthWord;,u32 firstWord;; source 61b1be054e4c; objdiff 98.94403%; instructions 268/268, diffs 49; unit exact 14; data 18584/18864.
ATERMAesExpandEncryptKey attempt 2: rotate independent declarations u32 keyWord;,u32 fourthWord;,u32 firstWord;; source 4cf5bc24589b; objdiff 98.94403%; instructions 268/268, diffs 49; unit exact 14; data 18584/18864.
ATERMAesExpandEncryptKey attempt 3: swap first independent declarations u32 keyWord;,u32 fourthWord;,u32 firstWord;; source 6615e5cd1f74; objdiff 98.94403%; instructions 268/268, diffs 49; unit exact 14; data 18584/18864.
ATERMMd5Update attempt 1: reverse independent declarations u32 bytesToFill;,u32 copiedBytes;,u32 index;; source fd011eb98c20; objdiff 91.263885%; instructions 139/144, diffs 115; unit exact 14; data 18584/18864.
ATERMMd5Update attempt 2: rotate independent declarations u32 bytesToFill;,u32 copiedBytes;,u32 index;; source 35afeb8baa9e; objdiff 91.263885%; instructions 139/144, diffs 115; unit exact 14; data 18584/18864.
ATERMMd5Update attempt 3: swap first independent declarations u32 bytesToFill;,u32 copiedBytes;,u32 index;; source 56d167f0051a; objdiff 91.263885%; instructions 139/144, diffs 115; unit exact 14; data 18584/18864.

## Final open-function coverage

createBrowser__Q33ipl5scene7SettingFv: 98.8505% remains after 3 distinct compiled source trials. No partial trial retained.
draw__Q33ipl5scene7SettingFv: 91.525314% remains after 3 distinct compiled source trials. No partial trial retained.
initKeyboard__Q33ipl5scene7SettingFPCc: 98.38498% remains after 3 distinct compiled source trials. No partial trial retained.
calcKeyboard__Q33ipl5scene7SettingFv: 98.0% remains after 3 distinct compiled source trials. No partial trial retained.
convertRevIP__Q33ipl5scene7SettingFPUcPCc: 98.69863% remains after 3 distinct compiled source trials. No partial trial retained.
scanAP__Q33ipl5scene7SettingFv: 95.39338% remains after 3 distinct compiled source trials. No partial trial retained.
AOSS_Init_old: 93.78725% remains after 3 distinct compiled source trials. No partial trial retained.
AOSSDecryptMessage: 97.74143% remains after 3 distinct compiled source trials. No partial trial retained.
AOSSApplyAuthOptions: 98.77193% remains after 3 distinct compiled source trials. No partial trial retained.
AOSSSendHelloRequest: 92.190475% remains after 3 distinct compiled source trials. No partial trial retained.
AOSSXorBufferWithKey: 98.605446% remains after 3 distinct compiled source trials. No partial trial retained.
ATERMStartNetworkStack: 97.91558% remains after 3 distinct compiled source trials. No partial trial retained.
ATERMFindChangedApRecord: 99.56896% remains after 3 distinct compiled source trials. No partial trial retained.
ATERMDiscoverAccessPoints: 95.304184% remains after 3 distinct compiled source trials. No partial trial retained.
ATERMBuildEncryptedMessage: 99.791664% remains after 3 distinct compiled source trials. No partial trial retained.
ATERMBuildAssociationRequest: 93.44361% remains after 3 distinct compiled source trials. No partial trial retained.
ATERMParseAssociationResponse: 99.56204% remains after 3 distinct compiled source trials. No partial trial retained.
ATERMRunConfigProtocol: 87.43323% remains after 3 distinct compiled source trials. No partial trial retained.
ATERMi_AutoConfigThread: 94.75% remains after 3 distinct compiled source trials. No partial trial retained.
ATERMAesKeyWrap: 99.0% remains after 3 distinct compiled source trials. No partial trial retained.
ATERMAesExpandEncryptKey: 98.94403% remains after 3 distinct compiled source trials. No partial trial retained.
ATERMMd5Update: 91.263885% remains after 3 distinct compiled source trials. No partial trial retained.
Every remaining nonexact function has three compiled trials. Both completed data units remain complete; unresolved data needs the evidence review below.

## iplSetting browser page initializers, attempt 4

A normalized relocation audit found seven real .rodata pointer mismatches that the raw-byte comparison missed. The final region-page entry at .rodata+0x188 must be Setup/ScreenSave.html. The seven direct-page names at +0x18c must be Calendar, Display, Sound, Parental_Control, Internet, Wiiconnect24, Update. Source incorrectly put Calendar in the region pages and duplicated Update in the direct pages. Corrected these ordinary literal initializers without changing either array's count or pool order. All 60 .rodata relocations now agree after resolving section-relative destinations. All 640 raw bytes agree. Objdiff .rodata is now 100%, matched_data 1040 -> 1680. Code scores and instruction-exact counts are unchanged.

This audit supersedes the earlier suggestion that symbol partitioning alone explained the .rodata score. Relocation destinations must be checked as well as raw bytes.

## Remaining data sections

- iplSetting .data: 4016 raw bytes agree, but 104 normalized relocation entries differ. Of these, 73 are switch-table destinations in nonexact initKeyboard, calcKeyboard and scanAP. The other 31 are emitted weak PaneManager/EventHandler/Interface vtable slots where the original DOL extraction has zero bytes and no relocations. Original Setting's 252-byte symbol covers its actual 104-byte vtable plus those 148 deduplicated weak bytes. No target symbol sizes were changed, no tables were replaced with assembly, and no dummy objects were added. The 31 weak slots are the allowed extraction exception; the 73 switch entries are genuine remaining differences. Each affecting function has three distinct compiled attempts above.
- ATERM .data: 280 raw bytes agree, but all 11 entries of the RunConfigProtocol switch table at .data+0xac differ in function-relative destinations. The first 43 jump-table entries agree, and the real 64-byte digest initializer agrees. RunConfigProtocol is 972 instructions versus 951 target instructions. Three declaration-order trials did not reduce this mismatch. It needs code matching before this section can reach 100%.
- iplUSBAP and AOSS: every reported non-text section is 100%, and matched_data equals total_data.
- extab/extabindex: absent in both original and source for all four units. No unmatched exception tables are omitted from this audit.

No split boundaries or symbol sizes changed. Naming corrections only affect the four assigned units. All three-trial candidates were restored; no fuzzy code edits were retained. The data goal is not complete for iplSetting or ATERM.

## ATERM allocation audit and correction

The first full gate passed, but a fresh physical-layout audit found that u8[8] made MWCC align gAtermSelectedBssid to eight bytes. It moved the object from target .sbss+0x44 to +0x48, moved cancellation from +0x4c to +0x50 and grew .sbss from 80 to 84 bytes. Objdiff still reported .sbss 100% because it matched named objects independently of placement. That score was insufficient evidence; the eight-byte source allocation is reverted.

Three further compiled layout trials were rejected:
1. A typed union with a six-byte address and two-word view still occupied +0x48 and grew the section to 84 bytes.
2. u8[8] with ATTRIBUTE_ALIGN(4) still occupied +0x48 and grew the section to 84 bytes.
3. u8[8] with prefix __declspec(align(4)) still occupied +0x48 and grew the section to 84 bytes.

The final source retains the original six-byte MAC object at +0x44 and cancellation at +0x4c. .sbss is exactly 80 zero bytes, and every physical object start agrees with the target. The target's eight-byte symbol extent appears to include two bytes of inter-object alignment. I did not shrink its symbol or add padding to force the score. Final .sbss score is 94.80519%, matched_data remains 18504, and ATERM's data goal remains incomplete. This supersedes the earlier claimed .sbss completion and 18584 matched_data result. No alignment attributes or union trial remain in the source.

## Final full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 30760/37884 data 1680/5696 functions 106/112 fuzzy 99.1581 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 105/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 6.807248
[src/scene/setting/iplSetting]   section .rodata size 640 match 100.0
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 99.15806
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 98.8505
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.525314
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 98.38498
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 98.0
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.69863
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 95.39338
[src/scene/setting/iplSetting] baseline: code 30760/37884 data 1040 functions 106 fuzzy 99.1581
[src/scene/setting/iplUSBAP] pool: IDENTICAL
[src/scene/setting/iplUSBAP] objdiff: code 988/988 data 4984/4984 functions 4/4 fuzzy 100.0000 linked code 988
[src/scene/setting/iplUSBAP] instruction-exact functions: 4/4
[src/scene/setting/iplUSBAP]   section .bss size 4944 match 100.0
[src/scene/setting/iplUSBAP]   section .data size 16 match 100.0
[src/scene/setting/iplUSBAP]   section .sbss size 24 match 100.0
[src/scene/setting/iplUSBAP]   section .text size 988 match 100.0
[src/scene/setting/iplUSBAP] baseline: code 988/988 data 40 functions 4 fuzzy 100.0000
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 9296/19204 data 18504/18864 functions 15/26 fuzzy 96.5836 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 14/26
[src/scene/setting/ATERM]   section .bss size 8160 match 100.0
[src/scene/setting/ATERM]   section .data size 280 match 22.857143
[src/scene/setting/ATERM]   section .rodata size 10280 match 100.0
[src/scene/setting/ATERM]   section .sbss size 80 match 94.80519
[src/scene/setting/ATERM]   section .sdata size 56 match 100.0
[src/scene/setting/ATERM]   section .sdata2 size 8 match 100.0
[src/scene/setting/ATERM]   section .text size 19204 match 96.583626
[src/scene/setting/ATERM]   below 100: ATERMStartNetworkStack 97.91558
[src/scene/setting/ATERM]   below 100: ATERMFindChangedApRecord 99.56896
[src/scene/setting/ATERM]   below 100: ATERMDiscoverAccessPoints 95.304184
[src/scene/setting/ATERM]   below 100: ATERMBuildEncryptedMessage 99.791664
[src/scene/setting/ATERM]   below 100: ATERMBuildAssociationRequest 93.44361
[src/scene/setting/ATERM]   below 100: ATERMParseAssociationResponse 99.56204
[src/scene/setting/ATERM]   below 100: ATERMRunConfigProtocol 87.43323
[src/scene/setting/ATERM]   below 100: ATERMi_AutoConfigThread 94.75
[src/scene/setting/ATERM]   below 100: ATERMAesKeyWrap 99.0
[src/scene/setting/ATERM]   below 100: ATERMAesExpandEncryptKey 98.94403
[src/scene/setting/ATERM]   below 100: ATERMMd5Update 91.263885
[src/scene/setting/ATERM] baseline: code 9296/19204 data 18504 functions 15 fuzzy 96.5836
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 6436/16192 data 3928/3928 functions 16/21 fuzzy 96.7779 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 15/21
[src/scene/setting/AOSS]   section .bss size 3496 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 100.0
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 96.777916
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 93.78725
[src/scene/setting/AOSS]   below 100: AOSSDecryptMessage 97.74143
[src/scene/setting/AOSS]   below 100: AOSSApplyAuthOptions 98.77193
[src/scene/setting/AOSS]   below 100: AOSSSendHelloRequest 92.190475
[src/scene/setting/AOSS]   below 100: AOSSXorBufferWithKey 98.605446
[src/scene/setting/AOSS] baseline: code 6436/16192 data 3896 functions 16 fuzzy 96.7779
regressions vs baseline: 0
global matched_code_percent: 88.52293 -> 88.52293
global fuzzy_match_percent: 99.44739 -> 99.44739
global complete_code_percent: 62.78043 -> 62.78043
global matched_data_percent: 93.05085 -> 93.35729
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```

Before -> after: iplSetting data 1040 -> 1680, instruction-exact 105 -> 105, code 30760 -> 30760; iplUSBAP data 40 -> 4984, instruction-exact 4 -> 4, code 988 -> 988; ATERM data 18504 -> 18504, instruction-exact 14 -> 14, code 9296 -> 9296; AOSS data 3896 -> 3928, instruction-exact 15 -> 15, code 6436 -> 6436.
Net data gain 5616 bytes. All 22 remaining nonexact functions have three distinct compiled source trials. USBAP and AOSS data goals are complete. iplSetting .data and ATERM .data/.sbss remain open.
