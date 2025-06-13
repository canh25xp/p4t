#pragma once

#include "result.h"

class TestResult : public Result {
public:
    void OutputStat(StrDict *varList) override;
    void OutputText(const char *data, int length) override;
    void OutputBinary(const char *data, int length) override;
};
