/*
 * Created by Costa Bushnaq
 *
 * 23-07-2021 @ 19:15:22
*/

#include "og/TcpListener.hpp"

using namespace og;

TcpListener::TcpListener()
	: Socket(AF_INET, SOCK_STREAM, 0)
{
}

TcpListener::TcpListener(Handle handle)
	: Socket(handle)
{
}

int TcpListener::listen(int backlog)
{
	return intl::listen(m_handle, backlog);
}

std::optional<TcpStream> TcpListener::try_accept()
{
	SocketAddr addr{SocketAddrV4{}};

	return try_accept(addr);
}

std::optional<TcpStream> TcpListener::try_accept(SocketAddr& addr)
{
	Handle accepted_handle = intl::accept(m_handle, addr);

	if (accepted_handle != k_bad_socket)
		return accepted_handle;

	return std::nullopt;
}
