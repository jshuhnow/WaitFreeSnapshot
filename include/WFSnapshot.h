//
// Created by iris on 11/3/17.
//

#ifndef PROJECT3_WFSNAPSHOT_H
#define PROJECT3_WFSNAPSHOT_H
#include <vector>
#include "StampedSnap.h"
#include "Snapshot.h"

template <typename T>
class WFSnapshot {
private:
    std::vector<StampedSnap<T>> a_table;
    int length;
public:
    WFSnapshot(int capacity, T init);
    ~WFSnapshot();

private:
    StampedSnap<T>* collect();
public:
    void update(int tid, T value);
    T* scan();
};



#include "WFSnapshot.tpp"
#endif //PROJECT3_WFSNAPSHOT_H
