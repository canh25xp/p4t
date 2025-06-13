#include <algorithm>

#include <p4/clientapi.h>

#include "changes_result.h"

void ChangesResult::OutputStat(StrDict *varList) {
    m_Changes.emplace_back(
        varList->GetVar("change")->Text(),
        varList->GetVar("desc")->Text(),
        varList->GetVar("user")->Text(),
        varList->GetVar("time")->Atoi64());
}

void ChangesResult::reverse() {
    std::reverse(m_Changes.begin(), m_Changes.end());
}
