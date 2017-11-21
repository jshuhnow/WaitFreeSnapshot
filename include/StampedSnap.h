//
// Created by iris on 11/3/17.
//

#ifndef PROJECT3_STAMPEDSNAP_H
#define PROJECT3_STAMPEDSNAP_H

#include <vector>

template <typename T>
class StampedSnap {
public:
    long stamp;
    T value;
    T *snap;
    int length;

    StampedSnap();
    StampedSnap(T value, int length);
    StampedSnap(long stamp, T value, T* snap, int length);
    StampedSnap<T>& operator=(const StampedSnap& other);
    ~StampedSnap();
};

#include "StampedSnap.tpp"
#endif //PROJECT3_STAMPEDSNAP_H
