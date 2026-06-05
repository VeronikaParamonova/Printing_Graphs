#ifndef COMPUTER_H
#define COMPUTER_H

#include "iprocessor.h"
#include <memory>

class Computer
{
public:
    Computer(std::shared_ptr<IPRocessor> proc) : m_proc(proc) {}//внедряем зависимость не через сеттер, а сразу в конструкторе
    void GetInfo();
private:
    std::shared_ptr<IPRocessor> m_proc;
};

#endif // COMPUTER_H
