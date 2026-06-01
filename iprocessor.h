#ifndef IPROCESSOR_H
#define IPROCESSOR_H

#include<string>

class IPRocessor
{
public:
    IPRocessor();
    virtual ~IProcessor() = default;
    virtual std::string GetProcessorInfo() = 0;
};

#endif // IPROCESSOR_H
