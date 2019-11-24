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

Socket::Socket(Type t_type) :
	m_socket(impl::SocketHelper::bad_socket()),
	m_blocking(true),
	m_type(t_type)
{

}

Socket::~Socket()
{
	/* RAII */
	close();
}

bool Socket::blocking() const
{
	return m_blocking;
}

void Socket::blocking(bool blocking)
{
	if (m_socket != impl::SocketHelper::bad_socket())
		impl::SocketHelper::blocking(m_socket, blocking);
	m_blocking = true;
}

void Socket::open()
{
	if (m_socket != impl::SocketHelper::bad_socket())
		return;
	
	SocketHandle t_socket = socket(PF_INET, m_type == UDP ? SOCK_DGRAM : SOCK_STREAM, 0);
	if (t_socket == impl::SocketHelper::bad_socket())
		throw SystemException("socket");
	open(t_socket);
}

void Socket::open(SocketHandle t_socket)
{
	if (m_socket != impl::SocketHelper::bad_socket())
		return;
	/* Take note of the new handle */
	m_socket = t_socket;
	/* Set its blocking status to the current blocking status */
	blocking(true);
}

void Socket::close()
{
	if (m_socket != impl::SocketHelper::bad_socket()) {
		impl::SocketHelper::close(m_socket);
		m_socket = impl::SocketHelper::bad_socket();
	}
}
