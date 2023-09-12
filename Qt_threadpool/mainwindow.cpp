#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include <QThreadPool>
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
        QThreadPool::globalInstance()->start(gen);
    });
    connect(gen, &Generate::sendArray,bubble,&BubbleSort::recNum);
    connect(gen, &Generate::sendArray, quick, &QuickSort::recNum);

    //接受数据
    connect(gen,&Generate::sendArray,this,[=](QVector<int> list)
    {
        QThreadPool::globalInstance()->start(bubble);
        QThreadPool::globalInstance()->start(quick);
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



}

MainWindow::~MainWindow()
{
    delete ui;
}

