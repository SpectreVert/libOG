/*
 * libOG, 2019
 *
 * Name: TcpSocket.cxx
 *
 * Description:
 * 
*/

#include "og/network/TcpSocket.hpp"
#include "og/network/SocketImplementation.hpp"

#include <errno.h>

namespace og {

static int get_flags()
{
#ifdef _WIN_32
	return 0;
#else
	return MSG_NOSIGNAL;
#endif
}

TcpSocket::TcpSocket() :
	Socket(PF_INET, SOCK_STREAM, 0)
{
	
}

Socket::Status TcpSocket::connect(const Ipv4& raddress, uint16_t rport)
{
	close();
	open();

	sockaddr_in addr = impl::SocketHelper::build_ipv4_sockaddr(raddress, rport);

	if (::connect(handle(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1)
		return get_error_status();

	return Success;
}

void TcpSocket::disconnect()
{
	close();
}

Socket::Status TcpSocket::send(const void* data, std::size_t len)
{
	std::size_t sent;

	return send(data, len, sent);
}

Socket::Status TcpSocket::send(const void* data, std::size_t len, ssize_t& sent)
{
	// We'll need to perform the send over a loop -- so that everything is sent correctly.
	ssize_t delivered = 0;

	for (sent = 0; sent < len; sent += delivered) {
		delivered = ::send(handle(), static_cast<const char*>(data) + sent, 
		static_cast<size_t>(len - sent), get_flags());

		if (delivered < 0)
			return get_error_status();
	
	}
	
	return Success;
}

Socket::Status TcpSocket::receive(void* data, std::size_t len)
{
	size_t received = 0;

	return receive(data, len, received);
}

Socket::Status TcpSocket::receive(void* data, std::size_t len, std::size_t& received)
{
	int bytesReceived = recv(handle(), data, len, get_flags());
	received = 0;

	if (bytesReceived > 0) {
		received = static_cast<std::size_t>(bytesReceived);
		return Success;
	}

	return get_error_status();
}

} // namespace og
