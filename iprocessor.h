#ifndef IPROCESSOR_H
#define IPROCESSOR_H

#include<string>

class IPRocessor
{

public:
    enum ProcessorType
    {
        x86,
        x64
    };

    IPRocessor();
    virtual ~IPRocessor() = default;
    virtual std::string GetProcessorInfo() = 0;
};

#endif // IPROCESSOR_H
