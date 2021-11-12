#include "randomnumgenerator.h"

RandomNumGenerator::RandomNumGenerator(QObject *parent, int min, int max) :
    Generator(parent, min, max)
{
    qDebug() << "Rnd Constructor: " << this;
}

RandomNumGenerator::~RandomNumGenerator()
{
    qDebug() << "Rnd Deconstructor: " << this;
}

void RandomNumGenerator::generate()
{
    if(isDataValid)
        emit newGenerate(QRandomGenerator::global()->bounded(min, max));
}

void RandomNumGenerator::checkMinMax()
{
    isDataValid = true;
    if(max == 0 || max <= min)
        isDataValid = false;
}

void RandomNumGenerator::run()
{
    qDebug() << "Rnd generator thread: " << QThread::currentThread() << "started";
    checkMinMax();
    loop.exec();
    qDebug() << "Exiting loop...";
}

