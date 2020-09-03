/*
 * libOG, 2020
 *
 * Name: socketimpl.cc
 *
*/

#include "og/net/unix/socketimpl.hpp"

#include <cstring>
#include <fcntl.h>
#include <unistd.h>

namespace og {

namespace impl {

SocketHandle SocketHelper::bad_socket = -1;

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

sockaddr_in mk_ipv4_sockaddr(const Ipv4& address, Ipv4::Port port)
{
	sockaddr_in addr;

	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = PF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = address.to_decimal();
	
	return addr;
}

} // namespace impl

} // namespace og
