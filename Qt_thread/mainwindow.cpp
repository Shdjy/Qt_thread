#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //创建子线程对象
    Generate *gen = new Generate;
    BubbleSort *bubble = new BubbleSort;
    QuickSort *quick = new QuickSort;

    connect(this,&MainWindow::starting,gen,&Generate::recNum);


    //启动子线程
    connect(ui->start,&QPushButton::clicked,this,[=]()
    {
        emit starting(10000);
        gen->start();
    });
    connect(gen, &Generate::sendArray,bubble,&BubbleSort::recNum);
    connect(gen, &Generate::sendArray, quick, &QuickSort::recNum);

    //接受数据
    connect(gen,&Generate::sendArray,this,[=](QVector<int> list)
    {
        bubble->start();
        quick->start();
        for(int i = 0;i < list.size();++i)
        {
            ui->randlist->addItem(QString::number(list.at(i)));
        }
    });

    connect(bubble, &BubbleSort::finish, this, [=](QVector<int> list){
           for(int i=0; i<list.size(); ++i)
           {
               ui->bubblelist->addItem(QString::number(list.at(i)));
           }
       });
    connect(quick, &QuickSort::finish, this, [=](QVector<int> list){
        for(int i=0; i<list.size(); ++i)
        {
            ui->quicklist->addItem(QString::number(list.at(i)));
        }
    });

    connect(this, &MainWindow::destroy, this, [=]()
    {
        gen->quit();
        gen->wait();
        gen->deleteLater();  // delete t1;

        bubble->quit();
        bubble->wait();
        bubble->deleteLater();

        quick->quit();
        quick->wait();
        quick->deleteLater();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

