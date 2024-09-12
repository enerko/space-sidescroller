#pragma once
#include <vector>
#include <algorithm>
#include "Observer.h"

template <typename T>
class Subject
{
public:
    void RegisterObserver(Observer<T>* observer);
    void UnregisterObserver(Observer<T>* observer);
    void NotifyObservers(const T& data) const;

private:
    std::vector<Observer<T>*> mObservers;
};

#include "Subject.inl"