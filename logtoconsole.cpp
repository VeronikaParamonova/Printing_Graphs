#include "logtoconsole.h"


void LogToConsole::log(const std::string& mes)
{
    std::cout << mes << std::endl;
}


void LogToConsole::logMes(const std::string& mes)
{
    log(mes);
}
