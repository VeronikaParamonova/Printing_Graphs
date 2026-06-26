#ifndef COMPUTER_H
#define COMPUTER_H

#include "iprocessor.h"
#include <memory>
#include <QObject>

class Computer : public QObject
{
    Q_OBJECT

public:
    Computer(std::shared_ptr<IProcessor> proc, QObject* parent = nullptr) : QObject(parent), m_proc(proc) {}//внедряем зависимость не через сеттер, а сразу в конструкторе
    void GetInfo();

signals:
    void logInfo(const std::string& inf);

private:
    std::shared_ptr<IProcessor> m_proc;
};

#endif // COMPUTER_H
