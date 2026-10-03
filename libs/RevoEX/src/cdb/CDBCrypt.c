#include <private/cdb.h>
#include <revolution/cdb.h>

static CDBCryptBuf* s_cryptBuf;

void CDBCryptBufSysInit(CDBCryptBuf* cryptBuf) {
    s_cryptBuf = cryptBuf;
    cryptBuf->allocated = FALSE;
}

CDBErr CDBCryptBufAllocate(CDBCryptBuf** cryptBuf) {
    CDBErr err = CDB_ERROR_OK;

    if (s_cryptBuf->allocated == FALSE) {
        *cryptBuf = &s_cryptBuf[err];
        s_cryptBuf[err].allocated = TRUE;
        return CDB_ERROR_OK;
    } else {
        CDBReportError("failed to allocate crypt buffer\n");
        return CDB_ERROR_CRYPT_ALLOC_FAIL;
    }
}

CDBErr CDBCryptBufFree(CDBCryptBuf** cryptBuf) {
    CDBErr err = CDB_ERROR_OK;

    if (*cryptBuf == s_cryptBuf) {
        s_cryptBuf[err].allocated = FALSE;
        *cryptBuf = NULL;
        return CDB_ERROR_OK;
    } else {
        CDBReportError("failed to free crypt buffer\n");
        return CDB_ERROR_1;
    }
}
