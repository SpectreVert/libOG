/*
 * Created by Costa Bushnaq
 *
 * 28-04-2021 @ 22:10:15
*/

#include "og/Error.hpp"
#include "og/Socket.hpp"

using namespace og;

Socket::~Socket()
{
	(void) close();
}

Socket::Socket(int dom, int type, int prot)
{
	(void) mk_handle(dom, type, prot);
}

Socket::Socket(Handle handle)
	: m_handle(handle)
{	
}

Socket::Handle Socket::handle() const
{
	return m_handle;
}

int Socket::mk_handle(int dom, int type, int prot)
{
	m_handle = intl::open(dom, type, prot);
	
	if (m_handle != k_bad_socket)
		return e_success;

	return e_failure;
}

void Socket::set_handle(Handle handle)
{
	m_handle = handle;
}

int Socket::close()
{
	if (intl::close(m_handle) == -1)
		return e_failure;

	m_handle = k_bad_socket;

	return e_success;
}

int Socket::bind(SocketAddr const& addr)
{
	return intl::bind(m_handle, addr);
}
