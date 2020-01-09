/*
 * libOG, 2019
 *
 * Name: TcpSocket.cxx
 *
 * Description:
 * 
*/

#include <og/network/TcpSocket.hpp>
#include <og/network/SocketImplementation.hpp>
#include <errno.h>

namespace og {

static Socket::Status get_error_status()
{
	switch (errno) {
		case EAGAIN:
		case EINPROGRESS:
		case EALREADY:
			return Socket::Status::Again;
		case ECONNREFUSED:
		case ECONNRESET:
		case ETIMEDOUT:
			return Socket::Status::Disconnect;
		default:
			return Socket::Status::Error;
	}
}

static int get_send_flags()
{
	#ifdef _WIN_32
		return 0;
	#else
		return MSG_NOSIGNAL;
	#endif
}

TcpSocket::TcpSocket() :
	Socket(TCP)
{
	
}

Socket::Status TcpSocket::connect(const Ipv4& raddress, uint16_t rport)
{
	close();
	open();

	sockaddr_in addr = impl::SocketHelper::fill_ipv4_sockaddr(raddress, rport);

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

Socket::Status TcpSocket::send(const void* data, std::size_t len, std::size_t& sent)
{
	// We'll need to perform the send over a loop -- so that everything is sent correctly.
	ssize_t delivered = 0;
	
	if (!len || !data)
		return Error;

	do {
		delivered = ::send(handle(), static_cast<const char*>(data) + sent, 
		static_cast<size_t>(len - sent), get_send_flags());

		if (delivered < 0) {
			Status status = get_error_status();
			return status;
		}
	} while (sent < len);
	
	return Success;
}

Socket::Status TcpSocket::receive(void* data, std::size_t len, std::size_t& received)
{
	return Success;
}

} // namespace og
