/*
 * libOG, 2020
 *
 * Name: SocketImplementation.hpp
 *
*/

#pragma once

#include "og/network/Socket.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace og {

class Ipv4;

namespace impl {

typedef socklen_t Addrlen;

//! \brief Unix-specific class for Socket operations
//!
class SocketHelper {
public:
	
	static SocketHandle bad_socket;

	static void set_blocking(SocketHandle socket, bool blocking);
	static void close(SocketHandle socket);

	static sockaddr_in build_ipv4_sockaddr(const Ipv4& address, uint16_t port);

}; // class SocketHelper

} // namespace impl

} // namespace og
