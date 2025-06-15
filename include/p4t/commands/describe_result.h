#pragma once

#include <vector>

#include "result.h"
#include "file_data.h"

class DescribeResult : public Result {
private:
    std::vector<FileData> m_FileData;

public:
    const std::vector<FileData> &GetFileData() const { return m_FileData; }

    void OutputStat(StrDict *varList) override;
    int OutputStatPartial(StrDict *varList) override;
    void OutputText(const char *data, int length) override;
    void OutputBinary(const char *data, int length) override;
};
