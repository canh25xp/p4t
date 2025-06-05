#include <CLI/CLI.hpp>

#include <clientapi.h>
#include <p4libs.h>

int main(int argc, char **argv);
int main(int argc, char **argv) {
    CLI::App app("p4 tool");

    argv = app.ensure_utf8(argv);

    std::string user = "";
    std::string port = "";
    std::string client = "";

    app.add_option("-u,--user", user, "P4USER");
    app.add_option("-p,--port", port, "P4PORT");
    app.add_option("-c,--api", client, "P4CLIENT");

    CLI11_PARSE(app, argc, argv);

    ClientUser ui;
    ClientApi api;
    StrBuf msg;
    Error e;

    P4Libraries::Initialize(P4LIBRARIES_INIT_ALL, &e);

    if (e.Test()) {
        e.Fmt(&msg);
        fprintf(stderr, "%s\n", msg.Text());
        return 1;
    }

    api.Init(&e);

    if (e.Test()) {
        e.Fmt(&msg);
        fprintf(stderr, "%s\n", msg.Text());
        return 1;
    }

    // Run the command "argv[1] argv[2...]"
    api.SetArgv(argc - 2, argv + 2);
    api.Run("info", &ui);

    api.Final(&e);

    if (e.Test()) {
        e.Fmt(&msg);
        fprintf(stderr, "%s\n", msg.Text());
        return 1;
    }

    P4Libraries::Shutdown(P4LIBRARIES_INIT_ALL, &e);

    if (e.Test()) {
        e.Fmt(&msg);
        fprintf(stderr, "%s\n", msg.Text());
        return 1;
    }

    return 0;
}
