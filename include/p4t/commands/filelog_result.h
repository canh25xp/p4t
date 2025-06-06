#pragma once

#include <vector>
#include <string>

#include "common.h"
#include "result.h"
#include "file_data.h"
#include "utils/std_helpers.h"

// Very limited to just a single file log entry per file.
class FileLogResult : public Result {
private:
    std::vector<FileData> m_FileData;

public:
    const std::vector<FileData> &GetFileData() const { return m_FileData; }

    void OutputStat(StrDict *varList) override;
    // int OutputStatPartial(StrDict* varList) override;
};
