/*
 * libOG, 2020
 *
 * Name: Socket.cc
 *
*/

#include "og/core/Error.hpp"
#include "og/core/System.hpp"
#include "og/net/Socket.hpp"

using namespace og::net;

Socket::Socket(int domain, int type, int protocol)
	: m_handle(intl::bad_socket)
{
	open(domain, type, protocol);
}

Socket::Socket(SocketHandle handle)
{
	m_handle = handle;
}

Socket::~Socket()
{
	close();
}

void Socket::handle(SocketHandle handle)
{
	if (m_handle != intl::bad_socket)
		close();

	m_handle = handle;
}

int Socket::bind(const SocketAddr& address)
{
	int res = intl::bind(m_handle, address);

	if (res != -1)
		return og::net::Success;

	return -errno;
}

// https://docs.rs/crate/mio/0.7.5/source/src/sys/unix/net.rs
int Socket::open(int domain, int type, int protocol)
{
	if (m_handle != intl::bad_socket)
		close();
	
	m_handle = intl::open(domain, type, protocol);
	if (m_handle != intl::bad_socket)
		return og::net::Success;

	return -errno;
}

int Socket::close()
{
	return intl::close(m_handle);
}
