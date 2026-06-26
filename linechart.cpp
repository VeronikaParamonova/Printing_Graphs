#include "linechart.h"

QT_CHARTS_USE_NAMESPACE

QChartView* LineChart::createChart(const DataSet& data)
{
    if (data.isEmpty()) {
        return new QChartView();
    }

    //Создаём серию точек
    QLineSeries* series = new QLineSeries();
    series->setName("Значения");

    //Добавляем данные
    int maxPoints = 1000;
    int step = qMax(1, data.size() / maxPoints);

    for (int i = 0; i < data.size(); i += step) {
        qint64 timestamp = data.points[i].date.toMSecsSinceEpoch();
        series->append(timestamp, data.points[i].value);
    }

    //Создаём ось с датами
    QDateTimeAxis* axisX = new QDateTimeAxis();
    axisX->setTitleText("Дата");
    axisX->setFormat("dd.MM");
    axisX->setTickCount(10);

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Значение");

    //Создаём график
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(data.name);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}
