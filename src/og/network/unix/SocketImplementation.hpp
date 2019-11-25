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

namespace impl {

class SocketHelper {
public:
	
	static SocketHandle bad_socket;

	static void blocking(SocketHandle socket, bool blocking);
	static void close(SocketHandle socket);

}; // class SocketHelper

} // namespace impl

} // namespace og
