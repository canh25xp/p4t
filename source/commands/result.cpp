#include "result.h"

#include "p4/clientapi.h"

#include "log.h"

void Result::HandleError(Error *e) {
    StrBuf str;
    e->Fmt(&str);
    ERROR("Received error: " << e->FmtSeverity() << " " << str.Text());
    m_Error = *e;
}
