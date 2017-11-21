//
// Created by iris on 11/3/17.
//

#include "StampedSnap.h"
#include <iostream>

template <typename T>
StampedSnap<T>::StampedSnap() {}

template <typename T>
StampedSnap<T>::StampedSnap(T value, int length) :
        stamp(0),
        length(length),
        value(value)
{}

template <typename T>
StampedSnap<T>::StampedSnap(long stamp, T value, T *snap, int length) :
        stamp(stamp), value(value), snap(snap), length(length)
{}

template <typename T>
StampedSnap<T>& StampedSnap<T>::operator=(const StampedSnap &other) {
//    std::cout << "Copy constructor called " << other.stamp << "\n";
    if (this != &other) {
        stamp = other.stamp;
        value = other.value;
        snap = (T*)malloc(sizeof(T)* (other.length));
        //std::cout << "allocated " << snap << "\n";
        for (int i=0; i<other.length; i++) {
            snap[i] = other.snap[i];
        }
        length = other.length;
    }
    return *this;
}

template <typename T>
StampedSnap<T>::~StampedSnap() {
    //we will free snap outside this class (it is publicly declared)
}
