# grok-parental Parental::dump

Replaced the eleven DECOMP_FORCE_ACTIVE strings with Parental::dump.
The function is not in the target object (linker stripped it). Strings stay in source order.

Attempt 1: print enable, rating, password, secret question/answer/length, SCGetNetContentRestrictions, wwwRestrict, mRequestNum, mMasterKey, getCountry.
- pool: IDENTICAL 17/17
- .data sha1 e3b3aaf3411decf3cd524b01cc437f434417dda1 matches the force-active build (332 bytes)
- .sdata identical to that build
- odiff: 30 functions differing 0
- gate: PASS. DOL 26116613f624061ba99c8d1a299aaa6efa85670d. data 1576/1576. functions 30/30. regressions 0.
