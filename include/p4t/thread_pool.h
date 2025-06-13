#pragma once

#include <vector>
#include <thread>
#include <deque>
#include <functional>
#include <atomic>
#include <condition_variable>

class P4T;

class ThreadPool {
    typedef std::function<void(P4T *)> Job;

    std::vector<std::thread> m_Threads;
    std::mutex m_ThreadExceptionsMutex;
    std::vector<std::exception_ptr> m_ThreadExceptions;
    std::vector<std::string> m_ThreadNames;
    std::vector<P4T> m_P4Contexts;

    std::deque<Job> m_Jobs;
    std::mutex m_JobsMutex;

    std::condition_variable m_CV;

    std::atomic<bool> m_ShouldStop;
    bool m_HasShutDownBeenCalled;

    std::atomic<long> m_JobsProcessing;

public:
    static ThreadPool *GetSingleton();

    ~ThreadPool();

    void Initialize(int size);
    void AddJob(Job function);
    void Wait();
    void RaiseCaughtExceptions();
    void ShutDown();

    void Resize(int size);
    int GetThreadCount() const { return m_Threads.size(); }
};
