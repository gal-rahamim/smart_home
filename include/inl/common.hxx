#ifndef COMMON_HXX
#define COMMON_HXX

#include "common.hpp"

namespace advcpp {

inline UnCopyable::UnCopyable(){}
////////////////////////////////////////////////////////////////////////////
inline RunabbleTemplate::RunabbleTemplate(Task a_action)
: m_action(a_action)
{}

inline void RunabbleTemplate::Run()
{
    m_action();
}
////////////////////////////////////////////////////////////////////////////
template <class T>
RunabbleTemplate1Arg<T>::RunabbleTemplate1Arg(Task a_action, T& a_arg)
: m_action(a_action)
, m_arg(a_arg)
{}
template <class T>
void RunabbleTemplate1Arg<T>::RunabbleTemplate1Arg::Run()
{
    m_action(m_arg);
}
////////////////////////////////////////////////////////////////////////////
template <class ClassName>
RunabbleTemplateMemFunc<ClassName>::RunabbleTemplateMemFunc(ClassName& a_class, Func a_func)
: m_class(a_class)
, m_func(a_func)
{}

template <class ClassName>
void RunabbleTemplateMemFunc<ClassName>::Run()
{
    (m_class.*m_func)();
}
////////////////////////////////////////////////////////////////////////////
template <class ClassName, class T>
RunabbleTemplateMemFunc1Arg<ClassName, T>::RunabbleTemplateMemFunc1Arg(ClassName& a_class, Func a_func, T a_arg)
: m_class(a_class)
, m_func(a_func)
, m_arg(a_arg)
{}

template <class ClassName, class T>
void RunabbleTemplateMemFunc1Arg<ClassName, T>::Run()
{
    (m_class.*m_func)(m_arg);
}
////////////////////////////////////////////////////////////////////////////
template <class ClassName, class T>
RunabbleTemplateMemFunc1constRefArg<ClassName, T>::RunabbleTemplateMemFunc1constRefArg(ClassName& a_class, Func a_func, const T& a_arg)
: m_class(a_class)
, m_func(a_func)
, m_arg(a_arg)
{}

template <class ClassName, class T>
void RunabbleTemplateMemFunc1constRefArg<ClassName, T>::Run()
{
    (m_class.*m_func)(m_arg);
}



} //advcpp

#endif //COMMON_HXX