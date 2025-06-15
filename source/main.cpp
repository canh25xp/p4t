#include <csignal>
#include <cstdlib>
#include <string>
#include <vector>
#include <ostream>

#include "CLI/CLI.hpp"
#include "dbg.h"

#include "log.h"
#include "p4t.h"
#include "thread_pool.h"

void SignalHandler(sig_atomic_t s);

#ifdef _WIN32
const char *strsignal(int sig);
#endif

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

    // Set the signal here because it gets reset after P4API library is initialized
    std::signal(SIGINT, SignalHandler);
    std::signal(SIGTERM, SignalHandler);

    P4T::P4USER = user;
    P4T::P4PORT = port;
    P4T::P4CLIENT = client;

    const Error &e = P4T().TestConnection().GetError();
    bool ok = e.IsError() == 0;
    if (ok) {
        INFO("Perforce server is available");
    } else {
        ERROR("Error occurred while connecting to " << P4T::P4PORT);
        return 1;
    }

    P4T::ClientSpec = P4T().Client().GetClientSpec();

    auto name = P4T::ClientSpec.client;
    auto views = P4T::ClientSpec.mapping;

    if (views.empty()) {
        WARN("Client " << name << " is empty.");
    } else {
        PRINT("Client " << name << " has " << views.size() << " mappings");
        for (auto view : views) {
            PRINT(view);
        }
    }

    if (!P4T::ShutdownLibraries()) {
        return 1;
    }

    return 0;
}

#ifdef _WIN32
const char *strsignal(int sig) {
    switch (sig) {
    case SIGINT: return "Interrupt";
    case SIGABRT: return "Abort";
    case SIGFPE: return "Floating point exception";
    case SIGILL: return "Illegal instruction";
    case SIGSEGV: return "Segmentation fault";
    case SIGTERM: return "Termination request";
    default: return "Unknown signal";
    }
}
#endif

void SignalHandler(sig_atomic_t s) {
    static bool called = false;
    if (called) {
        WARN("Already received an interrupt signal, waiting for threads to shutdown.");
        return;
    }
    called = true;

    ERROR("Signal Received: " << strsignal(s));

    ThreadPool::GetSingleton()->ShutDown();

    std::exit(s);
}
