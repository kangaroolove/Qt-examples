#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLineSeries>
#include <QDateTime>
#include <QChartView>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QChart>
#include <QDebug>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if 1
    QLineSeries *series = new QLineSeries;
    series->setName("Time");

    QDateTime xValue;
    xValue.setDate(QDate(2012, 1 , 18));
    xValue.setTime(QTime(9, 34));
    qreal yValue = 4;
    series->append(xValue.toMSecsSinceEpoch(), yValue);

    xValue.setDate(QDate(2013, 5 , 11));
    xValue.setTime(QTime(11, 14));

    qreal yValue2 = 50;
    series->append(xValue.toMSecsSinceEpoch(), yValue2);

    QChart *chart = new QChart;
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("yyyy-MM-dd");
    axisX->setTickCount(2);
    axisX->setLabelsAngle(-45);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("fdafdsa");
    axisY->setRange(0, 100);

    chart->addSeries(series);
    chart->setAxisY(axisY, series);
    chart->setAxisX(axisX, series);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHints(QPainter::Antialiasing);
#endif
    setCentralWidget(chartView);

}

MainWindow::~MainWindow()
{
    delete ui;
}

