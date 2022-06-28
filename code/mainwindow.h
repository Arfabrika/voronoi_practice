#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPair>
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
    void makeCentralPerps(point* center);

private:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    Ui::MainWindow *ui;
    QVector<locus*> locuses;
    QVector<QLine*> centralPerps;
    math* mathmodule;
};
#endif // MAINWINDOW_H
