#include "client_result.h"

#include "p4/clientapi.h"

void ClientResult::OutputStat(StrDict *varList) {
    m_Data.client = varList->GetVar("Client")->Text();

    int i = 0;
    StrPtr *view = nullptr;

    while (true) {
        std::string indexString = std::to_string(i++);
        view = varList->GetVar(("View" + indexString).c_str());

        if (!view) {
            break;
        }

        m_Data.mapping.push_back(view->Text());
    }
}
