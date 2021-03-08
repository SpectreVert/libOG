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

TcpStream::TcpStream(SocketFd socket) :
	Socket(socket)
{
}

TcpStream::~TcpStream()
{
	close();
}

int TcpStream::connect(const SocketAddr& address)
{
	int res = intl::connect(m_socket, address);

	if (res != -1)
		return og::net::Success;

	if (errno == EINPROGRESS)
		return og::net::InProgress;

	return -errno;
}

int TcpStream::send(core::RawBufferConst data)
{
	ssize_t res = intl::send(m_socket, data);

	if (res != -1)
		return og::net::Success;

	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return og::net::WouldBlock;

	return -errno;
}

int TcpStream::send(core::RawBufferConst data, std::size_t& sent)
{
	ssize_t res = intl::send(m_socket, data);

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
	/* Provided buffer and length should be bigger
	 * than zero.
	*/
	ssize_t res = intl::recv(m_socket, data);

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
	ssize_t res = intl::recv(m_socket, data);

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
