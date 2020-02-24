/*
 * libOG, 2019
 *
 * Name: SocketImplementation.cxx
 *
 * Description:
 * Unix-specific class for Socket operations
*/

#include <og/network/unix/SocketImplementation.hpp>
#include <og/network/Ipv4.hpp>
#include <og/base/SystemException.hpp>

#include <cstring>

namespace og {

namespace impl {

SocketHandle SocketHelper::bad_socket = -1;

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

sockaddr_in SocketHelper::fill_ipv4_sockaddr(const Ipv4& address, uint16_t port)
{
	sockaddr_in addr;

	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = address.to_int();
	return addr;
}

} // namespace impl

} // namespace og
