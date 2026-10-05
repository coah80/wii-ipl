#include <zi8clib/zi8getc.h>
#include <zi8clib/zitypes.h>

extern ziU8 _Zi8GetCandidates(ziGetParam* getParam ZI_NEED_WORK);

ziU8 Zi8GetCandidates(ziGetParam* getParam ZI_NEED_WORK) {
    ZI_WORK->candidateStateByteA = 0;
    ZI_WORK->candidateStateByteC = 0;
    ZI_WORK->candidateStateByteB = 0;
    ZI_WORK->candidateStateByteD = 0;
    ZI_WORK->candidateStateWordC = 0;
    ZI_WORK->candidateStateWordA = 0;
    ZI_WORK->candidateStateWordB = 0;
    return _Zi8GetCandidates(getParam, ZI_WORK);
}
