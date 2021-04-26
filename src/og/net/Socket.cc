/*
 * libOG, 2020
 *
 * Name: Socket.cc
 *
*/

#include "og/net/Error.hpp"
#include "og/core/System.hpp"
#include "og/net/Socket.hpp"

using namespace og::net;

Socket::Socket(int domain, int type, int protocol)
	: m_socket(intl::bad_socket)
{
	open(domain, type, protocol);
}

Socket::Socket(SocketFd socket)
{
	m_socket = socket;
}

Socket::~Socket()
{
	close();
}

void Socket::handle(SocketFd socket)
{
	if (m_socket != intl::bad_socket)
		close();

	m_socket = socket;
}

int Socket::bind(const SocketAddr& address)
{
	int res = intl::bind(m_socket, address);

	if (res != -1)
		return og::net::Status::e_success;

	return -errno;
}

int Socket::open(int domain, int type, int protocol)
{
	if (m_socket != intl::bad_socket)
		close();
	
	m_socket = intl::open(domain, type, protocol);
	if (m_socket != intl::bad_socket)
		return og::net::Status::e_success;

	return -errno;
}

int Socket::close()
{
	return intl::close(m_socket);
}
