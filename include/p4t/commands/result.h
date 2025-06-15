#pragma once

#include "p4/clientapi.h"

class Result : public ClientUser {
    Error m_Error;

public:
    void HandleError(Error *e) override;

    const Error &GetError() const { return m_Error; }
};
