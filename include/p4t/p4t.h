#pragma once

#include <thread>
#include <chrono>
#include <cstdint>

#include "common.h"

#include "file_map.h"
#include "changes_result.h"
#include "describe_result.h"
#include "filelog_result.h"
#include "sizes_result.h"
#include "sync_result.h"
#include "print_result.h"
#include "users_result.h"
#include "info_result.h"
#include "client_result.h"
#include "test_result.h"
#include "stream_result.h"

class P4T {
    ClientApi m_ClientAPI;
    FileMap m_ClientMapping;
    int m_Usage;

    bool Initialize();
    bool Deinitialize();
    bool Reinitialize();
    bool CheckErrors(Error &e, StrBuf &msg);

    static const int COMMAND_RETRIES = 1;
    static const int COMMAND_REFRESH_THRESHOLD = 1;

    template <class T>
    T Run(const char *command, const std::vector<std::string> &stringArguments, const int commandRetries = COMMAND_RETRIES);

public:
    static std::string P4PORT;
    static std::string P4USER;
    static std::string P4CLIENT;
    static ClientResult::ClientSpecData ClientSpec;

    // Helix Core C++ API seems to crash while making connections parallely.
    static std::mutex InitializationMutex;

    static bool InitializeLibraries();
    static bool ShutdownLibraries();

    P4T();
    ~P4T();

    bool IsDepotPathValid(const std::string &depotPath);
    bool IsFileUnderDepotPath(const std::string &fileRevision, const std::string &depotPath);
    bool IsDepotPathUnderClientSpec(const std::string &depotPath);
    bool IsFileUnderClientSpec(const std::string &fileRevision);

    void AddClientSpecView(const std::vector<std::string> &viewStrings);

    TestResult TestConnection(const int retries = 5);
    ChangesResult ShortChanges(const std::string &path);
    ChangesResult Changes(const std::string &path);
    ChangesResult Changes(const std::string &path, const std::string &from, int32_t maxCount);
    ChangesResult ChangesFromTo(const std::string &path, const std::string &from, const std::string &to);
    ChangesResult LatestChange(const std::string &path);
    ChangesResult OldestChange(const std::string &path);
    DescribeResult Describe(const std::string &cl);
    FileLogResult FileLog(const std::string &changelist);
    SizesResult Size(const std::string &file);
    Result Sync();
    Result Sync(const std::string &path);
    SyncResult GetFilesToSyncAtCL(const std::string &path, const std::string &cl);
    PrintResult PrintFile(const std::string &filePathRevision);
    PrintResult PrintFiles(const std::vector<std::string> &fileRevisions);
    void UpdateClientSpec();
    ClientResult Client();
    StreamResult Stream(const std::string &path);
    UsersResult Users();
    InfoResult Info();
};
