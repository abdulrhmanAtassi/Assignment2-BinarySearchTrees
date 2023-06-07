
#pragma once
#include "DLL.h"

template <class T>
class QueueDLL
{
public:
    void enqueue(const T &val);
    T dequeue();

    T get_first() const; // returns the first element added to the queue.
    T get_last() const;  // returns the last element added to the queue.

    bool is_empty() const;
    void clear();

private:
    DLList<T> list;
};
// NOTE. The default constructor and destructor of QueueDLL
// automatically call the default constructor and destructor
// of DLList.

template <class T>
void QueueDLL<T>::enqueue(const T &val)
{
    list.add_to_tail(val);
}

// Removes and returns the first added element.
// Throws an exception if the queue is empty.
template <class T>
T QueueDLL<T>::dequeue()
{
    T val = list.head_val();
    list.remove_head();
    return val;
}

// Returns the first added element.
// Throws an exception if the queue is empty.
template <class T>
T QueueDLL<T>::get_first() const
{
    return list.head_val();
}

// Returns the last added element.
// Throws an exception if the queue is empty.
template <class T>
T QueueDLL<T>::get_last() const
{
    return list.tail_val();
}

template <class T>
bool QueueDLL<T>::is_empty() const
{
    return list.is_empty();
}

template <class T>
void QueueDLL<T>::clear()
{
    list.clear();
}