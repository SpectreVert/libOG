/*
 * Created by Costa Bushnaq
 *
 * 23-07-2021 @ 19:15:22
*/

#include "og/TcpListener.hpp"
#include "og/internal.hpp"
#include "og/TcpStream.hpp"

using namespace og;

TcpListener::TcpListener()
    : Socket(AF_INET, SOCK_STREAM, 0)
{}

TcpListener::TcpListener(s32 socketfd)
    : Socket(socketfd)
{}

s32 TcpListener::listen(s32 backlog)
{
    return intl::listen(m_handle, backlog);
}

s32 TcpListener::accept_handle()
{
    SocketAddr addr{SocketAddrV4{}};

    return accept_handle(addr);
}

s32 TcpListener::accept_handle(SocketAddr &peer_address)
{
    return intl::accept(m_handle, peer_address);
}

std::unique_ptr<TcpStream> TcpListener::accept()
{
    SocketAddr addr{SocketAddrV4{}};

    return accept(addr);
}

std::unique_ptr<TcpStream> TcpListener::accept(SocketAddr& peer_address)
{
    s32 accepted_handle = intl::accept(m_handle, peer_address);

    if (accepted_handle != k_bad_socketfd)
        return std::make_unique<TcpStream>(accepted_handle);

    return std::nullptr_t{};
}
