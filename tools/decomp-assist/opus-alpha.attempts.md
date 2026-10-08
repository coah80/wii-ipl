# opus-alpha: Zi8AlphaGetCandidates

Start: 95.64% (odiff 3227/3946 differing).

1. Applied the rx51b "private-alpha-99.8036" patch plus `keyLayoutCursor += *keyLayoutCursor + 1`
   on the current file (old `void Zi8Memset(..., ziU32)` prototype): 518 differing.
2. Switched to the corrected `ziPtr Zi8Memset(ziPtr, ziU32, ziS32)` used by the rest of eZiText:
   68 differing (the rx51b 99.806% candidate reproduced).
3. Remaining structure: two copies where retail loads the index once, copies it, stores at the
   old index, then writes old+1, with the source character loaded before the index. That is the
   original post-increment-in-destination form:
     `wordCursor[elementIndex++] = parameters->elements[elementIndex];`
     `work->prefix[work->prefixCount++] = elements[work->prefixCount];`
   (the same shape as the existing else branch `prefix[prefixCount++] = letterHyphen`).
   MWCC evaluates the right-hand side first, as the retail order shows: 0 differing.
4. Dropping the `(ziU8)` on `prefixMode = work->suffixMode`: 1784 differing, kept.

Result: exact. zi8alpha.c flipped to Matching; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
Note: both post-increment statements read and modify the index in one expression (unsequenced in
ISO C); MWCC's RHS-first order gives the intended behaviour and the retail bytes.
