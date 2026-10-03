# ult15 single-function structural matching

Branch agent/w1003/sol-ult15-ultra; base 57ccda3883537a308568c03924af2cebf2d8a789.
All four initial pools identical. Existing untracked ult8b.attempts.md left untouched.

## ATERMRunConfigProtocol target CFG and calls
Target 951/source958 instructions, frame0x180. Earlier ult1/fz20/data-d3 trials read; no reference-index entry. Addresses below are target object offsets.
0x170c Initialize protocol state1, response/packet/session views, socket0/result-5/retries0/failure0.
0x1778 Initialize alarm/message queue, wait500ms, dispatch state0..10.
0x17e4 Initialize alarm/message queue, wait500ms, dispatch state0..10.
0x180c case1 DiscoverAccessPoints; failure exits loop; progress state3 with deadline time; advance2.
0x1814 case1 DiscoverAccessPoints; failure exits loop; progress state3 with deadline time; advance2.
0x1834 case1 DiscoverAccessPoints; failure exits loop; progress state3 with deadline time; advance2.
0x183c case1 DiscoverAccessPoints; failure exits loop; progress state3 with deadline time; advance2.
0x1868 case1 DiscoverAccessPoints; failure exits loop; progress state3 with deadline time; advance2.
0x1888 case2 StartNetworkStack; failure exits loop; extend deadline to now+10000; advance3.
0x1898 case2 StartNetworkStack; failure exits loop; extend deadline to now+10000; advance3.
0x18a0 case2 StartNetworkStack; failure exits loop; extend deadline to now+10000; advance3.
0x18d0 case2 StartNetworkStack; failure exits loop; extend deadline to now+10000; advance3.
0x18f8 case2 StartNetworkStack; failure exits loop; extend deadline to now+10000; advance3.
0x1904 case3 create UDP socket; initialize sockaddr and bind; failure-2 or advance4.
0x1920 case3 create UDP socket; initialize sockaddr and bind; failure-2 or advance4.
0x192c case3 create UDP socket; initialize sockaddr and bind; failure-2 or advance4.
0x1970 case3 create UDP socket; initialize sockaddr and bind; failure-2 or advance4.
0x197c case3 create UDP socket; initialize sockaddr and bind; failure-2 or advance4.
0x1988 case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x19b4 case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x19c8 case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x19f8 case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x1a0c case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x1a58 case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x1a60 case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x1a8c case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x1aa8 case5 construct request options in order, send broadcast encrypted type2; set lastSendTime and advance6.
0x1b94 case5 construct request options in order, send broadcast encrypted type2; set lastSendTime and advance6.
0x1be0 case5 construct request options in order, send broadcast encrypted type2; set lastSendTime and advance6.
0x1c3c case5 construct request options in order, send broadcast encrypted type2; set lastSendTime and advance6.
0x1c8c case5 construct request options in order, send broadcast encrypted type2; set lastSendTime and advance6.
0x1d18 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1d44 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1d58 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1d78 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1dac case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1dbc case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1dc0 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1dd8 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e20 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e30 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e40 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e5c case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e60 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e68 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e70 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e7c case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e84 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e8c case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1ea8 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1eb4 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1ebc case6 read option length and first option type/length, preserve type across SONtoHs; require type0x101.
0x1ed8 case6 read option length and first option type/length, preserve type across SONtoHs; require type0x101.
0x1ee0 case6 read option length and first option type/length, preserve type across SONtoHs; require type0x101.
0x1efc case6 read option length and first option type/length, preserve type across SONtoHs; require type0x101.
0x1f08 case6 copy challenge, MD5 init/update(time), encode bit count, MD5 padding and count updates.
0x1fe0 case6 copy challenge, MD5 init/update(time), encode bit count, MD5 padding and count updates.
0x1fe4 case6 copy challenge, MD5 init/update(time), encode bit count, MD5 padding and count updates.
0x2084 case6 encode4 digest words to session key+8; clear88-byte digest context by byte loop.
0x20ac case6 advance7/progress5, disable deadline, reset retries, callback.
0x20ec case6 timeout after2000ms returns state5.
0x2118 case6 timeout after2000ms returns state5.
0x2124 case7 build0x102 response with digest8, send type4, timestamp and clear scan settings; advance8.
0x2220 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2240 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2274 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2284 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2288 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x22a0 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x22e8 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x22f8 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2308 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2324 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2328 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2330 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2338 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2344 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x234c case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2354 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2370 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x237c case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2388 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2398 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x23c4 case8 after1000ms increment retries; ten closes/-2, otherwise state7.
0x23f0 case8 after1000ms increment retries; ten closes/-2, otherwise state7.
0x23fc case8 after1000ms increment retries; ten closes/-2, otherwise state7.
0x2410 case8 after1000ms increment retries; ten closes/-2, otherwise state7.
0x241c case9 build mode option0x301, send type6 or bypass send if link status!=5; timestamp and state10.
0x24b0 case9 build mode option0x301, send type6 or bypass send if link status!=5; timestamp and state10.
0x24e0 case9 build mode option0x301, send type6 or bypass send if link status!=5; timestamp and state10.
0x2548 case10 after1000ms ten retries apply scan security and exit; otherwise state9.
0x2574 case10 after1000ms ten retries apply scan security and exit; otherwise state9.
0x2580 case10 after1000ms ten retries apply scan security and exit; otherwise state9.
0x2590 case10 after1000ms ten retries apply scan security and exit; otherwise state9.
0x2598 Loop if !failed&&!cancel.
0x25a0 Loop if !failed&&!cancel.
0x25ac Close nonzero socket, cancellation overrides result-8; restore and return.
0x25b4 Close nonzero socket, cancellation overrides result-8; restore and return.
0x25bc Close nonzero socket, cancellation overrides result-8; restore and return.
0x25c8 Close nonzero socket, cancellation overrides result-8; restore and return.
0x25cc Close nonzero socket, cancellation overrides result-8; restore and return.
Target calls in order: _savegpr_14, OSInitMessageQueue, OSCreateAlarm, OSSetAlarmTag, OSSetAlarm, OSReceiveMessage, ATERMDiscoverAccessPoints, OSGetTime, __div2i, ATERMStartNetworkStack, OSGetTime, __div2i, OSGetTime, __div2i, SOSocket, memset, SOHtoNs, SOBind, OSGetTime, __div2i, SOClose, ATERMBuildAssociationRequest, SORecvFrom, ATERMParsePacket, OSGetTime, __div2i, OSGetTime, __div2i, SOHtoNs, memset, SOHtoNs, SOHtoNs, memset, memcpy, memset, SOHtoNs, SOHtoNs, memset, memcpy, memset, SOHtoNs, SOHtoNs, memset, memcpy, memset, SOHtoNs, SOHtoNs, memset, memcpy, memset, SOHtoNs, SOHtoNs, memset, memcpy, ATERMBuildEncryptedMessage, SOHtoNs, SOSendTo, OSGetTime, __div2i, OSGetTime, __div2i, SOClose, SORecvFrom, SONtoHs, SONtoHs, SONtoHs, ATERMAesKeyUnwrap, memcpy, SONtoHs, SONtoHs, SONtoHs, OSGetTime, __div2i, memcpy, ATERMMd5Update, ATERMMd5Update, ATERMMd5Update, OSGetTime, __div2i, memset, memset, SOHtoNs, SOHtoNs, memset, memcpy, ATERMBuildEncryptedMessage, SOHtoNs, SOSendTo, OSGetTime, __div2i, memset, SORecvFrom, SONtoHs, SONtoHs, SONtoHs, ATERMAesKeyUnwrap, memcpy, ATERMParseAssociationResponse, OSGetTime, __div2i, SOClose, memset, memset, SOHtoNs, SOHtoNs, memset, memcpy, ATERMBuildEncryptedMessage, NCDGetLinkStatus, OSGetTime, __div2i, SOHtoNs, SOSendTo, OSGetTime, __div2i, OSGetTime, __div2i, ATERMApplyScanSecuritySettings, SOClose, _restgpr_14

