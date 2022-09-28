/*
 * Created by Costa Bushnaq
 *
 * 28-04-2021 @ 22:10:15
*/

#include "og/internal.hpp"
#include "og/Socket.hpp"

using namespace og;

Socket::~Socket()
{
    (void) this->close();
}

Socket::Socket(s32 dom, s32 type, s32 prot)
{
    (void) mk_handle(dom, type, prot);
}

Socket::Socket(s32 socketfd)
    : m_handle(socketfd)
{}

s32 Socket::close()
{
    if (intl::close(m_handle) == -1)
        return e_failure;

    m_handle = k_bad_socketfd;

    return e_success;
}

s32 Socket::mk_handle(s32 domain, s32 type, s32 protocol)
{
    m_handle = intl::open(domain, type, protocol);
    
    if (m_handle != k_bad_socketfd)
        return e_success;

    return e_failure;
}

void Socket::set_handle(s32 socketfd)
{
    m_handle = socketfd;
}

s32 Socket::handle() const
{
    return m_handle;
}

s32 Socket::bind(SocketAddr const& addr)
{
    return intl::bind(m_handle, addr);
}
