#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chart = new QChart();
    chartView = new QChartView();
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    lineSeries = new QLineSeries();
    extendLineSeries = new QLineSeries();
    pointSeries = new QScatterSeries();
    extendPointSeries = new QScatterSeries();

    QFont font("楷体", 12);
    chart->setTitleFont(font);
    chart->legend()->setFont(font);
    chart->setTitle("色区容限调整");

    lineSeries->append(ui->p1x->text().toFloat(), ui->p1y->text().toFloat());
    lineSeries->append(ui->p2x->text().toFloat(), ui->p2y->text().toFloat());
    lineSeries->append(ui->p3x->text().toFloat(), ui->p3y->text().toFloat());
    lineSeries->append(ui->p4x->text().toFloat(), ui->p4y->text().toFloat());
    lineSeries->append(ui->p1x->text().toFloat(), ui->p1y->text().toFloat());
    lineSeries->setName("原始色区");

    pointSeries->append(ui->p1x->text().toFloat(), ui->p1y->text().toFloat());
    pointSeries->append(ui->p2x->text().toFloat(), ui->p2y->text().toFloat());
    pointSeries->append(ui->p3x->text().toFloat(), ui->p3y->text().toFloat());
    pointSeries->append(ui->p4x->text().toFloat(), ui->p4y->text().toFloat());
    pointSeries->setMarkerSize(8.0);
    pointSeries->setPointLabelsVisible(true);
    pointSeries->setPointLabelsFormat("(@xPoint, @yPoint)");
    pointSeries->setName("原始色区坐标");

    backToOriginal();

    axisX->setTitleText("X 轴");
    axisX->setRange(minValue(ui->p1x->text().toFloat(), ui->p2x->text().toFloat(), ui->p3x->text().toFloat(), ui->p4x->text().toFloat()) - 0.01, maxValue(ui->p1x->text().toFloat(), ui->p2x->text().toFloat(), ui->p3x->text().toFloat(), ui->p4x->text().toFloat()) + 0.01);
    axisX->setTickCount(9);
    axisX->setLabelFormat("%.4f");
    axisX->setLabelsFont(font);

    axisY->setTitleText("Y 轴");
    axisY->setRange(minValue(ui->p1y->text().toFloat(), ui->p2y->text().toFloat(), ui->p3y->text().toFloat(), ui->p4y->text().toFloat()) - 0.01, maxValue(ui->p1y->text().toFloat(), ui->p2y->text().toFloat(), ui->p3y->text().toFloat(), ui->p4y->text().toFloat()) + 0.01);
    axisY->setTickCount(9);
    axisY->setLabelFormat("%.4f");
    axisY->setLabelsFont(font);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addSeries(lineSeries);
    chart->addSeries(pointSeries);
    lineSeries->attachAxis(axisX);
    lineSeries->attachAxis(axisY);
    pointSeries->attachAxis(axisX);
    pointSeries->attachAxis(axisY);
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->horizontalLayout->addWidget(chartView);

    connect(ui->p1x, &QLineEdit::textChanged, this, &MainWindow::updateChart);
    connect(ui->p1y, &QLineEdit::textChanged, this, &MainWindow::updateChart);
    connect(ui->p2x, &QLineEdit::textChanged, this, &MainWindow::updateChart);
    connect(ui->p2y, &QLineEdit::textChanged, this, &MainWindow::updateChart);
    connect(ui->p3x, &QLineEdit::textChanged, this, &MainWindow::updateChart);
    connect(ui->p3y, &QLineEdit::textChanged, this, &MainWindow::updateChart);
    connect(ui->p4x, &QLineEdit::textChanged, this, &MainWindow::updateChart);
    connect(ui->p4y, &QLineEdit::textChanged, this, &MainWindow::updateChart);

    connect(ui->p1x, &QLineEdit::textChanged, this, &MainWindow::extendChart);
    connect(ui->p1y, &QLineEdit::textChanged, this, &MainWindow::extendChart);
    connect(ui->p2x, &QLineEdit::textChanged, this, &MainWindow::extendChart);
    connect(ui->p2y, &QLineEdit::textChanged, this, &MainWindow::extendChart);
    connect(ui->p3x, &QLineEdit::textChanged, this, &MainWindow::extendChart);
    connect(ui->p3y, &QLineEdit::textChanged, this, &MainWindow::extendChart);
    connect(ui->p4x, &QLineEdit::textChanged, this, &MainWindow::extendChart);
    connect(ui->p4y, &QLineEdit::textChanged, this, &MainWindow::extendChart);


    connect(ui->comboBox, &QComboBox::currentIndexChanged, this, &MainWindow::extendChart);
    connect(ui->comboBox_2, &QComboBox::currentIndexChanged, this, &MainWindow::extendChart);
}

