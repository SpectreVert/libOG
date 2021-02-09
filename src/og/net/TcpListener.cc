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

TcpListener::~TcpListener()
{
	close();
}

int TcpListener::listen(int backlog)
{
	int res = intl::listen(m_handle, backlog);

	if (res == -1)
		return -errno;

	return 0;
}

int TcpListener::accept(TcpStream& socket)
{
	return 0;
}
