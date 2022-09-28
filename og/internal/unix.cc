/*
 * Created by Costa Bushnaq
 *
 * 28-04-2021 @ 23:43:24
*/

#include "og/Buffer.hpp"
#include "og/SocketAddr.hpp"

#include <cassert>
#include <cerrno>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace og;

s32 intl::open(int domain, int type, int protocol)
{
    return ::socket(domain, type, protocol);
}

int intl::close(s32 socketfd)
{
    return ::close(socketfd);
}

int intl::bind(s32 socketfd, SocketAddr const& addr)
{
    sockaddr const* addr_ptr = addr.socket_address();
    socklen_t addr_size = addr.socket_address_size();

    return ::bind(socketfd, addr_ptr, addr_size);
}

int intl::connect(s32 socketfd, SocketAddr const& addr)
{
    sockaddr const* addr_ptr = addr.socket_address();
    socklen_t addr_size = addr.socket_address_size();
    int res;

    do
        res = ::connect(socketfd, addr_ptr, addr_size);
    while (res == -1 && errno == EINTR);

    return res;
}

int intl::listen(s32 socketfd, int backlog)
{
    return ::listen(socketfd, backlog);
}

s32 intl::accept(s32 socketfd, SocketAddr& new_address)
{
    s32 newfd;
    sockaddr addr;
    socklen_t addr_size;

    do
        newfd = ::accept(socketfd, &addr, &addr_size);
    while (newfd == k_bad_socketfd && errno == EINTR);

    if (newfd == k_bad_socketfd)
        return newfd;

    int res = intl::set_cloexec(newfd, true);
    if (!res)
        res = intl::set_nonblock(newfd, true);

    if (res)
    {
        // could not set the socket parameters -- get out
        close(newfd);
        return k_bad_socketfd;
    }

    // Ipv6 not yet implemented
    assert(addr_size == sizeof(sockaddr_in));
    new_address = SocketAddr(*reinterpret_cast<sockaddr_in*>(&addr));
    
    return newfd;
}

ssize_t intl::recv(s32 socketfd, Buffer &buf)
{
    ssize_t res;

    do
        res = ::recv(socketfd, buf.data, buf.k_capacity, intl::k_message_flag);
    while (res == -1 && errno == EINTR);

    return res;
}

ssize_t intl::recv_from(s32 socketfd, SocketAddr& address,
                        Buffer &buf)
{
    ssize_t res;
    sockaddr* addr_ptr = address.socket_address();
    socklen_t addr_size{0};

    do
        res = ::recvfrom(
            socketfd, buf.data, buf.k_capacity,
            intl::k_message_flag, addr_ptr, &addr_size
        );
    while (res == -1 && errno == EINTR);

    assert(addr_size == address.socket_address_size());

    return res;
}

ssize_t intl::send(s32 socketfd, Buffer const &buf)
{
    ssize_t res;

    do
        res = ::send(socketfd, buf.data, buf.size, intl::k_message_flag);
    while (res == -1 && errno == EINTR);

    return res;
}

ssize_t intl::send_to(s32 socketfd, SocketAddr const& address, Buffer const& buf)
{
    ssize_t res;
    sockaddr const* addr_ptr = address.socket_address();
    socklen_t addr_size = address.socket_address_size();

    do
        res = ::sendto(
            socketfd, buf.data, buf.size,
            intl::k_message_flag, addr_ptr, addr_size
        );
    while (res == -1 && errno == EINTR);

    return res;
}

int intl::set_cloexec(s32 socketfd, bool on)
{
    int res;

    do
        res = ioctl(socketfd, on ? FIOCLEX : FIONCLEX);
    while (res == -1 && errno == EINTR);

    return res;
}

int intl::set_nonblock(s32 socketfd, bool on)
{
    int res;

    do
        res = ioctl(socketfd, FIONBIO, &on);
    while (res == -1 && errno == EINTR);

    return res;
}
