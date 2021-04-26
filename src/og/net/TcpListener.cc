/*
 * Created by Costa Bushnaq
 *
 * 05-02-2021 @ 17:10:56
*/

#include "og/net/Error.hpp"
#include "og/net/Internal.hpp"
#include "og/net/TcpListener.hpp"

using namespace og::net;

TcpListener::TcpListener() :
	Socket(AF_INET, SOCK_STREAM)
{
}

TcpListener::TcpListener(SocketFd socket) :
	Socket(socket)
{
}

int TcpListener::listen(int backlog)
{
	int res = intl::listen(m_socket, backlog);

	if (res == -1)
		return -errno;

	return og::net::Status::e_success;
}

int TcpListener::accept(TcpStream& new_stream, int flags)
{
	SocketAddr tmp_address(0, 0);

	return this->accept(new_stream, tmp_address, flags);
}

/* BUG: a new socket is created in accept, but it is
 * closed right here before being assigned a new handle.
*/
int TcpListener::accept(TcpStream& new_stream, SocketAddr& new_address,
                        int flags)
{
	SocketFd new_socket;
	int res = intl::accept(m_socket, new_socket, new_address, flags);

	new_stream.handle(new_socket);
	if (res != -1)
		return og::net::Status::e_success;

	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return og::net::Status::e_would_block;

	return -errno;
}
