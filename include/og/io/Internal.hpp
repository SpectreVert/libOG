/*
 * libOG, 2020
 *
 * Name: Internal.hpp
 *
*/

#pragma once

#include "og/Config.hpp"

#include "og/net/Socket.hpp"
#include "og/net/Ipv4.hpp"
#include "og/net/SocketAddr.hpp"

#include <arpa/inet.h> // sockaddr

namespace og {

namespace io {

namespace intl {

constexpr SocketHandle bad_socket = -1;

/* here also the macro is really bad. Supported OSes are
 * linux, android, dragonfly, freebsd, openbsd, netbsd
*/
#if defined(OG_SYSTEM_UNIX)
	constexpr int MSG_FLAG = MSG_NOSIGNAL;
#else
	constexpr int MSG_FLAG = 0;
#endif // OG_SYSTEM_UNIX

/* The following function return 0 on success and -1 on error.
 * errno is set to indicate the error.
*/

/* Socket manipulation & operation */
SocketHandle open(int domain, int type, int protocol);
int close(SocketHandle socket);
int bind(SocketHandle socket, const net::SocketAddr& address);
int connect(SocketHandle socket, const net::SocketAddr& address);

int set_nonblock(SocketHandle socket, bool set);
int set_cloexec(SocketHandle socket, bool set);

/* Misc utils */
const sockaddr* get_sockaddr_ptr(const net::SocketAddr& address);
std::size_t get_sockaddr_size(int version);

} // namespace intl

} // namespace og

} // namespace og
