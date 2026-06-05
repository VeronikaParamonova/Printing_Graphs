#include "computer.h"
#include <iostream>

void Computer::GetInfo()
{
    std::cout << "Computer configuration: " << m_proc->GetProcessorInfo() << std::endl;
}
