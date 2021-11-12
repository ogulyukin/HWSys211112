#include "generator.h"

Generator::Generator(QObject *parent, int min, int max) : QObject(parent), QRunnable(),
    min(min), max(max), isDataValid(false)
{
    qDebug() << "Generator constructor: " << this;
}

Generator::~Generator()
{
    qDebug() << this << "/t" << QThread::currentThread() << " destroyed";
}

void Generator::stop()
{
    loop.exit();
    delete this;
}

void Generator::timeout()
{
    generate();
}




