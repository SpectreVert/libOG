/*
 * libOG, 2019
 *
 * Name: SocketImplementation.cxx
 *
 * Description:
 * Unix-specific class for Socket operations
*/

#include <og/network/unix/SocketImplementation.hpp>
#include <og/base/SystemException.hpp>

namespace og {

namespace impl {

SocketHandle bad_socket = INVALID_SOCKET;

void SocketHelper::blocking(SocketHandle socket, bool blocking)
{
	(void) socket;
	(void) blocking;
}

void SocketHelper::close(SocketHandle socket)
{
	(void) socket;
}

} // namespace impl

} // namespace og
