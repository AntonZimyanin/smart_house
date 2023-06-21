#pragma once

class IStorer
{
public:
    IStorer()
    {}
    virtual ~IStorer()
    {}

    virtual operator bool() = 0;
    virtual bool Store(const char* psStr) = 0;
    virtual bool Store(int value) = 0;
    virtual bool Store(bool value) = 0;
};

