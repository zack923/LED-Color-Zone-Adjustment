#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QDebug>
#include <QMessageBox>
#include <QPointF>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateChart();
    void extendChart();
    QPair<QPointF, QPointF> extendPoints(const QPointF &pointA, const QPointF &pointB, double extendLength);
    void drawExtendChart();
    void backToOriginal();
    float maxValue(const float num1, const float num2, const float num3, const float num4);
    float minValue(const float num1, const float num2, const float num3, const float num4);

private:
    Ui::MainWindow *ui;
    QChart *chart;
    QChartView *chartView;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QLineSeries *lineSeries;
    QLineSeries *extendLineSeries;
    QScatterSeries *pointSeries;
    QScatterSeries *extendPointSeries;
    QPointF p1;
    QPointF p2;
    QPointF p3;
    QPointF p4;
    QPointF p1New;
    QPointF p2New;
    QPointF p3New;
    QPointF p4New;
    float longAxis;
    float shortAxis;
    double dx;
    double dy;
    double length;
    double unitDx;
    double unitDy;

};
#endif // MAINWINDOW_H
