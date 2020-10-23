/*
 * libOG, 2020
 *
 * Name: SocketIO.hpp
 *
*/

#pragma once

#include "og/net/Socket.hpp"
#include "og/net/SocketHandle.hpp"
#include "og/net/Ipv4.hpp"
#include "og/net/SocketAddr.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>

namespace og {

namespace impl {

class SocketIO {
public:
	static constexpr int MSG_FLAG = MSG_NOSIGNAL;
	static SocketHandle bad_socket;

	static std::size_t get_sockaddr_size(int version);

	static int bind(SocketHandle socket, const SocketAddr& address);
	static int connect(SocketHandle socket, const SocketAddr& address);

	static int close(SocketHandle socket);
	static int set_blocking(SocketHandle socket, bool block);
	static bool is_blocking(SocketHandle socket);

}; // class SocketIO

} // namespace impl

} // namespace og
