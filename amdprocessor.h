#ifndef AMDPROCESSOR_H
#define AMDPROCESSOR_H

#include "iprocessor.h"
#include <string>


class AMDProcessor: public IProcessor
{
    Q_OBJECT

public:
    AMDProcessor(IProcessor::ProcessorType type, double speed, const std::string vers) : m_type(type), m_speed(speed), m_vers(vers) {}
    std::string GetProcessorInfo() override
    {
        std::string type_s;
        if (m_type == IProcessor::x64)
        {
            type_s = "x64";
        }
        else
        {
            type_s = "x86";
        }
        std::string res = "AMD Processor for " + type_s + ", " + std::to_string(m_speed) + ", " + m_vers;
        return(res);
    }
    void LogProcessorInfo() override
    {
        std::string inf = GetProcessorInfo();
        emit logInfo(inf);
    }
private:    
    IProcessor::ProcessorType m_type;
    double m_speed;
    std::string m_vers;
};

#endif // AMDPROCESSOR_H
