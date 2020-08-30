#include <errno.h>
#include <assert.h>
#include "thread.hpp"
#include "thread_exceptions.hpp"

namespace experis {

static void* StartRoutine(void* _cmd) {
    static_cast<std::tr1::shared_ptr<advcpp::Runnable>*>(_cmd)->get()->Run();
    return NULL;
}

Thread::Thread(const commandPtr &_cmd)
: m_cmd(_cmd), m_flag(e_notJoined) {
    int result = pthread_create(&m_trd, NULL, &StartRoutine, &m_cmd);
    if(0 != result) {
        assert(errno != EINVAL);

        if(result == EAGAIN) {
            throw ThreadInsufficientResources();
        }
        else if(result == EPERM) {
            throw ThreadInvalidPremissions();
        }
        else {
            assert(!"pthread_create failed");
        }
    }
}

Thread::~Thread() {
    if(m_flag != e_joined) {
        Join();
    }
}

void Thread::Join() const {
    if(m_flag == e_joined) {
        return;
    }
    m_flag = e_joined;
    int result = pthread_join(m_trd, NULL);
    if(0 != result) {
        if(result == EDEADLK) {
            throw ThreadJoiningEachOther();
        }
        else {
            assert(!"pthread_join failed");
        }
    }
}

void Thread::Cancel()
{
    pthread_cancel(m_trd);
    // int result = pthread_cancel(m_trd);
    // if(0 != result) {
    //     assert(!"pthread_cancel failed");
    // }
}

bool Thread::operator==(pthread_t a_trd) const
{
    return a_trd == m_trd;
}
bool Thread::operator==(const Thread& a_trd) const
{
    return m_trd == a_trd.m_trd;
}

} //experis
