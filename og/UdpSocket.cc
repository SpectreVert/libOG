/*
 * Created by Costa Bushnaq
 *
 * 04-08-2021 @ 15:40:31
*/

#include "og/Error.hpp"
#include "og/UdpSocket.hpp"

using namespace og;

UdpSocket::UdpSocket()
    : Socket(AF_INET, SOCK_DGRAM, 0)
{}

UdpSocket::UdpSocket(Handle handle)
    : Socket(handle)
{}

int UdpSocket::recv_from(SocketAddr& addr, RawBuffer& buf)
{
    ssize_t res = intl::recv_from(m_handle, addr, buf);

    if (res != -1)
        return e_success;

    if (errno == EAGAIN || errno == EWOULDBLOCK)
        return e_again;

    return e_failure;
}

int UdpSocket::recv_from(SocketAddr& addr, RawBuffer& buf, std::size_t& received)
{
    ssize_t res = intl::recv_from(m_handle, addr, buf);

    if (res != -1)
    {
        received = static_cast<std::size_t>(res);
        return e_success;
    }

    received = 0;
    if (errno == EAGAIN || errno == EWOULDBLOCK)
        return e_again;

    return e_failure;
}

int UdpSocket::send_to(SocketAddr const& addr, RawBuffer const& buf)
{
    ssize_t res = intl::send_to(m_handle, addr, buf);

    if (res != -1)
        return e_success;

    if (errno == EAGAIN || errno == EWOULDBLOCK)
        return e_again;

    return e_failure;
}

int UdpSocket::send_to(SocketAddr const& addr, RawBuffer const &buf, std::size_t& sent)
{
    ssize_t res = intl::send_to(m_handle, addr, buf);

    if (res != -1)
    {
        sent = static_cast<std::size_t>(res);
        return e_success;
    }

    sent = 0;
    if (errno == EAGAIN || errno == EWOULDBLOCK)
        return e_again;

    return e_failure;
}
