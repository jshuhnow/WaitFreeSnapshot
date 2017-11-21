//
// Created by iris on 11/3/17.
//
#include "StampedSnap.h"
#include <vector>
#include <assert.h>
#include <iostream>

template <typename T>
WFSnapshot<T>::WFSnapshot(int capacity, T init) :
        a_table(capacity, StampedSnap<T>(init, capacity)),
        length(capacity)
{
    // Initalize a_table
    for (int i=0; i<length; i++) {
        // Allocate memory for array
        a_table[i].snap = (T*)malloc(sizeof(T) * length);
        //std::cout << "allocated " << a_table[i].snap << "\n";
    }
}

template <typename T>
WFSnapshot<T>::~WFSnapshot() {
    for (int i=0; i<length; ++i) {
        free(a_table[i].snap);
        //std::cout << "deleted " << a_table[i].snap << "\n";
    }
}

// Caller is in charge of free-ing returning pointer
// O(N^2) deep copy
template <typename T>
StampedSnap<T>* WFSnapshot<T>::collect() {
    StampedSnap<T> *res = (StampedSnap<T>*) malloc(sizeof(StampedSnap<T>) * length);
    //std::cout << "allocated " << res << "\n";

    for (int i=0; i<length; i++) {
        res[i] = a_table[i];
    }

    // res will be free-d by caller
    return res;
}


template <typename T>
void WFSnapshot<T>::update(int tid, T value) {
    T *snap = scan();
    //StampedSnap<T> oldValue = a_table[tid];
    free(a_table[tid].snap);
    //std::cout << "deleted " << a_table[tid].snap << "\n";

    a_table[tid].stamp = a_table[tid].stamp + 1;
    a_table[tid].snap = snap;
    //a_table[tid] = StampedSnap<T>(a_table[tid].stamp + 1, value, snap, length);

    // No longer being used
    //free(snap);
    //std::cout << "deleted " << snap << "\n";
}

//returns instant snapshot
//O(N^3)
template <typename T>
T* WFSnapshot<T>::scan() {
    StampedSnap<T> *oldCopy, *newCopy;

    // check that we've tried
    std::vector<bool> moved(a_table.size(), false);

    oldCopy = collect();

    while(true) {
        newCopy = collect();

        bool flag = false; //determine to keep looping
        for (int i=0; i<a_table.size(); ++i) {
            if (oldCopy[i].stamp != newCopy[i].stamp) {
                // We have already handled i-th
                if (moved[i]) {
                    // Free oldCopy except for its j-th before returning
                    for (int j=0; j<length; ++j) {
                        if (i==j) continue;
                        free(oldCopy[j].snap);
                        //std::cout << "deleted " << oldCopy[j].snap << "\n";
                    }

                    // Free newCopy before return
                    for (int j=0; j<length; ++j) {
                        free(newCopy[j].snap);
                        //std::cout << "deleted " << newCopy[j].snap << "\n";
                    }

                    free(newCopy);
                    //std::cout << "deleted " << newCopy << "\n";
                    T* tmp = oldCopy[i].snap;
                    free(oldCopy);
                    //std::cout << "deleted " << oldCopy << "\n";

                    // Make sure that we've freed all memory
                    return tmp;
                } else { // New one
                    moved[i] = true;

                    // Free oldCopy before it points newCopy
                    for (int j=0; j<length; ++j) {
                        free(oldCopy[j].snap);
                        //std::cout << "deleted " << oldCopy[j].snap << "\n";
                    }
                    oldCopy = newCopy;
                    //////////////////////////////////////

                    // narrowing the range
                    flag = true;
                    break;
                }
            }
        }

        // Keep looping
        if (flag) continue;

        // result would contain newCopy[x].value
        T *result = new T[length];
        for (int j=0; j<length; ++j) {
            result[j] = newCopy[j].value;

            // No longer being used
            free(newCopy[j].snap);
            //std::cout << "deleted " << newCopy[j].snap << "\n";
        }

        // Free oldCopy before return
        for (int j=0; j<length; ++j) {
            free(oldCopy[j].snap);
            //std::cout << "deleted " << oldCopy[j].snap << "\n";
        }
        free(newCopy);
        //std::cout << "deleted " << newCopy << "\n";
        free(oldCopy);
        //std::cout << "deleted " << oldCopy << "\n";
        return result;
    }
}
