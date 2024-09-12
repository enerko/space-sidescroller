#pragma once

template <typename T>
class Observer
{
public:
    virtual ~Observer(){};
    virtual void Notify(const T& data) = 0;
};
