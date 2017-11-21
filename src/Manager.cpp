//
// Created by iris on 11/3/17.
//

#include "Manager.h"
#include "WFSnapshot.h"
#include <iostream>
const int Manager::RUNNING_TIME;

Manager::Manager(int threadCount) :
        snapshot(threadCount, 0),
        threadCount(threadCount),
        totalUpdate(0),
		status(0)
{
    threads.resize(threadCount);
	status = PENDING;
    for (std::size_t i=0; i<threadCount; ++i) {
        threads[i] = std::thread(&Manager::run, this, i);
    }

    //std::this_thread::sleep_for(std::chrono::seconds(5));
    status = RUNNING;
    __sync_synchronize();


    std::this_thread::sleep_for(std::chrono::seconds(RUNNING_TIME));

    __sync_synchronize();
    status = END;
}
int Manager::join() {
    for (std::size_t i=0; i<threadCount; ++i) {
        threads[i].join();
    }
    return totalUpdate;
}
void Manager::run(int tid) {
    int localUpdate = 0;
    while(status==PENDING); // spinlock
    while(status==RUNNING) {
        snapshot.update(tid, localUpdate);
        ++localUpdate;
    }
    {
        std::unique_lock<std::mutex> lock(lk);
        totalUpdate += localUpdate;
    }
}
