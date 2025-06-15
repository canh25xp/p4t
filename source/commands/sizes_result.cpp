#include "sizes_result.h"

#include "p4/clientapi.h"

void SizesResult::OutputStat(StrDict *varList) {
    m_Size = varList->GetVar("fileSize")->Text();
}
