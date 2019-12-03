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
	return Success;
}

} // namespace og
