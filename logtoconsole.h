#ifndef LOGTOCONSOLE_H
#define LOGTOCONSOLE_H

#include "ilog.h"
#include <iostream>

class LogToConsole : public ILog
{
    Q_OBJECT

public:
    void log(const std::string& mes) override;

public slots:
    void logMes(const std::string& mes) override;
};

#endif // LOGTOCONSOLE_H
