//
// Created by iris on 11/3/17.
//

#ifndef PROJECT3_SNAPSHOT_H
#define PROJECT3_SNAPSHOT_H
#include <vector>

template <typename T>
class Snapshot {
public:
    virtual void update(int tid, T v) = 0;
    virtual std::vector<T> scan() = 0;

};


#endif //PROJECT3_SNAPSHOT_H
