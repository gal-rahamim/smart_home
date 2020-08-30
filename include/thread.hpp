#ifndef TREAD_HPP
#define TREAD_HPP

#include <tr1/memory>
#include <pthread.h>
#include "common.hpp"

namespace experis {

class Thread {
public:
    typedef std::tr1::shared_ptr<advcpp::Runnable> commandPtr;

public:
	Thread(const commandPtr &_cmd);
    ~Thread();

    void Join() const;
	void Cancel();
	bool operator==(pthread_t a_trd) const;
	bool operator==(const Thread& a_trd) const;

private:
	Thread(const Thread&); // no copy
	Thread& operator=(const Thread&); // no copy

	enum flag {
		e_joined,
		e_notJoined
	};

private:
	commandPtr m_cmd;
	pthread_t m_trd;
	mutable flag m_flag;
};

} //experis

#endif //TREAD_HPP
