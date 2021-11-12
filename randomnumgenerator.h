#ifndef RANDOMNUMGENERATOR_H
#define RANDOMNUMGENERATOR_H

#include "generator.h"
#include <QRandomGenerator>

class RandomNumGenerator : public Generator
{
    Q_OBJECT
public:
    explicit RandomNumGenerator(QObject *parent = nullptr, int min = 2, int max = 0);
    ~RandomNumGenerator();
    // Generator interface
private:
    virtual void generate() override;
    virtual void checkMinMax() override;

    // QRunnable interface
public:
    virtual void run() override;
};

#endif // RANDOMNUMGENERATOR_H
