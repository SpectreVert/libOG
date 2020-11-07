/*
 * libOG, 2020
 *
 * Name: Socket.cc
 *
*/

#include "og/net/Socket.hpp"
#include "og/io/Internal.hpp"

using namespace og::net;

Socket::Socket(int domain, int type, int protocol)
	: m_socket(io::intl::bad_socket)
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
	return io::intl::bind(m_socket, address);
}

// TODO: add open() to io::intl
// https://docs.rs/crate/mio/0.7.5/source/src/sys/unix/net.rs
int Socket::open()
{
	io::SocketHandle sock;

	if (m_socket != io::intl::bad_socket)
		return Socket::Success;

	sock = socket(m_domain, m_type, m_protocol);

	return open(sock);
}

int Socket::close()
{
	return io::intl::close(m_socket);
}
