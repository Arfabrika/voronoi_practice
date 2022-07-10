#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <locus.h>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int generateColor();
    void makeCentralPerps(QPointF* center);
    locus* createLocus(QPointF& site, QVector<QPointF*> points, int oldColor);

private slots:
    void on_pushButton_clicked();

private:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void updateLocuses(QVector<QPointF *> points);
    Ui::MainWindow *ui;
    QVector<locus*> locuses;
    QVector<QLineF*> centralPerps;
    math* mathmodule;
    polygon* border;
};
#endif // MAINWINDOW_H
