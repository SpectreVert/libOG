/*
 * libOG, 2020
 *
 * Name: SocketIO.hpp
 *
*/

#pragma once

#include "og/net/Socket.hpp"
#include "og/net/Ipv4.hpp"
#include "og/net/SocketAddr.hpp"

#if defined(OG_SYSTEM_WINDOWS)
	#include <winsock2.h>
	#include <ws2tcpip.h>
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
#endif

namespace og {

namespace impl {

class SocketIO {
public:
#if defined(OG_SYSTEM_WINDOWS)
	// static constexpr SocketHandle bad_socket = ??;
#else
	static constexpr SocketHandle bad_socket = -1;
#endif // OG_SYSTEM_WINDOWS

#if defined(OG_SYSTEM_UNIX)
	static constexpr int MSG_FLAG = MSG_NOSIGNAL;
#else
	static constexpr int MSG_FLAG = 0;
#endif // OG_SYSTEM_UNIX

	static const sockaddr* get_sockaddr_ptr(const SocketAddr& address);
	static std::size_t get_sockaddr_size(int version);

	static int bind(SocketHandle socket, const SocketAddr& address);
	static int connect(SocketHandle socket, const SocketAddr& address);

	static int close(SocketHandle socket);
	static int set_blocking(SocketHandle socket, bool block);
	static bool is_blocking(SocketHandle socket);

}; // class SocketIO

} // namespace impl

} // namespace og
