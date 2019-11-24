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

namespace impl {

class SocketHelper {
public:

	static SocketHandle bad_socket();

} // class SocketHelper

} // namespace impl

} // namespace og
