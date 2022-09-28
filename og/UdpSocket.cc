/*
 * Created by Costa Bushnaq
 *
 * 04-08-2021 @ 15:40:31
*/

#include "og/UdpSocket.hpp"

#include <arpa/inet.h>
#include <cerrno>

using namespace og;

UdpSocket::UdpSocket()
    : Socket(AF_INET, SOCK_DGRAM, 0)
{}

UdpSocket::UdpSocket(s32 socketfd)
    : Socket(socketfd)
{}

int UdpSocket::recv_from(SocketAddr& addr, Buffer& buf)
{
    ssize_t res = intl::recv_from(m_handle, addr, buf);

    if (res != -1)
        return e_success;

    if (errno == EAGAIN || errno == EWOULDBLOCK)
        return e_again;

    return e_failure;
}

int UdpSocket::recv_from(SocketAddr& addr, Buffer& buf, u32& received_bytes)
{
    ssize_t res = intl::recv_from(m_handle, addr, buf);

    if (res != -1)
    {
        received_bytes = static_cast<u32>(res);
        return e_success;
    }

    received_bytes = 0;
    if (errno == EAGAIN || errno == EWOULDBLOCK)
        return e_again;

    return e_failure;
}

int UdpSocket::send_to(SocketAddr const& addr, Buffer const& buf)
{
    ssize_t res = intl::send_to(m_handle, addr, buf);

    if (res != -1)
        return e_success;

    if (errno == EAGAIN || errno == EWOULDBLOCK)
        return e_again;

    return e_failure;
}

int UdpSocket::send_to(
    SocketAddr const &addr,
    Buffer const &buf,
    u32& sent)
{
    ssize_t res = intl::send_to(m_handle, addr, buf);

    if (res != -1)
    {
        sent = static_cast<u32>(res);
        return e_success;
    }

    sent = 0;
    if (errno == EAGAIN || errno == EWOULDBLOCK)
        return e_again;

    return e_failure;
}
