/*
 * SGE, 2019
 *
 * Name: SystemException.cxx
 *
 * Description:
 *
*/

#include <og/base/SystemException.hpp>

using namespace og;

SystemException::SystemException(const char* t_message) :
    m_message(t_message), m_errno(errno)
{}

SystemException::SystemException(const char* t_message, int t_errno) :
    m_message(t_message), m_errno(t_errno)
{}

const char* SystemException::what() const noexcept
{
    return strerror(m_errno);
}

const char* SystemException::who() const noexcept
{
    return m_message;
}
