//
// Created by iris on 11/3/17.
//

#ifndef PROJECT3_MANAGER_H
#define PROJECT3_MANAGER_H

#include "WFSnapshot.h"
#include <vector>
#include <thread>
#include <mutex>
class Manager {
private:
    std::vector<std::thread> threads;
    WFSnapshot<int> snapshot; // Wait-free snapshot
    void run(int tid);
    std::size_t threadCount;
    volatile int status;

    int totalUpdate;
    std::mutex lk; // this should be used only for evaluating performance

public:
    static const int RUNNING_TIME=60;
    Manager(int threadCount);

    enum status_t {PENDING,RUNNING,END};
    // returns how man updates has been done
    int join();
};

#endif //PROJECT3_MANAGER_H
