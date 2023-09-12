#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QVector>

//生成随机数
class Generate : public QThread
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);

    void recNum(int num);
signals:
    void sendArray(QVector<int> num);

protected:
    void run() override;

private:
    int m_num;

};

//冒泡排序
class BubbleSort : public QThread
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);

    void recNum(QVector<int> list);
signals:
    void finish(QVector<int> num);

protected:
    void run() override;

private:
    QVector<int> m_list;

};

//快速排序
class QuickSort : public QThread
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);

    void recNum(QVector<int> list);

    //快速排序
    void quickSort(QVector<int> &s, int l, int r);
signals:
    void finish(QVector<int> num);

protected:
    void run() override;

private:
    QVector<int> m_list;

};

#endif // MYTHREAD_H
