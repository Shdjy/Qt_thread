#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QVector>
#include <QRunnable>
#include <QObject>

//生成随机数
class Generate : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);

    void recNum(int num);

    void run() override;
signals:
    void sendArray(QVector<int> num);




private:
    int m_num;

};

//冒泡排序
class BubbleSort : public  QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);

    void recNum(QVector<int> list);

    void run() override;

signals:
    void finish(QVector<int> num);



private:
    QVector<int> m_list;

};

//快速排序
class QuickSort : public  QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);

    void recNum(QVector<int> list);

    void run() override;

    //快速排序
    void quickSort(QVector<int> &s, int l, int r);
signals:
    void finish(QVector<int> num);




private:
    QVector<int> m_list;

};

#endif // MYTHREAD_H
