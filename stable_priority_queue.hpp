// Copyright David Baumann 2018

#ifndef STABLE_PRIORITY_QUEUE
#define STABLE_PRIORITY_QUEUE

#include <queue>
#include <vector>
#include <map>
#include <exception>

// Priority Queue that mainains FIFO ordering for elements with the same priority
template <class T>
class Stable_Priority_Queue {
 private:
    std::map<int, std::queue<T>> mQueues;
    std::priority_queue<int, std::vector<int>, std::greater<int>> mPriorityQueue;

 public:
    Stable_Priority_Queue() {}
    bool empty() {
        return mPriorityQueue.empty();
    }
    int size() {
        return mPriorityQueue.size();
    }
    T top() {
        if (mPriorityQueue.empty()) {
            throw std::runtime_error("Attempted to pop from empty queue!");
        }
        return mQueues[mPriorityQueue.top()].front();
    }
    void pop() {
        mQueues[mPriorityQueue.top()].pop();
        if (mQueues[mPriorityQueue.top()].empty()) {
            mQueues.erase(mPriorityQueue.top());
        }
        mPriorityQueue.pop();
    }
    void push(int priority, const T& item) {
    mPriorityQueue.push(priority);
        auto theQueue = mQueues.find(priority);
        if (theQueue == mQueues.end()) {
            // queue for this priority does not exist yet, so make one
            mQueues.insert({priority, std::queue<T>()});
        }
        mQueues[priority].push(item);
    }
};

#endif  // STABLE_PRIORITY_QUEUE

/* test code
    std::cout << "Testing Stable Priority Queue" << std::endl;
    Stable_Priority_Queue<int> myQueue;
    std::cout << "trying empty()" << std::endl;
    if (myQueue.empty()) {
        std::cout << "empty" << std::endl;
    } else {
        std::cout << "not empty" << std::endl;
    }
    std::cout << "trying pushes" << std::endl;

    int thing = 3;
    myQueue.push(int(1), thing);
    thing = 4;
    myQueue.push(int(1), thing);
    thing = 1;
    myQueue.push(int(5), thing);
    thing = 5;
    myQueue.push(int(0), thing);
    thing = 2;
    myQueue.push(int(5), thing);
    std::cout << "Checking size (should be 5): " << myQueue.size() << std::endl;
    std::cout << "top: " << myQueue.top() << std::endl;
    std::cout << "popping things off of the queue" << std::endl;
    // expected order: 0, 10, 5, 4, 0
    while (!myQueue.empty()) {
        std::cout << myQueue.top() << std::endl;
        myQueue.pop();
    }
    std::cout << "done" << std::endl;
    return std::list<Coordinate>();
*/
