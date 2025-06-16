#pragma once

#include <stdint.h>
#include <memory>
#include <condition_variable>
#include <mutex>
#include <string>
#include <vector>

#include "branch_set.h"
#include "file_data.h"

struct ChangeList {
    enum State {
        Initialized,
        Described,
        Downloaded,
        Freed
    };

    std::string number;
    std::string user;
    std::string description;
    int64_t timestamp = 0;
    std::unique_ptr<ChangedFileGroups> changedFileGroups = ChangedFileGroups::Empty();

    std::unique_ptr<std::condition_variable> stateCV;
    std::unique_ptr<std::mutex> stateMutex;
    int filesDownloaded;
    State state;

    ChangeList() = default; // Defaulted so that vector<ChangeList>::resize() can be used.
    ChangeList(const std::string &number, const std::string &description, const std::string &user, const int64_t &timestamp);

    ChangeList(const ChangeList &other) = delete;
    ChangeList &operator=(const ChangeList &) = delete;
    ChangeList(ChangeList &&) = default;
    ChangeList &operator=(ChangeList &&) = default;
    ~ChangeList() = default;

    void PrepareDownload(const BranchSet &branchSet);
    void StartDownload(const int &printBatch);
    void Flush(std::shared_ptr<std::vector<std::string>> printBatchFiles, std::shared_ptr<std::vector<FileData *>> printBatchFileData);
    void WaitForDownload();
    void Clear();

    friend bool operator==(ChangeList const &cl1, ChangeList const &cl2) {
        return cl1.timestamp == cl2.timestamp;
    }

    friend bool operator!=(ChangeList const &cl1, ChangeList const &cl2) {
        return !(cl1 == cl2);
    }

    friend bool operator<(ChangeList const &cl1, ChangeList const &cl2) {
        return cl1.timestamp < cl2.timestamp;
    }

    friend bool operator<=(ChangeList const &cl1, ChangeList const &cl2) {
        return (cl1 < cl2) || (cl1 == cl2);
    }

    friend bool operator>(ChangeList const &cl1, ChangeList const &cl2) {
        return cl2 < cl1;
    }

    friend bool operator>=(ChangeList const &cl1, ChangeList const &cl2) {
        return (cl1 > cl2) || (cl1 == cl2);
    }
};
