/*
 * libOG, 2019
 *
 * Name: SystemException.hpp
 *
 * Description:
 * Exception to throw in case of system call
 * failure.
*/

// TODO: take a string as parameter just like perror

#pragma once

#include <exception>
#include <cstring>
#include <cerrno>

namespace og {

class SystemException : public std::exception {
public:
    SystemException(const char* t_message);
    SystemException(const char* t_message, int t_errno);

    const char* what() const noexcept;
    const char* who() const noexcept;
private:
    const char* m_message;
    int m_errno;

}; // class SystemException

} // namespace og
