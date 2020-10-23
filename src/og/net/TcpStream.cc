/*
 * libOG, 2020
 *
 * Name: TcpStream.cxx
 *
*/

#include "og/net/TcpStream.hpp"
#include "og/net/SocketIO.hpp"

using namespace og;

TcpStream::TcpStream() :
	Socket(PF_INET, SOCK_STREAM)
{
}

int TcpStream::connect(const SocketAddr& address)
{
	close(); open();

	return impl::SocketIO::connect(m_socket, address);
}

void TcpStream::disconnect()
{
	close();
}

int TcpStream::send(const void* data, std::size_t len)
{
	ssize_t sent;

	return send(data, len, sent);
}

int TcpStream::send(const void* data, std::size_t len, ssize_t& sent)
{
	ssize_t delivered = 0;

	for (sent = 0; static_cast<size_t>(sent) < len; sent += delivered)
	{
		delivered = ::send(
			m_socket,
			static_cast<const char*>(data) + sent,
			static_cast<std::size_t>(len - sent),
			impl::SocketIO::MSG_FLAG
		);

		if (delivered < 0)
		{
			// We already sent data but the socket can't send more for now
			if ((errno == EAGAIN || errno == EWOULDBLOCK) && sent)
			{
				return Socket::PartialSend;
			}
			else if (!sent) // No data was sent ; the socket is not available
			{
				return Socket::Retry;
			}

			return Socket::Error;
		}
	}

	return Socket::Success;
}

int TcpStream::receive(void* data, std::size_t len)
{
	ssize_t received = 0;

	return receive(data, len, received);
}

int TcpStream::receive(void* data, std::size_t len, ssize_t& received)
{
	received = ::recv(
		m_socket,
		data,
		len,
		impl::SocketIO::MSG_FLAG
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
