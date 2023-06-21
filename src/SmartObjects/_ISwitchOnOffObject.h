#pragma once
class ISwitchOnOffObject
{
public:
    ISwitchOnOffObject(){}
    virtual ~ISwitchOnOffObject(){}

    virtual void SwitchOn() = 0;
    virtual void SwitchOff() = 0;
};

