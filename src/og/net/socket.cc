/*
 * libOG, 2020
 *
 * Name: socket.cc
 *
*/

#include "og/net/socket.hpp"
#include "og/net/socketimpl.hpp"

using namespace og;

Socket::Socket(int domain, int type, int protocol)
	: m_socket(impl::SocketHelper::bad_socket)
	, m_domain(domain)
	, m_type(type)
	, m_protocol(protocol)
{
}

Socket::~Socket()
{
	close();
}

int Socket::bind(const Ipv4& address, Ipv4::Port port)
{
	sockaddr_in addr = impl::SocketHelper::mk_ipv4_sockaddr(address, port);

	close(); open();

	if (::bind(m_socket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1)
		return Socket::Error;

	return Socket::Success;
}

int Socket::open()
{
	if (m_socket != impl::SocketHelper::bad_socket)
		return Socket::Success;

	SocketHandle sock = socket(m_domain, m_type | SOCK_NONBLOCK, m_protocol);

	return open(sock);
}

int Socket::open(SocketHandle sock)
{
	if (sock == impl::SocketHelper::bad_socket)
		return Socket::Error;

	m_socket = sock;

	return impl::SocketHelper::set_blocking(sock, true);
}

int Socket::close()
{
	return impl::SocketHelper::close(m_socket);
}
