/*
 * libOG, 2020
 *
 * Name: TcpStream.cxx
 *
*/

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
		return 0;

	return -errno;
}

int TcpStream::send(core::RawBufferConst data)
{
	ssize_t res = intl::send(m_handle, data);

	if (res != -1)
		return 0;

	/* We could get a case of EAGAIN or EWOULDBLOCK here - but
	 * normally we should be using a selector so as to get these
	 * errors less.
	*/

	return -errno; 
}

int TcpStream::send(core::RawBufferConst data, std::size_t& sent)
{
	ssize_t res = intl::send(m_handle, data);

	if (res != -1)
	{
		sent = static_cast<std::size_t>(res);
		return 0;
	}
	
	sent = 0;
	return -errno;
}

int TcpStream::recv(core::RawBuffer& data)
{
	ssize_t res = intl::recv(m_handle, data);

	// if(res) == 0 -> orderly disconnect for stream socket.
	if (res >= 0)
		return 0;
	
	return -errno;
}

int TcpStream::recv(core::RawBuffer& data, size_t& received)
{
	ssize_t res = intl::recv(m_handle, data);

	if (res > 0)
	{
		received = static_cast<std::size_t>(res);
		return 0;
	}

	received = 0;
	return -errno;
}
