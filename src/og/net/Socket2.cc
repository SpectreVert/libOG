/*
 * Created by Costa Bushnaq
 *
 * 28-04-2021 @ 22:10:15
*/

#include "og/net/Error.hpp"
#include "og/net/Socket2.hpp"

using namespace og::net;

Socket::Handle Socket::handle() const
{
	return m_handle;
}

void Socket::set_handle(Handle handle)
{
	m_handle = handle;
}

int Socket::make_handle(int dom, int type, int prot)
{
	return intl::open(dom, type, prot);
}

/* not calling close twice is left
 * to the discretion of the user. */
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
