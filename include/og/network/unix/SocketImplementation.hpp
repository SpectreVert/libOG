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

//! \brief A namespace for OS-specific implementations
//!
namespace impl {

//! \brief 
typedef socklen_t Addrlen;

//! \brief Unix-specific class for Socket operations
//!
class SocketHelper {
public:
	
	static SocketHandle bad_socket;

	static constexpr int MSG_FLAG = MSG_NOSIGNAL;

	static void set_non_blocking(SocketHandle socket);
	static void close(SocketHandle socket);

	static sockaddr_in build_ipv4_sockaddr(const Ipv4& address, uint16_t port);

}; // class SocketHelper

} // namespace impl

} // namespace og
