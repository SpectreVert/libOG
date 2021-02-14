/*
 * Created by Costa Bushnaq
 *
 * 05-02-2021 @ 17:10:56
*/

#include "og/core/Error.hpp"
#include "og/net/Internal.hpp"
#include "og/net/TcpListener.hpp"

using namespace og::net;

TcpListener::TcpListener() :
	Socket(AF_INET, SOCK_STREAM)
{
}

TcpListener::TcpListener(SocketHandle handle) :
	Socket(handle)
{
}

TcpListener::~TcpListener()
{
	close();
}

int TcpListener::listen(int backlog)
{
	int res = intl::listen(m_handle, backlog);

	if (res == -1)
		return -errno;

	return og::net::Success;
}

int TcpListener::accept(TcpStream& new_stream, int flags)
{
	SocketAddr tmp_address(0, 0);

	return this->accept(new_stream, tmp_address, flags);
}

int TcpListener::accept(TcpStream& new_stream, SocketAddr& new_address,
                        int flags)
{
	SocketHandle new_handle;
	int res = intl::accept(m_handle, new_handle, new_address, flags);

	new_stream.handle(new_handle);
	if (res != -1)
		return og::net::Success;

	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return og::net::WouldBlock;

	return -errno;
}
