/*
 * Created by Costa Bushnaq
 *
 * 30-09-2022 @ 10:33:19
*/

#include "og/internal.hpp"

namespace og {

namespace intl {

s32 set_cloexec(s32 socketfd, bool on)
{
    s32 res;

    do
        res = ioctl(socketfd, on ? FIOCLEX : FIONCLEX);
    while (res == -1 && errno == EINTR);

    return res;
}

s32 set_nonblock(s32 socketfd, bool on)
{
    s32 res;

    do
        res = ioctl(socketfd, FIONBIO, &on);
    while (res == -1 && errno == EINTR);

    return res;
}

s32 open(s32 domain, s32 type, s32 protocol)
{
    return ::socket(domain, type, protocol);
}

s32 close(s32 socketfd)
{
    return ::close(socketfd);
}

s32 bind(s32 socketfd, SocketAddr const& addr)
{
    sockaddr const* addr_ptr = addr.socket_address();
    socklen_t addr_size = addr.socket_address_size();

    return ::bind(socketfd, addr_ptr, addr_size);
}

s32 connect(s32 socketfd, SocketAddr const& addr)
{
    sockaddr const* addr_ptr = addr.socket_address();
    socklen_t addr_size = addr.socket_address_size();
    s32 res;

    do
        res = ::connect(socketfd, addr_ptr, addr_size);
    while (res == -1 && errno == EINTR);

    return res;
}

s32 listen(s32 socketfd, s32 backlog)
{
    return ::listen(socketfd, backlog);
}

s32 accept(s32 socketfd, SocketAddr& new_address)
{
    s32 newfd;
    sockaddr addr;
    socklen_t addr_size;

    do
        newfd = ::accept(socketfd, &addr, &addr_size);
    while (newfd == k_bad_socketfd && errno == EINTR);

    if (newfd == k_bad_socketfd)
        return newfd;

    s32 res = set_cloexec(newfd, true);
    if (!res)
        res = set_nonblock(newfd, true);

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

s64 recv(s32 socketfd, Buffer &buf)
{
    s64 res;

    do
        res = ::recv(socketfd, buf.data, buf.k_capacity, k_message_flag);
    while (res == -1 && errno == EINTR);

    return res;
}

s64 recv_from(s32 socketfd, SocketAddr& address, Buffer &buf)
{
    s64 res;
    sockaddr* addr_ptr = address.socket_address();
    socklen_t addr_size{0};

    do
        res = ::recvfrom(
            socketfd, buf.data, buf.k_capacity,
            k_message_flag, addr_ptr, &addr_size
        );
    while (res == -1 && errno == EINTR);

    assert(addr_size == address.socket_address_size());

    return res;
}

s64 send(s32 socketfd, Buffer const &buf)
{
    s64 res;

    do
        res = ::send(socketfd, buf.data, buf.size, k_message_flag);
    while (res == -1 && errno == EINTR);

    return res;
}

s64 send_to(s32 socketfd, SocketAddr const& address, Buffer const& buf)
{
    s64 res;
    sockaddr const* addr_ptr = address.socket_address();
    socklen_t addr_size = address.socket_address_size();

    do
        res = ::sendto(
            socketfd, buf.data, buf.size,
            k_message_flag, addr_ptr, addr_size
        );
    while (res == -1 && errno == EINTR);

    return res;
}

} // namespace intl

} // namespace og
