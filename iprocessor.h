#ifndef IPROCESSOR_H
#define IPROCESSOR_H

#include<string>
#include <QObject>

class IProcessor : public QObject
{

    Q_OBJECT

public:
    enum ProcessorType
    {
        x86,
        x64
    };

    explicit IProcessor(QObject* parent = nullptr) : QObject(parent) {}//QObject требует вызова своего конструктора в списке инициализации
    virtual ~IProcessor() = default;
    virtual std::string GetProcessorInfo() = 0;
    virtual void LogProcessorInfo() = 0;

signals:
    void logInfo(const std::string& inf);
};

#endif // IPROCESSOR_H
