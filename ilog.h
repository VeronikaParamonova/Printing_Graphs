#ifndef ILOG_H
#define ILOG_H

#include <string>
#include <QObject>

class ILog : public QObject
{
    Q_OBJECT

public:
    explicit ILog(QObject* parent = nullptr): QObject(parent) {};
    virtual ~ILog() = default;
    virtual void log(const std::string& mes) = 0;

public slots:
    virtual void logMes(const std::string& mes);
};

#endif // ILOG_H
