/*
 * libOG, 2019
 *
 * Name: SocketImplementation.hpp
 *
 * Description:
 * Windows-specific class for Socket operations
*/

#pragma once

#include <og/network/Socket.hpp>

#include <winsock2.h>

namespace og {

class Ipv4;

namespace impl {

typedef int Addrlen;

class SocketHelper {
public:

	static SocketHandle bad_socket;

    static void blocking(SocketHandle socket, bool blocking);
    static void close(SocketHandle socket);

} // class SocketHelper

} // namespace impl

} // namespace og
