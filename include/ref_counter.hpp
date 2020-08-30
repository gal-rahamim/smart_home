#ifndef REF_COUNTER_HPP
#define REF_COUNTER_HPP

#include "atomic_value.hpp"

namespace advcpp {

template <typename P, typename C> 
class RefCounter {
public:
    explicit RefCounter(P* a_ptr = 0);
    ~RefCounter();
    RefCounter(const RefCounter& a_other);
    RefCounter& operator=(const RefCounter& a_other);

    template <typename D, typename E>
    RefCounter(RefCounter<D, E>& a_other);
    template <typename D, typename E>
    RefCounter& operator=(RefCounter<D, E>& a_other);

    C Usage() const;
    void Reset();

private:
    template <typename D, typename E>
    friend class RefCounter;   

private:
    P* m_ptr;
    AtomicValue<C>* m_counter;
};

} //advcpp

#include "inl/ref_counter.hxx"

#endif //REF_COUNTER_HPP