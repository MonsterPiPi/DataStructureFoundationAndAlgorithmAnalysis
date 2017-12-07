#ifndef QUEUE_H
#define QUEUE_H
#include<cassert>
#include<iostream>
using namespace std;
template<typename T>
class Queue
{
public:
    Queue(int maxsize = 10);
    Queue(const Queue<T>& rhs);
    Queue<T>& operator=(const Queue<T>& rhs);
    ~Queue();
public:
    bool empty() const;
    bool IsFull() const;
    int size() const;

    void push(const T& data);
    void pop();
    T& front();
    T   front() const;
    T& back();
    T   back() const;
private:
    T *array;
    int Front;
    int rear;
    int capacity;
};

template<typename T>
Queue<T>::Queue(int maxsize) :Front(0), rear(0),capacity(maxsize)
{
    array = new T[maxsize];
    assert(array != NULL);    //�洢����ʧ�����˳�;
}

template<typename T>
Queue<T>::Queue(const Queue<T>& rhs) :Front(rhs.Front), rear(rhs.rear),capacity(rhs.capacity)
{
    array = new T[capacity];
    for (int i = 0; i != (this->size()); i++)
        array[i] = rhs.array[i];
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& rhs)
{
    if (this != &rhs)
    {
        delete[] array;
        capacity = rhs.capacity;
        Front = rhs.Front;
        rear = rhs.rear;
        array = new T[capacity];
        for (int i = 0; i != (this->size()); i++)
            array[i] = rhs.array[i];
    }
    return *this;
}
template<typename T>
Queue<T>::~Queue()
{
        delete[] array;
}

template<typename T>
bool Queue<T>::empty() const
{
    return Front == rear;      //�˴�Ϊѭ�����У���front==rearʱΪ�ա�
}

template<typename T>
bool Queue<T>::IsFull() const
{
    return(rear + 1) % capacity == Front;   //����rear+1��%capacity==frontΪ��,��ΪΪ��ʱ��һ��Ԫ�أ����ǿ���rear>front,Ҳ����rear<front.
}

template<typename T>
int Queue<T>::size() const
{
    return (rear - Front + capacity) % capacity;
}

template<typename T>
void Queue<T>::push(const T& data)
{
    if (!IsFull())
    {
        array[rear] = data;
        rear = (rear + 1) % capacity;
    }
    else                                                  //����������֮��ɽ�������
    {
        T *newarray=new T[ 2*capacity ];
        for (int i = 0; i != 2*capacity&&!this->empty(); i++)
        {
            newarray[i] =this-> front();
            this->pop();
        }
        delete [ ] array;
        array = newarray;
        Front = 0;
        array[rear] = data;
        rear =this->rear+1;
        capacity = 2*capacity;
    }
}

template<typename T>
void Queue<T>::pop()
{
    if (!empty())
    {
        //array[Front].~T();   //����ͷԪ��������
        Front = (Front + 1) % capacity;
    }
    else
        cout<<"empty queue!"<<endl;
}

template<typename T>
T& Queue<T>::front()
{
    if (empty())
        cerr << "Error, queue is empty!";
    return array[Front];
}
template<typename T>
T Queue<T>::front() const
{
    if (empty())
        cerr << "Error, queue is empty!";
    return array[Front];
}
template<typename T>
T& Queue<T>::back()
{
    if (empty())
        cerr << "Error, queue is empty!";
    return array[rear-1];                             //rear������β��ָ��
}
template<typename T>
T Queue<T>::back() const
{
    if (empty())
        cerr << "Error, queue is empty!";
    return array[rear-1];
}
#endif // QUEUE_H
