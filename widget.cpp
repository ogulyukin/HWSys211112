#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget), timer(new QTimer(this)),
      fibo(false), rnd(false)
{
    ui->setupUi(this);
    pool = QThreadPool::globalInstance();
    pool->setExpiryTimeout(2000); //not shure how it work... don't help.
    timer->setInterval(1000);
}

Widget::~Widget()
{
    qDebug() << "Main thread: " << QThread::currentThread() << " destroyed";
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    if(rnd)
        return;
    rnd = true;
    pool->releaseThread(); //This release threads for newxt use!!!
    qDebug() << "Main Thread: " << QThread::currentThread() << "Start Random Generator...";
    Generator* randThread = new RandomNumGenerator(nullptr, ui->minLineEdit->text().toInt(), ui->maxLineEdit->text().toInt());
    connect(this, &Widget::killRandomThread, randThread, &Generator::stop);
    connect(randThread, &Generator::newGenerate, this, &Widget::onRandomNumber);
    startNewThread(randThread);
}


void Widget::on_fibostartButton_clicked()
{
    if(fibo)
        return;
    fibo = true;
    pool->releaseThread(); //This release threads for newxt use!!!
    qDebug() << "Main Thread: " << QThread::currentThread() << "Start Fibonachi Generator...";
    Generator* fiboThread = new FiboNumGenerator(nullptr, ui->minLineEdit->text().toInt(), ui->maxLineEdit->text().toInt());
    connect(this, &Widget::killFiboThread, fiboThread, &Generator::stop);
    connect(fiboThread, &Generator::newGenerate, this, &Widget::onFiboNumber);
    startNewThread(fiboThread);
}

void Widget::on_pushButton_2_clicked()
{
    emit killRandomThread();
    rnd = false;
}


void Widget::on_fiboStopButton_clicked()
{
    emit killFiboThread();
    fibo = false;
}


void Widget::onRandomNumber(int number)
{
    ui->randomLabel->setText(QString::number(number));
}

void Widget::onFiboNumber(int number)
{
    ui->fibonachiLabel->setText(QString::number(number));
}


void Widget::startNewThread(Generator* generator)
{
    generator->setAutoDelete(true);
    connect(timer, &QTimer::timeout, generator, &Generator::timeout);
    pool->start(generator);
    if(!timer->isActive())
        timer->start();
    qDebug() << "The timer is started: " << timer->isActive();
    qDebug() << "Threads avaible: " << pool->maxThreadCount() << " Used: " << pool->activeThreadCount();
    qDebug() << "Ideal Thread count: " << QThread::idealThreadCount();
}

