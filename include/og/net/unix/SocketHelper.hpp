/*
 * libOG, 2020
 *
 * Name: SocketHelper.hpp
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

class SocketHelper {
public:
	static constexpr int msg_flags = MSG_NOSIGNAL;
	static SocketHandle bad_socket;

	static int bind(SocketHandle socket, const SocketAddr& address);
	static int close(SocketHandle socket);
	static int set_blocking(SocketHandle socket, bool block);
	static bool is_blocking(SocketHandle socket);

}; // class SocketHelper

} // namespace impl

} // namespace og
