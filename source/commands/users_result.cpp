#include "users_result.h"

void UsersResult::OutputStat(StrDict *varList) {
    StrPtr *userIDPtr = varList->GetVar("User");
    StrPtr *emailPtr = varList->GetVar("Email");

    if (!userIDPtr || !emailPtr) {
        ERROR("UserID or email not found for a Perforce user");
        return;
    }

    UserID userID = userIDPtr->Text();
    UserData userData;

    userData.email = emailPtr->Text();

    StrPtr *fullNamePtr = varList->GetVar("FullName");
    if (fullNamePtr) {
        userData.fullName = fullNamePtr->Text();
    } else {
        userData.fullName = userID;
    }

    m_Users.insert({userID, userData});
}