MainWindow::~MainWindow()
{
    delete chart;
    delete chartView;
    delete axisX;
    delete axisY;
    delete lineSeries;
    delete extendLineSeries;
    delete pointSeries;
    delete extendPointSeries;
    delete ui;
}

void MainWindow::updateChart() {
    lineSeries->clear();
    pointSeries->clear();

    lineSeries->append(ui->p1x->text().toFloat(), ui->p1y->text().toFloat());
    lineSeries->append(ui->p2x->text().toFloat(), ui->p2y->text().toFloat());
    lineSeries->append(ui->p3x->text().toFloat(), ui->p3y->text().toFloat());
    lineSeries->append(ui->p4x->text().toFloat(), ui->p4y->text().toFloat());
    lineSeries->append(ui->p1x->text().toFloat(), ui->p1y->text().toFloat());

    pointSeries->append(ui->p1x->text().toFloat(), ui->p1y->text().toFloat());
    pointSeries->append(ui->p2x->text().toFloat(), ui->p2y->text().toFloat());
    pointSeries->append(ui->p3x->text().toFloat(), ui->p3y->text().toFloat());
    pointSeries->append(ui->p4x->text().toFloat(), ui->p4y->text().toFloat());

    axisX->setRange(minValue(ui->p1x->text().toFloat(), ui->p2x->text().toFloat(), ui->p3x->text().toFloat(), ui->p4x->text().toFloat()) - 0.01, maxValue(ui->p1x->text().toFloat(), ui->p2x->text().toFloat(), ui->p3x->text().toFloat(), ui->p4x->text().toFloat()) + 0.01);
    axisY->setRange(minValue(ui->p1y->text().toFloat(), ui->p2y->text().toFloat(), ui->p3y->text().toFloat(), ui->p4y->text().toFloat()) - 0.01, maxValue(ui->p1y->text().toFloat(), ui->p2y->text().toFloat(), ui->p3y->text().toFloat(), ui->p4y->text().toFloat()) + 0.01);
}

void MainWindow::extendChart() {
    longAxis = ui->comboBox->currentText().toFloat();
    shortAxis = ui->comboBox_2->currentText().toFloat();

    extendLineSeries->clear();
    extendPointSeries->clear();

    if (chart->series().contains(extendLineSeries)) {
        chart->removeSeries(extendLineSeries);
    }

    if (chart->series().contains(extendPointSeries)) {
        chart->removeSeries(extendPointSeries);
    }

    p1 = pointSeries->points().at(0);
    p2 = pointSeries->points().at(1);
    p3 = pointSeries->points().at(2);
    p4 = pointSeries->points().at(3);

    if (shortAxis == 0 && longAxis !=0) {
        auto newPoints = extendPoints(p1, p4, longAxis);
        auto newPoints2 = extendPoints(p2, p3, longAxis);
        p1New = newPoints.first;
        p2New = newPoints2.first;
        p3New = newPoints2.second;
        p4New = newPoints.second;

        drawExtendChart();
    } else if (longAxis == 0 && shortAxis !=0) {
        auto newPoints = extendPoints(p1, p2, shortAxis);
        auto newPoints2 = extendPoints(p3, p4, shortAxis);
        p1New = newPoints.first;
        p2New = newPoints.second;
        p3New = newPoints2.first;
        p4New = newPoints2.second;

        drawExtendChart();
    } else if (longAxis != 0 && shortAxis !=0) {
        auto newPoints = extendPoints(p1, p4, longAxis);
        auto newPoints2 = extendPoints(p2, p3, longAxis);
        p1New = newPoints.first;
        p2New = newPoints2.first;
        p3New = newPoints2.second;
        p4New = newPoints.second;

        newPoints = extendPoints(p1New, p2New, shortAxis);
        newPoints2 = extendPoints(p3New, p4New, shortAxis);
        p1New = newPoints.first;
        p2New = newPoints.second;
        p3New = newPoints2.first;
        p4New = newPoints2.second;

        drawExtendChart();
    } else {
        backToOriginal();
    }
}

