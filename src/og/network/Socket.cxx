/*
 * libOG, 2019
 *
 * Name: Socket.cxx
 *
 * Description:
 * 
*/

#include "og/base/SystemException.hpp"
#include "og/network/Socket.hpp"
#include "og/network/SocketImplementation.hpp"

using namespace og;

Socket::Socket(int t_domain, int t_type, int t_protocol) :
	IBaseSocket(t_domain, t_type, t_protocol),
	m_socket(impl::SocketHelper::bad_socket),
	m_blocking(true),
	m_domain(t_domain),
	m_type(t_type),
	m_protocol(t_protocol)
{

}

Socket::~Socket()
{
	/* RAII */
	close();
}

bool Socket::isBlocking() const
{
	return m_blocking;
}

void Socket::setBlocking(bool block)
{
	if (m_socket != impl::SocketHelper::bad_socket)
		impl::SocketHelper::setBlocking(m_socket, block);
	
	m_blocking = block;
}

Socket::Status Socket::bind(uint16_t port, const Ipv4& address)
{
	sockaddr_in addr = impl::SocketHelper::buildIpv4Sockaddr(address, port);

	close(); // Reset the socket in case it was already bound
	open();

	if (::bind(getHandle(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1)
		return Error;
	
	return Success;
}

void Socket::unbind()
{
	close();
}

SocketHandle Socket::getHandle() const
{
	return m_socket;
}

void Socket::open()
{
	if (m_socket != impl::SocketHelper::bad_socket)
		return;
	
	SocketHandle newSocket = socket(m_domain, m_type, m_protocol);

	if (newSocket == impl::SocketHelper::bad_socket)
		throw SystemException("socket");
	
	// Assign the newly created socket as our own
	open(newSocket);
}

void Socket::open(SocketHandle t_socket)
{
	if (m_socket != impl::SocketHelper::bad_socket)
		return;

	// Take note of the new handle
	m_socket = t_socket;

	// Set its blocking status to the current blocking status
	setBlocking(m_blocking);
}

void Socket::close()
{
	if (m_socket != impl::SocketHelper::bad_socket) {
		impl::SocketHelper::close(m_socket);
		m_socket = impl::SocketHelper::bad_socket;
	}
}

Socket::Status Socket::getErrorStatus()
{
	switch (errno) {
		case EAGAIN:
		case EINPROGRESS:
		case EALREADY:
			return Socket::Status::Again;
		case ECONNREFUSED:
		case ECONNRESET:
		case ETIMEDOUT:
			return Socket::Status::Disconnect;
		default:
			return Socket::Status::Error;
	}
}