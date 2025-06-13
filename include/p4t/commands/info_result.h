#pragma once

#include "result.h"

class InfoResult : public Result {
    int m_TimezoneMinutes;

public:
    InfoResult();

    int GetServerTimezoneMinutes() const { return m_TimezoneMinutes; };

    void OutputStat(StrDict *varList) override;
};
