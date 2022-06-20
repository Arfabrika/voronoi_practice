#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPair>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    Ui::MainWindow *ui;
    QVector<QPair<int, int>> points;
};
#endif // MAINWINDOW_H
