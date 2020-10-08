/*
 * libOG, 2020
 *
 * Name: SocketHelper.cc
 *
*/

#include "og/net/unix/SocketHelper.hpp"

#include <cstring>
#include <fcntl.h>
#include <unistd.h>

namespace og {

namespace impl {

SocketHandle SocketHelper::bad_socket = -1;

int SocketHelper::bind(SocketHandle socket, const SocketAddr& address)
{
	const sockaddr* addr_ptr = reinterpret_cast<const sockaddr*>(&address.addr);
	std::size_t addr_size = 0;

	if (address.version == SocketAddr::V4)
		addr_size = sizeof(sockaddr_in);
	else
		addr_size = sizeof(sockaddr_in6);

	if (::bind(socket, addr_ptr, addr_size) == -1)
		return Socket::Error;

	return Socket::Success;
}

int SocketHelper::close(SocketHandle socket)
{
	if (::close(socket) == -1)
		return Socket::Error;

	return Socket::Success;
}

int SocketHelper::set_blocking(SocketHandle socket, bool block)
{
	int status = fcntl(socket, F_GETFL);

	if (block)
	{
		if (fcntl(socket, F_SETFL, status & ~O_NONBLOCK) == -1)
			return Socket::Error;
	}
	else
	{
		if (fcntl(socket, F_SETFL, status | O_NONBLOCK) == -1)
			return Socket::Error;
	}

	return Socket::Success;
}

bool is_blocking(SocketHandle socket)
{
	int status = fcntl(socket, F_GETFL);

	if (status & O_NONBLOCK)
		return false;

	return true;
}

} // namespace impl

} // namespace og
