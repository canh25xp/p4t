#include "sizes_result.h"

void SizesResult::OutputStat(StrDict *varList) {
    m_Size = varList->GetVar("fileSize")->Text();
}
