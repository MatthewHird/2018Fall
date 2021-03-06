//------------------------------------------------------------------------------
// @file    priority_queue.h
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief   PriorityQueue is a templated priority queue ADT. It is implemented
//          using a binary heap ADT. The expected performance of standard
//          methods are listed below (N = number of Nodes in queue):
//          insert = O(LogN), removeMin = O(logN), decreaseKey = O(logN),
//          minPriority = O(1), minData = O(1)
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_1_PRIORITY_QUEUE_H
#define ASSIGNMENT_1_PRIORITY_QUEUE_H


#include "my_exceptions.h"
#include <iostream>


template <typename Priority, typename Data>
class PriorityQueue {
public:
    /**
     * @brief Parameterized class constructor.
     *
     * @param minPriority   The minimum valid priority value.
     * @param maxSize       Maximum number of Priority/Data pairs the queue can
     *                      contain.
     */
    explicit PriorityQueue(Priority minPriority, int maxSize);

    /**
     * @brief Class deconstructor.
     */
    ~PriorityQueue();

    /**
     * @brief Inserts a Priority/Data (key/value) pair into the priority queue.
     *
     * @param priority  The Priority (key) value.
     * @param data  The Data (value) object.
     *
     * @throws FullHeapException    if priority queue if full.
     */
    void insert(Priority priority, Data *data) throw(FullHeapException);

    /**
     * @brief Removes the Priority/Data pair with the minimum Priority value.
     *
     * @return A pointer to the Data from the removed Priority/Data pair.
     *
     * @throws EmptyHeapException   if priority queue is empty
     */
    Data* removeMin() throw (EmptyHeapException);

    /**
     * @brief Removes a random Priority/Data pair (no matter what its priority is).
     *
     * @return A pointer to the Data from the removed Priority/Data pair.
     *
     * @throws EmptyHeapException   if priority queue is empty.
     */
    Data* removeRandom() throw (EmptyHeapException);

    /**
     * @return The minimum priority of any Priority/Data pair int the queue.
     */
    Priority minPriority() const;

    /**
     * @return A pointer to the Data of the Priority/Data pair with the minimum
     *         priority in the queue.
     */
    const Data* minData() const;

    /**
     * @brief Checks if the priority queue is empty.
     *
     * @return True if queue is empty.
     */
    bool isEmpty() const;

    /**
     * @brief Checks if priority queue is full.
     *
     * @return True if queue is full.
     */
    bool isFull() const;

    /**
     * @brief Checks number of Priority/Data pairs in queue.
     *
     * @return Number of pairs in queue.
     */
    int getSize() const;

private:
    struct Node {
        Priority priority;
        Data* data;
    };

    /**
     * @brief Restores the heap ordering property along the branch from the Node
     *        at index to root.
     *
     * @param index Index of starting Node.
     */
    void upheap(int index);

    /**
     * @brief Restores the heap ordering property along the branch from the Node
     *        at index to the bottom of the heap tree.
     *
     * @param index Index of starting Node.
     */
    void downheap(int index);

    /**
     * @brief Lowers the Priority value of the Node at index to newValue, and
     *        restores the heap ordering property along the branch from the Node
     *        at index to root.
     *
     * @param index Index of Node whose priority is to be lowered.
     *
     * @param newValue  New priority value of Node at index.
     */
    void decreasePriority(int index, Priority newValue) throw(InvalidPriority);

    /**
     * @brief Finds the index of the left child Node of the Node at index.
     *
     * @param index Index of Node.
     *
     * @return Index of left child Node.
     */
    int leftChildIndex(int index);

    /**
     * @brief Finds the index of the right child Node of the Node at index.
     *
     * @param index Index of Node.
     *
     * @return Index of right child Node.
     */
    int rightChildIndex(int index);

    /**
     * @brief Finds the index of the parent Node of the Node at index.
     *
     * @param index Index of Node.
     *
     * @return Index of right child Node.
     */
    int parentIndex(int index);

    /**
     * @brief Swaps the contents of two Node addresses.
     *
     * @param x Node to swap.
     *
     * @param y Node to swap.
     */
    void swap(Node *x, Node *y);

    Node* heapArray;
    Priority minimumPriority;
    int maxSize;
    int size;
};

#include "priority_queue.inl.h"

#endif //ASSIGNMENT_1_PRIORITY_QUEUE_H
