#include "mythread.h"
#include <QElapsedTimer>
#include <QDebug>
#include <QThread>
Generate::Generate(QObject *parent) : QObject(parent)
{

}



void Generate::working(int num)
{
    qDebug()<<"生成随机数的线程地址"<<QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for(int i = 0;i < num;i++)
    {
        list.push_back(qrand() % 100000);
    }
    int milsec = time.elapsed();
    qDebug()<<"生成"<<num<<"个随机数总共用时:"<<milsec<<"毫秒";
    emit sendArray(list);
}



BubbleSort::BubbleSort(QObject *parent) : QObject(parent)
{

}



void BubbleSort::working(QVector<int> list)
{
    qDebug()<<"冒泡排序的线程地址"<<QThread::currentThread();

    QElapsedTimer time;
    time.start();
    for(int i = 0;i < list.size();++i)
    {
        for(int j = 0;j < list.size()-i-1;++j)
        {
            if(list[j] > list[j+1])
            {
                int temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
    int milsec = time.elapsed();
    qDebug()<<"冒泡排序共用时:"<<milsec<<"毫秒";
    emit finish(list);
}




QuickSort::QuickSort(QObject *parent) : QObject(parent)
{

}



void QuickSort::quickSort(QVector<int> &s, int l, int r)
{
    if(l < r)
    {
        int i = l;
        int j = r;

       int x = s[l];
        while(i < j)
        {
            //从右向左找到小于x的数
            while(i < j && s[j] >= x)
            {
                j--;
            }
            if(i < j)
            {
                s[i++] = s[j];

            }
            //从左向右找到大于等于x的数
            while(i < j && s[i] < x)
            {
                i++;
            }
            if(i < j)
            {
                s[j--] = s[i];

            }
        }
        s[i] = x;
        quickSort(s, l, i - 1);
        quickSort(s, i + 1, r);
    }
}

void QuickSort::working(QVector<int> list)
{
    qDebug()<<"快速排序的线程地址"<<QThread::currentThread();

    QElapsedTimer time;
    time.start();
    quickSort(list, 0, list.size()-1);
    int milsec = time.elapsed();
    qDebug()<<"快速排序共用时:"<<milsec<<"毫秒";
    emit finish(list);
}
