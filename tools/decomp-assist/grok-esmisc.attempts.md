# grok-esmisc DeleteSharedContent

Replaced the ten DECOMP_FORCE_ACTIVE strings with ESMisc::DeleteSharedContent.
The function is not in the target object (linker stripped it). Strings stay in source order.

Attempt 1: heap-alloc a max TMD, ES_ListSharedContents count/list, ES_ListTitlesOnCard count/list, ES_GetTmd size/data per title, mark shared-content hashes (type & 0x8000), ES_DeleteSharedContent on the rest.
- pool: IDENTICAL 114/114
- .data sha1 b38f8ebbacceb1818e343c6ce51f9abf8603ec23 matches the force-active build (4378 bytes)
- .sdata identical to that build
- odiff: 30 functions differing 0; DeleteUnauthorizedData differing 74/449 (fuzzy 99.14254), same as the force-active build
- gate: PASS. DOL 26116613f624061ba99c8d1a299aaa6efa85670d. data 4416/4416. regressions 0.
