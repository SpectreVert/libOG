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
#include "og/net/SocketHandle.hpp"

#include <arpa/inet.h> // sockaddr, socklen_t

namespace og {

namespace net {

namespace intl {

SocketHandle constexpr bad_socket = -1;

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

SocketHandle open(int domain, int type, int protocol);
int close(SocketHandle handle);
int bind(SocketHandle handle, SocketAddr const& address);
int connect(SocketHandle handle, SocketAddr const& address);
int listen(SocketHandle handle, int backlog);
int accept(SocketHandle handle, SocketHandle& new_handle, \
           SocketAddr& new_address, int flags);

ssize_t send(SocketHandle handle, core::RawBufferConst data);
ssize_t send_to(SocketHandle handle, core::RawBufferConst data, SocketAddr const& addr);
ssize_t recv(SocketHandle handle, core::RawBuffer const& data);
ssize_t recv_from(SocketHandle handle, core::RawBuffer const& data, SocketAddr& addr);

int set_nonblock(SocketHandle handle, bool set);
int set_cloexec(SocketHandle handle, bool set);

sockaddr* get_sockaddr_ptr(SocketAddr& address);
sockaddr const* get_sockaddr_ptr(SocketAddr const& address);
std::size_t get_sockaddr_size(int version);

} // namespace intl

} // namespace io

} // namespace og