## ATERMRunConfigProtocol target CFG and calls
Target 951/source958 instructions, frame0x180. Earlier ult1/fz20/data-d3 trials read; no reference-index entry. Addresses below are target object offsets.
0x170c Initialize protocol state1, response/packet/session views, socket0/result-5/retries0/failure0.
0x1778 Initialize alarm/message queue, wait500ms, dispatch state0..10.
0x17e4 Initialize alarm/message queue, wait500ms, dispatch state0..10.
0x180c case1 DiscoverAccessPoints; failure exits loop; progress state3 with deadline time; advance2.
0x1814 case1 DiscoverAccessPoints; failure exits loop; progress state3 with deadline time; advance2.
0x1834 case1 DiscoverAccessPoints; failure exits loop; progress state3 with deadline time; advance2.
0x183c case1 DiscoverAccessPoints; failure exits loop; progress state3 with deadline time; advance2.
0x1868 case1 DiscoverAccessPoints; failure exits loop; progress state3 with deadline time; advance2.
0x1888 case2 StartNetworkStack; failure exits loop; extend deadline to now+10000; advance3.
0x1898 case2 StartNetworkStack; failure exits loop; extend deadline to now+10000; advance3.
0x18a0 case2 StartNetworkStack; failure exits loop; extend deadline to now+10000; advance3.
0x18d0 case2 StartNetworkStack; failure exits loop; extend deadline to now+10000; advance3.
0x18f8 case2 StartNetworkStack; failure exits loop; extend deadline to now+10000; advance3.
0x1904 case3 create UDP socket; initialize sockaddr and bind; failure-2 or advance4.
0x1920 case3 create UDP socket; initialize sockaddr and bind; failure-2 or advance4.
0x192c case3 create UDP socket; initialize sockaddr and bind; failure-2 or advance4.
0x1970 case3 create UDP socket; initialize sockaddr and bind; failure-2 or advance4.
0x197c case3 create UDP socket; initialize sockaddr and bind; failure-2 or advance4.
0x1988 case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x19b4 case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x19c8 case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x19f8 case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x1a0c case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x1a58 case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x1a60 case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x1a8c case4 deadline close/-3; build association request; receive/parse packet; progress4 and advance5.
0x1aa8 case5 construct request options in order, send broadcast encrypted type2; set lastSendTime and advance6.
0x1b94 case5 construct request options in order, send broadcast encrypted type2; set lastSendTime and advance6.
0x1be0 case5 construct request options in order, send broadcast encrypted type2; set lastSendTime and advance6.
0x1c3c case5 construct request options in order, send broadcast encrypted type2; set lastSendTime and advance6.
0x1c8c case5 construct request options in order, send broadcast encrypted type2; set lastSendTime and advance6.
0x1d18 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1d44 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1d58 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1d78 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1dac case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1dbc case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1dc0 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1dd8 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e20 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e30 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e40 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e5c case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e60 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e68 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e70 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e7c case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e84 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1e8c case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1ea8 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1eb4 case6 deadline close/-4; receive, sequence3 and length, byte checksum; unwrap or copy payload; zero length leaves authentication.
0x1ebc case6 read option length and first option type/length, preserve type across SONtoHs; require type0x101.
0x1ed8 case6 read option length and first option type/length, preserve type across SONtoHs; require type0x101.
0x1ee0 case6 read option length and first option type/length, preserve type across SONtoHs; require type0x101.
0x1efc case6 read option length and first option type/length, preserve type across SONtoHs; require type0x101.
0x1f08 case6 copy challenge, MD5 init/update(time), encode bit count, MD5 padding and count updates.
0x1fe0 case6 copy challenge, MD5 init/update(time), encode bit count, MD5 padding and count updates.
0x1fe4 case6 copy challenge, MD5 init/update(time), encode bit count, MD5 padding and count updates.
0x2084 case6 encode4 digest words to session key+8; clear88-byte digest context by byte loop.
0x20ac case6 advance7/progress5, disable deadline, reset retries, callback.
0x20ec case6 timeout after2000ms returns state5.
0x2118 case6 timeout after2000ms returns state5.
0x2124 case7 build0x102 response with digest8, send type4, timestamp and clear scan settings; advance8.
0x2220 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2240 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2274 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2284 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2288 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x22a0 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x22e8 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x22f8 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2308 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2324 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2328 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2330 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2338 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2344 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x234c case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2354 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2370 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x237c case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2388 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x2398 case8 receive sequence5/checksum; unwrap session-key payload or copy; parse association; state9 and ssid-based mode.
0x23c4 case8 after1000ms increment retries; ten closes/-2, otherwise state7.
0x23f0 case8 after1000ms increment retries; ten closes/-2, otherwise state7.
0x23fc case8 after1000ms increment retries; ten closes/-2, otherwise state7.
0x2410 case8 after1000ms increment retries; ten closes/-2, otherwise state7.
0x241c case9 build mode option0x301, send type6 or bypass send if link status!=5; timestamp and state10.
0x24b0 case9 build mode option0x301, send type6 or bypass send if link status!=5; timestamp and state10.
0x24e0 case9 build mode option0x301, send type6 or bypass send if link status!=5; timestamp and state10.
0x2548 case10 after1000ms ten retries apply scan security and exit; otherwise state9.
0x2574 case10 after1000ms ten retries apply scan security and exit; otherwise state9.
0x2580 case10 after1000ms ten retries apply scan security and exit; otherwise state9.
0x2590 case10 after1000ms ten retries apply scan security and exit; otherwise state9.
0x2598 Loop if !failed&&!cancel.
0x25a0 Loop if !failed&&!cancel.
0x25ac Close nonzero socket, cancellation overrides result-8; restore and return.
0x25b4 Close nonzero socket, cancellation overrides result-8; restore and return.
0x25bc Close nonzero socket, cancellation overrides result-8; restore and return.
0x25c8 Close nonzero socket, cancellation overrides result-8; restore and return.
0x25cc Close nonzero socket, cancellation overrides result-8; restore and return.
Target calls in order: _savegpr_14, OSInitMessageQueue, OSCreateAlarm, OSSetAlarmTag, OSSetAlarm, OSReceiveMessage, ATERMDiscoverAccessPoints, OSGetTime, __div2i, ATERMStartNetworkStack, OSGetTime, __div2i, OSGetTime, __div2i, SOSocket, memset, SOHtoNs, SOBind, OSGetTime, __div2i, SOClose, ATERMBuildAssociationRequest, SORecvFrom, ATERMParsePacket, OSGetTime, __div2i, OSGetTime, __div2i, SOHtoNs, memset, SOHtoNs, SOHtoNs, memset, memcpy, memset, SOHtoNs, SOHtoNs, memset, memcpy, memset, SOHtoNs, SOHtoNs, memset, memcpy, memset, SOHtoNs, SOHtoNs, memset, memcpy, memset, SOHtoNs, SOHtoNs, memset, memcpy, ATERMBuildEncryptedMessage, SOHtoNs, SOSendTo, OSGetTime, __div2i, OSGetTime, __div2i, SOClose, SORecvFrom, SONtoHs, SONtoHs, SONtoHs, ATERMAesKeyUnwrap, memcpy, SONtoHs, SONtoHs, SONtoHs, OSGetTime, __div2i, memcpy, ATERMMd5Update, ATERMMd5Update, ATERMMd5Update, OSGetTime, __div2i, memset, memset, SOHtoNs, SOHtoNs, memset, memcpy, ATERMBuildEncryptedMessage, SOHtoNs, SOSendTo, OSGetTime, __div2i, memset, SORecvFrom, SONtoHs, SONtoHs, SONtoHs, ATERMAesKeyUnwrap, memcpy, ATERMParseAssociationResponse, OSGetTime, __div2i, SOClose, memset, memset, SOHtoNs, SOHtoNs, memset, memcpy, ATERMBuildEncryptedMessage, NCDGetLinkStatus, OSGetTime, __div2i, SOHtoNs, SOSendTo, OSGetTime, __div2i, OSGetTime, __div2i, ATERMApplyScanSecuritySettings, SOClose, _restgpr_14

