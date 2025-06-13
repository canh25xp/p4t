#pragma once

#include <vector>
#include "change_list.h"
#include "result.h"

class ChangesResult : public Result {
private:
    std::vector<ChangeList> m_Changes;

public:
    std::vector<ChangeList> &GetChanges() { return m_Changes; }
    void reverse();

    void OutputStat(StrDict *varList) override;
};
