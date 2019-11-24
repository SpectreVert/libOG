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

using namespace og;

void SocketHelper::blocking(SocketHandle socket, bool blocking)
{
	int socket_status = fcntl(socket, F_GETFL);

	if (blocking) {
		/* Negate non-blocking bits (so do block) */
		if (fcntl(socket, socket_status &~ O_NONBLOCK) == -1)
			throw SystemException("fcntl");
	} else {
		if (fcntl(socket, socket_status | O_NONBLOCK) == -1)
			throw SystemException("fcntl");
	}
}

void SocketHelper::close(SocketHandle socket)
{
	if (::close(socket) == -1)
		throw SystemException("close");
}