ATTEMPT ATERMRunConfigProtocol | initialize response and session views after state1 | {"percent": 88.19559, "insns": [958, 951], "structural": 215, "diffs": 928, "pool": 0, "regress": [], "hash": "511fa936cdec"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMRunConfigProtocol | defined option type gates authentication after state-first views | {"percent": 88.07571, "insns": [955, 951], "structural": 205, "diffs": 935, "pool": 0, "regress": [], "hash": "b2c633616cbb"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMRunConfigProtocol | const response object view with session initialization after state1 | {"percent": 88.19559, "insns": [958, 951], "structural": 215, "diffs": 928, "pool": 0, "regress": [], "hash": "8cd30b63a572"} | POOL IDENTICAL up to 0 (mine=0 base=0)

## ATERMMd5Update target blocks
0x3910 countLow += length<<3 and carry to high; bufferIndex=countLow_old>>3&63.
0x3960 high += length>>29; fillLength=64-bufferIndex; length<fillLength ->0x3a6c.
0x397c..0x3a38 inline bytecopy, independent destination/source/length locals, eight-byte unroll then byte remainder. Target destination is &context->buffer8[bufferIndex] as a formal copy view, not context+indexed field stores.
0x3a38 transform context buffer;0x3a48 full input blocks;0x3a58 test offset+63<length;0x3a64 reset bufferIndex0;0x3a6c copiedBytes0 for partial input.
0x3a70..0x3b30 inline bytecopy remainder to context buffer, same eight-byte+remainder loops;0x3b30 restore/return. Calls ATERMMd5Transform(buffer), ATERMMd5Transform(input+copiedBytes). Local NETMD5Update uses memcpy with a different context byte-count API; its memcpy call boundaries do not reproduce this routine. Prior ult1/fz20 pointer-induction/macro/static-inline attempts read.

ATTEMPT ATERMMd5Update | RFC copy views with independent indices and const source | {"percent": 72.84722, "insns": [138, 144], "structural": 38, "diffs": 129, "pool": 0, "regress": [], "hash": "8411f4692343"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | opaque RFC copy formals cast only at indexed access | {"percent": 83.47222, "insns": [142, 144], "structural": 23, "diffs": 129, "pool": 0, "regress": [], "hash": "7db429d82edf"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | copy pointers bounded by destination end | {"percent": 66.80556, "insns": [124, 144], "structural": 56, "diffs": 136, "pool": 0, "regress": [], "hash": "6ef07a3886f1"} | POOL IDENTICAL up to 0 (mine=0 base=0)

## Card texture target CFG
_create_icon frame0x30,100/100insns. 0xf54 fetch dir and validate slot/file;0xf94 NULL;0xf9c fetch icons, preserve separate slot0x1fc0 and file0x40 strides;0xfc4 RGB path form row icon member and file0x15c stride, init texture then recompute address/load;0x1020 test CI;0x1028 CI init, reload icon palette offset through original icons array, form row palette member before file stride, init/loadTLUT then recompute texture address/load;0x10c0 unsupported NULL;0x10c8 return selectedtexture;0x10cc restore. Calls getCardDirState,getIconStateArray,GXInitTexObj/GXLoadTexObj or GXInitTexObjCI/GXInitTlutObj/GXLoadTlut/GXLoadTexObj.
create_banner frame0x40,106/106insns. 0x12d0 fetch dirs/icons, resolve logical index to actual file;0x132c validity check uses file column before slot row, independently reconstruct rendering icon at0x1350;0x1348 NULL;0x1364 RGB init/load with separately held texture rowbase/file stride;0x13b4 CI guard;0x13bc CI init, reload paletteoffset using original icons array, palette init/load and texture load;0x1444 recompute returned banner address;0x1460 restore. No strings or data sections. Earlier ult3/partial-oct2d/partial-oct2f/card logs exclude cached complete cell pointer, cached row pointer and same typed-address accessor trials.

ATTEMPT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | const directory and icon metadata views at GX boundaries | {"percent": 87.55, "insns": [100, 100], "structural": 16, "diffs": 37, "pool": 0, "regress": [], "hash": "9b42af64c201"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | render metadata as mutable typed reference | {"percent": 87.55, "insns": [100, 100], "structural": 16, "diffs": 37, "pool": 0, "regress": [], "hash": "1d91ba26ea93"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | linear icon records using actual slot stride and typed field access | {"percent": 83.89, "insns": [97, 100], "structural": 25, "diffs": 79, "pool": 0, "regress": [], "hash": "44d98c9cfa18"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | typed member pointer accessor for texture and palette | {"percent": 83.75, "insns": [99, 100], "structural": 20, "diffs": 62, "pool": 0, "regress": [], "hash": "734552180bf8"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | const directory and icon metadata views at GX boundaries | {"percent": 90.42453, "insns": [106, 106], "structural": 15, "diffs": 70, "pool": 0, "regress": [], "hash": "0535043cad90"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | render metadata as mutable typed reference | {"percent": 90.42453, "insns": [106, 106], "structural": 15, "diffs": 70, "pool": 0, "regress": [], "hash": "ed6af8d05486"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | linear icon records using actual slot stride and typed field access | {"percent": 84.66038, "insns": [103, 106], "structural": 23, "diffs": 96, "pool": 0, "regress": [], "hash": "9bc6859408b7"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | typed member pointer accessor for texture and palette | {"percent": 84.57547, "insns": [105, 106], "structural": 22, "diffs": 87, "pool": 0, "regress": [], "hash": "3924c36bc132"} | POOL IDENTICAL up to 0 (mine=0 base=0)

## setElementBuffer target blocks
0x12e4 initialize pooled BSS base, this and count0;0x1308 clear elements0x1fe;0x1318 clear second candidate region0x1fe;0x1328 bind elements and candidates, loop guard.
0x1334 store loaded candidate, getPredictLanguage virtual0x104;0x1358 language1 tests digits0x30..0x39;0x136c add0xf300;0x137c test lowercase then uppercase;0x139c reload and add0xf300;0x13ac increment count;0x13b0 narrowcount16, read candidate, require nonzero/count<255;0x13cc restore and returncount. Frame0x20,65/65. Exact loop CFG/calls agree; target one pooled BSS base while current separately constructs ElementBuffer/CandidatesBuffer symbols. All7680data bytes already exact. No legitimate alias outside array bounds introduced. Prior tiZi/fz7/structural/ult2 view/index/declaration trials read.

ATTEMPT setElementBuffer__Q39textinput8tistring6WithZiFv | bounded array references for both element and candidate views | {"percent": 88.66154, "insns": [65, 65], "structural": 7, "diffs": 21, "pool": 0, "regress": [], "hash": "ae9552f34c59"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT setElementBuffer__Q39textinput8tistring6WithZiFv | candidate-first for loop with explicit capacity exit | {"percent": 80.95385, "insns": [65, 65], "structural": 12, "diffs": 50, "pool": 0, "regress": [], "hash": "ae1178d23992"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT setElementBuffer__Q39textinput8tistring6WithZiFv | explicit digit rejection then separate lowercase and uppercase conversion | {"percent": 67.87692, "insns": [69, 65], "structural": 26, "diffs": 58, "pool": 0, "regress": [], "hash": "4c9904d449ce"} | POOL IDENTICAL up to 0 (mine=0 base=0)

## Decolated inputChar target blocks
0x6cc sentinel0xfffe exits;0x6f8 initialize five output chars;0x710 translation1/2 selects Kana, otherwise0x7cc.
0x720 reset Kana output and test newline;0x73c LookAhead;0x754 flush queue0xffff;0x770 lowercase+PutChar;0x78c count/char-copy;0x798 GetChar;0x7ac byte-narrow count test;0x7b8 lookahead output.
0x7cc mode3 or direct;0x7d4 original inline literal converter clears output, retains newline comparison, indexed append count0->1 and terminator then clears preview;0x80c direct literal;0x818 setCandidate0;0x830 getSelected;0x85c insert when selected start=end then cursor+=count;0x890 replace selection and cursor=start+count;0x8c4 copy start to end;0x8cc restore. Frame0x30,target136/current125. Target dead newline comparison has no branch; prior fz3 R5..R11 builders/newline-reset aliases failed. New trials test dispatch structure and meaningful shared literal-copy boundaries, never a no-op newline argument.

ATTEMPT inputChar__Q39textinput8tistring9DecolatedFw | bounded single-character conversion with counted output loop | {"percent": 90.757355, "insns": [126, 136], "structural": 17, "diffs": 73, "pool": 0, "regress": [], "hash": "f7321d864f40"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT inputChar__Q39textinput8tistring9DecolatedFw | structured mode switch preserving Kana and literal converter paths | {"percent": 86.64706, "insns": [129, 136], "structural": 24, "diffs": 126, "pool": 0, "regress": [], "hash": "ced7330165ae"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT inputChar__Q39textinput8tistring9DecolatedFw | terminated literal pair copied as bounded UTF16 sequence | {"percent": 90.132355, "insns": [125, 136], "structural": 18, "diffs": 73, "pool": 0, "regress": [], "hash": "069a4900344f"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMRunConfigProtocol | decoded reply view plus actual session challenge and digest fields | {"percent": 85.872765, "insns": [968, 951], "structural": 268, "diffs": 944, "pool": 0, "regress": [], "hash": "752ce99014b1"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMRunConfigProtocol | configuration struct pointer owns reply and packet field views | {"percent": 88.19559, "insns": [958, 951], "structural": 215, "diffs": 928, "pool": 0, "regress": [], "hash": "03a9e0281617"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMRunConfigProtocol | byte reply storage with typed decoding only at packet boundaries | {"percent": 87.1346, "insns": [965, 951], "structural": 249, "diffs": 944, "pool": 0, "regress": [], "hash": "cc914ad7a7b9"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | bounded icon row reference before frame format selection | {"percent": 87.55, "insns": [100, 100], "structural": 16, "diffs": 37, "pool": 0, "regress": [], "hash": "359dcec94cc8"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | return each format texture through its post-initialization local | {"percent": 82.75, "insns": [101, 100], "structural": 23, "diffs": 69, "pool": 0, "regress": [], "hash": "63b2d32d4235"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | writable destination manager reference separated from icon metadata | {"percent": 87.55, "insns": [100, 100], "structural": 16, "diffs": 37, "pool": 0, "regress": [], "hash": "7b24a74470f4"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | bounded icon row reference before frame format selection | {"percent": 90.42453, "insns": [106, 106], "structural": 15, "diffs": 70, "pool": 0, "regress": [], "hash": "0c9b67da5e48"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | return each format texture through its post-initialization local | {"percent": 79.99056, "insns": [110, 106], "structural": 30, "diffs": 96, "pool": 0, "regress": [], "hash": "ffdf0a10fa73"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | writable destination manager reference separated from icon metadata | {"percent": 90.42453, "insns": [106, 106], "structural": 15, "diffs": 70, "pool": 0, "regress": [], "hash": "80e89eb4b927"} | POOL IDENTICAL up to 0 (mine=0 base=0)

## ATERM explicit inline-boundary audit
Build flags end with -inline off, which explains earlier helper-call results. Test only this unit configuration with explicit/auto inlining and the ordinary RFC-shaped byte copy helper; every other unit flag stays unchanged. A change can survive only if all other function scores and code/data measures do not drop.

ATTEMPT ATERMMd5Update | ordinary byte copy helper with inline on | {"percent": 90.43056, "insns": [140, 144], "structural": 33, "diffs": 122, "pool": 0, "regress": [], "hash": "faaf1e4c49c4"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | ordinary byte copy helper with inline auto | {"percent": 90.43056, "insns": [140, 144], "structural": 33, "diffs": 122, "pool": 0, "regress": [], "hash": "faaf1e4c49c4"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | ordinary byte copy helper with inline smart | {"percent": 90.43056, "insns": [140, 144], "structural": 33, "diffs": 122, "pool": 0, "regress": [], "hash": "faaf1e4c49c4"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | mutable byte input RFC prototype under explicit inline | {"percent": 91.68056, "insns": [139, 144], "structural": 32, "diffs": 115, "pool": 0, "regress": [], "hash": "25c72e25014e"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | opaque void copy prototype with indexed byte views under explicit inline | {"percent": 97.84722, "insns": [144, 144], "structural": 2, "diffs": 19, "pool": 0, "regress": [], "hash": "5172686bc07f"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | opaque copy prototype with mutable input under explicit inline | {"percent": 97.84722, "insns": [144, 144], "structural": 2, "diffs": 19, "pool": 0, "regress": [], "hash": "9f8629f26ad5"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | opaque void copy prototype with typed local views under explicit inline | {"percent": 72.56944, "insns": [138, 144], "structural": 38, "diffs": 127, "pool": 0, "regress": [], "hash": "e97c4116d2f4"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | byte copy source formal precedes destination under explicit inline | {"percent": 90.43056, "insns": [140, 144], "structural": 33, "diffs": 122, "pool": 0, "regress": [], "hash": "0cc678ab6cdb"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | opaque copy source formal precedes destination under explicit inline | {"percent": 97.84722, "insns": [144, 144], "structural": 2, "diffs": 19, "pool": 0, "regress": [], "hash": "7e12456ee6d0"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | actual u8* input formal and opaque inline copy | {"percent": 100.0, "insns": [144, 144], "structural": 0, "diffs": 0, "pool": 0, "regress": [], "hash": "a0a1a0da6371"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | actual const u8* input formal and opaque inline copy | {"percent": 95.701385, "insns": [144, 144], "structural": 16, "diffs": 43, "pool": 0, "regress": [], "hash": "41b5e6eddc0e"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | actual const void* input formal and opaque inline copy | {"percent": 93.548615, "insns": [144, 144], "structural": 18, "diffs": 61, "pool": 0, "regress": [], "hash": "7e12f77bfc92"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | actual u8* input formal and opaque inline copy | {"percent": 100.0, "insns": [144, 144], "structural": 0, "diffs": 0, "pool": 0, "regress": [], "hash": "a0a1a0da6371"} | POOL IDENTICAL up to 0 (mine=0 base=0)

RETAIN exact ATERMMd5Update. 144/144 instructions, objdiff100 and diffs0. RFC byte copy uses opaque formals and mutable u8 input formal; explicit inlining required. No other function score dropped. All other trial sources restored before handoff.

ATTEMPT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | single GX object field array decay icon | {"percent": 87.55, "insns": [100, 100], "structural": 16, "diffs": 37, "pool": 0, "regress": [], "hash": "7fc379d6b1ff"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | single GX object field array decay iconTlut | {"percent": 87.55, "insns": [100, 100], "structural": 16, "diffs": 37, "pool": 0, "regress": [], "hash": "242481a3e099"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | single GX object field array decay icon,iconTlut | {"percent": 87.55, "insns": [100, 100], "structural": 16, "diffs": 37, "pool": 0, "regress": [], "hash": "dfffb5b7be9a"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | single GX object field array decay banner | {"percent": 90.42453, "insns": [106, 106], "structural": 15, "diffs": 70, "pool": 0, "regress": [], "hash": "1fdfd74c6c6e"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | single GX object field array decay bannerTlut | {"percent": 90.42453, "insns": [106, 106], "structural": 15, "diffs": 70, "pool": 0, "regress": [], "hash": "ec1eb10c3292"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | single GX object field array decay banner,bannerTlut | {"percent": 90.42453, "insns": [106, 106], "structural": 15, "diffs": 70, "pool": 0, "regress": [], "hash": "8b67d38fcbcf"} | POOL IDENTICAL up to 0 (mine=0 base=0)

ATTEMPT ATERMMd5Update | readable readonly copy helper and removal of obsolete local | {"percent": 100.0, "insns": [144, 144], "structural": 0, "diffs": 0, "pool": 0, "regress": [], "hash": "404e45ea9e55"} | POOL IDENTICAL up to 0 (mine=0 base=0)

## Data ownership audit
MemoryCardManager has no target data objects; tiString all288/288, tiZiString all7680/7680 exact. ATERM .bss8160,.rodata10280,.sbss80,.sdata56,.sdata2=8 all100%; .data280 remains92.14286%, eleven switch-table relocations into open RunConfigProtocol. All generated-table names already paired, and no extent/name correction is supported. No symbols.txt edits.
AUDIT ATERMRunConfigProtocol | 88.19559% | 6 distinct successfully built source attempts.
AUDIT ATERMMd5Update | 100.0% | 14 distinct successfully built source attempts.
AUDIT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | 87.55% | 10 distinct successfully built source attempts.
AUDIT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | 90.42453% | 10 distinct successfully built source attempts.
AUDIT inputChar__Q39textinput8tistring9DecolatedFw | 90.132355% | 3 distinct successfully built source attempts.
AUDIT setElementBuffer__Q39textinput8tistring6WithZiFv | 90.33846% | 3 distinct successfully built source attempts.
All rejected source/header/config trials restored. Retained only exact MD5 helper/signature and ATERM inline flag. Original untracked ult8b log untouched. No other unit function score dropped from current baseline.

Independent original-source object compiled into /tmp with original -inline off flags: instruction-exact 16 -> 17; new ['ATERMMd5Update']; lost []. Worktree source and final build unmodified.

## Final full non-quick gate
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 11036/19204 data 18584/18864 functions 18/26 fuzzy 97.0367 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 17/26
[src/scene/setting/ATERM]   section .bss size 8160 match 100.0
[src/scene/setting/ATERM]   section .data size 280 match 92.14286
[src/scene/setting/ATERM]   section .rodata size 10280 match 100.0
[src/scene/setting/ATERM]   section .sbss size 80 match 100.0
[src/scene/setting/ATERM]   section .sdata size 56 match 100.0
[src/scene/setting/ATERM]   section .sdata2 size 8 match 100.0
[src/scene/setting/ATERM]   section .text size 19204 match 97.03666
[src/scene/setting/ATERM]   below 100: ATERMStartNetworkStack 97.91558
[src/scene/setting/ATERM]   below 100: ATERMDiscoverAccessPoints 95.304184
[src/scene/setting/ATERM]   below 100: ATERMBuildEncryptedMessage 99.791664
[src/scene/setting/ATERM]   below 100: ATERMBuildAssociationRequest 93.44361
[src/scene/setting/ATERM]   below 100: ATERMParseAssociationResponse 99.56204
[src/scene/setting/ATERM]   below 100: ATERMRunConfigProtocol 88.19559
[src/scene/setting/ATERM]   below 100: ATERMi_AutoConfigThread 94.75
[src/scene/setting/ATERM]   below 100: ATERMAesExpandEncryptKey 98.94403
[src/scene/setting/ATERM] baseline: code 10460/19204 data 18584 functions 17 fuzzy 96.7746
[src/scene/memoryCard/iplMemoryCardManager] pool: IDENTICAL
[src/scene/memoryCard/iplMemoryCardManager] objdiff: code 2572/5396 data None/None functions 18/26 fuzzy 97.8836 linked code 0
[src/scene/memoryCard/iplMemoryCardManager] instruction-exact functions: 18/26
[src/scene/memoryCard/iplMemoryCardManager]   section .text size 5396 match 97.88362
[src/scene/memoryCard/iplMemoryCardManager]   below 100: isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl 99.830505
[src/scene/memoryCard/iplMemoryCardManager]   below 100: isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl 99.830505
[src/scene/memoryCard/iplMemoryCardManager]   below 100: isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs 92.30769
[src/scene/memoryCard/iplMemoryCardManager]   below 100: update_file_array__Q33ipl5scene17MemoryCardManagerFUc 99.72222
[src/scene/memoryCard/iplMemoryCardManager]   below 100: _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl 87.55
[src/scene/memoryCard/iplMemoryCardManager]   below 100: getComment__Q33ipl5scene17MemoryCardManagerFUcsi 98.94309
[src/scene/memoryCard/iplMemoryCardManager]   below 100: create_banner__Q33ipl5scene17MemoryCardManagerFUcs 90.42453
[src/scene/memoryCard/iplMemoryCardManager]   below 100: getBlocks__Q33ipl5scene17MemoryCardManagerFUcs 92.0
[src/scene/memoryCard/iplMemoryCardManager] baseline: code 2572/5396 data None functions 18 fuzzy 97.8836
[src/keyboard/tiString] pool: IDENTICAL
[src/keyboard/tiString] objdiff: code 4632/5176 data 288/288 functions 41/42 fuzzy 98.9629 linked code 0
[src/keyboard/tiString] instruction-exact functions: 41/42
[src/keyboard/tiString]   section .data size 288 match 100.0
[src/keyboard/tiString]   section .text size 5176 match 98.962906
[src/keyboard/tiString]   below 100: inputChar__Q39textinput8tistring9DecolatedFw 90.132355
[src/keyboard/tiString] baseline: code 4632/5176 data 288 functions 41 fuzzy 98.9629
[src/keyboard/tiZiString] pool: IDENTICAL
[src/keyboard/tiZiString] objdiff: code 3136/5504 data 7680/7680 functions 26/29 fuzzy 98.2645 linked code 0
[src/keyboard/tiZiString] instruction-exact functions: 26/29
[src/keyboard/tiZiString]   section .bss size 7296 match 100.0
[src/keyboard/tiZiString]   section .data size 328 match 100.0
[src/keyboard/tiZiString]   section .rodata size 56 match 100.0
[src/keyboard/tiZiString]   section .text size 5504 match 98.264534
[src/keyboard/tiZiString]   below 100: clearCandidates__Q39textinput8tistring6WithZiFv 93.28395
[src/keyboard/tiZiString]   below 100: update__Q39textinput8tistring6WithZiFv 97.273544
[src/keyboard/tiZiString]   below 100: setElementBuffer__Q39textinput8tistring6WithZiFv 90.33846
[src/keyboard/tiZiString] baseline: code 3136/5504 data 7680 functions 26 fuzzy 98.2645
regressions vs baseline: 0
global matched_code_percent: 91.93089 -> 91.95013
global fuzzy_match_percent: 99.71608 -> 99.71777
global complete_code_percent: 74.84181 -> 74.84181
global matched_data_percent: 99.77803 -> 99.77803
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: configure.py (orchestrator reviews every config/symbols change)
GATE PASS
```
Source review: only ATERMMd5Update byte-copy helper/signature, its RunConfigProtocol byte-view call, and the ATERM inline setting are retained. No other source/header/symbol edit remains. Exact MD5 objdiff100,144/144,diffs0; parent verification still required.
