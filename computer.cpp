#include "computer.h"
#include <iostream>

void Computer::GetInfo()
{
    emit logInfo("Computer configuration: " + m_proc->GetProcessorInfo());
}
