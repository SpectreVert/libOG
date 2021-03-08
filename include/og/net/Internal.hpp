/*
 * libOG, 2020
 *
 * Name: Internal.hpp
 *
*/

#pragma once

#include "og/core/RawBuffer.hpp"
#include "og/core/System.hpp"
#include "og/net/Ipv4.hpp"
#include "og/net/SocketAddr.hpp"
#include "og/net/SocketFd.hpp"

#include <arpa/inet.h> // sockaddr, socklen_t

namespace og {

namespace net {

namespace intl {

SocketFd constexpr bad_socket = -1;

/* Supported OSes are
 * linux, android, dragonfly, freebsd, openbsd, netbsd
*/
#if defined(OG_SYSTEM_LINUX)   \
 || defined(OG_SYSTEM_ANDROID) \
 || defined(OG_SYSTEM_FREEBSD)
static int constexpr MSG_FLAG = MSG_NOSIGNAL;
#else
static int constexpr MSG_FLAG = 0;
#endif

#if defined(SOCK_NONBLOCK) && defined(SOCK_CLOEXEC)
static int constexpr ACCEPT_FLAG = SOCK_NONBLOCK | SOCK_CLOEXEC;
#else
static int constexpr ACCEPT_FLAG = 0;
#endif

/* The following functions return a negative integer in case of error.
 * Otherwise, they return either zero or a positive integer.
*/

SocketFd open(int domain, int type, int protocol);
int close(SocketFd socket);
int bind(SocketFd socket, SocketAddr const& address);
int connect(SocketFd socket, SocketAddr const& address);
int listen(SocketFd socket, int backlog);
int accept(SocketFd socket, SocketFd& new_handle, SocketAddr& new_address, int flags);

ssize_t send(SocketFd socket, core::RawBufferConst data);
ssize_t send_to(SocketFd socket, core::RawBufferConst data, SocketAddr const& addr);
ssize_t recv(SocketFd socket, core::RawBuffer& data);
ssize_t recv_from(SocketFd socket, core::RawBuffer& data, SocketAddr& addr);

int set_nonblock(SocketFd socket, bool set);
int set_cloexec(SocketFd socket, bool set);

} // namespace intl

} // namespace io

} // namespace og
