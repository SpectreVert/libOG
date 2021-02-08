/*
 * libOG, 2020
 *
 * Name: TcpStream.cxx
 *
*/

#include "og/core/Error.hpp"
#include "og/net/Internal.hpp"
#include "og/net/TcpStream.hpp"

using namespace og::net;

TcpStream::TcpStream() :
	Socket(AF_INET, SOCK_STREAM)
{
}

TcpStream::~TcpStream()
{
	close();
}

int TcpStream::connect(const SocketAddr& address)
{
	int res = intl::connect(m_handle, address);

	if (res == -1 && errno == EINPROGRESS)
		return og::net::InProgress;

	return -errno;
}

int TcpStream::send(core::RawBufferConst data)
{
	ssize_t res = intl::send(m_handle, data);

	if (res != -1)
		return og::net::Success;

	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return og::net::WouldBlock;

	return -errno;
}

int TcpStream::send(core::RawBufferConst data, std::size_t& sent)
{
	ssize_t res = intl::send(m_handle, data);

	if (res != -1)
	{
		sent = static_cast<std::size_t>(res);
		return og::net::Success;
	}
	
	sent = 0;
	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return og::net::WouldBlock;

	return -errno;
}

int TcpStream::recv(core::RawBuffer& data)
{
	ssize_t res = intl::recv(m_handle, data);

	/* I have quite a dilema going on here. The POSIX implementation of
	 * recv() is said to return 0 if the connection has been gracefully
	 * closed, more than zero if bytes were received and -1 for an error.
	 * Linux's man page says that recv() could return zero if the length
	 * argument for the buffer size is zero. Now BSD's man pages do NOT
	 * indicate anything similar. So we won't be testing for that case here.
	 * FIXME
	*/
	if (res > 0)
		return og::net::Success;

	if (res == 0)
		return og::net::Closed;

	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return og::net::WouldBlock;

	return -errno;
}

int TcpStream::recv(core::RawBuffer& data, size_t& received)
{
	ssize_t res = intl::recv(m_handle, data);

	if (res > 0)
	{
		received = static_cast<std::size_t>(res);
		return og::net::Success;
	}

	received = 0;
	if (res == 0)
		return og::net::Closed;

	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return og::net::WouldBlock;

	return -errno;
}
