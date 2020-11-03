/*
 * libOG, 2020
 *
 * Name: SocketIO.cc
 *
*/

// TODO: change this to check if it is unix instead
#ifndef OG_SYSTEM_WINDOWS

// BTW: https://docs.rs/crate/mio/0.7.5/source/src/sys/unix/net.rs

#include "og/net/SocketIO.hpp"

#include <cstring>
#include <fcntl.h>
#include <unistd.h>

using namespace og::net::impl;

inline const sockaddr* SocketIO::get_sockaddr_ptr(const SocketAddr& address)
{
	if (address.version == SocketAddr::V4)
		return reinterpret_cast<const sockaddr*>(&address.addr.v4.socket_addr);

	return 0x0;
}

inline std::size_t SocketIO::get_sockaddr_size(int version)
{
	switch (version)
	{
		case SocketAddr::V4:
			return sizeof(sockaddr_in);
		case SocketAddr::V6:
			return sizeof(sockaddr_in6);
		default:
			return 0;
	}
}

int SocketIO::bind(SocketHandle socket, const SocketAddr& address)
{
	const sockaddr* addr_ptr = get_sockaddr_ptr(address);
	std::size_t addr_size = get_sockaddr_size(address.version);

	if (::bind(socket, addr_ptr, addr_size) == -1)
		return Socket::Error;

	return Socket::Success;
}

int SocketIO::connect(SocketHandle socket, const SocketAddr& address)
{
	const sockaddr* addr_ptr = get_sockaddr_ptr(address);
	std::size_t addr_size = get_sockaddr_size(address.version);

	if (::connect(socket, addr_ptr, addr_size) == -1)
	{
		if (errno == EINPROGRESS)
			return Socket::Connecting;

		return Socket::Error;
	}

	return Socket::Success;
}

int SocketIO::close(SocketHandle socket)
{
	if (socket == impl::SocketIO::bad_socket)
	{
		return Socket::Success;
	}
	else if (::close(socket) == -1)
	{
		return Socket::Error;
	}

	return Socket::Success;
}

int SocketIO::set_blocking(SocketHandle socket, bool block)
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

bool SocketIO::is_blocking(SocketHandle socket)
{
	int status = fcntl(socket, F_GETFL);

	if (status & O_NONBLOCK)
		return false;

	return true;
}

#endif // !OG_SYSTEM_WINDOWS
