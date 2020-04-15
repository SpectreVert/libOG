/*
 * libOG, 2020
 *
 * Name: SocketImplementation.cxx
 *
*/

#include "og/network/unix/SocketImplementation.hpp"
#include "og/network/Ipv4.hpp"
#include "og/base/SystemException.hpp"

#include <cstring>

namespace og {

namespace impl {

SocketHandle SocketHelper::bad_socket = -1;

void SocketHelper::set_non_blocking(SocketHandle socket)
{
	int socket_status = fcntl(socket, F_GETFL);

	// Socket is blocking
	if (socket_status & O_NONBLOCK)
	{
		if (fcntl(socket, socket_status | O_NONBLOCK) == -1)
			throw SystemException("fcntl");
	}
}

void SocketHelper::close(SocketHandle socket)
{
	if (::close(socket) == -1)
		throw SystemException("close");
}

sockaddr_in SocketHelper::build_ipv4_sockaddr(const Ipv4& address, uint16_t port)
{
	sockaddr_in addr;

	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = address.toInt();
	return addr;
}

} // namespace impl

} // namespace og
