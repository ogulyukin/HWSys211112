#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QRunnable>
#include <QEventLoop>

class Generator : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = nullptr, int min = 2, int max = 0);
    ~Generator();


signals:
    void newGenerate(int number);

private:

public slots:
    void stop();
    void timeout();

protected:
    virtual void generate() = 0;
    virtual void checkMinMax() = 0;
    int min;
    int max;
    bool isDataValid;
    QEventLoop loop;
};

#endif // GENERATOR_H
