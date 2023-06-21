#pragma once
class IOpenCloseObject
{
public:
    IOpenCloseObject(){}
    virtual ~IOpenCloseObject(){}

    virtual void Open() = 0;
    virtual void Close() = 0;
};

