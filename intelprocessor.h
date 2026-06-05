#ifndef INTELPROCESSOR_H
#define INTELPROCESSOR_H

#include "iprocessor.h"
#include <string>


class IntelProcessor: public IPRocessor
{
public:
    IntelProcessor(IPRocessor::ProcessorType type, double speed, const std::string vers) : m_speed(speed), m_type(type), m_vers(vers) {}
    std::string GetProcessorInfo() override
    {
        return ("Intel Processor for" + m_vers + m_speed + m_type);
    }
private:
    std::string m_vers;
    IPRocessor::ProcessorType m_type;
    double m_speed;
};

#endif // INTELPROCESSOR_H
