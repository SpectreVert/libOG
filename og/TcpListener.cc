/*
 * Created by Costa Bushnaq
 *
 * 23-07-2021 @ 19:15:22
*/

#include "og/TcpListener.hpp"

using namespace og;

TcpListener::TcpListener()
    : Socket(AF_INET, SOCK_STREAM, 0)
{}

TcpListener::TcpListener(Handle handle)
    : Socket(handle)
{}

int TcpListener::listen(int backlog)
{
    return intl::listen(m_handle, backlog);
}

Socket::Handle TcpListener::accept_handle()
{
    SocketAddr addr{SocketAddrV4{}};

    return accept_handle(addr);
}

Socket::Handle TcpListener::accept_handle(SocketAddr &peer_address)
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
    Handle accepted_handle = intl::accept(m_handle, peer_address);

    if (accepted_handle != k_bad_socket)
        return std::make_unique<TcpStream>(accepted_handle);

    return std::nullptr_t{};
}
