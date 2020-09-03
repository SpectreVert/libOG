/*
 * libOG, 2020
 *
 * Name: socketimpl.h
 *
*/

#pragma once

#include "og/net/ipv4.hpp"
#include "og/net/sockethandle.hpp"
#include "og/net/socket.hpp"

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
