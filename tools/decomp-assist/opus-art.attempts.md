# opus-art: prior-art port attempts (library units)

| unit | symbol | sources found | result |
|------|--------|---------------|--------|
| libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL | NHTTPi_strnicmp | yannicksuter/mscharged-decomp src/RVL_SDK/nhttp/NHTTP_stdlib_RVL.c (+ configure note: NHTTP exact under GC/3.0a5 only); InusualZ/mhtri-decomp src/NHTTP/d_nhttp.c (non-matching there) | 2 -> 0. mscharged source alone stays at 2 under 3.0a5.2; our old int-helper source stays at 2 under 3.0a5; mscharged source + `mw_version="GC/3.0a5"` = exact. |
| libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL | NHTTPi_compareToken | same | 2 -> 0, same fix. Unit fully exact, flipped to Matching, DOL SHA1 unchanged. Using a `LowerCase()` helper instead of the literal ternaries regresses (2 / 17 differing). |
| libs/RevoEX/src/net/aes | AESiEncryptBlock | none (searched AESiEncryptBlock, NETiAESEncryptoBlock, AESiRoundKeyRcon0, NET_AES_BLOCK_MODE_CBC, NETAESCreate: only symbol maps in riptl/wii-symbols and a WiiLink patch header) | no change; GC/3.0a5, 3.0a3.4, 3.0a3 give the same score |
| libs/RevoEX/src/net/aes | AESiDecryptBlock | none (same searches) | no change; same compiler sweep |
| libs/RVL_SDK/src/kbd/kbd_lib | kbdProcMod | headers only (DarkRTA/rb3 kbd.h, galaxymaster2007/THPConv kbd.h); robojumper/sdk_2009-12-11 has kpr_lib.c but no kbd_lib.c | no change (4 differing); compiler sweep no effect |
| libs/RVL_SDK/src/kbd/kbd_lib | kbd_led_handler | same | 3 differing; if/else, `err = 7; if (success == TRUE)`, reordered switch cases give 13-23 (worse); compiler sweep no effect |
| libs/RVL_SDK/src/kbd/kbd_lib | KBDSetModState | same | no change (4 differing) |
| libs/RVL_SDK/src/fa/driver/sd_drv | pfd_sddrv_init / pfd_sddrv_finalize / pfd_sddrv_build_fat32_mbr_bpb | ACreTeam/cf-decomp has only sd_drv.h (VF variant) and nand_drv.c (nanddrv_init/finalize: different body, saved to _refs/prior) | no portable code; compiler sweep no effect |
| libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var | TMCJPEGDEC_IdctBlock_Lumi / _Col | none outside upstream | no change; compiler sweep no effect |
| libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 | TMCJPEGDEC_set_converterRGBA8 / TMCJPEGDEC_converterYUV411toRGBA8 | none outside upstream | no change; compiler sweep no effect |
| libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main | TMCJPEGDEC_err_restart (asm PLACEHOLDER) | none outside upstream | still asm |
| libs/RVL_SDK/src/cntcache/cntcache | CNTCACHEClear (asm PLACEHOLDER) | bgsamm/pbr-dtk cntcache.h (header only, saved); pret/pokerevo has asm only | still asm |

Note for the NHTTP_recvbuf owner: mscharged-decomp builds all of NHTTP with GC/3.0a5 ("retail code keeps the older compiler's constant order and saved-register zeros ... exact under GC/3.0a5 only"). That is what fixed NHTTP_stdlib_RVL here, so NHTTPi_compareTokenN_HdrRecvBuf is worth trying with `mw_version="GC/3.0a5"` and mscharged's NHTTP_recvbuf.c (already in _refs/prior).

## Round 2: readability
- NHTTP_stdlib_RVL: replaced the four inline tolower ternaries with `NHTTPi_TOLOWER(c)` macro. 14/14 exact, pool identical, DOL SHA1 26116613. `LowerCase()` kept (still used by NHTTPi_strToHex).

## Round 2: NHTTP_recvbuf
- mw_version GC/3.0a5 alone: 6/7, compareTokenN still 5/124.
- Reference compareTokenN control flow (prior/yannicksuter_mscharged-decomp__NHTTP_recvbuf.c), with NHTTPi_TOLOWER macro: 0/124, 7/7.
- Same, without the gotos (if/else reads): 86/128. Rejected; goto form kept.
- Locate step through the existing FindHeaderBlock() helper: still 0/124. Kept.
- Removed the unused static LowerCase(): still 7/7, pool identical, ctxdiff diffs 0.
- Flipped to Matching: DOL SHA1 26116613.
