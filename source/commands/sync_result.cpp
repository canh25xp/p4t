#include "sync_result.h"

#include "p4/clientapi.h"

void SyncResult::OutputStat(StrDict *varList) {
    m_SyncData.push_back(SyncData{varList->GetVar("depotFile")->Text(), varList->GetVar("rev")->Text()});
}
