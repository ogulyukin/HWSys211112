#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QRandomGenerator>
#include <QtConcurrent>
#include <QTimer>
#include "randomnumgenerator.h"
#include <QThreadPool>
#include "fibonumgenerator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void killRandomThread();
    void killFiboThread();
    void tick();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void onRandomNumber(int number);
    void onFiboNumber(int number);
    void on_fibostartButton_clicked();
    void on_fiboStopButton_clicked();

private:
    Ui::Widget *ui;
    QThreadPool *pool;
    QTimer *timer;
    void startNewThread(Generator* generator);
    bool fibo, rnd;
};
#endif // WIDGET_H
