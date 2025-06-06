#pragma once

#include "common.h"
#include "result.h"

class UsersResult : public Result {
public:
    using UserID = std::string;

    struct UserData {
        std::string fullName;
        std::string email;
    };

private:
    std::unordered_map<UserID, UserData> m_Users;

public:
    const std::unordered_map<UserID, UserData> &GetUserEmails() const { return m_Users; }

    void OutputStat(StrDict *varList) override;
};
