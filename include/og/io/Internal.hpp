/*
 * libOG, 2020
 *
 * Name: Internal.hpp
 *
*/

#pragma once

#include "og/Config.hpp"

#include "og/io/RawBuffer.hpp"
#include "og/net/Socket.hpp"
#include "og/net/Ipv4.hpp"
#include "og/net/SocketAddr.hpp"

#include <arpa/inet.h> // sockaddr

namespace og {

namespace io {

namespace intl {

SocketHandle constexpr bad_socket = -1;

/* here also the macro is really bad. Supported OSes are
 * linux, android, dragonfly, freebsd, openbsd, netbsd
*/
#if defined(OG_SYSTEM_UNIX)
	int constexpr MSG_FLAG = MSG_NOSIGNAL;
#else
	int constexpr MSG_FLAG = 0;
#endif // OG_SYSTEM_UNIX

/* The following function return 0 on success and -1 on error.
 * errno is set to indicate the error.
*/

/* Socket manipulation & operation */
SocketHandle open(int domain, int type, int protocol);
int close(SocketHandle socket);
int bind(SocketHandle socket, net::SocketAddr const& address);
int connect(SocketHandle socket, net::SocketAddr const& address);

/* Proposition: implement lower-level calls like send_msg() or recv_msg().
*/
ssize_t send(SocketHandle handle, RawBuffer const data);
ssize_t send_to(SocketHandle handle, RawBuffer const data, net::SocketAddr const& addr);
ssize_t recv(SocketHandle handle, RawBuffer const data);
ssize_t recv_from(SocketHandle handle, RawBuffer const data, net::SocketAddr const& addr);

int set_nonblock(SocketHandle socket, bool set);
int set_cloexec(SocketHandle socket, bool set);

/* Misc utils */
const sockaddr* get_sockaddr_ptr(net::SocketAddr const& address);
std::size_t get_sockaddr_size(int version);

} // namespace intl

} // namespace og

} // namespace og
