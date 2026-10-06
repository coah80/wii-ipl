# grok-so SOGetSockName

baseline differing: 3 / 63
only first memcpy arg order: ours mr r3,r28 / mr r4,r27 / lbz r5; target mr r4 / lbz r5 / mr r3

len local after reply: 3 / 63
source local then len local: 3 / 63
len local then source local: 3 / 63
memcpy source is the void* parameter: 5 / 63 (also swaps the entry saves)
source and length both from the void* parameter: 5 / 63
reply assigned before socket store: 3 / 63
memcpy dest &request->address, reply assigned after: 6 / 63
memcpy dest &request->address, reply assigned before: 3 / 63
reply assigned inside the dest argument: 3 / 63
length ((u8*)addr)[0]: 3 / 63
length *(u8*)addr: 3 / 63
dest cast to void*: 3 / 63
length cast to unsigned long: 3 / 63
const source local: 3 / 63
u8* dest local: 14 / 63
reply = (SOSockAddr*)((u8*)request+32), memcpy from reply: 3 / 63
reply and memcpy dest both (u8*)request+32: 0 / 63
len local before reply: 3 / 63
len local before socket store: 3 / 63, register shift
socketBlock+32, sizeof, and [32]: 3 / 63
u8* raw local plus 32: 3 / 63
reply and memcpy dest both ((u8*)request)+32: 0 / 63, style check clean, all 22 functions 0

kept ((u8*)request)+32. Field address schedules the destination move first; the byte offset schedules it last.

Linking stripped SORead, SOFcntl and SOInetPtoN (nothing live calls them) and shifted the DOL by 660 code bytes. config/43U/config.yml force_active keeps them, same as SOGetSockOpt. DOL sha1 26116613f624061ba99c8d1a299aaa6efa85670d.
