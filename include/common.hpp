#ifndef COMMON_HPP
#define COMMON_HPP

#include <stddef.h>

namespace advcpp {


struct Runnable {
	virtual ~Runnable() {}
	virtual void Run() = 0;
};

///////////////////////////////
class UnCopyable {
protected:
    UnCopyable();
private:
    UnCopyable(const UnCopyable&);
    UnCopyable& operator=(const UnCopyable&);           
};

////////////////////////////////////////////////////////////

class NoHeap {
private:
    void* operator new(size_t);
    void* operator new[](size_t);
    void operator delete(void*);
    void operator delete[](void*);
};

///////////////////////////////////////////////////////////////

class RunabbleTemplate : public Runnable {
public: 
    typedef void (*Task)(void);
public:
    RunabbleTemplate(Task a_action);
    virtual void Run();

private:
    Task m_action;
};

/////////////////////////////////////////////////////////////////

template <class T>
class RunabbleTemplate1Arg : public Runnable {
public: 
    typedef void (*Task)(T&);
public:
    RunabbleTemplate1Arg(Task a_action, T& a_arg);
    virtual void Run();

private:
    Task m_action;
    T& m_arg;
};

///////////////////////////////////////////////////////////////////

template <class ClassName>
class RunabbleTemplateMemFunc : public Runnable {
public: 
    typedef void (ClassName::*Func)(void);
public:
    RunabbleTemplateMemFunc(ClassName& a_class, Func a_func);
    virtual void Run();

private:
    ClassName& m_class;
    Func m_func;
};
///////////////////////////////////////////////////////////////////

template <class ClassName, class T>
class RunabbleTemplateMemFunc1Arg : public Runnable {
public: 
    typedef void (ClassName::*Func)(T);
public:
    RunabbleTemplateMemFunc1Arg(ClassName& a_class, Func a_func, T a_arg);
    virtual void Run();

private:
    ClassName& m_class;
    Func m_func;
    T m_arg;
};

template <class ClassName, class T>
class RunabbleTemplateMemFunc1constRefArg : public Runnable {
public: 
    typedef void (ClassName::*Func)(const T&);
public:
    RunabbleTemplateMemFunc1constRefArg(ClassName& a_class, Func a_func, const T& a_arg);
    virtual void Run();

private:
    ClassName& m_class;
    Func m_func;
    T m_arg;
};

} //advcpp

#include "inl/common.hxx"

#endif //COMMON_HPP