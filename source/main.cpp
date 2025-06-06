#include <CLI/CLI.hpp>
#include <dbg.h>

#include "p4t.h"

int main(int argc, char **argv);
int main(int argc, char **argv) {
    CLI::App app("p4 tool");

    argv = app.ensure_utf8(argv);

    std::string user = "";
    std::string port = "";
    std::string client = "";

    app.add_option("-u,--user", user, "P4USER");
    app.add_option("-p,--port", port, "P4PORT");
    app.add_option("-c,--client", client, "P4CLIENT");

    CLI11_PARSE(app, argc, argv);

    dbg(user, port, client);

    if (!P4T::InitializeLibraries()) {
        return 1;
    }

    const Error &e = P4T().TestConnection(5).GetError();
    bool ok = e.IsError() == 0;
    if (ok) {
        INFO("Perforce server is available");
    } else {
        ERROR("Error occurred while connecting to " << P4T::P4PORT);
        return 1;
    }

    if (!P4T::ShutdownLibraries()) {
        return 1;
    }

    return 0;
}
