/*
 * Created by Costa Bushnaq
 *
 * 02-05-2021 @ 01:04:20
*/

#include "og/TcpStream.hpp"

#include <arpa/inet.h>
#include <cerrno>

using namespace og;

TcpStream::TcpStream()
    : Socket(AF_INET, SOCK_STREAM, 0)
{}

TcpStream::TcpStream(s32 handle)
    : Socket(handle)
{}

s32 TcpStream::mk_handle(SocketAddr const& peer_address)
{
    s32 handle = intl::open(AF_INET, SOCK_STREAM, 0);

    if (handle == k_bad_socketfd)
        return handle;

    if (intl::connect(handle, peer_address) == 0 || errno == EINPROGRESS)
        return handle;

    intl::close(handle);

    return k_bad_socketfd;
}

std::unique_ptr<TcpStream> TcpStream::mk_stream(SocketAddr const& peer_address)
{
    s32 handle = intl::open(AF_INET, SOCK_STREAM, 0);

    if (handle == k_bad_socketfd)
        return std::nullptr_t{};

    if (intl::connect(handle, peer_address) == 0 || errno == EINPROGRESS)
        return std::make_unique<TcpStream>(handle);

    intl::close(handle);

    return std::nullptr_t{};
}

int TcpStream::connect(SocketAddr const& peer_address)
{
    if (intl::connect(m_handle, peer_address) == 0)
        return e_success;

    if (errno == EINPROGRESS)
        return e_in_progress;

    return e_failure;
}

int TcpStream::send(Buffer const& buf)
{
    s64 res = intl::send(m_handle, buf);

    if (res != -1)
        return e_success;

    if (errno == EAGAIN || errno == EWOULDBLOCK)
        return e_again;

    return e_failure;
}

int TcpStream::send(Buffer const &buf, u32& sent)
{
    s64 res = intl::send(m_handle, buf);

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

int TcpStream::recv(Buffer& buf)
{
    s64 res = intl::recv(m_handle, buf);

    if (res > 0)
        return e_success;

    if (res == 0)
        return e_closed;
    else if (errno == EAGAIN || errno == EWOULDBLOCK)
        return e_again;

    return e_failure;
}

int TcpStream::recv(Buffer& buf, u32& recv)
{
    s64 res = intl::recv(m_handle, buf);

    if (res > 0)
    {
        recv = static_cast<u32>(res);
        return e_success;
    }

    recv = 0;
    if (res == 0)
        return e_closed;
    else if (errno == EAGAIN || errno == EWOULDBLOCK)
        return e_again;

    return e_failure;
}
