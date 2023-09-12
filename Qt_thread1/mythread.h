#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QVector>

//生成随机数
class Generate : public QObject
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);


    void working(int num);
signals:
    void sendArray(QVector<int> num);

protected:


private:


};

//冒泡排序
class BubbleSort : public QObject
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);

    void working(QVector<int> list);
signals:
    void finish(QVector<int> num);

protected:


private:

};

//快速排序
class QuickSort : public QObject
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);

    void working(QVector<int> list);

    //快速排序
    void quickSort(QVector<int> &s, int l, int r);

signals:
    void finish(QVector<int> num);

protected:


private:


};

#endif // MYTHREAD_H
