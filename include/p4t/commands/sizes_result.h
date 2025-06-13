#pragma once

#include <string>

#include "result.h"

class SizesResult : public Result {
    std::string m_Size;

public:
    std::string GetSize() { return m_Size; }

    void OutputStat(StrDict *varList) override;
};
