#include "fibonumgenerator.h"

FiboNumGenerator::FiboNumGenerator(QObject *parent, int min, int max) : Generator(parent, min, max)
{
    qDebug() << "Fibonachi constructor: " << this;
    one = two = 0;
}

void FiboNumGenerator::run()
{
    qDebug() << "Rnd generator thread: " << QThread::currentThread() << "started";
    checkMinMax();
    loop.exec();
    qDebug() << "Exiting loop...";
}

void FiboNumGenerator::generate()
{
    if(isDataValid && two < max)
    {
        getNext();
        if(two < max)
            emit newGenerate(two);
    }
}

void FiboNumGenerator::checkMinMax()
{
    isDataValid = true;
    if(max == min || max < 0)
        isDataValid = false;
    while(min > two)
    {
        getNext();
    }
    if(isDataValid)
        emit newGenerate(two);
}

void FiboNumGenerator::getNext()
{
    if(one == 0 && two == 0)
    {
        two = 1;
        return;
    }
    if(one == 0 && two == 1)
    {
        one = 1;
        return;
    }
    int temp = two;
    two += one;
    one = temp;
    qDebug() << "Fibo tick: " << two;
}
