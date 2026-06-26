#include "mainwindow.h"

#include <QApplication>
#include "ioccontainer.h"
#include "iprocessor.h"
#include "intelprocessor.h"
#include "amdprocessor.h"
#include "computer.h"
#include "logtoconsole.h"
#include <memory>
#include <iostream>


using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //РАБОТА С ЛОКАЛЬНЫМ КОНТЕЙНЕРОМ
    IOCContainer injector;

    //Регистрируем логгер
    auto logger = make_shared<LogToConsole>();
    injector.RegisterInstance<ILog>(logger);//регистрируем уже созданный объект

    //регистрация уже созданного объекта (синглтон) Данный тест ПЛОХ ТЕМ, что пользователь использует make_shared вне ответственности контейнера
    auto intelProc = make_shared<IntelProcessor>(IProcessor::x64, 3.4, "Core i7-11700K");
    injector.RegisterInstance<IProcessor>(intelProc);

    auto proc1 = injector.GetObject<IProcessor>();
    QObject::connect(proc1.get(), &IProcessor::logInfo, logger.get(), &LogToConsole::logMes);

    proc1->LogProcessorInfo();


    auto proc1_again = injector.GetObject<IProcessor>();
    QObject::connect(proc1_again.get(), &IProcessor::logInfo, logger.get(), &LogToConsole::logMes);


    injector.GetObject<ILog>()->log("Get again: ");
    proc1_again->LogProcessorInfo();//выведет два раза т к, подключив proc1_again к слоту logMes, мы подключили proc1 второй раз. Т к это ОДИН И ТОТ ЖЕ объект

    if(proc1.get() == proc1_again.get())
    {
        injector.GetObject<ILog>()->log("identical pointer");
    }
    else
    {
        injector.GetObject<ILog>()->log("unidentical pointer");
    }

    //перерегестрируем IProcessor на фабрику вместо синглтона
    std::function<std::shared_ptr<IProcessor>()> functor1 = []() { //здесь же, хоть мы и в ручную прописываем make_shared в лямбде, но когда запускать эту лямбду, решает уже контейнер
        return make_shared<AMDProcessor>(IProcessor::x86, 3.6, "Ryzen 7 5800X");
    };
    injector.RegisterFunctor<IProcessor>(functor1);

    auto proc2 = injector.GetObject<IProcessor>();
    QObject::connect(proc2.get(), &IProcessor::logInfo, logger.get(), &LogToConsole::logMes);

    proc2->LogProcessorInfo();


    auto proc2_again = injector.GetObject<IProcessor>();
    QObject::connect(proc2_again.get(), &IProcessor::logInfo, logger.get(), &LogToConsole::logMes);

    injector.GetObject<ILog>()->log("Get again: ");
    proc2_again->LogProcessorInfo();
    if(proc2.get() == proc2_again.get())
    {
        injector.GetObject<ILog>()->log("identical pointer");
    }
    else
    {
        injector.GetObject<ILog>()->log("unidentical pointer");
    }

    //регистрируем Computer (IProcessor уже как фабрика через RegisterFunctor)
    injector.RegisterFactory<Computer, Computer, IProcessor>();

    auto comp1 = injector.GetObject<Computer>();
    QObject::connect(comp1.get(), &Computer::logInfo, logger.get(), &LogToConsole::logMes);

    injector.GetObject<ILog>()->log("Computer 1: ");
    comp1->GetInfo();

    //поменяем процессор для второго компьютера
    std::function<std::shared_ptr<IProcessor>()> functor2 = []() {
        return make_shared<IntelProcessor>(IProcessor::x64, 3.4, "Core i7-11700K");
    };
    injector.RegisterFunctor<IProcessor>(functor2);

    auto comp2 = injector.GetObject<Computer>();
    QObject::connect(comp2.get(), &Computer::logInfo, logger.get(), &LogToConsole::logMes);

    injector.GetObject<ILog>()->log("Computer 2: ");
    comp2->GetInfo();

    //РАБОТА С ГЛОБАЛЬНЫМ КОНТЕЙНЕРОМ
    injector.GetObject<ILog>()->log("Global container: ");

    gContainer.RegisterFunctor<IProcessor>(functor2);
    gContainer.RegisterFactory<Computer, Computer, IProcessor>();

    auto g_comp1 = gContainer.GetObject<Computer>();
    QObject::connect(g_comp1.get(), &Computer::logInfo, logger.get(), &LogToConsole::logMes);


    g_comp1->GetInfo();


    gContainer.RegisterFunctor<IProcessor>(functor1);

    auto g_comp2 = gContainer.GetObject<Computer>();
    QObject::connect(g_comp2.get(), &Computer::logInfo, logger.get(), &LogToConsole::logMes);


    g_comp2->GetInfo();

    //также можно добавить другие типы в контейнер
    std::function<std::shared_ptr<int>()> functor3 = []() { //здесь же, хоть мы и в ручную прописываем make_shared в лямбде, но когда запускать эту лямбду, решает уже контейнер
        return make_shared<int>(123);
    };

    std::function<std::shared_ptr<std::string>()> functor4 = []() { //здесь же, хоть мы и в ручную прописываем make_shared в лямбде, но когда запускать эту лямбду, решает уже контейнер
        return make_shared<std::string>("string");
    };

    gContainer.RegisterFunctor(functor3);
    gContainer.RegisterFunctor(functor4);

    injector.GetObject<ILog>()->log(std::to_string(*gContainer.GetObject<int>()));
    injector.GetObject<ILog>()->log(*gContainer.GetObject<std::string>());

    return a.exec();
}
