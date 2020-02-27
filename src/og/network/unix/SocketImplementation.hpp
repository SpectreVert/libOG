/*
 * libOG, 2019
 *
 * Name: SocketImplementation.hpp
 *
 * Description:
 * Unix-specific class for Socket operations
*/

#pragma once

#include <og/network/Socket.hpp>

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace og {

class Ipv4;

namespace impl {

typedef socklen_t Addrlen;

class SocketHelper {
public:
	
	static SocketHandle bad_socket;

	static void setBlocking(SocketHandle socket, bool blocking);
	static void close(SocketHandle socket);

	static sockaddr_in buildIpv4Sockaddr(const Ipv4& address, uint16_t port);

}; // class SocketHelper

} // namespace impl

} // namespace og