QPair<QPointF, QPointF> MainWindow::extendPoints(const QPointF &pointA, const QPointF &pointB, double extendLength) {
    dx = pointB.x() - pointA.x();
    dy = pointB.y() - pointA.y();

    length = std::sqrt(dx * dx + dy * dy);

    unitDx = dx / length;
    unitDy = dy / length;

    QPointF newPointA(pointA.x() - extendLength * unitDx, pointA.y() - extendLength * unitDy);
    QPointF newPointB(pointB.x() + extendLength * unitDx, pointB.y() + extendLength * unitDy);

    return qMakePair(newPointA, newPointB);
}

void MainWindow::drawExtendChart() {
    chart->addSeries(extendLineSeries);
    chart->addSeries(extendPointSeries);
    extendLineSeries->attachAxis(axisX);
    extendLineSeries->attachAxis(axisY);
    extendPointSeries->attachAxis(axisX);
    extendPointSeries->attachAxis(axisY);

    extendLineSeries->append(p1New.x(), p1New.y());
    extendLineSeries->append(p2New.x(), p2New.y());
    extendLineSeries->append(p3New.x(), p3New.y());
    extendLineSeries->append(p4New.x(), p4New.y());
    extendLineSeries->append(p1New.x(), p1New.y());
    extendLineSeries->setName("调整色区");

    extendPointSeries->append(QString::number(p1New.x(), 'f', 4).toFloat(), QString::number(p1New.y(), 'f', 4).toFloat());
    extendPointSeries->append(QString::number(p2New.x(), 'f', 4).toFloat(), QString::number(p2New.y(), 'f', 4).toFloat());
    extendPointSeries->append(QString::number(p3New.x(), 'f', 4).toFloat(), QString::number(p3New.y(), 'f', 4).toFloat());
    extendPointSeries->append(QString::number(p4New.x(), 'f', 4).toFloat(), QString::number(p4New.y(), 'f', 4).toFloat());
    extendPointSeries->setMarkerSize(8.0);
    extendPointSeries->setColor(Qt::red);
    extendPointSeries->setPointLabelsVisible(true);
    extendPointSeries->setPointLabelsFormat("(@xPoint, @yPoint)");
    extendPointSeries->setName("调整色区坐标");

    ui->p1x_2->setText(QString::number(p1New.x(), 'f', 4));
    ui->p1y_2->setText(QString::number(p1New.y(), 'f', 4));
    ui->p2x_2->setText(QString::number(p2New.x(), 'f', 4));
    ui->p2y_2->setText(QString::number(p2New.y(), 'f', 4));
    ui->p3x_2->setText(QString::number(p3New.x(), 'f', 4));
    ui->p3y_2->setText(QString::number(p3New.y(), 'f', 4));
    ui->p4x_2->setText(QString::number(p4New.x(), 'f', 4));
    ui->p4y_2->setText(QString::number(p4New.y(), 'f', 4));
}

void MainWindow::backToOriginal() {
    ui->p1x_2->setText(QString::number(ui->p1x->text().toFloat(), 'f', 4));
    ui->p1y_2->setText(QString::number(ui->p1y->text().toFloat(), 'f', 4));
    ui->p2x_2->setText(QString::number(ui->p2x->text().toFloat(), 'f', 4));
    ui->p2y_2->setText(QString::number(ui->p2y->text().toFloat(), 'f', 4));
    ui->p3x_2->setText(QString::number(ui->p3x->text().toFloat(), 'f', 4));
    ui->p3y_2->setText(QString::number(ui->p3y->text().toFloat(), 'f', 4));
    ui->p4x_2->setText(QString::number(ui->p4x->text().toFloat(), 'f', 4));
    ui->p4y_2->setText(QString::number(ui->p4y->text().toFloat(), 'f', 4));
}

float MainWindow::maxValue(const float num1, const float num2, const float num3, const float num4) {
    return std::ceil(std::max({num1, num2, num3, num4}) * 100) /100;
}

float MainWindow::minValue(const float num1, const float num2, const float num3, const float num4) {
    return std::floor(std::min({num1, num2, num3, num4}) * 100) /100;
}
