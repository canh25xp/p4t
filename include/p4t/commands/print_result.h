#pragma once

#include <vector>

#include "result.h"

class PrintResult : public Result {
public:
    struct PrintData {
        std::vector<char> contents;
    };

private:
    std::vector<PrintData> m_Data;

public:
    const std::vector<PrintData> &GetPrintData() const { return m_Data; }

    void OutputStat(StrDict *varList) override;
    void OutputText(const char *data, int length) override;
    void OutputBinary(const char *data, int length) override;
};
