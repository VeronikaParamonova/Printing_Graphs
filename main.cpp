#include <QCoreApplication>//для прил c GUI
#include <QApplication> //для прил без GUI
#include <QDebug>
#include <memory>
#include "ModelData.h"
#include "IAdapter.h"
#include "SqlAdaptee.h"
#include "JsonAdaptee.h"
#include "SqlAdapter.h"
#include "JsonAdapter.h"
#include "ioccontainer.h"
#include <QFileInfo>
#include <QStringList>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto container = std::make_shared<IOCContainer>();

    // Регистрируем Adaptee (синглтоны)
    container->RegisterInstance<SqlAdaptee>(std::make_shared<SqlAdaptee>());
    container->RegisterInstance<JsonAdaptee>(std::make_shared<JsonAdaptee>());

     // Регистрируем Adapter (конкретные адаптеры)
    container->RegisterFactory<SqlAdapter, SqlAdapter, SqlAdaptee>();
    container->RegisterFactory<JsonAdapter, JsonAdapter, JsonAdaptee>();

    // Регистрируем ОДИН адаптер для IAdapter
    container->RegisterAdapter<IAdapter>(
        // Условие: принимает ЛЮБОЙ файл, который мы поддерживаем
        [](const QString& path) {
            return path.endsWith(".db") || path.endsWith(".sqlite") || path.endsWith(".sqlite3") || path.endsWith(".json");
        },
        // Фабрика: выбирает адаптер по расширению файла
        [&container](const QString& path) -> std::shared_ptr<IAdapter> {
            if (path.endsWith(".db") || path.endsWith(".sqlite") || path.endsWith(".sqlite3"))
            {
                return std::static_pointer_cast<IAdapter>(container->GetObject<SqlAdapter>());
            }
            else if (path.endsWith(".json"))
            {
                return std::static_pointer_cast<IAdapter>(container->GetObject<JsonAdapter>());
            }
            return nullptr;
        }
        );

    // Регистрируем графики в контейнере
    container->RegisterInstance<IChart>(std::make_shared<BarChart>(), "BarChart");
    container->RegisterInstance<IChart>(std::make_shared<LineChart>(), "LineChart");

    MainWindow window(container);
    window.show();

    return app.exec();
}
