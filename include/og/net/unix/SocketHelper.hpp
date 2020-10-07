/*
 * libOG, 2020
 *
 * Name: SocketHelper.hpp
 *
*/

#pragma once

#include "og/net/Ipv4.hpp"
#include "og/net/SocketHandle.hpp"
#include "og/net/Socket.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>

namespace og {

namespace impl {

class SocketHelper {
public:
	static constexpr int msg_flags = MSG_NOSIGNAL;
	static SocketHandle bad_socket;

	static int close(SocketHandle socket);
	static int set_blocking(SocketHandle socket, bool block);
	static bool is_blocking(SocketHandle socket);
	static sockaddr_in mk_ipv4_sockaddr(const Ipv4& address, Ipv4::Port port);

}; // class SocketHelper

} // namespace impl

} // namespace og
