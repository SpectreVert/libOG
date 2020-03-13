/*
 * libOG, 2019
 *
 * Name: Socket.cxx
 *
 * Description:
 * 
*/

#include "og/network/Socket.hpp"
#include "og/network/SocketImplementation.hpp"
#include "og/base/SystemException.hpp"

using namespace og;

Socket::Socket(int t_domain, int t_type, int t_protocol, bool t_blocking) :
	IBaseSocket(t_domain, t_type, t_protocol),
	m_socket(impl::SocketHelper::bad_socket),
	m_blocking(t_blocking),
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


bool Socket::is_blocking() const
{
	return m_blocking;
}

void Socket::set_blocking(bool block)
{
	if (m_socket != impl::SocketHelper::bad_socket)
		impl::SocketHelper::set_blocking(m_socket, block);
	
	m_blocking = block;
}

Socket::Status Socket::bind(uint16_t port, const Ipv4& address)
{
	sockaddr_in addr = impl::SocketHelper::build_ipv4_sockaddr(address, port);

	// Reset the socket in case it was already bound
	close();
	open();

	if (::bind(handle(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1)
		return Error;
	
	return Success;
}

void Socket::unbind()
{
	close();
}

SocketHandle Socket::handle() const
{
	return m_socket;
}

void Socket::open()
{
	if (m_socket != impl::SocketHelper::bad_socket)
		return;
	
	SocketHandle new_socket = socket(m_domain, m_type, m_protocol);

	if (new_socket == impl::SocketHelper::bad_socket)
		throw SystemException("socket");
	
	// Assign the newly created socket as our own
	open(new_socket);
}

void Socket::open(SocketHandle t_socket)
{
	if (m_socket != impl::SocketHelper::bad_socket)
		return;

	// Take note of the new handle
	m_socket = t_socket;

	// Set the socket's blocking state
	impl::SocketHelper::set_blocking(m_socket, m_blocking);	
}

void Socket::close()
{
	if (m_socket != impl::SocketHelper::bad_socket) {
		impl::SocketHelper::close(m_socket);
		m_socket = impl::SocketHelper::bad_socket;
	}
}

Socket::Status Socket::get_error_status()
{
	switch (errno) {
		case EAGAIN:
		case EINPROGRESS:
		case EALREADY:
			return Socket::Status::Partial;
		case ECONNREFUSED:
		case ECONNRESET:
		case ETIMEDOUT:
			return Socket::Status::Disconnect;
		default:
			return Socket::Status::Error;
	}
}
