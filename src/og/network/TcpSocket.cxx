/*
 * libOG, 2019
 *
 * Name: TcpSocket.cxx
 *
 * Description:
 * 
*/

#include <og/network/TcpSocket.hpp>

namespace og {


TcpSocket::TcpSocket() :
	Socket(TCP)
{
	
}

Socket::Status TcpSocket::connect(const Ipv4& address, uint16_t port)
{
	return Success;
}

void TcpSocket::disconnect()
{
	close();
}

} // namespace og
