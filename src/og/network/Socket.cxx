/*
 * libOG, 2019
 *
 * Name: Socket.cxx
 *
 * Description:
 * 
*/

#include <og/base/SystemException.hpp>
#include <og/network/Socket.hpp>
#include <og/network/SocketImplementation.hpp>

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

void Socket::setBlocking(bool blocking)
{
	if (m_socket != impl::SocketHelper::bad_socket)
		impl::SocketHelper::setBlocking(m_socket, blocking);
	
	m_blocking = true;
}

SocketHandle Socket::getHandle() const
{
	return m_socket;
}

void Socket::open()
{
	if (m_socket != impl::SocketHelper::bad_socket)
		return;
	
	SocketHandle t_socket = socket(m_domain, m_type, m_protocol);

	if (t_socket == impl::SocketHelper::bad_socket)
		throw SystemException("socket");
	
	// Assign the newly created socket as our own
	open(t_socket);
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