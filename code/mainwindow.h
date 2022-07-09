#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
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

private:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void updateLocuses(QVector<QPointF *> points);
    Ui::MainWindow *ui;
    QVector<locus*> locuses;
    QVector<QLineF*> centralPerps;
    math* mathmodule;
    polygon* border;
    int cnt = 0;
};
#endif // MAINWINDOW_H
