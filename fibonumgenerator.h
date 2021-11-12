#ifndef FIBONUMGENERATOR_H
#define FIBONUMGENERATOR_H

#include "generator.h"

class FiboNumGenerator : public Generator
{
    Q_OBJECT
public:
    explicit FiboNumGenerator(QObject *parent = nullptr, int min = 2, int max = 0);

    // QRunnable interface
public:
    virtual void run() override;

    // Generator interface
private:
    virtual void generate() override;
    virtual void checkMinMax() override;
    void getNext();
    int one;
    int two;
};

#endif // FIBONUMGENERATOR_H
