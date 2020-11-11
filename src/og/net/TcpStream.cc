/*
 * libOG, 2020
 *
 * Name: TcpStream.cxx
 *
*/

#include "og/net/TcpStream.hpp"
#include "og/io/Internal.hpp"

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
	return io::intl::connect(m_handle, address);
}

int TcpStream::send(const void* data, std::size_t len)
{
	ssize_t sent;

	return send(data, len, sent);
}

int TcpStream::send(const void* data, std::size_t len, ssize_t& sent)
{

}

int TcpStream::receive(void* data, std::size_t len)
{
	ssize_t received = 0;

	return receive(data, len, received);
}

int TcpStream::receive(void* data, std::size_t len, ssize_t& received)
{
	received = ::recv(
		m_handle,
		data,
		len,
		io::intl::MSG_FLAG
	);

	if (received < 0)
	{
		received = 0;

		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return Socket::Retry;

		return Socket::Error;
	}

	return Socket::Success;
}
