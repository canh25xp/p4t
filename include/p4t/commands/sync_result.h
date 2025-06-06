#pragma once

#include <vector>
#include <string>

#include "common.h"
#include "result.h"

class SyncResult : public Result {
public:
    struct SyncData {
        std::string depotFile;
        std::string revision;
    };

private:
    std::vector<SyncData> m_SyncData;

public:
    const std::vector<SyncData> &GetSyncData() const { return m_SyncData; }

    void OutputStat(StrDict *varList) override;
};
