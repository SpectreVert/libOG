/*
 * libOG, 2020
 *
 * Name: TcpStream.cxx
 *
*/

#include "og/net/Internal.hpp"
#include "og/net/TcpStream.hpp"

#include <assert.h>

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
		return Success;

	return res;
}

int TcpStream::send(core::RawBufferConst data)
{
	ssize_t res = intl::send(m_handle, data);

	if (res != -1)
		return Success;

	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return WouldBlock;

	return Error;
}

int TcpStream::send(core::RawBufferConst data, std::size_t& sent)
{
	ssize_t res = intl::send(m_handle, data);

	if (res != -1)
	{
		sent = static_cast<std::size_t>(res);
		return Success;
	}
	
	sent = 0;
	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return WouldBlock;

	return Error;
}

int TcpStream::recv(core::RawBuffer& data)
{
	ssize_t res = intl::recv(m_handle, data);

	if (res > 0)
		return Success;

	if (res == 0)
		return Closed;
	
	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return WouldBlock;

	return Error;
}

int TcpStream::recv(core::RawBuffer& data, size_t& received)
{
	ssize_t res = intl::recv(m_handle, data);

	if (res > 0)
	{
		received = static_cast<std::size_t>(res);
		return og::Success;
	}

	received = 0;
	if (res == 0)
		return Closed;
	
	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return WouldBlock;

	return Error;
}
