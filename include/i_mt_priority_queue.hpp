#ifndef I_MT_PRIORITY_QUEUE_HPP
#define I_MT_PRIORITY_QUEUE_HPP
#include <stddef.h>
namespace experis {

template <class T>
class IMTQueue {
public:
    virtual ~IMTQueue() {} 

    virtual void Enqueue(const T& _val) = 0;
    virtual void Dequeue(T& _res) = 0;
    virtual size_t Size() const = 0;

};

} //experis

#endif //I_MT_PRIORITY_QUEUE_HPP
