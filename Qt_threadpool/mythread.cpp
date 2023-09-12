#include "mythread.h"
#include <QElapsedTimer>
#include <QDebug>

Generate::Generate(QObject *parent) : QObject(parent), QRunnable()
{
    setAutoDelete(true);
}

void Generate::recNum(int num)
{
    m_num = num;
}

void Generate::run()
{
    qDebug()<<"生成随机数的线程地址"<<QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for(int i = 0;i < m_num;i++)
    {
        list.push_back(qrand() % 100000);
    }
    int milsec = time.elapsed();
    qDebug()<<"生成"<<m_num<<"个随机数总共用时:"<<milsec<<"毫秒";
    emit sendArray(list);
}



BubbleSort::BubbleSort(QObject *parent) : QObject(parent), QRunnable()
{
    setAutoDelete(true);
}

void BubbleSort::recNum(QVector<int> list)
{
    m_list = list;
}

void BubbleSort::run()
{
    qDebug()<<"冒泡排序的线程地址"<<QThread::currentThread();

    QElapsedTimer time;
    time.start();
    for(int i = 0;i < m_list.size();++i)
    {
        for(int j = 0;j < m_list.size()-i-1;++j)
        {
            if(m_list[j] > m_list[j+1])
            {
                int temp = m_list[j];
                m_list[j] = m_list[j+1];
                m_list[j+1] = temp;
            }
        }
    }
    int milsec = time.elapsed();
    qDebug()<<"冒泡排序共用时:"<<milsec<<"毫秒";
    emit finish(m_list);
}




QuickSort::QuickSort(QObject *parent) : QObject(parent), QRunnable()
{
    setAutoDelete(true);
}

void QuickSort::recNum(QVector<int> list)
{
    m_list = list;
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

void QuickSort::run()
{
    qDebug()<<"快速排序的线程地址"<<QThread::currentThread();

    QElapsedTimer time;
    time.start();
    quickSort(m_list, 0, m_list.size()-1);
    int milsec = time.elapsed();
    qDebug()<<"快速排序共用时:"<<milsec<<"毫秒";
    emit finish(m_list);
}
