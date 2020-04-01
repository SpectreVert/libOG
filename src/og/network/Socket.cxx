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

Socket::Socket(int t_domain, int t_type, int t_protocol) :
	IBaseSocket(t_domain, t_type, t_protocol),
	m_socket(impl::SocketHelper::bad_socket),
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

Socket::Status Socket::bind(Port port, const Ipv4& address)
{
	sockaddr_in addr = impl::SocketHelper::build_ipv4_sockaddr(address, port);

	// Reset the socket in case it was already bound
	close();
	open();

	if (::bind(handle(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1)
		return Socket::Status::Error;
	
	return Socket::Status::Success;
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
	// Return immediately if the socket is already open & good
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
	// Return immediately if the socket is already open & good
	if (m_socket != impl::SocketHelper::bad_socket)
		return;

	// Take note of the new handle
	m_socket = t_socket;

	// Set the socket as non-blocking if it wasn't previously done
	impl::SocketHelper::set_non_blocking(m_socket);
}

void Socket::close()
{
	if (m_socket != impl::SocketHelper::bad_socket)
	{
		impl::SocketHelper::close(m_socket);
		m_socket = impl::SocketHelper::bad_socket;
	}
}