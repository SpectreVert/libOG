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

/* here also the macro is really bad. Supported OSes are
 * linux, android, dragonfly, freebsd, openbsd, netbsd
*/
# if defined(OG_SYSTEM_LINUX) \
  || defined(OG_SYSTEM_ANDROID) \
  || defined(OG_SYSTEM_FREEBSD)
	int constexpr MSG_FLAG = MSG_NOSIGNAL;
# else
	int constexpr MSG_FLAG = 0;
# endif 

/* The following function return 0 on success and -1 on error.
 * errno is set to indicate the error.
*/

/* Socket manipulation & operation */
SocketHandle open(int domain, int type, int protocol);
int close(SocketHandle socket);
int bind(SocketHandle socket, SocketAddr const& address);
int connect(SocketHandle socket, SocketAddr const& address);

/* Proposition: implement lower-level calls like send_msg() or recv_msg().
*/
ssize_t send(SocketHandle handle, core::RawBuffer const data);
ssize_t send_to(SocketHandle handle, core::RawBuffer const data, SocketAddr const& addr);
ssize_t recv(SocketHandle handle, core::RawBuffer const& data);
ssize_t recv_from(SocketHandle handle, core::RawBuffer const& data, SocketAddr& addr);

int set_nonblock(SocketHandle socket, bool set);
int set_cloexec(SocketHandle socket, bool set);

/* Misc utils */
sockaddr* get_sockaddr_ptr(SocketAddr& address);
sockaddr const* get_sockaddr_ptr(SocketAddr const& address);
std::size_t get_sockaddr_size(int version);

} // namespace intl

} // namespace io

} // namespace og
