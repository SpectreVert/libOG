/*
 * libOG, 2020
 *
 * Name: Socket.cc
 *
*/

#include "og/net/Socket.hpp"
#include "og/net/SocketIO.hpp"

using namespace og;

Socket::Socket(int domain, int type, int protocol)
	: m_socket(impl::SocketIO::bad_socket)
	, m_domain(domain)
	, m_type(type)
	, m_protocol(protocol)
{
}

Socket::~Socket()
{
	close();
}

int Socket::bind(const SocketAddr& address)
{
	close(); open();

	return impl::SocketIO::bind(m_socket, address);
}

int Socket::open()
{
	if (m_socket != impl::SocketIO::bad_socket)
		return Socket::Success;

	SocketHandle sock = socket(m_domain, m_type | SOCK_NONBLOCK, m_protocol);

	return open(sock);
}

int Socket::open(SocketHandle model)
{
	if (model == impl::SocketIO::bad_socket)
		return Socket::Error;

	m_socket = model;

	return impl::SocketIO::set_blocking(m_socket, false);
}

int Socket::close()
{
	return impl::SocketIO::close(m_socket);
}
