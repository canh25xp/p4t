#include <p4/clientapi.h>

#include "info_result.h"
#include "time_helpers.h"

InfoResult::InfoResult()
    : m_TimezoneMinutes(0) {
}

void InfoResult::OutputStat(StrDict *varList) {
    std::string serverDate = varList->GetVar("serverDate")->Text();
    m_TimezoneMinutes = Time::GetTimezoneMinutes(serverDate);
}
