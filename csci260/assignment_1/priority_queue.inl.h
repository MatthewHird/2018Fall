//------------------------------------------------------------------------------
// @file    priority_queue.inl.h
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief   PriorityQueue is a templated priority queue ADT. It is implemented
//          using a binary heap ADT. The expected performance of standard
//          methods are listed below (N = number of Nodes in queue):
//          insert = O(LogN), removeMin = O(logN), decreaseKey = O(logN),
//          minPriority = O(1), minData = O(1)
//------------------------------------------------------------------------------

#include <cstdlib>
#include <iostream>
#include "my_exceptions.h"


template <typename Priority, typename Data>
PriorityQueue<Priority,Data>::PriorityQueue(Priority minPriority, int maxSize)
        : minimumPriority(minPriority)
        , maxSize(maxSize)
        , size(0)
{
    heapArray = new Node[maxSize];
}


template <typename Priority, typename Data>
PriorityQueue<Priority,Data>::~PriorityQueue() {
    for (int i = 0; i < size; i++) {
        delete heapArray[i].data;
    }
    delete heapArray;
}


template <typename Priority, typename Data>
void PriorityQueue<Priority,Data>::insert(Priority priority, Data *data) throw(FullHeapException) {
    if (isFull()) {
        throw FullHeapException();
    }

    heapArray[size] = Node();
    heapArray[size].priority = priority;
    heapArray[size].data = data;
    upheap(size);
    size++;
}


template <typename Priority, typename Data>
Data* PriorityQueue<Priority,Data>::removeMin() throw (EmptyHeapException) {
    if (isEmpty()) {
        throw EmptyHeapException();
    }

    Node tempNode = heapArray[0];
    heapArray[0] = heapArray[size - 1];
    size--;
    downheap(0);
    return tempNode.data;
}


template <typename Priority, typename Data>
Data* PriorityQueue<Priority,Data>::removeRandom() throw (EmptyHeapException) {
    if (isEmpty()) {
        throw EmptyHeapException();
    }

    int index = std::rand() % getSize();
    decreasePriority(index, minimumPriority);
    return removeMin();
}


template <typename Priority, typename Data>
Priority PriorityQueue<Priority,Data>::minPriority() const {
    return heapArray[0].priority;
}


template <typename Priority, typename Data>
const Data* PriorityQueue<Priority,Data>::minData() const {
    return heapArray[0].data;
}


template <typename Priority, typename Data>
bool PriorityQueue<Priority,Data>::isEmpty() const {
    return size <= 0;
}


template <typename Priority, typename Data>
bool PriorityQueue<Priority,Data>::isFull() const {
    return size >= maxSize;
}


template <typename Priority, typename Data>
int PriorityQueue<Priority,Data>::getSize() const {
    return size;
}


template <typename Priority, typename Data>
void PriorityQueue<Priority,Data>::upheap(int index) {
    int i = index;
    while (i > 0 && heapArray[i].priority < heapArray[parentIndex(i)].priority) {
        swap(&heapArray[i], &heapArray[parentIndex(i)]);
        i = parentIndex(i);
    }
}


template <typename Priority, typename Data>
void PriorityQueue<Priority,Data>::downheap(int index) {
    int i = index;
    int minChildIndex;
    while (leftChildIndex(i) < size) {
        if (rightChildIndex(i) >= size) {
            minChildIndex = leftChildIndex(i);
        } else {
            if (heapArray[leftChildIndex(i)].priority < heapArray[rightChildIndex(i)].priority) {
                minChildIndex = leftChildIndex(i);
            } else {
                minChildIndex = rightChildIndex(i);
            }
        }
        if (heapArray[minChildIndex].priority < heapArray[i].priority) {
            swap(&heapArray[i], &heapArray[minChildIndex]);
        }
        i = minChildIndex;
    }
}


template <typename Priority, typename Data>
void PriorityQueue<Priority,Data>::decreasePriority(int index, Priority newValue) throw(InvalidPriority) {
    if (newValue < 0) {
        throw InvalidPriority();
    }
    heapArray[index].priority = newValue;
    upheap(index);
}


template <typename Priority, typename Data>
int PriorityQueue<Priority,Data>::leftChildIndex(int index) {
    return 2 * index + 1;
}


template <typename Priority, typename Data>
int PriorityQueue<Priority,Data>::rightChildIndex(int index) {
    return 2 * index + 2;
}


template <typename Priority, typename Data>
int PriorityQueue<Priority,Data>::parentIndex(int index) {
    return (index - 1) / 2;
}


template <typename Priority, typename Data>
void PriorityQueue<Priority,Data>::swap(Node *x, Node *y) {
    Node temp = *x;
    *x = *y;
    *y = temp;
}
