#pragma once
#include "Subject.h"
#include <iostream>

template <typename T>
void Subject<T>::RegisterObserver(Observer<T>* observer)
{
    mObservers.push_back(observer);
    std::cout << "Registered observer" << mObservers.size() << std::endl;
}

template <typename T>
void Subject<T>::UnregisterObserver(Observer<T>* observer)
{
    auto iter = std::find(mObservers.begin(), mObservers.end(), observer);
    if (iter != mObservers.end())
    {
        mObservers.erase(iter);
    }
}

template <typename T>
void Subject<T>::NotifyObservers(const T& data) const
{
    for (auto obs : mObservers)
    {
        std::cout << "Notifying observers... " << std::endl;
        obs->Notify(data);
    }
    std::cout << "Notified observer" << std::endl;
}